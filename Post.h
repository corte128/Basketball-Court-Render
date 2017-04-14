//
//  post.h
//  Assignment3_2_2
//
//  Created by Patrick  Lin on 1/24/17.
//  Copyright © 2017 Patrick  Lin. All rights reserved.
//
#ifndef post_h
#define post_h

#include <GL/glut.h>

class Post
{
public:
    //default constructor
    Post(float x, float z, float angle);

    //member functions for drawing the post

    void drawAll(void);
    bool ballIn(float ball_x, float ball_y, float ball_z);

    float shear = -0.1;
    bool goleft = false;

private:
    void initializeNet();

    void drawNet(void);
    void drawBoard(void);
    void drawBridge(void);
    void drawPost(void);

    float angle; //angle post is rotated
    float x, z; //location of post

    //parameters of the hoop and net
    float hoop_height = 120.0/12.0;
    float hoop_diameter = 18.0/12.0;
    float net_top_y = 0.0, net_height = 1.6;

    //parameters of the board
    float board_width = 72.0/12.0;
    float board_height = 48.0/12.0;
    float boardPos_front = -1.0, boardPos_back = -1.5;
    float inner_rect_height = 18.0/12.0;
    float inner_rect_width = 24.0/12.0;

    //parameters of the bridge
    float bridge_width = 0.2;
    float bridge_depth = boardPos_front;

    //parameters of the post
    float post_width = 2.0;
    float post_top_length = 6.0;
    float post_height = 10.0;

    //vertices of board
    float board_1[3] = {board_width/2, -1.0, boardPos_front};
    float board_2[3] = {board_width/2, -1.0, boardPos_back};
    float board_3[3] = {-board_width/2, -1.0, boardPos_front};
    float board_4[3] = {-board_width/2, -1.0, boardPos_back};
    float board_5[3] = {-board_width/2, board_height, boardPos_front};
    float board_6[3] = {-board_width/2, board_height, boardPos_back};
    float board_7[3] = {board_width/2,  board_height, boardPos_front};
    float board_8[3] = {board_width/2,  board_height, boardPos_back};

    //vertices of inner board
    float inRect_1[3] = {inner_rect_width/2, 0.0, boardPos_front};
    float inRect_2[3] = {-inner_rect_width/2, 0.0, boardPos_front};
    float inRect_4[3] = {-inner_rect_width/2, inner_rect_height, boardPos_front};
    float inRect_3[3] = {inner_rect_width/2, inner_rect_height, boardPos_front};

    //vertices of bridge
    float bridge_1[3], bridge_2[3], bridge_4[3], bridge_3[3];

    //vertices of post
    float post_4[3] = {post_width/2, 0, boardPos_back};
    float post_3[3] = {-post_width/2, 0, boardPos_back};
    float post_1[3] = {-post_width/2, -post_width/2, boardPos_back};
    float post_2[3] = {post_width/2, -post_width/ 2, boardPos_back};
    float post_5[3] = {post_width/2, 0, -post_top_length};
    float post_6[3] = {-post_width/2, 0, -post_top_length};
    float post_11[3] = {-post_width/2, -post_width/ 2, -post_top_length + post_width/2};
    float post_12[3] = {post_width/2, -post_width/ 2, -post_top_length + post_width/2};
    float post_7[3] = {post_width/2, -10, -post_top_length};
    float post_8[3] = {-post_width/2, -10, -post_top_length};
    float post_10[3] = {post_width/2, -10, -post_top_length + post_width/2};
    float post_9[3] = {-post_width/2, -10, -post_top_length + post_width/2};

    float rot_angle;
    float netCoord[90][3];
    float netCoordExp[90][3];

    float box_x_min = -0.2, box_x_max = 0.2;
    float box_y_min = 0.1, box_y_max = 0.2;
    float box_z_min = -0.2, box_z_max = 0.2;
};


#endif
