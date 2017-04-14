/*
 * Ball.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: William
 */

#include <GL/glut.h>
#include "Ball.h"
#include "Post.h"

Ball::Ball(float* direction, float* pos,  float radius, GLint texture, Post* front)
{
	this->rotationDirection[0] = direction[0];
	this->rotationDirection[1] = direction[1];
	this->rotationDirection[2] = direction[2];
	this->vel[0] = direction[0];
	this->vel[1] = direction[1];
	this->vel[2] = direction[2];

	for(int i = 0;i < 3;++i)
	{
		vel[i] *= 7;
	}

	this->radius = radius;
	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	this->pos[2] = pos[2];
	this->texture = texture;
	this->front = front;
	this->angle = 0;
}
void Ball::moveBall()
{
	pos[0] += vel[0]/2;
	pos[1] += vel[1]/2;
	pos[2] += vel[2]/2;


	//boundary detection
	if((pos[0] >= 75 || pos[0] <= 25) && pos[1] <= 20)
	{
		vel[0] = -vel[0];
	}
	if((pos[2] >= 97 || pos[2] <= 3) && pos[1] <= 20)
	{
		vel[2] = -vel[2];
	}
	if(pos[1] <= 0)
	{
		vel[1] = -vel[1];
	}
	else
	{
		//apply gravity
		vel[1] -= 9.8/20;
	}



}
void Ball::renderBall()
{
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	//glRotatef(angle, rotationDirection[0], 0, rotationDirection[2]);
	glRotatef(90, 0, 0, 1);

	glBindTexture(GL_TEXTURE_2D, texture); //bind passed in texture to ball and render it
	glEnable(GL_TEXTURE_2D);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	/*
	if(front->ballIn(pos[0], pos[1], pos[2]))
	{
		dropStraight();
	}
	*/

	gluSphere(sphere, radius, 20, 20);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void Ball::dropStraight()
{
	vel[0] = 0;
	vel[2] = 0;
}
void Ball::rotateBall()
{
	angle += 1;
}
