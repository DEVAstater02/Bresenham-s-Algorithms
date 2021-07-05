#include <stdio.h>
#include <math.h>
#include <glut.h>

#define MAX_COORDINATE 250

int Xc, Yc, r;
int X1, X2, Y1, Y2;

void myInit();
void plotPixel(int x, int y, int Xc, int Yc);
void midpointCircle(int Xc, int Yc, int r);
void vectorCircle(int X1, int Y1);
void printDisplay();

/// <summary>
/// main function contains all the necessary glut library initialisation funtions
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char **argv) {
	//glutInit is used to initialise GLUT library
	glutInit(&argc, argv);
	//glutInitDisplayMode is important to mention the mode of the display
	//GLUT_SINGLE mentions single buffer setting 
	//GLUT_RGB represents RGB color mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//Size of the window is set by glutInitWindowSize
	glutInitWindowSize(800, 600);
	//glutInitWindowPostion specifies the position of the window
	glutInitWindowPosition(0, 0);
	//glutCreateWindow creates a window with the argument provided as the window name
	glutCreateWindow("Circle Vector field");

	myInit();
	glutDisplayFunc(printDisplay);
	glutMainLoop();

	return 0;
}

/// <summary>
/// init function calls a few other functions which initialises the glut library and clears the color buffer
/// </summary>
void myInit() {
	//clears the color buffer bit so that there aren't any traces of the previous state
	glClear(GL_COLOR_BUFFER_BIT);
	//clears the R, G, B and alpha values
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//this specifies which matrix is being targetted, and the argument gives the matrix
	glMatrixMode(GL_PROJECTION);
	//defines a 2D orthographic projecion matrix sets up a 2D orthographic viewing region. Its parameters are used to clip the plane.
	gluOrtho2D(-400, 400, -300, 300);
}

/// <summary>
/// This function plots the actual pixel on our display.
/// </summary>
/// <param name="x">x coordinate to be plotted</param>
/// <param name="y">y coordinate to be plotted</param>
/// <param name="Xc">Xc is the x coordinate of the center of the circle</param>
/// <param name="Yc">Yc is the y coordinate of the center of the circle</param>
void plotPixel(int x, int y, int Xc, int Yc) {
	//glBegin specifies the way in which the vertices are to be interpreted, its argument gives the value
	//GL_POINTS treats each vertex as a single point
	//glVertex is used to check specifie a vertex

	glBegin(GL_POINTS);
	//we assume that the circle is at the origin which simplifies the calculations
	//after calculating the circle points , we transform each and every point to its original location.
	glVertex2i(x + Xc, y + Yc);
	glEnd();
}

/// <summary>
/// Funtion contains the bresenham's midpoint circle drawing algorithm which makes use of 8 way symmetry to plot the circle
/// onto the viewport.
/// </summary>
/// <param name="Xc">X coordinate of the center of the circle</param>
/// <param name="Yc">Y coordinate of the center of the circle</param>
/// <param name="r">r is the radius the circle</param>
void midpointCircle(int Xc, int Yc, int r) {
	//we choose to start from the top most point of the circle
	int x = 0;
	int y = r;
	int d = 1 - r;
	plotPixel(x, y, Xc, Yc);

	//the below loop will run only till the point (r/2, r/2)
	//using the 8 way symmetry we can plot 8 symmetric points on the circle 
	while (y > x) {
		if (d < 0) {
			d += 2 * x + 3;
		}
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		plotPixel(x, y, Xc, Yc);
		plotPixel(x, -y, Xc, Yc);
		plotPixel(-x, y, Xc, Yc);
		plotPixel(-x, -y, Xc, Yc);
		plotPixel(y, x, Xc, Yc);
		plotPixel(y, -x, Xc, Yc);
		plotPixel(-y, x, Xc, Yc);
		plotPixel(-y, -x, Xc, Yc);
	}
}

/// <summary>
/// VectorCircle computes the length of the vector and plots the circle with diameter equal to the length of the vector.
/// (X2, Y2) is the head of the vector.
/// We dont reduce the length to 40% like we did in part A,
/// as we want a circle with its radius equal to half the length of the field vector at any point.
/// After computing the length of the vector midpointCircle is called to plot triangles.
/// </summary>
/// <param name="X1"></param>
/// <param name="Y1"></param>
void vectorCircle(int X1, int Y1) {
	int x = X1;
	int y = Y1;

	//(X2, Y2) is the head of the vector
	X2 = X1 + y;
	Y2 = Y1 - x;

	int dx = X2 - X1;
	//squaring of x length
	dx *= dx;
	int dy = Y2 - Y1;
	//squaring of y length
	dy *= dy;

	int t = dx + dy;
	r = sqrt(t)/2;
	midpointCircle(X1 - r, Y1, r);
}

/// <summary>
/// Display function to plot the points which will be able to show the circles distinctively
/// </summary>
void printDisplay() {
	for (int i = 1; i < MAX_COORDINATE; i++) {
		if (i % 40 == 0) {
			vectorCircle(i, 0);
			vectorCircle(0, i);
			vectorCircle(-i, 0);
			vectorCircle(0, -i);
		}
		if (i % 33 == 0) {
			vectorCircle(i, i);
			vectorCircle(i, -i);
			vectorCircle(-i, i);
			vectorCircle(-i, -i);
		}
	}

	glFlush();
}
