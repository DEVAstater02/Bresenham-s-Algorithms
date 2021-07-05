#include <stdio.h>
#include <glut.h>

int X1, X2, Y1, Y2;
void init();
void plotPixel(int x, int y);
void plotDisplay();
void printLine(int X1, int Y1, int X2, int Y2);

/// <summary>
/// main function contains all the necessary glut library initialisation funtions
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char **argv) {
	printf("Enter x1, y1; x2, y2 : ");
	scanf_s("%d %d %d %d", &X1, &Y1, &X2, &Y2);
	///used to initialise glut library
	glutInit(&argc, argv);
	///glutInitDisplayMode is important to mention the mode of the display
	///GLUT_SINGLE mentions single buffer setting 
	///GLUT_RGB represents RGB color mode
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	///Size of the window is set by glutInitWindowSize
	glutInitWindowSize(500, 500);
	///glutInitWindowPostion specifies the position of the window
	glutInitWindowPosition(0,0);
	///glutCreateWindow creates a window with the argument provided as the window name
	glutCreateWindow("Line drawing algorithm");//create a window to draw and names it as the parameter given inside the function
	///call to the init function
	init();
	glutDisplayFunc(plotDisplay);
	glutMainLoop();

	return 0;
}

/// <summary>
/// init function calls a few other functions which initialises the glut library and clears the color buffer
/// </summary>
void init() {
	glClear(GL_COLOR_BUFFER_BIT);///clears the color buffer, equivalent to erasing the black boarding before writing.
	glClearColor(0.0, 0.0, 0.0, 1.0);///clears the color buffer.
	glMatrixMode(GL_PROJECTION);///specifies which matrix stack is targetted, in this case it is the projection matrix stack.
	gluOrtho2D(-250, 250, -250, 250);///defines a 2D orthographic projecion matrix sets up a 2D orthographic viewing region. Its parameters are used to clip the plane.
}


/// <summary>
/// This function plots the actual pixel on our display.
/// </summary>
/// <param name="x">x coordinate to be plotted</param>
/// <param name="y">y coordinate to be plotted</param>
void plotPixel(int x, int y){
	/// <summary>
	/// glBegin tells the compiler the way in which the points are to be interpretted
	/// Vertex2i specifies the two integer coordinates x and y to be plotted on the screen.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

/// <summary>
/// plotDisplay function is the display function which tells the compiler what is to be compiled and displayed.
/// </summary>
void plotDisplay() {
	printLine(X1, Y1, X2, Y2);
	/// <summary>
	/// glFlush functions forcefully executes all the previous functions so that display function can run seamlessly.
	/// </summary>
	glFlush();
}

/// <summary>
/// printLine funtion plots all the pixels(using bresenham's line drawing algorithm) on the line given by the two end points.
/// </summary>
/// <param name="X1"> X coordinate of tail point</param>
/// <param name="Y1"> Y coordinate of tail point</param>
/// <param name="X2"> x coordinate of head point</param>
/// <param name="Y2"> y coordinate of head point</param>
void printLine(int X1, int Y1, int X2, int Y2) {
	///x1, x2, y1, y2 are the end vertices of the line to be drawn
	int x = X1, y = Y1;
	int dx, dy;
	int incX = 1, incY = 1;
	int incE, incNE;
	int d;

	dx = X2 - X1;
	dy = Y2 - Y1;

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	if (X2 < X1)
		incX = -1;
	if (Y2 < Y1)
		incY = -1;

	if (dx > dy) {
		plotPixel(x,y);
		d = 2 * dy - dx;
		incNE = 2 * (dy - dx);
		incE = 2 * dy;

		for (int i = 0; i < dx; i++) {
			if (d < 0) {
				d += incE;
			}
			else {
				y += incY;
				d += incNE;
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
