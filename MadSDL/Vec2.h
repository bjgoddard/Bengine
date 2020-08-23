#pragma once

class Vec2
{
public:
	float X, Y;
public:
	Vec2(float x = 0, float y = 0) : X(x), Y(y) {};

	
	inline Vec2 operator+(const Vec2& v2) const
	{
		return Vec2(X + v2.X, Y + v2.Y);
	}
	
	inline Vec2 operator-(const Vec2& v2) const
	{
		return Vec2(X - v2.X, Y - v2.Y);
	}
	inline Vec2 operator*(const float scalar) const
	{
		return Vec2(X * scalar, Y * scalar);
	}

};
