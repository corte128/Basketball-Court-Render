/*
 * Post.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Patrick
 */

#include <GL/glut.h>
#include "Math.h"
#include "Post.h"


//default constructor, left empty
Post::Post(float x, float z, float angle)
{
	this->x = x;
	this->z = z;
	this->angle = angle;
	this->rot_angle = 0;

    box_x_min += (50 + x);
    box_x_max += (50 + x);
    box_y_min += 10;
    box_y_max += 10;
    box_z_min += (z - 10);
    box_z_max += (z - 10);
}

bool Post::ballIn(float ball_x, float ball_y, float ball_z)
{
	if((box_x_min < ball_x && ball_x < box_x_max) && (box_y_min < ball_y && ball_y < box_y_max) && (box_z_min < ball_z && ball_z < box_z_max))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//funciton to draw the net
void Post::drawNet(void)
{

	float tempX = 0.0;

    GLfloat m[16] =
    {
        1.0f, 0.0f, 0.0f, -shear*tempX,
        shear, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.753, 0.753, 0.753);
    glPushMatrix();                                        //scale down the hoop to fit the board
    glMultMatrixf(m);
    for(int i = 0; i < 18; ++i)                                     //draw vertical lines of net
    {
        glRotatef(20.0, 0, 1, 0);                                   //rotate about y-xis by 10 degrees to draw the next line
        glBegin(GL_LINE_STRIP);
			for(float y = -net_height; y < net_top_y + 0.2; y += 0.2)   //draw vertical line by points with GL_LINE_STRIP
			{
				glVertex3f((pow(2, y) + 0.5)*0.5, y, 0);                      //line path follows exponential function
			}

        glEnd();
    }

    for(float j = -net_height; j < net_top_y + 0.2; j += 0.4)       //draw horizontal loops of net, bottom to top
    {
        float r = (pow(2, j) + 0.5)*0.5;                                  //radius of each loop
        glBegin(GL_LINE_STRIP);
			for(float theta = 0; theta < 360; theta += 0.01)            //draw 1 point every 5 degrees
			{
			   float incX = r * cos(theta);                            //x of point, from current radius
			   float incZ = r * sin(theta);                            //z of point, from current radius
			   glVertex3f(incX, j, incZ);

			}
		glEnd();
    }
    glPopMatrix();
                                     //reset scale for following draws
}





//function to draw backboard
void Post::drawBoard(void)
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(1.0, 1.0, 1.0);

    //draw backboard
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.0, 2.0);

    glBegin(GL_QUADS);
		glVertex3fv(board_1);   glVertex3fv(board_2);   glVertex3fv(board_4);   glVertex3fv(board_3);
		glVertex3fv(board_1);   glVertex3fv(board_2);   glVertex3fv(board_8);   glVertex3fv(board_7);
		glVertex3fv(board_3);   glVertex3fv(board_4);   glVertex3fv(board_6);   glVertex3fv(board_5);
		glVertex3fv(board_1);   glVertex3fv(board_3);   glVertex3fv(board_5);   glVertex3fv(board_7);
		glVertex3fv(board_2);   glVertex3fv(board_4);   glVertex3fv(board_6);   glVertex3fv(board_8);
		glVertex3fv(board_5);   glVertex3fv(board_6);   glVertex3fv(board_8);   glVertex3fv(board_7);
    glEnd();


    //draw innter rectangle of backboard
    glBegin(GL_QUAD_STRIP);
    	glVertex3fv(inRect_1);  glVertex3fv(inRect_2);  glVertex3fv(inRect_3);  glVertex3fv(inRect_4);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor3f(1.0, 0.0, 0.0);


    glBegin(GL_QUAD_STRIP);
		glVertex3fv(board_1);   glVertex3fv(board_2);   glVertex3fv(board_3);   glVertex3fv(board_4);
		glVertex3fv(board_5);   glVertex3fv(board_6);   glVertex3fv(board_7);   glVertex3fv(board_8);
		glVertex3fv(board_1);   glVertex3fv(board_2);
    glEnd();

    glBegin(GL_QUADS);
    	glVertex3fv(inRect_1);  glVertex3fv(inRect_2);  glVertex3fv(inRect_4);  glVertex3fv(inRect_3);
    glEnd();
}

//function to draw the bridge between hoop and board
void Post::drawBridge(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(1.0, 0.549, 0.0);

    //bridge vertices
    bridge_1[0] = bridge_width/2; bridge_1[1] = 0.0; bridge_1[2] = bridge_depth;
    bridge_2[0] = bridge_width/2; bridge_2[1] = 0.0; bridge_2[2] = -0.75;
    bridge_4[0] = -bridge_width/2; bridge_4[1] = 0.0; bridge_4[2] = -0.75;
    bridge_3[0] = -bridge_width/2; bridge_3[1] = 0.0; bridge_3[2] = bridge_depth;

    //draw bridge
    glBegin(GL_QUAD_STRIP);
    	glVertex3fv(bridge_1);  glVertex3fv(bridge_2);  glVertex3fv(bridge_3);  glVertex3fv(bridge_4);
    glEnd();
}


//function to draw the post
void Post::drawPost(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glScalef(0.5, 1.0, 1.0);

    glBegin(GL_QUADS);
		glVertex3fv(post_1);    glVertex3fv(post_2);    glVertex3fv(post_4);    glVertex3fv(post_3);
		glVertex3fv(post_4);    glVertex3fv(post_2);    glVertex3fv(post_12);   glVertex3fv(post_5);
		glVertex3fv(post_3);    glVertex3fv(post_1);    glVertex3fv(post_11);   glVertex3fv(post_6);
		glVertex3fv(post_5);    glVertex3fv(post_6);    glVertex3fv(post_8);    glVertex3fv(post_7);
		glVertex3fv(post_6);    glVertex3fv(post_8);    glVertex3fv(post_9);    glVertex3fv(post_11);
		glVertex3fv(post_5);    glVertex3fv(post_7);    glVertex3fv(post_10);   glVertex3fv(post_12);
		glVertex3fv(post_7);    glVertex3fv(post_8);    glVertex3fv(post_9);    glVertex3fv(post_10);
		glVertex3fv(post_9);    glVertex3fv(post_10);   glVertex3fv(post_12);   glVertex3fv(post_11);
		glVertex3fv(post_11);   glVertex3fv(post_12);   glVertex3fv(post_2);    glVertex3fv(post_1);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.753, 0.753, 0.753);

    glBegin(GL_QUAD_STRIP);
		glVertex3fv(post_1);    glVertex3fv(post_2);    glVertex3fv(post_3);    glVertex3fv(post_4);
		glVertex3fv(post_5);    glVertex3fv(post_6);    glVertex3fv(post_7);    glVertex3fv(post_8);
		glVertex3fv(post_9);    glVertex3fv(post_10);    glVertex3fv(post_11);    glVertex3fv(post_12);
		glVertex3fv(post_1);    glVertex3fv(post_2);
    glEnd();
    glPopMatrix();
}


//function to draw all components
void Post::drawAll(void)
{

    glPushMatrix();
    glTranslatef(x+50, 10, z - 10);
    glRotatef(angle, 0, 1, 0);
    drawNet();
    drawBoard();
    drawBridge();
    drawPost();
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
