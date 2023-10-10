#include "Pipe.h"
#include <cmath>
#include <GL/glut.h>

Pipe::Pipe()
{
	x = 1400;
	y = 200;
	w = 50;
}

bool Pipe::isOverlapping(double x, double y, int r)
{
	//Calculate Distance between points
	double distance = std::sqrt(std::pow(x - this->x, 2) + std::pow(y - this->y, 2));

	// Check if the distance is less than the sum of the radii
	return (distance < r) ? true : false;
}

void Pipe::Draw()
{
	glPushMatrix();

	glColor3f(0, 195, 0);

	glBegin(GL_QUADS);
	glVertex2d(x, y);
	glVertex2d(x, 0);
	glVertex2d(x + w, 0);
	glVertex2d(x + w, y);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2d(x - w / 2, 100);
	glVertex2d(x - w / 2, 0);
	glVertex2d(x, 0);
	glVertex2d(x, 100);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2d(x + w / 2, 300);
	glVertex2d(x + w / 2, 0);
	glVertex2d(x, 0);
	glVertex2d(x, 300);
	glEnd();

	glPopMatrix();
}