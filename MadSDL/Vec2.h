#pragma once

class Vec2
{
public:
	float X, Y;
public:
	Vec2(float x = 0.0f, float y = 0.0f) : X(x), Y(y) {};

	
	Vec2 operator+(const Vec2& v2) const
	{
		return Vec2(X + v2.X, Y + v2.Y);
	}
	
	Vec2 operator-(const Vec2& v2) const
	{
		return Vec2(X - v2.X, Y - v2.Y);
	}
	Vec2 operator*(const float scalar) const
	{
		return Vec2(X * scalar, Y * scalar);
	}

	Vec2& Zero() { X = 0.0f, Y = 0.0f; }
};
