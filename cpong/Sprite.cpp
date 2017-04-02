#include "Sprite.h"
#include <tuple>
#include <cmath>

#define PI 3.141592f
using namespace std;


Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float w, float h)
{
	_w = w / 640.0f;
	_h = h / 480.0f;
	_x = -1.0f + (x / 320.0f) - _w / 2;
	_y = 1.0f - (y / 240.0f) - _h / 2;
	updateVertex();
}

void Sprite::moveBy(float x, float y)
{
	_x += (x / 320.0f);
	_y += (y / 240.0f);
	updateVertex();
}

tuple<float, float> Sprite::returnCoords()
{
	float x = 320.0f*(1.0f + _w / 2 + _x);
	float y = -240.0f*(-1.0f + _h / 2 + _y);
	return make_tuple(x, y);
}

void Sprite::updateCoords(float x, float y)
{
	_x = -1.0f + (x / 320.0f) - _w / 2;
	_y = 1.0f - (y / 240.0f) - _h / 2;
	updateVertex();
}

void Sprite::updateVertex()
{
	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}
	float vertexData[12];

	vertexData[0] = _x + _w;
	vertexData[1] = _y + _h;

	vertexData[2] = _x;
	vertexData[3] = _y + _h;

	vertexData[4] = _x;
	vertexData[5] = _y;

	vertexData[6] = _x;
	vertexData[7] = _y;

	vertexData[8] = _x + _w;
	vertexData[9] = _y;

	vertexData[10] = _x + _w;
	vertexData[11] = _y + _h;

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Ball::move()
{
	_x += cos(_angle*PI)*sqrt(2.0f)*(0.25f / 320.0f);
	_y += sin(_angle*PI)*sqrt(2.0f)*(0.25f / 240.0f);
	updateVertex();
}

float Ball::returnAngle()
{
	return _angle;
}
