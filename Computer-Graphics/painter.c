#define NULL 0
#define LINE 1
#define RECTANGLE 2
#define TRIANGLE  3
#define POINTS_S 4
#define TEXT_T 5
#define PENTAGON 6
#define STAR 7
#define CIRCLE 8
#define HALF_CIRCLE 9
#define PI 3.14
#define PEN 10
#define ERASE 11
#include <glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


float linewidth = 1.0f;
void CaptureScreen();
void LoadScreen();
void * memset(void * ptr, int value, size_t num);

GLsizei wh = 1000, ww = 500; /* initial window size */
GLfloat size = 3.0;   /* half side length of square */
int draw_mode = 0; /* drawing mode */
int rx, ry; /*raster position*/
int tempx, tempy, tempx2;

int save, save_x, save_y;
int up;
int Pen_on = 0;
GLfloat r = 1.0, g = 1.0, b = 1.0; /* drawing color */
int fill = 0; /* fill flag */

void mouse(int, int, int, int);
void key(unsigned char, int, int);
void display(void);
void drawSquare(int, int);
void myReshape(GLsizei, GLsizei);

void myinit(void);

void screen_box(int, int, int);
void right_menu(int);
void color_menu(int);
void pixel_menu(int);
void fill_menu(int);
int pick(int, int);

void drawSquare(int x, int y)
{

	y = wh - y;
	glColor3ub((char)rand() % 256, (char)rand() % 256, (char)rand() % 256);
	glBegin(GL_POLYGON);
	glVertex2f(x + size, y + size);
	glVertex2f(x - size, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);
	glEnd();
}


/* rehaping routine called whenever window is resized
or moved */

void myReshape(GLsizei w, GLsizei h)
{

	/* adjust clipping box */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* adjust viewport and  clear */

	glViewport(0, 0, w, h);
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	display();
	glFlush();

	/* set global size for use by drawing routine */

	ww = w;
	wh = h;
}

void myinit(void)
{

	glViewport(0, 0, ww, wh);


	/* Pick 2D clipping window to match size of X window
	This choice avoids having to scale object coordinates
	each time window is resized */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);

	/* set clear color to black and clear window */

	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void drag_func(int x, int y) {
	if (Pen_on == 1) {
		if (save == 0)
		{
			save_x = x;
			save_y = wh - y;
			save = 1;
		}
		else if (save == 1) {
			glColor3f(r, g, b);
			glLineWidth(linewidth);
			glBegin(GL_LINE_LOOP);
			glVertex2i(save_x, save_y);
			glVertex2i(x, wh - y);
			glEnd();
			glFlush();
			save_x = x;
			save_y = wh - y;
		}
	}
}

void mouse(int btn, int state, int x, int y)
{
	static int count;
	int where;
	static int xp[2], yp[2];
	if (up = 1) {
		save = 0;
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		where = pick(x, y);
		glColor3f(r, g, b);
		if (where != 0)
		{
			count = 0;
			draw_mode = where;
		}
		else switch (draw_mode)
		{
		case(LINE):
			Pen_on = 0;
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				glLineWidth(linewidth);
				glBegin(GL_LINES);
				glVertex2i(x, wh - y);
				glVertex2i(xp[0], wh - yp[0]);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		case(RECTANGLE):
			Pen_on = 0;
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON);
				else
					glLineWidth(linewidth);
				glBegin(GL_LINE_LOOP);
				glVertex2i(x, wh - y);
				glVertex2i(x, wh - yp[0]);
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[0], wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		case (TRIANGLE):
			Pen_on = 0;
			switch (count)
			{
			case(0):
				count++;
				xp[0] = x;
				yp[0] = y;
				break;
			case(1):
				count++;
				xp[1] = x;
				yp[1] = y;
				break;
			case(2):
				if (fill) glBegin(GL_POLYGON);
				else
					glLineWidth(linewidth);
				glBegin(GL_LINE_LOOP);
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[1], wh - yp[1]);
				glVertex2i(x, wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		case(POINTS_S):
		{
			drawSquare(x, y);
			count++;
		}
		break;
		case(TEXT_T):
		{
			rx = x;
			ry = wh - y;
			glRasterPos2i(rx, ry);
			count = 0;
		}
		break;
		case(PENTAGON):
		{
			Pen_on = 0;
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON);
				else
					glLineWidth(linewidth);
				glBegin(GL_LINE_LOOP);
				tempx = x - xp[0];
				tempy = y - yp[0];
				tempx2 = (x - xp[0]) / 2;
				glVertex2d(x - tempx2, wh - yp[0]);
				glVertex2d(xp[0], wh - yp[0] - (3 * tempy / 8));
				glVertex2d((x - tempx2) - (3 * tempx / 10), wh - y);
				glVertex2d((x - tempx2) + (3 * tempx / 10), wh - y);
				glVertex2d(x, wh - yp[0] - (3 * tempy / 8));
				glEnd();
				draw_mode = 0;
				count = 0;
			}
		}
		break;
		case(STAR):
		{
			Pen_on = 0;
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON);
				else
					glLineWidth(linewidth);
				glBegin(GL_LINE_LOOP);
				tempx = x - xp[0];
				tempy = y - yp[0];
				tempx2 = (x - xp[0]) / 2;
				glVertex2f((x - tempx2) + (2 * tempx / 15), wh - yp[0] - (3 * tempy / 8));
				glVertex2f(x - tempx2, wh - yp[0]);
				glVertex2f((x - tempx2) - (2 * tempx / 15), wh - yp[0] - (3 * tempy / 8));
				glVertex2f(xp[0], wh - yp[0] - (3 * tempy / 8));
				glVertex2f((x - tempx2) - (3 * tempx / 15), wh - yp[0] - (3 * tempy / 5));
				glVertex2f((x - tempx2) - (3 * tempx / 10), wh - y);
				glVertex2f(x - tempx2, wh - yp[0] - (3 * tempy / 4));
				glVertex2f((x - tempx2) + (3 * tempx / 10), wh - y);
				glVertex2f((x - tempx2) + (3 * tempx / 15), wh - yp[0] - (3 * tempy / 5));
				glVertex2f(x, wh - yp[0] - (3 * tempy / 8));

				glEnd();
				draw_mode = 0;
				count = 0;
			}
		}
		break;
		case(CIRCLE):
		{
			Pen_on = 0;
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON);
				else
					glLineWidth(linewidth);
				glBegin(GL_LINE_LOOP);
				int radius = (x - xp[0]) / 2;
				for (int i = 0; i <= 360; i++)
				{
					glVertex2f(radius*sin(2 * PI*i / 360) + (x - radius), radius*cos(2 * PI*i / 360) + ((wh - y)));
				}
				glEnd();
				draw_mode = 0;
				count = 0;
			}
		}
		break;
		case(HALF_CIRCLE):
		{
			Pen_on = 0;
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON);
				else
					glLineWidth(linewidth);
				glBegin(GL_LINE_LOOP);
				int radius = (x - xp[0]) / 2;
				for (int i = 0; i <= 360; i++)
				{
					glVertex2f(radius*sin(PI*i / 360) + (x - radius), radius*cos(PI*i / 360) + ((wh - y)));
				}
				glEnd();
				draw_mode = 0;
				count = 0;
			}
		}
		break;
		case(PEN):
		{
			if (Pen_on == 1)
				Pen_on = 0;
			else if (Pen_on == 0)
				Pen_on = 1;
		}
		break;
		case(ERASE):
		{
			color_menu(9);
			if (Pen_on == 1)
				Pen_on = 0;
			else if (Pen_on == 0)
				Pen_on = 1;
		}
		break;
		}
		glPopAttrib();
		glFlush();
	}
}

int pick(int x, int y)
{
	y = wh - y;
	if (y < wh - ww / 20) return 0;
	else if (x < ww / 20) return LINE;
	else if (x < 2 * ww / 20) return RECTANGLE;
	else if (x < 3 * ww / 20) return TRIANGLE;
	else if (x < 4 * ww / 20) return POINTS_S;
	else if (x < 5 * ww / 20) return TEXT_T;
	else if (x < 6 * ww / 20) return PENTAGON;
	else if (x < 7 * ww / 20) return STAR;
	else if (x < 8 * ww / 20) return CIRCLE;
	else if (x < 9 * ww / 20) return HALF_CIRCLE;
	else if (x < 10 * ww / 20) return PEN;
	else if (x < 10 * ww / 10) return ERASE;
	else return 0;
}

void screen_box(int x, int y, int s)
{
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + s, y);
	glVertex2i(x + s, y + s);
	glVertex2i(x, y + s);
	glEnd();
}

void right_menu(int id)
{
	if (id == 1) return;
	else if (id == 3) {
		CaptureScreen();
	}
	else if (id == 4) {
		LoadScreen();
	}
	else display();
}

void color_menu(int id)
{
	if (id == 1) { r = 1.0; g = 0.0; b = 0.0; }
	else if (id == 2) { r = 0.0; g = 1.0; b = 0.0; }
	else if (id == 3) { r = 0.0; g = 0.0; b = 1.0; }
	else if (id == 4) { r = 0.0; g = 1.0; b = 1.0; }
	else if (id == 5) { r = 1.0; g = 0.0; b = 1.0; }
	else if (id == 6) { r = 1.0; g = 1.0; b = 0.0; }
	else if (id == 7) { r = 1.0; g = 1.0; b = 1.0; }
	else if (id == 8) { r = 0.0; g = 0.0; b = 0.0; }
	else if (id == 9) { r = 0.8; g = 0.8; b = 0.8; }
}


void pixel_menu(int id)
{
	if (id == 2)
		if (linewidth <= 1.0f)
			linewidth = 1.0f;
		else linewidth -= 2.0f;
	else
		linewidth += 2.0f;
}

void fill_menu(int id)
{
	if (id == 1) fill = 1;
	else fill = 0;
}

void key(unsigned char k, int xx, int yy)
{
	if (draw_mode != TEXT_T) return;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(rx, ry);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
	/*glutStrokeCharacter(GLUT_STROKE_ROMAN,i); */
	rx += glutBitmapWidth(GLUT_BITMAP_9_BY_15, k);

}

void display(void)
{
	int shift = 0;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	screen_box(0, wh - ww / 20, ww / 20);
	glColor3f(1.0, 0.0, 0.0);
	screen_box(ww / 20, wh - ww / 20, ww / 20);
	glColor3f(0.0, 1.0, 0.0);
	screen_box(2 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(0.0, 0.0, 1.0);
	screen_box(3 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(1.0, 1.0, 0.0);
	screen_box(4 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(0.5, 0.9, 0.1);
	screen_box(5 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(0.2, 0.5, 1.0);
	screen_box(6 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(1.0, 0.3, 0.6);
	screen_box(7 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(0.3, 1.0, 0.3);
	screen_box(8 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(0.6, 0.3, 1.0);
	screen_box(9 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(0.2, 0.9, 7.0);
	screen_box(10 * ww / 20, wh - ww / 20, ww / 20);
	glColor3f(0.0, 0.0, 0.0);
	screen_box(ww / 20 + ww / 80, wh - ww / 20 + ww / 80, ww / 40); //rectangle gui




	glBegin(GL_LINES);
	glVertex2i(wh / 80, wh - ww / 40);
	glVertex2i(wh / 80 + ww / 40, wh - ww / 40);
	glEnd();

	/*glBegin(GL_TRIANGLES);
	glVertex2i(ww / 5 + ww / 40, wh - ww / 10 + ww / 40);
	glVertex2i(ww / 5 + ww / 20, wh - ww / 40);
	glVertex2i(ww / 5 + 3 * ww / 40, wh - ww / 10 + ww / 40);
	glEnd();*/

	glRasterPos2i(2 * ww / 20, wh - ww / 40); //triange gui
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'T');
	glRasterPos2i(2 * ww / 20 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'r');
	glRasterPos2i(2 * ww / 20 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'i');
	glRasterPos2i(2 * ww / 20 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'a');
	glRasterPos2i(2 * ww / 20 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');


	glPointSize(7.0); //point gui
	glBegin(GL_POINTS);
	glVertex2i(3 * ww / 20 + ww / 40, wh - ww / 40);
	glEnd();

	glRasterPos2i(2 * ww / 10, wh - ww / 40); //text gui
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'T');
	glRasterPos2i(2 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'e');
	glRasterPos2i(2 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'x');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'x');
	glRasterPos2i(2 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');

	glRasterPos2i(2.5 * ww / 10, wh - ww / 40); //Pentagon gui
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'P');
	glRasterPos2i(2.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'e');
	glRasterPos2i(2.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'n');
	glRasterPos2i(2.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 't');
	glRasterPos2i(2.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');


	glRasterPos2i(3 * ww / 10, wh - ww / 40); //Star gui
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'S');
	glRasterPos2i(3 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 't');
	glRasterPos2i(3 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'a');
	glRasterPos2i(3 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');

	glRasterPos2i(3.5 * ww / 10, wh - ww / 40); //circle gui
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'C');
	glRasterPos2i(3.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'i');
	glRasterPos2i(3.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'r');
	glRasterPos2i(3.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'c');
	glRasterPos2i(3.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');

	glRasterPos2i(4 * ww / 10, wh - ww / 40); //Semi circle gui
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'S');
	glRasterPos2i(4 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'e');
	glRasterPos2i(4 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'C');
	glRasterPos2i(4 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'i');
	glRasterPos2i(4 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');

	glRasterPos2i(4.5 * ww / 10, wh - ww / 40); //pen gui
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'P');
	glRasterPos2i(4.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'e');
	glRasterPos2i(4.5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');

	glRasterPos2i(5 * ww / 10, wh - ww / 40); //Erase gui
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'E');
	glRasterPos2i(5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'r');
	glRasterPos2i(5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'a');
	glRasterPos2i(5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 's');
	glRasterPos2i(5 * ww / 10 + shift, wh - ww / 40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');


	glFlush();
	glPopAttrib();
}


void CaptureScreen()
{

	BITMAPFILEHEADER bmpfile; // 비트맵파일헤더
	BITMAPINFOHEADER bmpinfo; // 비트맵정보헤더

	int Width, Height;
	Width = 1000;
	Height = 500;

	unsigned char *pixels = new unsigned char[sizeof(unsigned char)*Width*Height * 3]; //unsigned char = BYTE 0-255
	FILE *file;
	fopen_s(&file, "save.bmp", "wb");

	glReadPixels(0, 0, Width, Height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

	memset(&bmpfile, 0, sizeof(bmpfile)); // 14바이트 0 값.
	memset(&bmpinfo, 0, sizeof(bmpinfo)); // 

	bmpfile.bfType = 'MB';
	bmpfile.bfSize = sizeof(bmpfile) + sizeof(bmpinfo) + Width*Height * 3;
	bmpfile.bfOffBits = sizeof(bmpfile) + sizeof(bmpinfo);

	bmpinfo.biSize = sizeof(bmpinfo); // 구조체크기
	bmpinfo.biWidth = Width; // 이미지 가로
	bmpinfo.biHeight = Height; // 이미지 세로
	bmpinfo.biPlanes = 1; // 플레인수
	bmpinfo.biBitCount = 24; // 비트수 
	bmpinfo.biSizeImage = Width*Height * 3; // 이미지의크기

	fwrite(&bmpfile, sizeof(bmpfile), 1, file);
	fwrite(&bmpinfo, sizeof(bmpinfo), 1, file);
	fwrite(pixels, sizeof(unsigned char), Height*Width * 3, file);

	fclose(file);

	free(pixels);
}

void LoadScreen() {
	int Height, Width;
	Height = 500;
	Width = 1000;

	BITMAPFILEHEADER bmpfile; // 비트맵파일헤더
	BITMAPINFOHEADER bmpinfo; // 비트맵정보헤더

	unsigned char *pixels = new unsigned char[sizeof(unsigned char)*Width*Height * 3]; //unsigned char = BYTE 0-255
	FILE *file;
	fopen_s(&file, "save.bmp", "rb");

	fread(&bmpfile, 1, sizeof(BITMAPFILEHEADER), file);
	fread(&bmpinfo, 1, sizeof(BITMAPINFOHEADER), file);
	fread(pixels, 1, bmpinfo.biSizeImage, file);
	glRasterPos2i(0, 0);
	glDrawPixels(Width, Height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

	fclose(file);
	delete[] pixels;
	glFlush();
}

int main(int argc, char** argv)
{
	int c_menu, p_menu, f_menu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("square");
	glutDisplayFunc(display);
	c_menu = glutCreateMenu(color_menu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Cyan", 4);
	glutAddMenuEntry("Magenta", 5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("White", 7);
	glutAddMenuEntry("Black", 8);
	p_menu = glutCreateMenu(pixel_menu);
	glutAddMenuEntry("increase pixel size", 1);
	glutAddMenuEntry("decrease pixel size", 2);
	f_menu = glutCreateMenu(fill_menu);
	glutAddMenuEntry("fill on", 1);
	glutAddMenuEntry("fill off", 2);
	glutCreateMenu(right_menu);
	glutAddMenuEntry("quit", 1);
	glutAddMenuEntry("clear", 2);
	glutAddMenuEntry("save Image", 3);
	glutAddMenuEntry("load Image", 4);
	glutAddSubMenu("Colors", c_menu);
	glutAddSubMenu("Pixel Size", p_menu);
	glutAddSubMenu("Fill", f_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	myinit();
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(key);
	glutMotionFunc(drag_func);
	glutMouseFunc(mouse);
	glutMainLoop();

}
