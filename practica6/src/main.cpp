#define STB_IMAGE_IMPLEMENTATION
#define LITE_GFX_IMPLEMENTATION

#include <iostream>

#include "World.h"
#include "Collider.h"

using namespace std;

ltex_t* loadTexture(const char* filename);
//void printBackground(ltex_t* loadedTexture, int wXsize);


int main()
{

	if (!glfwInit())
	{
		printf("error");
	}

	GLFWwindow* window = glfwCreateWindow(1000, 800, "Practica 6", nullptr, nullptr);
	if (!window)
	{
		printf("error 2");
	}

	glfwMakeContextCurrent(window);
	//glfwGetWindowSize(GLFWwindow * window, int* width, int* height)

	lgfx_setup2d(1000, 800);

	int wXsize = 0, wYsize = 0;
	double xpos, ypos;
	float bkgImagesRepeated, angle = 0, scale = 1;

	int fps = 60;
	int frameTime = 0.0;
	int setUpdateFrames = (60 - 4) / 8;

	ltex_t* BeeTexture = loadTexture("data/images/bee_anim.png");
	ltex_t* LevelTexture = loadTexture("data/images/level.png");
	ltex_t* Trees1Texture = loadTexture("data/images/trees1.png");
	ltex_t* Trees2Texture = loadTexture("data/images/trees2.png");
	ltex_t* CloudsTexture = loadTexture("data/images/clouds.png");

	//SETUP SPRITE: Tipo de Sprite, Escala, Pivote, Fps, Angulo, Modo de Blend, Tipo de Colision

	Sprite Bee(BeeTexture, 8, 1);
	Bee.setupSprite("beeSprite", ESpriteType::SINGULAR, Vec2(1, 1), Vec2(0, 0), 8, 0.f, BLEND_ALPHA, Sprite::COLLISION_NONE, 1);

	Sprite Level(LevelTexture, 8, 1);
	Level.setupSprite("levelSprite", ESpriteType::SINGULAR, Vec2(1, 1), Vec2(0, 0), 8, 0.f, BLEND_ALPHA, Sprite::COLLISION_NONE , 1);

	Sprite Trees1(Trees1Texture, 8, 1);
	Trees1.setupSprite("tree1Sprite", ESpriteType::HORIZONTALBACKGROUND, Vec2(1, 1), Vec2(0, 0), 8, 0.f, BLEND_ALPHA, Sprite::COLLISION_NONE, 0.8);

	Sprite Trees2(Trees2Texture, 8, 1);
	Trees2.setupSprite("tree2Sprite", ESpriteType::HORIZONTALBACKGROUND, Vec2(1, 1), Vec2(0,0), 8, 0.f, BLEND_ALPHA, Sprite::COLLISION_NONE, 0.6);

	Sprite Clouds(CloudsTexture, 8, 1);
	Clouds.setupSprite("cloudsSprite", ESpriteType::FULLBACKGROUND, Vec2(1, 1), Vec2(0, 0), 8, 0.f, BLEND_ALPHA, Sprite::COLLISION_NONE, 0.4);

	//set pixels array

	World gameWorld(0.15f, 0.15f, 0.15f, LevelTexture, Trees1Texture, Trees2Texture, CloudsTexture);
	gameWorld.setCameraPosition(Vec2(0, 0));

	gameWorld.addSprite(Clouds);
	gameWorld.addSprite(Trees1);
	gameWorld.addSprite(Trees2);
	gameWorld.addSprite(Level);
	
	bool mustReverseRotation = true, mustReverseScale = false;

	while (!glfwWindowShouldClose(window))
	{
		//Actualizamos delta de tiempo
		static float previous_seconds = static_cast<float>(glfwGetTime());
		float current_seconds = static_cast<float>(glfwGetTime());
		float elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;

		gameWorld.setPlayerIdleState(Bee.getIdleState());

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		//Leemos input usuario
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwGetWindowSize(window, &wXsize, &wYsize);

		//Actualizamos logica juego
		//--
		lgfx_setup2d(wXsize, wYsize);

		//Pintar las imagenes en el centro de la pantalla siempre

		//Limpiar el backbuffer
		lgfx_clearcolorbuffer(0.5f, 0.5f, 0.5f);

		lgfx_setblend(Bee.getBlend());
		lgfx_setcolor(Bee.getRed(), Bee.getGreen(), Bee.getBlue(), Bee.getAlpha());
		Bee.update(elapsed_seconds);
		Bee.setPosition(Vec2(xpos, ypos));
		
		gameWorld.update(elapsed_seconds);
		gameWorld.draw(Vec2(wXsize, wXsize));
		Bee.draw(0.125);
		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	ltex_free(BeeTexture);

	return 0;

}

ltex_t* loadTexture(const char* filename)
{
	int xSize, ySize, Buffer;

	stbi_uc* Image = stbi_load(filename, &xSize, &ySize, &Buffer, 4);
	if (!Image)
	{
		printf("Error no se ha podido cargar la imagen");
	}

	ltex_t* texture = ltex_alloc(xSize, ySize, 1);
	if (texture == nullptr)
	{
		printf("Error al alocar la textura");
	}

	ltex_setpixels(texture, Image);
	return texture;
}



