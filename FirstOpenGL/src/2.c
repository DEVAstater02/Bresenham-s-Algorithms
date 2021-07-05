#include <stdio.h>
#include <glut.h>

int	Xc, Yc, r;

void myInit();
void plotPixel(int x, int y);
void midpointCircle();
void printDisplay();

/// <summary>
/// main function contains all the necessary glut library initialisation funtions
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char **argv) {
	printf("Enter the x coordinate of the center: ");
	scanf_s("%d", &Xc);

	printf("Enter the y coordinate of the center: ");
	scanf_s("%d", &Yc);

	printf("Enter the radius of the circle: ");
	scanf_s("%d", &r);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Midpoint Circle Algorithm");
	glutDisplayFunc(printDisplay);
	myInit();
	glutMainLoop();

	return 0;
}

/// <summary>
/// init function calls a few other functions which initialises the glut library and clears the color buffer
/// </summary>
void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);//clears the color buffer, equivalent to erasing the black boarding before writing.
	glClearColor(0.0, 0.0, 0.0, 1.0);//clears the color buffer.
	glMatrixMode(GL_PROJECTION);//specifies which matrix stack is targetted, in this case it is the projection matrix stack.
	gluOrtho2D(-320, 320, -240, 240);//defines a 2D orthographic projecion matrix sets up a 2D orthographic viewing region. Its parameters are used to clip the plane.
}

/// <summary>
/// This function plots the actual pixel on our display.
/// </summary>
/// <param name="x">x coordinate to be plotted</param>
/// <param name="y">y coordinate to be plotted</param>
void plotPixel(int x, int y) {
	/// <summary>
	/// glBegin tells the compiler the way in which the points are to be interpretted
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	glBegin(GL_POINTS);
	/// <summary>
	/// glVertex2i plots the integer coordinates given to it
	/// </summary>
	/// <param name="x">x + Xc because we translate the coordinates to the center of the circle from origin</param>
	/// <param name="y">y+ Yc because we translate the coordinates to the center of the circle from origin</param>
	glVertex2i(x + Xc,y + Yc);
	glEnd();
}

/// <summary>
/// This function computes the points on the circle and using 8 way symmetry, completes the entire circle.
/// </summary>
void midpointCircle() {
	//we choose to start from the top most point of the circle
	int x = 0;
	int y = r;
	int d = 1 - r;
	plotPixel(x, y);

	//the below loop will run only till (r/2, r/2)
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
		plotPixel(x, y);
		plotPixel(x, -y);
		plotPixel(-x, y);
		plotPixel(-x, -y);
		plotPixel(y, x);
		plotPixel(y,-x);
		plotPixel(-y,x);
		plotPixel(-y,-x);
	}
}

/// <summary>
/// Display function which calls the midpointCircle funtion to plot the circle
/// </summary>
void printDisplay() {
	midpointCircle();
	glFlush();//force executes GL commands until this func is called
}