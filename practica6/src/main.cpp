#define STB_IMAGE_IMPLEMENTATION
#define LITE_GFX_IMPLEMENTATION

#include <iostream>
#include "Sprite.h"
#include "World.h"
#include "Collider.h"

using namespace std;

ltex_t* loadTexture(const char* filename);
void printBackground(ltex_t* loadedTexture, int wXsize);


int main()
{

	if (!glfwInit())
	{
		printf("error");
	}

	GLFWwindow* window = glfwCreateWindow(1000, 700, "Practica 5", nullptr, nullptr);
	if (!window)
	{
		printf("error 2");
	}

	glfwMakeContextCurrent(window);
	//glfwGetWindowSize(GLFWwindow * window, int* width, int* height)

	lgfx_setup2d(1920, 1080);

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

	Sprite Bee(BeeTexture, 8, 1);
	Bee.setScale(Vec2(1, 1));
	Bee.setPivot(Vec2(0.5, 0.5));
	Bee.setFps(8);
	Bee.setAngle(0.0f);
	Bee.setBlend(BLEND_ALPHA);
	Bee.setCollisionType(Sprite::COLLISION_PIXELS);
	Bee.setPixels(BeeTexture);
	//set pixels array

	World gameWorld(0.15f, 0.15f, 0.15f, LevelTexture, Trees1Texture, Trees2Texture, CloudsTexture);
	gameWorld.setCameraPosition(Vec2(0, 0));
	

	bool mustReverseRotation = true, mustReverseScale = false;

	while (!glfwWindowShouldClose(window))
	{
		//Actualizamos delta de tiempo
		static float previous_seconds = static_cast<float>(glfwGetTime());
		float current_seconds = static_cast<float>(glfwGetTime());
		float elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;

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
		Bee.draw();



		

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

void printBackground(ltex_t* loadedTexture, int wXsize)
{
	//En Funcion del tamaño de la ventana calculo cuantas imagenes caben a lo ancho de esta
	// y voy creando copias de esta mediante el uso de bucles for
	int bkgImagesRepeated = wXsize / loadedTexture->width;

	for (int i = 0; i <= bkgImagesRepeated; i++)
	{
		lgfx_setblend(BLEND_ALPHA);
		ltex_draw(loadedTexture, loadedTexture->width * i, 0);
		for (int j = 1; j <= bkgImagesRepeated + 1; j++)
		{
			lgfx_setblend(BLEND_ALPHA);
			ltex_draw(loadedTexture, loadedTexture->width * i, loadedTexture->height * j);
		}
	}
}


