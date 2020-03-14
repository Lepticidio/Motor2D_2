#pragma once
#include "Vec2.h";


enum CollisionType
{
	COLLISION_NONE,
	COLLISION_CIRCLE,
	COLLISION_RECT,
	COLLISION_PIXELS
};
class Collider abstract
{
public:
	virtual bool collides(Collider& other);
	virtual bool collides(const Vec2& circlePos, float circleRadius);
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize);
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
		const uint8_t* pixels);
	bool checkCircleCircle(const Vec2& pos1, float radius1,
		const Vec2& pos2, float radius2);
	bool checkCircleRect(const Vec2& circlePos, float circleRadius,
		const Vec2& rectPos, const Vec2& rectSize);
	bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1,
		const Vec2& rectPos2, const Vec2& rectSize2);
	bool checkCirclePixels(const Vec2& circlePos, float circleRadius,
		const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels);
	bool checkPixelsPixels(
		const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1,
		const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2);
	bool checkPixelsRect(
		const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels,
		const Vec2& rectPos, const Vec2& rectSize);
	CollisionType type;

};

