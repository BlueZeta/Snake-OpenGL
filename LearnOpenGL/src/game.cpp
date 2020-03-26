#include <GL/glut.h>
#include <GL/GL.h>
#include "game.h"
#include <time.h>

int grid_x, grid_y;
int foodX, foodY;
short snake_dir = right;
extern bool gameover;
bool food = true;
int snake_len = 5;
int score = 0;
int posX[max] = { 20,20,20,20,20 }, posY[max] = {20,19,18,17,16};

void initGrid(int x, int y)
{
	grid_x = x;
	grid_y = y;
}

void drawGrid()
{
	int x, y;
	for (x = 0; x < grid_x; x++)
	{
		for (y = 0; y < grid_y; y++)
		{
			unit(x, y);
		}
	}
}

void unit(int x, int y)
{
	if (x == 0 || y == 0 || x == grid_x - 1 || y == grid_y - 1)
	{
		glLineWidth(1.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	else
	{
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}
	
	glBegin(GL_LINE_LOOP);
	glVertex2f((GLfloat)x, (GLfloat)y);
	glVertex2f((GLfloat)(x+1), (GLfloat)y);
	glVertex2f((GLfloat)(x+1), (GLfloat)(y+1));
	glVertex2f((GLfloat)x, (GLfloat)(y+1));
	glEnd();
}

void drawFood()
{
	if (food)
		random(foodX, foodY);
	food = false;
	glColor3f(0.0, 1.0, 0.0);
	glRectf((GLfloat)foodX, (GLfloat)foodY, (GLfloat)(foodX + 1), (GLfloat)(foodY + 1));
}

void drawSnake()
{
	int i;
	for (i = snake_len - 1; i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}
	if (snake_dir == up)
		posY[0]++;
	else if (snake_dir == down)
		posY[0]--;
	else if (snake_dir == right)
		posX[0]++;
	else if (snake_dir == left)
		posX[0]--;
	for (i = 0; i < snake_len; i++)
	{
		if (i == 0)
			glColor3f(1.0, 0.0, 0.0);
		else
			glColor3f(0.0, 0.0, 1.0);
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
	}

	if (posX[0] == 0 || posX[0] == grid_x - 1 || posY[0] == 0 || posY[0] == grid_y - 1)
		gameover = true;
	if (posX[0] == foodX && posY[0] == foodY)
	{
		score++;
		snake_len++;
		if (snake_len > max)
			snake_len = max;
		food = true;
	}
}

void random(int &x, int &y)
{
	int maxX = grid_x - 2;
	int maxY = grid_y - 2;
	int min = 1;
	srand(time(NULL));
	x = min + rand() % (maxX - min);
	y = min + rand() % (maxY - min);
}