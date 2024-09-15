
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"

const int HEIGHT = 600;
const int WIDTH = 600;
const double PI = 3.14;

double offset = 1.2;
double xt = 0, yt = 0;
double Vx = 0, Vy = 0;
double Start_x = 0, Start_y = 0;
double x_0 = 0, y_0 = 0;
double f = 0;
double alph = 0;
double t = 0;
bool ballMoved = false;

double airResistance;
double gravity = -9.81;
void init()
{

	//  R   G    B
	glClearColor(0.5, 0.5, 0.5, 0);// color of window background
	glOrtho(-1, 1, -1, 1, -1, 1); // set the coordinates system

}

double distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void DrawCircleNew(int num_pts)
{
	double alpha, teta = 2 * PI / num_pts;
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

void DrawCloud()
{
	glPushMatrix(); // 1
	glColor3d(0.9, 0.9, 0.9);
	glTranslated(-0.3, 0.2, 0);
	glScaled(0.3, 0.2, 1);
	DrawCircleNew(40);
	glPopMatrix();

	glPushMatrix(); // 2
	glColor3d(0.9, 0.9, 0.9);
	glTranslated(-0.2, 0.3, 0);
	glScaled(0.2, 0.2, 1);
	DrawCircleNew(40);
	glPopMatrix();

	glPushMatrix(); // 3
	glColor3d(0.9, 0.9, 0.9);
	glTranslated(-0.1, 0.1, 0);
	glScaled(0.2, 0.2, 1);
	DrawCircleNew(40);
	glPopMatrix();

	glPushMatrix(); // 4
	glColor3d(0.9, 0.9, 0.9);
	glTranslated(0.2, 0.2, 0);
	glScaled(0.15, 0.15, 1);
	DrawCircleNew(40);
	glPopMatrix();

	glPushMatrix(); // 5
	glColor3d(0.9, 0.9, 0.9);
	glTranslated(0.05, 0.3, 0);
	glScaled(0.15, 0.15, 1);
	DrawCircleNew(40);
	glPopMatrix();

	glPushMatrix(); // 6
	glColor3d(0.9, 0.9, 0.9);
	glTranslated(0.2, 0.1, 0);
	glScaled(0.2, 0.14, 1);
	DrawCircleNew(40);
	glPopMatrix();

}

void DrawSky()
{

	glColor3d(0.5, 0.7, 1);
	glBegin(GL_POLYGON);
	glVertex2d(-1, 1);
	glVertex2d(1, 1);
	glVertex2d(1, 0.0);
	glVertex2d(-1, 0.0);
	glEnd();


	glPushMatrix();
	glTranslated(offset, 0.6, 0);
	glScaled(0.5, 0.4, 1);
	DrawCloud();
	glPopMatrix();



	glPushMatrix();
	glTranslated(offset+0.5, 0.4, 0);
	glScaled(-0.5, 0.4, 1);
	DrawCloud();
	glPopMatrix();
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
	glLineWidth(1);

	glTranslated(xt, yt +0.06, 1);
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

	glTranslated(xt,yt -0.06, 1);
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

void DrawBasketLinesThatIsActuallyNetwork()
{
	//LEFT TO RIGHT
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.9, 0.5);
	glVertex2d(-0.65, 0.25);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.85, 0.5);
	glVertex2d(-0.64, 0.3);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.8, 0.5);
	glVertex2d(-0.63, 0.35);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.73, 0.5);
	glVertex2d(-0.62, 0.4);
	glEnd();

	//RIGHT TO LEFT
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.6, 0.5);
	glVertex2d(-0.85, 0.25);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.65, 0.5);
	glVertex2d(-0.86, 0.3);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.72, 0.5);
	glVertex2d(-0.87, 0.35);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.8, 0.5);
	glVertex2d(-0.88, 0.42);
	glEnd();
}

void DrawBasket()
{
	double teta = 2 * PI / 40;
	double x, y;


	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-1,0.5);
	glVertex2d(-0.9, 0.5);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.9, 0.5);
	glVertex2d(-0.6, 0.5);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.9, 0.5);
	glVertex2d(-0.85, 0.25);
	glEnd();

	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2d(-0.6, 0.5);
	glVertex2d(-0.65, 0.25);
	glEnd();

	glPushMatrix();
	glTranslated(-0.75, 0.25, 1);
	glScaled(0.1, 0.1, 1);
	glBegin(GL_LINE_STRIP);
	for (double alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha) * 0.3;
		glVertex2d(x, y);
	}
	glEnd();
	glPopMatrix();

	DrawBasketLinesThatIsActuallyNetwork();

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

void DrawGround()
{
	glColor3d(0, 0.7, 0.6);
	glBegin(GL_POLYGON);
	glVertex2d(-1,0);
	glVertex2d(1,0);
	glVertex2d(1,-1);
	glVertex2d(-1,-1);
	glEnd();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (ballMoved)
		{
			ballMoved = false;
			xt = 0;
			yt = 0;
			Start_x = 0;
			Start_y = 0;
			Vx = 0;
			Vy = 0;
			f = 0;
			alph = 0;
			t = 0;
		}
		else
		{
			x_0 = 2.0 * x / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
			y_0 = 1.0 - (2.0 * y) / glutGet(GLUT_INIT_WINDOW_HEIGHT);
			f = distance(0, 0, x_0, y_0) / 1.5;
			if (x_0 >= 0 && (y_0 >= 0))//RAVIA 1
			{
				alph = atan(fabs(y_0) / fabs(x_0));
			}
			else if (x_0 < 0 && (y_0 >= 0))//ARAVIA 2
			{
				alph = PI - atan(fabs(y_0) / fabs(x_0));
			}
			else if (x_0 >= 0 && (y_0 < 0))//ARAVIA 4
			{
				alph = -atan(fabs(y_0) / fabs(x_0));
			}
			else //ARAVIA 3
			{
				alph = PI + atan(fabs(y_0) / fabs(x_0));
			}
			//alph = PI - atan((double)fabs(y_0) / fabs(x_0));
			Vx = f * cos(alph);
			Vy = f * sin(alph);
			ballMoved = true;
		}
	}
		
}


void nextPos()
{
	//Walls
	if(xt <= -0.92)
	{
		t = 0;
		Start_x = -0.9199;
		Start_y = yt;
		Vx = -(Vx*0.95);
		Vy = (Vy + 2 * 0.05 * t) * 0.95;
	}
	else if (xt >= 0.92)
	{
		t = 0;
		Start_x = 0.9199;
		Start_y = yt;
		Vx = -(Vx * 0.95);
		Vy = (Vy + 2 * 0.05 * t)*0.95;
	}

	//Floor & Roof
	if (yt <= -0.92 ) 
	{
		t = 0;
		Start_x = xt;
		Start_y = -0.9199;
		Vx *= 0.95;
		Vy = (-(Vy + 2 * 0.05 * t)) * 0.95;
	}
	else if (yt >= 0.92)
	{
		t = 0;
		Start_x = xt;
		Start_y = 0.9199;
		Vx *= 0.95;
		Vy = ( - (Vy + 2 * 0.05 * t))*0.95;
	}

	//Ring
	if ((pow(xt+0.6,2)+pow(yt-0.5,2))<=0.007)//Right side
	{
		if(xt >= -0.6 && (yt >= 0.5))//RAVIA 1
		{
			alph = atan(fabs(yt-0.5)/fabs(xt+0.6));
		}
		else if(xt < -0.6 && (yt >= 0.5))//ARAVIA 2
		{
			alph = PI - atan(fabs(yt-0.5)/fabs(xt+0.6));
		}
		else if(xt >= -0.6 && (yt < 0.5))//ARAVIA 4
		{
			alph = -atan(fabs(yt-0.5)/fabs(xt+0.6));
		}
		else //ARAVIA 3
		{
			alph = PI + atan(fabs(yt-0.5)/fabs(xt+0.6));
		}
		Vx = f * cos(alph);
		Vy = f * sin(alph);
		Start_x = xt;
		Start_y = yt;
		t=0.001;
	}

	if ((pow(xt+0.9,2)+pow(yt-0.5,2))<=0.007)//Left side
	{
		if(xt >= -0.9 && (yt >= 0.5))//RAVIA 1
		{
			alph = atan(fabs(yt-0.5)/fabs(xt+0.9));
		}
		else if(xt < -0.9 && (yt >= 0.5))//ARAVIA 2
		{
			alph = PI - atan(fabs(yt-0.5)/fabs(xt+0.9));
		}
		else if(xt >= -0.9 && (yt < 0.5))//ARAVIA 4
		{
			alph = -atan(fabs(yt-0.5)/fabs(xt+0.9));
		}
		else //ARAVIA 3
		{
			alph = PI + atan(fabs(yt-0.5)/fabs(xt+0.9));
		}
		Vx = f * cos(alph);
		Vy = f * sin(alph);
		Start_x = xt;
		Start_y = yt;
		t=0.001;
	}
	else if((xt <= -0.9)&&(yt <= 0.52)&&(yt >= 0.48))
	{
		if (Vy <= 0) 
		{
			t = 0;
			Start_x = xt;
			Start_y = 0.52011;
			Vx *= 0.95;
			Vy = (-(Vy + 2 * 0.05 * t)) * 0.95;
		}
		else
		{
			t = 0;
			Start_x = xt;
			Start_y = 0.47999;
			Vx *= 0.95;
			Vy = ( - (Vy + 2 * 0.05 * t))*0.95;
		}
	}

	//Final movement
	xt = (Start_x + Vx * t);
	yt = (Start_y + Vy * t - 0.05 * pow(t, 2));

}


// put all drawings here
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // start transformations here
	
	DrawGround();
	DrawSky();
	DrawBasketBall();

	DrawBasket();

	glutSwapBuffers(); // show all
}

void idle()
{
	offset -= 0.00005;
	if (offset<-2)
	{
		offset = 2;
	}
	if (ballMoved)
	{
		t += 0.0015;
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
	glutCreateWindow("BasketBallz");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);

	init();

	glutMainLoop();
}