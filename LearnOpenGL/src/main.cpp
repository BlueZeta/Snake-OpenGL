#include <GL/glut.h>
#include <GL/GL.h>
#include <iostream>
#include "game.h"
#include <stdlib.h>

extern short snake_dir;
extern int score;

void display_callback();
void reshape_callback(int w, int h);
void init();
void timer_callback(int);
void keyboard_callback(int, int, int);

const int columns = 40;
const int rows = 40;
const int frames = 10;
int index = 0;
bool gameover = false;

int main(int argc, char **argv)
{
	// init glut
	glutInit(&argc, argv);
	// set the initial display mode to RGB
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(500, 500);
	glutCreateWindow("Snake");
	glutReshapeFunc(reshape_callback);
	glutDisplayFunc(display_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutSpecialFunc(keyboard_callback);
	
	init();
	glutMainLoop();
	return 0;
}

void init()
{
	// make everything black
	glClearColor(0.0,0.0,0.0,0.0);
	// init the grids
	initGrid(columns, rows);
}

void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,columns,0.0,rows,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawSnake();
	drawFood();
	glutSwapBuffers();
	if (gameover)
	{
		char _score[10];
		_itoa_s(score, _score, 10);
		char text[50] = "Your score: ";
		strcat_s(text, _score);
		MessageBox(NULL, text, "GAME OVER", 0);
		exit(0);
	}
}

void timer_callback(int)
{
	// call display function as soon as possible
	glutPostRedisplay();
	// 1000 milliseconds = 1 seconds
	glutTimerFunc(1000 / frames, timer_callback, 0);
}

void keyboard_callback(int key, int, int)
{
	switch (key) 
	{
		case GLUT_KEY_UP:
			snake_dir = up;
			break;
		case GLUT_KEY_DOWN:
			snake_dir = down;
			break;
		case GLUT_KEY_RIGHT:
			snake_dir = right;
			break;
		case GLUT_KEY_LEFT:
			snake_dir = left;
			break;
	}
}