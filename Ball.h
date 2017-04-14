/*
 * Ball.h
 *
 *  Created on: Jan 24, 2017
 *      Author: William
 */

#include "Post.h"
#ifndef BALL_H
#define BALL_H

class Ball
{
public:
	Ball(float* direction, float* pos, float radius, GLint texture, Post* front);
	float getX();
	float getY();
	float getZ();
	void moveBall();
	void renderBall();
	void dropStraight();
	void rotateBall();

private:
	Post* front;
	GLint texture;
	float vel[3];
	float pos[3];
	float rotationDirection[3];
	float radius;
	float angle;
};
#endif
