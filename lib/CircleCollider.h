#pragma once
#include "Collider.h"
class CircleCollider :public Collider
{	
public:
	CircleCollider(float _fRadius, Vec2 _vPosition);
	virtual bool collides(Collider& other) ;
	virtual bool collides(const Vec2& circlePos, float circleRadius) ;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) ;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
		const uint8_t* pixels);
	float fRadius;
	Vec2 vPosition;
};

