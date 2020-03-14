#include "RectCollider.h"

RectCollider::RectCollider(Vec2 _vSize, Vec2 _vPosition) : vSize(_vSize), vPosition(_vPosition)
{
	type = COLLISION_RECT;
}
bool RectCollider::collides(Collider& other)
{
	return false;
}
bool RectCollider::collides(const Vec2& circlePos, float circleRadius)
{
	return checkCircleRect(circlePos, circleRadius, vPosition, vSize);
}
bool RectCollider::collides(const Vec2& rectPos, const Vec2& rectSize)
{
	return checkRectRect(vPosition, vSize, rectPos, rectSize);
}
bool RectCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
	const uint8_t* pixels)
{
	return checkPixelsRect(pixelsPos, pixelsSize, pixels, vPosition, vSize);
}
