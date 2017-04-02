#pragma once
#include <GL/glew.h>
#include <tuple>

#define PI 3.141592f
using namespace std;

class Sprite
{
public:
	Sprite();
	~Sprite();
	void init(float x, float y, float w, float h);
	void moveBy(float x, float y);
	tuple<float, float> returnCoords();
	void updateCoords(float x, float y);
	void updateVertex();
	void draw();

protected:
	float _x;
	float _y;
	float _w;
	float _h;
	GLuint _vboID;
};

class Ball : public Sprite
{
public:
	void move();
	float returnAngle();
	float _angle = 0.75f;
};
