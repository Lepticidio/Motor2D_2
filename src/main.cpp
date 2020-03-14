
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "Sprite.h"
#include "AudioListener.h"
#include <stb_image.h>


using namespace std;


int iWidth = 1000;
int iHeight = 1000;

Vec2 vMousePos;

void ListenerCallback(Sprite& _sprite, float _deltaTime)
{
}

void MouseSpriteCallback(Sprite& _sprite, float _deltaTime)
{
	_sprite.setPosition(vMousePos);
}

void GrowSpriteCallback(Sprite& _sprite, float _deltaTime);
void ShrinkSpriteCallback(Sprite& _sprite, float _deltaTime);
void GrowSpriteCallback(Sprite& _sprite, float _deltaTime)
{
	float fMaxSize = 1.1f;
	float fOscillationSpeed = 0.25f * _deltaTime;
	Vec2 vCurrentScale = _sprite.getScale();

	_sprite.setScale(vCurrentScale + Vec2(fOscillationSpeed, fOscillationSpeed));

	if (vCurrentScale.x > fMaxSize)
	{
		_sprite.setCallback(ShrinkSpriteCallback);
		_sprite.setScale(Vec2(fMaxSize, fMaxSize));
	}
}
void ShrinkSpriteCallback(Sprite& _sprite, float _deltaTime)
{
	float fMinSize= 0.9f;
	float fOscillationSpeed = 0.25f * _deltaTime;
	Vec2 vCurrentScale = _sprite.getScale();

	_sprite.setScale(vCurrentScale - Vec2(fOscillationSpeed, fOscillationSpeed));

	if (vCurrentScale.x < fMinSize)
	{
		_sprite.setCallback(GrowSpriteCallback);
		_sprite.setScale(Vec2(fMinSize, fMinSize));
	}
}

int main()
{

	//1) Iniciamos la librería GFWX
	glfwInit();

	//2) Creamos una ventana
	GLFWwindow* pWindow = glfwCreateWindow(iWidth, iHeight, "", nullptr, nullptr);

	//3) Asociamos el contexto de OpenGL a la ventana
	glfwMakeContextCurrent(pWindow);

	//4) Iniciamos la librería LiteGFX
	lgfx_setup2d(iWidth, iHeight);

	bool bOpen = true;
	int iWidthWasp = 0;
	int iHeightWasp = 0;
	int iWidthBall = 0;
	int iHeightBall = 0;
	int iWidthBox = 0;
	int iHeightBox = 0;
	int iWidthCircle = 0;
	int iHeightCircle = 0;
	int iWidthRect = 0;
	int iHeightRect = 0;
	double deltaTime = 0;
	double previousTime = glfwGetTime();

	double dXMouse = 0;
	double dYMouse = 0;
	double* pXMouse = &dXMouse;
	double* pYMouse = &dYMouse;

	unsigned char* sWaspBytes = stbi_load("data//wasp.png", &iWidthWasp, &iHeightWasp, nullptr, 4);
	ltex_t* pTextureWasp = nullptr;
	pTextureWasp = ltex_alloc(iWidthWasp, iHeightWasp, 1);
	ltex_setpixels(pTextureWasp, sWaspBytes);
	stbi_image_free(sWaspBytes);

	Sprite wasp(pTextureWasp, 1, 1);
	wasp.setPosition(Vec2(500, 750));
	wasp.setCollisionType(COLLISION_PIXELS);


	unsigned char* sCircleBytes = stbi_load("data//circle.png", &iWidthCircle, &iHeightCircle, nullptr, 4);
	ltex_t* pTextureCircle = nullptr;
	pTextureCircle = ltex_alloc(iWidthCircle, iHeightCircle, 1);
	ltex_setpixels(pTextureCircle, sCircleBytes);
	stbi_image_free(sCircleBytes);

	Sprite listenerSprite(pTextureCircle, 1, 1);
	listenerSprite.setPosition(Vec2(500, 900));
	listenerSprite.setCallback(ListenerCallback);
	listenerSprite.setCollisionType(COLLISION_CIRCLE);
	listenerSprite.setScale(Vec2(4,4));

	unsigned char* sRectBytes = stbi_load("data//rect.png", &iWidthRect, &iHeightRect, nullptr, 4);
	ltex_t* pTextureRect = nullptr;
	pTextureRect = ltex_alloc(iWidthRect, iHeightRect, 1);
	ltex_setpixels(pTextureRect, sRectBytes);
	stbi_image_free(sRectBytes);
	const int iNumberSprites = 2;
	Sprite* allSprites [iNumberSprites] = {&wasp, &listenerSprite };

	//Audio
	ALCdevice* pDevice = alcOpenDevice(NULL);
	ALCcontext* pContext = alcCreateContext(pDevice, NULL);
	ALCboolean contextCurrent = alcMakeContextCurrent(pContext);

	//AudioListener* pListener;
	//pListener->getInstance();
	AudioListener* pAudioListener = new AudioListener();
	ALenum auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return 0;
	}
	AudioBuffer* pMusic;
	pMusic = pMusic->load("data//engine.wav");

	auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return 0;
	}
	AudioSource source = AudioSource(pMusic);

	auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return 0;
	}

	source.play();
	source.setGain(20);
	source.setLooping(true);

	float fListenerSpeed = 200;
	float fSourceAngularSpeed = 90;
	alDopplerFactor(50);

	//5) Bucle principal
	while (!glfwWindowShouldClose(pWindow) && bOpen)
	{
		//5.1) Actualizamos delta de tiempo
		deltaTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();
		//5.2) Leemos input del usuario
		if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			bOpen = false;
		}


		Vec2 vListenerVelocity(0, 0);
		Vec2 vPreviousPosition = listenerSprite.getPosition();


		//Set listener position
		if (GetAsyncKeyState(VK_RIGHT))
		{
			vListenerVelocity = Vec2(deltaTime*fListenerSpeed, 0);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			vListenerVelocity = Vec2(-deltaTime * fListenerSpeed, 0);
		}
		Vec2 vNewListenerPosition = vPreviousPosition + vListenerVelocity;
		pAudioListener->setListenerVelocity(vListenerVelocity.x, vListenerVelocity.y, 0);
		pAudioListener->setListenerPosition(vNewListenerPosition.x, vNewListenerPosition.y, 0);
		listenerSprite.setPosition(vNewListenerPosition);
		glfwGetCursorPos(pWindow, pXMouse, pYMouse);
		vMousePos = Vec2(dXMouse, dYMouse);



		//Set source position
		Vec2 vSourcePreviousPosition = wasp.getPosition();
		Vec2 vCenter = Vec2(iWidth / 2, iHeight / 2);
		Vec2 vSourcePreviousPositionDirection = vSourcePreviousPosition - vCenter;

		Vec2 vNewSourcePositionDirection = vSourcePreviousPositionDirection.Rotate(fSourceAngularSpeed*deltaTime);
		Vec2 vSourceVelocity = vNewSourcePositionDirection - vSourcePreviousPositionDirection;
		Vec2 vNewSourcePosition = vCenter + vNewSourcePositionDirection;

		source.setPosition(vNewSourcePosition.x, vNewSourcePosition.y, 0);
		source.setVelocity(vSourceVelocity.x, vSourceVelocity.y, 0);
		wasp.setPosition(vNewSourcePosition);
		if (vSourceVelocity.x > 0)
		{
			wasp.setScale(Vec2(1, 1));
		}
		else
		{
			wasp.setScale(Vec2(-1, 1));
		}

		//5.3) Actualizamos lógica de juego
		listenerSprite.update(deltaTime);

		for (int i = 0; i < iNumberSprites - 1; i++)
		{
			bool bCollides = false;
			for (int j = i + 1; j < iNumberSprites; j++)
			{
				(*allSprites[i]).collides((*allSprites[j]));				
			}
		}
		//5.4) Limpiamos el backbuffer
		lgfx_clearcolorbuffer(0, 0, 0);

		//5.5) Renderizamos la escena.
		wasp.draw();
		listenerSprite.draw();

		wasp.setColor(1, 1, 1, 1);
		listenerSprite.setColor(1, 1, 1, 1);

		//5.6) Cambiamos el backbuffer por el frontbuffer
		glfwSwapBuffers(pWindow);

		//5.7) Procesamos eventos
		glfwPollEvents();

	}
	//6) Liberamos los recursos.
	glfwTerminate();




	return 0;
}