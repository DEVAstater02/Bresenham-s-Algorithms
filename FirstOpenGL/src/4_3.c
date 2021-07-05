#include <stdio.h>
#include <glut.h>

#define MAX_COORDINATE 250

int X1, X2, Y1, Y2;
void myInit();
void plotPixel(int x, int y);
void printLine(int X1, int Y1, int X2, int Y2);
void plotDisplay();
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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Vector Field");

	myInit();
	glutDisplayFunc(plotDisplay);
	glutMainLoop();
	return 0;
}

/// <summary>
/// init function calls a few other functions which initialises the glut library and clears the color buffer
/// </summary>
void myInit() {
	//clears the color buffer bit so that there isn't any traces of the previous state
	glClear(GL_COLOR_BUFFER_BIT);
	//clears the R, G, B and alpha values
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//this specifies which matrix is being targetted, and the argument gives the matrix
	glMatrixMode(GL_PROJECTION);
	//defines a 2D orthographic projecion matrix sets up a 2D orthographic viewing region. Its parameters are used to clip the plane.
	gluOrtho2D(-250, 250, -250, 250);
}

/// <summary>
/// This function plots the actual pixel on our display.
/// </summary>
/// <param name="x">x coordinate to be plotted</param>
/// <param name="y">y coordinate to be plotted</param>
void plotPixel(int x, int y) {
	//glBegin tells the compiler the way in which the set of points are to be interpreted
	//GL_POINTS is the argument that is to be passed into glBegin.
	glBegin(GL_POINTS);
	//glVertex2i just plots the vertex with integer coordinates.
	glVertex2i(x, y);
	glEnd();
}

/// <summary>
/// This function contains the bresenham's algorithm which is used to draw the vector body.
/// </summary>
/// <param name="X1">X1 is the x coordinate at which we need to find the field direction</param>
/// <param name="Y1">Y1 is the y coordinate at which we need to find the field direction</param>
/// <param name="X2">X2 is the x coordinate of the head vector</param>
/// <param name="Y2">Y2 is the y coordinate of the head vector</param>
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
/// Display function:- 
/// instead of choosing every single point on viewport
/// i choose points with 20 distance between them in every row and column
/// </summary>
void plotDisplay() {

	for (int i = 1; i < MAX_COORDINATE; i++) {
		if (i % 20 == 0) {
			for (int j = 1; j < MAX_COORDINATE; j++) {
				if (j % 20 == 0) {
					vector(i, j);
					vector(-i, j);
					vector(i, -j);
					vector(-i, -j);
				}
			}
		}
	}
	//glFlush is used to make sure that all other programs are compiled and executed and don't interupt the display function
	glFlush();
}

/// <summary>
/// vector is a user defined function,given the tail of the vector , will compute the head coordinates
/// And also draws the vector after computing the coordinates of the head.
/// The vector field that I used is F(x, y) = (-x,-y)
/// The vector would have been drawn till (-x,-y) if (X1, Y1) was the origin but it isn't,
/// hence we transform the coordinates by adding (X1, Y1) to (x, y).
/// Since we want the vector pattern through out the coordinate space,
/// a polyline representation of the vector field is not that appealing
/// Therefore we draw each vector with only 10% of its length for better representation of the field
/// </summary>
/// <param name="X1"></param>
/// <param name="Y1"></param>
void vector(int X1, int Y1) {
	int x = X1, y = Y1;
	X2 = X1 - x;
	Y2 = Y1 - y;

	int dx = X2 - X1;
	int dy = Y2 - Y1;

	Y2 = Y1 + 0.1 * dy;
	X2 = X1 + 0.1 * dx;

	printLine(X1, Y1, X2, Y2);
	arrowHead1(X2, Y2, X1, Y1);
	arrowHead2(X2, Y2, X1, Y1);
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
