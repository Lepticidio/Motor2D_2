#include "PixelsCollider.h"

PixelsCollider::PixelsCollider(Vec2 _vSize, Vec2 _vPosition, uint8_t* _pixels) : vSize(_vSize), vPosition(_vPosition), m_pixels(_pixels)
{
	type = COLLISION_PIXELS;
}
bool PixelsCollider::collides(Collider& other)
{
	return false;
}
bool PixelsCollider::collides(const Vec2& circlePos, float circleRadius)
{
	return checkCirclePixels(circlePos, circleRadius, vPosition, vSize, m_pixels);
}
bool PixelsCollider::collides(const Vec2& rectPos, const Vec2& rectSize)
{
	return checkPixelsRect(vPosition, vSize, m_pixels, rectPos, rectSize);
}
bool PixelsCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
	const uint8_t* pixels)
{
	return checkPixelsPixels(vPosition, vSize, m_pixels, pixelsPos, pixelsSize, pixels);
}

