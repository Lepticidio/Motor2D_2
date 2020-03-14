#pragma once

#include <glfw3.h>
#include <litegfx.h>
#include "CircleCollider.h"
#include "RectCollider.h"
#include "PixelsCollider.h"

class Sprite
{
public:
	// Tpo de la función callback 
	typedef void (* CallbackFunc)(Sprite&, float);

	// Indicamos el número de frames en horizontal y vertical
	// que tendrá la imagen del sprite 
	Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1); 

	// Establecemos puntero a la función callback 
	void setCallback(CallbackFunc func); 

	// Puntero genérico a datos (normalmente introducimos aquí los datos 
	// del sprite que se van a utilizar en la función callback) 
	void* getUserData(); 
	void setUserData(void* data); 

	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* tex, int hframes, int vframes);
	lblend_t getBlend() const; 
	void setBlend(lblend_t mode);
	float getRed() const; 
	float getGreen() const; 
	float getBlue() const; 
	float getAlpha() const; 
	void setColor(float r, float g, float b, float a);
	const Vec2& getPosition() const; 
	void setPosition(const Vec2& pos);
	float getAngle() const; 
	void setAngle(float angle);
	const Vec2& getScale() const; 
	void setScale(const Vec2& scale);

	// Tamaño de un frame multiplicado por la escala 
	Vec2 getSize() const; 
	// Este valor se pasa a ltex_drawrotsized en el pintado 
	// para indicar el pivote de rotación 
	const Vec2& getPivot() const; 
	void setPivot(const Vec2& pivot); 

	int getHframes() const; 
	int getVframes() const;

	// Veces por segundo que se cambia el frame de animación 
	int getFps() const; 
	void setFps(int fps); 
	// Frame actual de animación 
	float getCurrentFrame() const; 
	void setCurrentFrame(int frame); 

	void update(float deltaTime);
	void draw() const;

	void setCollisionType(CollisionType type);
	CollisionType getCollisionType() const;
	const Collider* getCollider() const;
	bool collides(Sprite& other);


private:
	ltex_t texture;
	lblend_t blend = BLEND_ALPHA;
	int iCurrentFrame = 0;
	int iFps = 1;
	int iHorizontalFrames;
	int iVerticalFrames;
	float fRed = 1;
	float fGreen = 1;
	float fBlue = 1;
	float fAlpha = 1;
	float fAngle = 0;
	float fcurrentAnimationTime = 0;
	Vec2 vPosition = Vec2(0,0);
	Vec2 vScale = Vec2(1,1);
	Vec2 vPivot = Vec2(0.5f, 0.5f);
	CallbackFunc callbackFunc;
	Collider* pCollider;
};

