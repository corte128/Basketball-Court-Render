/*
 * main.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: William
 */


#include <GL/glut.h>
#include "Ball.h"
#include <list>
#include "Math.h"
#include "imageloader.h"
#include "Post.h"

double width = 1500, height = 900;
float* view = new float[3];  //position the camera views
float* pos = new float[3];  //position of the camera
Post* frontPost = new Post(0, 96, 180);
Post* backPost = new Post(0, 24, 0);

float theta = 0;
std::list<Ball> balls;

GLfloat light_position[] = {50, 39, 50, 1}; //position of the light

void throwBall(int, int, int, int);
void lookAround(int, int);
void moveAround(unsigned char, int, int);
void renderCourt();
void destroyBall(int);
void moveBalls(int);
void swayNet();
GLint basketballTexture, sideTexture, courtTexture, skyTexture;
GLint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					 GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image->width, image->height,
				   GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}
void loadTextures()
{
	Image* basketBall = loadBMP("basketball5.bmp");
	basketballTexture = loadTexture(basketBall);

	Image* side = loadBMP("brickWall4.bmp");
	sideTexture = loadTexture(side);

	Image* court = loadBMP("court4.bmp");
	courtTexture = loadTexture(court);

	Image* sky = loadBMP("sky.bmp");
	skyTexture = loadTexture(sky);
}
void initLighting()
{
	//GLfloat mat_specular[] = {1, 1, 1, 1};
	//GLfloat mat_shininess[] = {0.01};
	GLfloat light_diffuse[] = {1, 1, 1, 1};

	glShadeModel (GL_SMOOTH);

	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}
void init()
{
	view[0] = 0; view[1] = 0; view[2] = 1;
	pos[0] = 50; pos[1] = 5; pos[2] = 50;
	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90, width/height, -100, 100);
	gluPerspective(90, width/height, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos[0], pos[1], pos[2], view[0] + pos[0], view[1] + pos[1], view[2] + pos[2], 0, 1, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GL_DOUBLE | GL_RGB | GL_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Basketball Court");

	init();
	loadTextures();

	//glutIdleFunc(swayNet);
	glutDisplayFunc(renderCourt);
	glutMouseFunc(throwBall);
	glutKeyboardFunc(moveAround);
	glutTimerFunc(50, moveBalls, 0);
	glutPassiveMotionFunc(lookAround);
	glutMainLoop();
}
void moveAround(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'a': //strafe left
		pos[0] += sin(theta + (M_PI/2));
		pos[2] += cos(theta + (M_PI/2));
		break;
	case 'd': //strafe right
		pos[0] += sin(theta - (M_PI/2));
		pos[2] += cos(theta - (M_PI/2));
		break;
	case 's': //move back
		pos[0] -= sin(theta);
		pos[2] -= cos(theta);
		break;
	case 'w': //move forward
		pos[0] += sin(theta);
		pos[2] += cos(theta);
		break;
	case 'e':
		exit(0);
	}
	glLoadIdentity();
	gluLookAt(pos[0], pos[1], pos[2], view[0] + pos[0], view[1] + pos[1], view[2] + pos[2], 0, 1, 0);
}
void lookAround(int x, int y)
{
	static float phi = 0;

	static float centerX = width/2;
	static float centerY = height/2;

	theta -= (x - centerX)/40;

	phi -= (y - centerY)/40;

	if(phi >= (M_PI/2))
		phi = (M_PI/2) - 0.1;
	else if(phi <= -(M_PI/2))
		phi = -(M_PI/2) + 0.1;


	view[1] = sin(phi);
	double cosOfPhi = cos(phi);
	view[0] = cosOfPhi*sin(theta);
	view[2] = cosOfPhi*cos(theta);
	glLoadIdentity();
	gluLookAt(pos[0], pos[1], pos[2], view[0] + pos[0], view[1] + pos[1], view[2] + pos[2], 0, 1, 0);


}
void throwBall(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		balls.push_back(Ball(view, pos, 2.8/(2*M_PI), basketballTexture, frontPost));
		glutTimerFunc(5000, destroyBall, 0);
	}
}
void renderCourt()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);

	for(std::list<Ball>::iterator i = balls.begin();i != balls.end(); ++i)
	{
		i->renderBall();
	}

	glBindTexture(GL_TEXTURE_2D, sideTexture);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(2, 2); glVertex3f(75, 20, 97);
		glTexCoord2f(2, 0); glVertex3f(75, 0, 97);
		glTexCoord2f(0, 0); glVertex3f(25, 0, 97);
		glTexCoord2f(0, 2); glVertex3f(25, 20, 97);

		glTexCoord2f(2, 2); glVertex3f(75, 20, 3);
		glTexCoord2f(2, 0); glVertex3f(75, 0, 3);
		glTexCoord2f(0, 0); glVertex3f(25, 0, 3);
		glTexCoord2f(0,	2); glVertex3f(25, 20, 3);

		glTexCoord2f(4, 0); glVertex3f(25, 0, 97);
		glTexCoord2f(4, 2); glVertex3f(25, 20, 97);
		glTexCoord2f(0, 2); glVertex3f(25, 20, 3);
		glTexCoord2f(0, 0); glVertex3f(25, 0, 3);

		glTexCoord2f(4, 0); glVertex3f(75, 0, 97);
		glTexCoord2f(4, 2); glVertex3f(75, 20, 97);
		glTexCoord2f(0, 2); glVertex3f(75, 20, 3);
		glTexCoord2f(0, 0); glVertex3f(75, 0, 3);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, courtTexture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(1, 1); glVertex3f(25, 0, 97);
    	glTexCoord2f(1, 0); glVertex3f(75, 0, 97);
    	glTexCoord2f(0, 0); glVertex3f(75, 0, 3);
    	glTexCoord2f(0, 1); glVertex3f(25, 0, 3);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
		glTexCoord2f(1, 1); glVertex3f(-50, 40, 220);
		glTexCoord2f(1, 0); glVertex3f(150, 40, 220);
		glTexCoord2f(0, 0); glVertex3f(150, 40, -120);
		glTexCoord2f(0, 1); glVertex3f(-50, 40, -120);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    frontPost->drawAll();
    backPost->drawAll();
	glutSwapBuffers();
	glutWarpPointer(width/2, height/2);
}
void destroyBall(int value)
{
	balls.pop_front();
}
void moveBalls(int value)
{
	for(std::list<Ball>::iterator i = balls.begin();i != balls.end(); ++i)
	{
		i->moveBall();
	}
	swayNet();
	glutTimerFunc(50, moveBalls, 0);
	glutPostRedisplay();
}

//shear the bottom of the net to create a wind effect acting on the net
void swayNet()
{
    if(frontPost->goleft == false)
    {
        frontPost->shear -= 0.003;
        if(frontPost->shear < -0.1)
        {
            frontPost->goleft = true;
        }
    }

    else if(frontPost->goleft == true)
    {
        frontPost->shear += 0.003;

        if(frontPost->shear > 0.1)
        {
            frontPost->goleft = false;
        }
    }


    if(backPost->goleft == false)
	{
		backPost->shear -= 0.003;
		if(backPost->shear < -0.1)
		{
			backPost->goleft = true;
		}
	}

	else if(backPost->goleft == true)
	{
		backPost->shear += 0.003;
		if(backPost->shear > 0.1)
		{
			backPost->goleft = false;
		}
	}
    glutPostRedisplay();
}
