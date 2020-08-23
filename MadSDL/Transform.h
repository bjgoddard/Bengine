#pragma once
#include "Vec2.h"
class Transform
{
public:
	float X, Y;
	Transform(float x=0, float y=0) : X(x), Y(y) {}

public:
	inline void TranslateX(float x) { X += x; }
	inline void TranslateY(float y) { Y += y; }
	inline void Translate(Vec2 v) { X += v.X; Y += v.Y; }

};