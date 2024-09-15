
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"

const int HEIGHT = 600;
const int WIDTH = 600;
const double PI = 3.14;

double offset = 0;
double xt = 0, yt = 0;
double Vx = 0, Vy = 0;
double x_0 = 0, y_0 = 0;
double f = 0;
double alph = 0;
double t = 0;
bool ballMoved = false;

void init()
{

				//  R   G    B
	glClearColor(0.5,0.5,0.5,0);// color of window background
	glOrtho(-1, 1, -1, 1, -1, 1); // set the coordinates system

}

double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


void DrawCircle(int num_pts)
{
	double alpha;
	double teta = 2 * PI / num_pts;
	double x, y;

	glBegin(GL_POLYGON);
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawWheel(int num_pts)
{
	double alpha;
	double teta = 2 * PI / num_pts;
	double x, y;


	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		glBegin(GL_POLYGON);
		x = cos(alpha);   // first point
		y = sin(alpha);
		glColor3d(fabs(x), fabs(y), alpha / PI);
		glVertex2d(x, y);
		glColor3d(0, 0, 0);
		glVertex2d(0, 0); // second point
		alpha += teta;
		x = cos(alpha);	// third point
		y = sin(alpha);
		glColor3d(fabs(x), fabs(y), alpha / PI);
		glVertex2d(x, y);
		glEnd();
	}
/*
	glBegin(GL_LINE_LOOP);
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();
*/

}

void RotatingWheel()
{
	glRotated(2 * offset, 0, 0, -1);
	glScaled(0.25, 0.25, 1);
	DrawWheel(30);

}

void DrawBallLines()
{
	double alpha;
	double teta = 2 * PI / 40;
	double x, y;

	glPushMatrix();

	glLoadIdentity(); // start transformations here
	glColor3d(1, 1, 1);


	glTranslated(0,0.06, 1);
	glScaled(0.05, 0.05, 1);
	glBegin(GL_LINE_STRIP);
	for (alpha = PI; alpha <= 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();

	glLoadIdentity(); // start transformations here
	glColor3d(1, 1, 1);

	glTranslated(0, -0.06, 1);
	glScaled(0.05, 0.05, 1);
	glBegin(GL_LINE_STRIP);
	for (alpha = 0; alpha <= PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();


	glPopMatrix();

	glBegin(GL_LINES);
	glVertex2d(-1, 0);
	glVertex2d(1, 0);

	glEnd();

	glBegin(GL_LINES);
	glVertex2d(0, -1);
	glVertex2d(0, 1);
	glEnd();

	
}
void DrawBasket()
{

	double alpha;
	double teta = 2 * PI / 40;
	double x, y;

	//bracket
	glBegin(GL_LINES);
	glVertex2d(-1, 0.4);
	glVertex2d(-0.9, 0.4);
	glEnd();

	//hoop
	glPushMatrix();
	glTranslated(-0.75, 0.4, 1);
	glScaled(0.15, 0.15, 1);
	glBegin(GL_LINE_STRIP);
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha) * 0.75;
		glVertex2d(x, y);
	}
	glEnd();

	glPopMatrix();

	//ropes
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);

	glVertex2d(-0.9, 0.4);
	glVertex2d(-0.85, 0.2);

	glVertex2d(-0.6, 0.4);
	glVertex2d(-0.65, 0.2);

	//glVertex2d(-0.9, 0.57);
	//glVertex2d(-0.65, 0.3);

	//glVertex2d(-0.76, 0.49);
	//glVertex2d(-0.635, 0.36);

	//glVertex2d(-0.7, 0.5);
	//glVertex2d(-0.630, 0.43);

	//glVertex2d(-0.6, 0.526);
	//glVertex2d(-0.630, 0.43);

	glEnd();


	/*glPushMatrix();
	for (alpha = PI; alpha <= 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha) ;
		glVertex2d(x, y);
		glVertex2d(0,0);
	}
	glEnd();
	glPopMatrix();
	*/

}

void DrawBasketBall()
{
	glPushMatrix();
	glTranslated(xt, yt, 1);
	glScaled(0.08, 0.08, 1);
	glColor3d(1, 0.5, 0);
	DrawCircle(50);
	glColor3d(1, 1, 1);
	DrawBallLines();
	glPopMatrix();
}



void mouse(int button, int state, int x, int y)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		t += 0.0002;
		if (x>300)
			x_0 = (double)((double)(x-300)/300);
		else
			x_0 = (double)((double)(300-x) / 300)*-1;

		if (y > 300)
			y_0 = (double)((double)(y - 300) / 300);
		else
			y_0 = (double)((double)(300 - y) / 300) * -1;

		f=distance(300,300,x,y);
		alph = PI - atan2(y,x);
		Vx = f * cos(alph);
		Vy = f * sin(alph);
		xt = (x_0 + Vx * t)/1000;
		yt =( y_0 + Vy + 1 * pow(t, 2)) / 1000;
		ballMoved = true;

	}
		
}

void nextPos()
{
	if (ballMoved)
	{
		if (xt > -1 && yt > -1)
		{
			x_0 = xt;
			y_0 = yt;
			xt = (x_0 + Vx * t) / 1000;
			yt = (y_0 + Vy*t + 0.002 * pow(t, 2)) / 1000;
		}
		else if (xt <= -1)
		{

		}
		else if (yt <= -1)
		{

		}
	}

}
// put all drawings here
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // start transformations here

	
	DrawBasketBall();
	
	DrawBasket();

	glutSwapBuffers(); // show all
}

void idle() 
{
	offset+=0.2;
	if (t>0)
	{
		t += 0.0002;
	}
	nextPos();
	
	glutPostRedisplay(); // calls indirectly display
}

void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 50);
	glutCreateWindow("2D graphics Example");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	
	init();

	glutMainLoop();
}