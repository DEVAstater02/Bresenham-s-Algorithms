#include <stdio.h>
#include <glut.h>
#define MAX_COORDINATE 400

int X1, Y1, X2, Y2;

void myInit();
void myDisplay();
void plotPixel(int x, int y);
void printLine(int X1, int Y1, int X2, int Y2);
void vector(int X1, int Y1);
void arrowHead1(int X2, int Y2, int X1, int Y1);
void arrowHead2(int X2, int Y2, int X1, int Y1);

/// <summary>
/// main function contains all the necessary glut library initialisation funtions
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char** argv) {
	printf("Enter the starting coordinate of the polyline (X1, Y1): ");
	scanf_s("%d%d", &X1, &Y1);

	//glutInit is used to initialise GLUT library
	glutInit(&argc, argv);
	//glutInitDisplayMode is important to mention the mode of the display
	//GLUT_SINGLE mentions single buffer setting 
	//GLUT_RGB represents RGB color mode
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	//Size of the window is set by glutInitWindowSize
	glutInitWindowSize(800, 800);
	//glutInitWindowPostion specifies the position of the window
	glutInitWindowPosition(0,0);
	//glutCreateWindow creates a window with the argument provided as the window name
	glutCreateWindow("Poly Line");

	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}

/// <summary>
/// init function calls a few other functions which initialises the glut library and clears the color buffer
/// </summary>
void myInit() {
	//glClear clears the color buffer bit 
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor clears the RGB values which essentially clears the color.
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glMatrixMode sets the type of matrix/stack is to be used with the use of argument
	//GL_PROJECTION tells the function which matrix is to be used
	glMatrixMode(GL_PROJECTION);
	//gluOrtho2D defines a 2D projection matrix and sets a 2D viewing plane. Its arguments are used for clipping the viewing region to a set of coordinates
	gluOrtho2D(-400, 400, -400, 400);
}

/// <summary>
/// This function plots the actual pixel on our display.
/// </summary>
/// <param name="x">x coordinate to be plotted</param>
/// <param name="y">y coordinate to be plotted</param>
void plotPixel(int x, int y) {
	//glBegin tells the compiler the way in which the set of points are to be interpreted
	//GL_POINTS is the argument that is to be passed into glBegin
	glBegin(GL_POINTS);
	//glVertex2i just plots the vertex with integer coordinates
	glVertex2i(x,y);
	glEnd();
}

/// <summary>
/// This function contains the bresenham's algorithm which is used to draw the vector body.
/// </summary>
/// <param name="X1">X1 is the x coordinate at which we need to find the field direction</param>
/// <param name="Y1">Y1 is the y coordinate at which we need to find the field direction</param>
/// <param name="X2">X2 is the x coordinate at which we need to find the field direction</param>
/// <param name="Y2">Y2 is the y coordinate at which we need to find the field direction</param>
void printLine(int X1, int Y1, int X2, int Y2) {
	int x = X1, y = Y1;
	int dx, dy;
	dx = X2 - X1;
	dy = Y2 - Y1;

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	int incX = 1, incY = 1;
	int incE, incNE;
	int d;

	if (X1 > X2)
		incX = -1;
	if (Y1 > Y2)
		incY = -1;

	if (dx > dy) {
		plotPixel(x, y);
		d = 2 * dy - dx;
		incE = 2 * dy;
		incNE = 2 * (dy - dx);

		for (int i = 0; i < dx; i++) {
			if (d < 0) {
				d += incE;
			}
			else {
				d += incNE;
				y += incY;
			}
			x += incX;
			plotPixel(x, y);
		}

	}
	else {
		plotPixel(x, y);
		d = 2 * dx - dy;
		incE = 2 * dx;
		incNE = 2 * (dx - dy);

		for (int i = 0; i < dy; i++) {
			if (d < 0) {
				d += incE;
			}
			else {
				x += incX;
				d += incNE;
			}
			y += incY;
			plotPixel(x, y);
		}
	}
}

/// <summary>
/// Display function which calls the vector funtion to plot the polyline
/// </summary>
void myDisplay() {
	vector(X1, Y1);
	//glFlush is used to make sure that all other programs are compiled and executed and don't interupt the display function
	glFlush();
}

/// <summary>
/// vector function is used to compute the coordinates head of the vector given the tail coordinates
/// And also draws the vector after computing the coordinates of the head.
/// The vector field that I used is F(x, y) = (y, -x)
/// The vector would have been drawn till (y ,-x) if (X1, Y1) was the origin but it isn't
/// hence we transform the coordinates by adding (X1, Y1) to (x, y).
/// We don't clip the vector to 40% of its length like we did in part A because we need a polyline
/// and polylines are continuous.
/// </summary>
/// <param name="X1">x coordinate of the base of the vector</param>
/// <param name="Y1">y coordinate of the base of the vector</param>
void vector(int X1, int Y1) {
	int x = X1, y = Y1;
	X2 = X1 + y;
	Y2 = Y1 - x;
	//plots the line segment of the vector
	printLine(X1, Y1, X2, Y2);
	arrowHead1(X2, Y2, X1, Y1);
	arrowHead2(X2, Y2, X1, Y1);

	//The if condition ensures that the recursive call stops if the next coordinate is out of the viewport coordinates
	//we recursively keep calling the vector function till the point goes out of the window
	if (X2 > -MAX_COORDINATE && Y2 > -MAX_COORDINATE && X2 < MAX_COORDINATE && Y2 < MAX_COORDINATE) {
		vector(X2, Y2);
	}
}

/// <summary>
/// This function is used to produce arrow lines of the arrow head. 
/// What is basically does is that it rotates the line about point (X2, Y2) about 45 degrees anticlockwise
/// and plots those two lines using bresenham's line drawing algorithm
/// </summary>
/// <param name="X2">x coordinate of the head of a vector</param>
/// <param name="Y2">y coordinate of the head of a vector</param>
/// <param name="X1">x coordinate of the base of a vector</param>
/// <param name="Y1">y coordinate of the base of a vector</param>
void arrowHead1(int X2, int Y2, int X1, int Y1) {
	int a = X2;
	int b = Y2;
	int c = X1;
	int d = Y1;

	a -= X2;
	b -= Y2;
	c -= X2;
	d -= Y2;

	c = 0.2 * c;
	d = 0.2 * d;

	float cosTheta = 0.707;
	float sinTheta = 0.707;

	c = c * cosTheta - d * sinTheta;
	d = c * sinTheta + d * cosTheta;

	c += X2;
	d += Y2;

	printLine(c, d, X2, Y2);
}

/// <summary>
/// This function is used to produce arrow lines of the arrow head.
/// What is basically does is that it rotates the line about point (X2, Y2) about 45 degrees clockwise
/// and plots those two lines using bresenham's line drawing algorithm
/// </summary>
/// <param name="X2">x coordinate of the head of a vector</param>
/// <param name="Y2">y coordinate of the head of a vector</param>
/// <param name="X1">x coordinate of the base of a vector</param>
/// <param name="Y1">y coordinate of the base of a vector</param>
void arrowHead2(int X2, int Y2, int X1, int Y1) {
	int a = X2;
	int b = Y2;
	int c = X1;
	int d = Y1;

	a -= X2;
	b -= Y2;
	c -= X2;
	d -= Y2;

	c = 0.2 * c;
	d = 0.2 * d;

	float cosTheta = 0.707;
	float sinTheta = 0.707;

	c = c * cosTheta + d * sinTheta;
	d = d * cosTheta - c * sinTheta;

	c += X2;
	d += Y2;

	printLine(c, d, X2, Y2);
}