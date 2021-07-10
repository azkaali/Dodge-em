//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

//AZKA ALI
//19I-0597
//Project Phase 1
//Submitted on 4th December,2019

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
int glox1=40,gloy1=140,glox2=40,gloy2=40;
int r,c,score,life=3,level=0,l,w;
int food[1000]={0},count1=0,j;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;
void gameover(){
// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	DrawString( 300, 400, "GAME OVER. You crashed 3 times", colors[MISTY_ROSE]);
	// calling some functions from util.cpp file to help students
	glutSwapBuffers();

}
void menu(){
glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
        DrawString( 300, 400, "DODGE 'EM", colors[MISTY_ROSE]);
        DrawString( 300, 300, "press S to start Dodge 'em", colors[MISTY_ROSE]);
        glutSwapBuffers();
}
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
        //Display Score
        string scr=to_string(score);
        string lif=to_string(life);
	DrawString( 40, 900, "Score=", colors[MISTY_ROSE]);
        DrawString( 200, 900, scr, colors[MISTY_ROSE]);
        DrawString( 450, 900, "Life=", colors[MISTY_ROSE]);
        DrawString( 500, 900, lif, colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	// Drawing player car
	float x = glox1; 
	float y = gloy1; 
	float width = 10; 
	float height = 7;
	float* color = colors[BLUE_VIOLET]; 
	float radius = 5.0;
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect

        // Drawing opponent car
	float x1 = glox2; 
	float y1 = gloy2; 
	float width1 = 10; 
	float height1 = 7;
	float* color1 = colors[YELLOW]; 
	float radius1 = 5.0;
	DrawRoundRect(x1,y1,width1,height1,color1,radius1); // bottom left tyre
	DrawRoundRect(x1+width1*3,y1,width1,height1,color1,radius1); // bottom right tyre
	DrawRoundRect(x1+width1*3,y1+height1*4,width1,height1,color1,radius1); // top right tyre
	DrawRoundRect(x1,y1+height1*4,width1,height1,color1,radius1); // top left tyre
	DrawRoundRect(x1, y1+height1*2, width1, height1, color1, radius1/2); // body left rect
	DrawRoundRect(x1+width1, y1+height1, width1*2, height1*3, color1, radius1/2); // body center rect
	DrawRoundRect(x1+width1*3, y1+height1*2, width1, height1, color1, radius1/2); // body right rect


	// Drawing Arena
	int gap_turn = 60;
	int sx = 20;
	int sy = 10;
	int swidth = 800/2 - gap_turn/2; // half width
	int sheight = 10;
	float *scolor = colors[BROWN];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+810, swidth, sheight, scolor); // top left
	DrawRectangle(sx, sy+810, swidth, sheight, scolor); // top right
	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down







count1=0;
for(r=50;r<760;r+=100){
for(c=50;c<760;c+=100){
DrawSquare( r , c ,15,colors[RED]);
}
}

/*if((r+719==glox1||c+85==gloy1)&&food[count1]==0){
food[count1]==1;
score++;
}
if(food[count1]==1){
int negx=r;
int negy=c;
r=-360;
c=-360;
DrawSquare( r , c ,15,colors[RED]);
glutPostRedisplay();
r=negx;
c=negy;
}
else
{
DrawSquare( r , c ,15,colors[RED]);
glutPostRedisplay();
}


for(r=50;r<760;r+=100){
for(c=50;c<760;c+=100){
DrawSquare( r , c ,15,colors[RED]);
}
}


//drawing food
count1=0;
for(l=40, w=60; l<=750; l+=100)
{
if((l==glox1||glox1==l)&&gloy1==140&&w==60)
{
food[count1]=1;
score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;
l=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
//2
count1=0;
for(l=40, w=160; l<=750; l+=100)
{
if((l==glox1||glox1==l)&&gloy1==140&&w==160)
{
food[count1]=1;
//score++;
}
if(food[count1]==1)
{
//int temp=l;
int temp1=w;
//l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
//l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
//3
count1=0;
for(l=40, w=260; l<=750; l+=100)
{
if((l==glox1||glox1==l)&&(gloy1==w||w==gloy1)&&gloy1==240&&w==260)
{
food[count1]=1;
//score++;
}
if(food[count1]==1)
{
//int temp=l;
int temp1=w;
//l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
//l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
//3
count1=0;
for(l=40, w=360; l<=750; l+=100)
{
if((l==glox1||glox1==l)&&gloy1==240&&w==260)
{
food[count1]=1;
//score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;
l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
//4
count1=0;
for(l=40, w=460; l<=750; l+=100)
{
if((l==glox1||glox1==l)&&gloy1==440&&w==460)
{
food[count1]=1;
//score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;
l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
//5
count1=0;
for(l=40, w=560; l<=750; l+=100)
{
if((l==glox1||glox1==l)&&gloy1==540&&w==560)
{
food[count1]=1;
//score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;
l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
//6
count1=0;
for(l=40, w=660; l<=750; l+=100)
{
if((l==glox1||glox1==l)&&gloy1==640&&w==660)
{
food[count1]=1;
//score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;
l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
//7
count1=0;
for(l=40, w=760; l<=750; l+=100)
{
if((l==glox1||glox1==l)&&gloy1==740&&w==760)
{
food[count1]=1;
//score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;
l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
/*count1=0;
for(l=40,w=760; l<750;l+=100)
{
if((l==glox1+20||l==glox1+30)&&w==760&&food[count1]==0)
{
food[count1]=1;
score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;
l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
 
}*/

/*for(l=40,w=240; l<750; l+=100)
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
if((l+20==glox1||l==glox1+30)&&w==60&&food[count1]==0)
{
food[count1]=1;
score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;

l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
for(l=40,w=340; l<750;l+=100)
{
//DrawRectangle( l, w ,10,10,colors[GREEN]); 
if((l+20==glox1||l==glox1+30)&&w==60&&food[count1]==0)
{
food[count1]=1;
score++;
}
if(food[count1]==1)
{
int temp=l;
int temp1=w;

l=-60;
w=-60;
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
l=temp;
w=temp1;
}
else
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
glutPostRedisplay();
}
count1++;
}
for(l=40,w=440; l<750;l+=100)
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
}
for(l=40,w=540; l<750;l+=100)
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
}
for(l=40,w=640; l<750;l+=100)
{
DrawRectangle( l, w ,10,10,colors[GREEN]); 
}
count1=0;
for(l=40,w=140; l<750;l+=100)
{
DrawRectangle( l, w ,10,10,colors[GREEN]);

}*/




        // Drawing Arena
	int gap_turn1 = 60;
	int sx1 = 120;
	int sy1 = 110;
	int swidth1 = 600/2 - gap_turn1/2; // half width
	int sheight1 = 10;
	float *scolor1 = colors[BROWN];
	DrawRectangle(sx1, sy1, swidth1, sheight1, scolor1); // bottom left
	DrawRectangle(sx1 + swidth1 + gap_turn1, sy1, swidth1, sheight1, scolor1); // bottom right
	DrawRectangle(sx1+swidth1*1.98+gap_turn1, sy1+sheight1, sheight1*1.98, swidth1, scolor1); // right down
	DrawRectangle(sx1+swidth1*1.98+gap_turn1, sy1+sheight1+swidth1+gap_turn1, sheight1*1.98, swidth1, scolor1); // right up
	DrawRectangle(sx1 + swidth1 + gap_turn1, sy1+600, swidth1, sheight1, scolor1); // top left
	DrawRectangle(sx1, sy1+600, swidth1, sheight1, scolor1); // top right
	DrawRectangle(sx1-sheight1*1.98, sy1+sheight1+swidth1+gap_turn1, sheight1*1.98, swidth1, scolor1); // left up
	DrawRectangle(sx1-sheight1*1.98, sy1+sheight1, sheight1*1.98, swidth1, scolor1); // left down

        // Drawing Arena
	int gap_turn2 = 60;
	int sx2 = 220;
	int sy2 = 210;
	int swidth2 = 400/2 - gap_turn2/2; // half width
	int sheight2 = 10;
	float *scolor2 = colors[BROWN];
	DrawRectangle(sx2, sy2, swidth2, sheight2, scolor2); // bottom left
    
	DrawRectangle(sx2 + swidth2 + gap_turn2, sy2, swidth2, sheight2, scolor2); // bottom right
        
	DrawRectangle(sx2+swidth2*1.96+gap_turn2, sy2+sheight2, sheight2*1.96, swidth2, scolor2); // right down

	DrawRectangle(sx2+swidth2*1.96+gap_turn2, sy2+sheight2+swidth2+gap_turn2, sheight2*1.96, swidth2, scolor2); // right up

	DrawRectangle(sx2 + swidth2 + gap_turn2, sy2+390, swidth2, sheight2, scolor2); // top left

	DrawRectangle(sx2, sy2+ 390, swidth2, sheight2, scolor2); // top right

	DrawRectangle(sx2-sheight2, sy2+sheight2+swidth2+gap_turn2, sheight2, swidth2, scolor2); // left up

	DrawRectangle(sx2-sheight2, sy2+sheight2, sheight2, swidth2, scolor2); // left down


        // Drawing Arena
	int gap_turn3 = 60;
	int sx3 = 320;
	int sy3 = 310;
	int swidth3 = 200/2 - gap_turn3/2; // half width
	int sheight3 = 10;
	float *scolor3 = colors[BROWN];
	DrawRectangle(sx3, sy3, swidth3, sheight3, scolor3); // bottom left
	DrawRectangle(sx3 + swidth3 + gap_turn3, sy3, swidth3, sheight3, scolor3); // bottom right
	DrawRectangle(sx3+swidth3*2+gap_turn3, sy3+sheight3, sheight3*2, swidth3, scolor3); // right down
	DrawRectangle(sx3+swidth3*2+gap_turn3, sy3+sheight3+swidth3+gap_turn3, sheight3*2, swidth3, scolor3); // right up
	DrawRectangle(sx3 + swidth3 + gap_turn3, sy3+200, swidth3, sheight3, scolor3); // top left
	DrawRectangle(sx3, sy3+200, swidth3, sheight3, scolor3); // top right
	DrawRectangle(sx3-sheight3, sy3+sheight3+swidth3+gap_turn3, sheight3*2, swidth3, scolor3); // left up
	DrawRectangle(sx3-sheight3*2, sy3+sheight3, sheight3*2, swidth3, scolor3); // left down
//Collision Detection
if(glox2==glox1+30||glox2+30==glox1)
{
score=0;
life--;
glox1=40;
gloy1=140;
}




	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
if(gloy1==400&&glox1<=750&&glox1>40)
{
glox1=glox1-10;
}


		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
if(gloy1==400&&glox1>=40&&glox1<750)
{
glox1=glox1+10;
}

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
if(glox1==400&&gloy1>=40)
{
gloy1=gloy1+10;
}

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
if(glox1==400&&gloy1<=750&&gloy1>40)
{
gloy1=gloy1-10;
}

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 's' || key == 'S')
			{
		//do something if b is pressed
		cout << "b pressed" << endl;
                level=1;
	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {
	// implement your functionality here
//player car
if(gloy1==40&&glox1<=750)
{
glox1+=10;
glutPostRedisplay();
}
if(glox1==750&&gloy1<=750)
{
gloy1+=10;
glutPostRedisplay();
}
if(glox1>=40&&gloy1==750)
{
glox1-=10;
glutPostRedisplay();
}
if(glox1==40&&gloy1>=40)
{
gloy1-=10;
glutPostRedisplay();
}
//if(gloy1>370&&gloy1<430)
//{
//glox1=glox1-60;
//}
//for inner maze
if(gloy1<=650&&gloy1>=150&&glox1==140)
{
gloy1+=10;
glutPostRedisplay();
}
if(gloy1==650&&glox1<=650&&glox1>=140)
{
glox1+=10;
glutPostRedisplay();
}
if(glox1<=650&&glox1>=150&&gloy1==150)
{
glox1-=10;
glutPostRedisplay();
}
if(glox1==650&&gloy1>=150&&gloy1<=650)
{
gloy1-=10;
glutPostRedisplay();
}
//for innermost maze
if(gloy1<=550&&gloy1>=250&&glox1==240)
{
gloy1+=10;
glutPostRedisplay();
}
if(gloy1==550&&glox1<=550&&glox1>=240)
{
glox1+=10;
glutPostRedisplay();
}
if(glox1<=550&&glox1>=250&&gloy1==250)
{
glox1-=10;
glutPostRedisplay();
}
if(glox1==550&&gloy1>=250&&gloy1<=550)
{
gloy1-=10;
glutPostRedisplay();
}
//for centremost maze
if(gloy1<=450&&gloy1>=350&&glox1==340)
{
gloy1+=10;
glutPostRedisplay();
}
if(gloy1==450&&glox1<=450&&glox1>=340)
{
glox1+=10;
glutPostRedisplay();
}
if(glox1<=450&&glox1>=350&&gloy1==350)
{
glox1-=10;
glutPostRedisplay();
}
if(glox1==450&&gloy1>=350&&gloy1<=450)
{
gloy1-=10;
glutPostRedisplay();
}


//for opponent car
if(gloy2<=750&&glox2==40)
{
gloy2+=10;
glutPostRedisplay();
}
if(gloy2==750&&glox2<=750)
{
glox2+=10;
glutPostRedisplay();
}
if(glox2<=750&&gloy2==40)
{
glox2-=10;
glutPostRedisplay();
}
if(glox2==750&&gloy2>=40)
{
gloy2-=10;
glutPostRedisplay();
}
if(level==1&&life>0){
glutDisplayFunc(GameDisplay);
}
if(life==0){
glutDisplayFunc(gameover);
}

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(30.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 940, height = 940; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Centipede"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(menu); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
