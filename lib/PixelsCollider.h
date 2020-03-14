#pragma once
#include "Collider.h"
class PixelsCollider :public Collider
{
public:
	PixelsCollider(Vec2 _vSize, Vec2 _vPosition, uint8_t* _pixels);
	virtual bool collides(Collider& other);
	virtual bool collides(const Vec2& circlePos, float circleRadius);
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize);
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
		const uint8_t* pixels);
	Vec2 vSize;
	Vec2 vPosition;
	const uint8_t* m_pixels;
};

