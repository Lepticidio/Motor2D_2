#pragma once
#include "Collider.h"
class RectCollider:public Collider
{
public:
	RectCollider(Vec2 _vSize, Vec2 _vPosition);
	virtual bool collides(Collider& other);
	virtual bool collides(const Vec2& circlePos, float circleRadius);
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize);
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
		const uint8_t* pixels);
	Vec2 vSize;
	Vec2 vPosition;
};

