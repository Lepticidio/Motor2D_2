#include "Sprite.h"


unsigned char* generateUCharArray(const int _size)
{
	return new unsigned char[_size];
}
Sprite::Sprite(const ltex_t* tex, int hframes, int vframes)
	:texture(*tex), iHorizontalFrames(hframes), iVerticalFrames(vframes)
{

}
void Sprite::setCallback(CallbackFunc func)
{
	callbackFunc = func;
}
const ltex_t* Sprite::getTexture() const
{
	return &texture;
}
void Sprite::setTexture(const ltex_t* tex, int hframes, int vframes)
{
	texture = *tex;
	iHorizontalFrames = hframes;
	iVerticalFrames = vframes;
}
lblend_t Sprite::getBlend() const
{
	return blend;
}
void Sprite::setBlend(lblend_t mode)
{
	blend = mode;
}
float Sprite::getRed() const
{
	return fRed;
}
float Sprite::getGreen() const
{
	return fGreen;
}
float Sprite::getBlue() const
{
	return fBlue;
}
float Sprite::getAlpha() const
{
	return fAlpha;
}
void Sprite::setColor(float r, float g, float b, float a)
{
	fRed = r;
	fGreen = g;
	fBlue = b;
	fAlpha = a;
}
const Vec2& Sprite::getPosition() const
{
	return vPosition;
}
void Sprite::setPosition(const Vec2& pos)
{
	vPosition = pos;
}
float Sprite::getAngle() const
{
	return fAngle;
}
void Sprite::setAngle(float angle)
{
	fAngle = angle;
}
const Vec2& Sprite::getScale() const
{
	return vScale;
}
void Sprite::setScale(const Vec2& scale)
{
	vScale = scale;
}
Vec2 Sprite::getSize() const
{
	return Vec2(vScale.x * texture.width / iHorizontalFrames, vScale.y * texture.height / iVerticalFrames);
}
const Vec2& Sprite::getPivot() const
{
	return vPivot;
}
void Sprite::setPivot(const Vec2& pivot)
{
	vPivot = pivot;
}
int Sprite::getHframes() const
{
	return iHorizontalFrames;
}
int Sprite::getVframes() const
{
	return iVerticalFrames;
}
int Sprite::getFps() const
{
	return iFps;
}
void Sprite::setFps(int fps)
{
	iFps = fps;
}
float Sprite::getCurrentFrame() const
{
	return iCurrentFrame;
}
void Sprite::setCurrentFrame(int frame)
{
	iCurrentFrame = frame;
}
void Sprite::update(float _deltaTime)
{
	switch (getCollisionType())
	{
	case COLLISION_CIRCLE:
	{
		const Collider* pCollider = getCollider();
		CircleCollider* pCircle = static_cast<CircleCollider*>( const_cast<Collider*>(pCollider));
		pCircle->vPosition = vPosition;
		pCircle->fRadius = getSize().x / 2;
	}
	break;
	case COLLISION_RECT:
	{
		const Collider* pCollider = getCollider();
		RectCollider* pRect = static_cast<RectCollider*>(const_cast<Collider*>(pCollider));
		pRect->vPosition = vPosition;
		pRect->vSize = getSize();
	}
	break;
	case COLLISION_PIXELS:
	{
		const Collider* pCollider = getCollider();
		PixelsCollider* pPixels = static_cast<PixelsCollider*>(const_cast<Collider*>(pCollider));
		pPixels->vPosition = vPosition;
		pPixels->vSize = getSize();
	}
	break;
	default:
	{
	}
	}
	callbackFunc(*this, _deltaTime);
	fcurrentAnimationTime += _deltaTime;
	float fTotalAnimationTime = (iHorizontalFrames * iVerticalFrames) / iFps;
	if (fcurrentAnimationTime > fTotalAnimationTime)
	{
		fcurrentAnimationTime -= fTotalAnimationTime;
	}
	iCurrentFrame = iVerticalFrames*iHorizontalFrames*(fcurrentAnimationTime/ fTotalAnimationTime);
}
void Sprite::draw() const
{
	Vec2 vSize = getSize();
	Vec2 vPositionInArray(iCurrentFrame % iHorizontalFrames, iCurrentFrame / iHorizontalFrames);
	lgfx_setblend(blend);
	lgfx_setcolor(fRed, fGreen, fBlue, fAlpha);
	ltex_drawrotsized(&texture, vPosition.x, vPosition.y, fAngle, vPivot.x, vPivot.y, vSize.x, vSize.y, 
		vPositionInArray.x /(float)iHorizontalFrames, vPositionInArray.y / (float) iVerticalFrames, (vPositionInArray.x + 1.)/(float)iHorizontalFrames, (vPositionInArray.y + 1.)/(float)iVerticalFrames);
	lgfx_setcolor(1, 1, 1, 1);
}

void Sprite::setCollisionType(CollisionType type)
{
	switch (type)
	{
		case COLLISION_CIRCLE:
		{
			Vec2 size = getSize();
			float radius = size.x / 2;
			if (size.y > size.x)
			{
				radius = size.y/2;
			}
			pCollider = new CircleCollider(radius, vPosition);
		}
		break;
		case COLLISION_RECT:
		{
			pCollider = new RectCollider(getSize(), vPosition);
		}
		break;
		case COLLISION_PIXELS:
		{
			int iNumberChars = getSize().x * getSize().y * 4;
			uint8_t* sTextureChars = generateUCharArray(iNumberChars);
			ltex_getpixels(&texture, sTextureChars);

			pCollider = new PixelsCollider(getSize(), vPosition, sTextureChars);

		}
		break;
		default:
		{

		}
	}
}
CollisionType Sprite::getCollisionType() const
{
	if (pCollider == nullptr)
	{
		return COLLISION_NONE;
	}
	else
	{
		return pCollider->type;
	}
}
const Collider* Sprite::getCollider() const
{
	return pCollider;
}
bool Sprite::collides(Sprite& other)
{
	if (pCollider != nullptr)
	{
		bool bResult = false;
		switch (other.getCollisionType())
		{
			case COLLISION_CIRCLE:
			{
				Collider* pCollider = const_cast<Collider*>( other.getCollider());
				CircleCollider* pCircle = static_cast<CircleCollider*>(pCollider);
				bResult = const_cast<Collider*>(getCollider())->collides(pCircle->vPosition, pCircle->fRadius);
			}
			break;
			case COLLISION_RECT:
			{
				Collider* pCollider = const_cast<Collider*>(other.getCollider());
				RectCollider* pRect = static_cast<RectCollider*>(pCollider);
				bResult = const_cast<Collider*>(getCollider())->collides(pRect->vPosition, pRect->vSize);
			}
			break;
			case COLLISION_PIXELS:
			{
				Collider* pCollider = const_cast<Collider*>(other.getCollider());
				PixelsCollider* pPixels = static_cast<PixelsCollider*>(pCollider);
				bResult = const_cast<Collider*>(getCollider())->collides(pPixels->vPosition, pPixels->vSize, pPixels->m_pixels);
			}
			break;
			default:
			{
				bResult = false;
			}
		}
		
		pCollider->collides(*(other.pCollider));
		if (bResult)
		{
			setColor(1, 0, 0, 1);
			other.setColor(1, 0, 0, 1);
		}
		return bResult;
	}
	else
	{
		return false;
	}
}