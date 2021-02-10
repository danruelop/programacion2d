#define STB_IMAGE_IMPLEMENTATION
#define LITE_GFX_IMPLEMENTATION

#include <iostream>
#include "Sprite.h"
#include "Collider.h"

using namespace std;

ltex_t* loadTexture(const char* filename);
void printBackground(ltex_t* loadedTexture, int wXsize);
unsigned char* TEST_checkPixels = new unsigned char[500 * 500];


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

	ltex_t* BeeTexture = loadTexture("data/images/bee.png");
	ltex_t* BallTexture = loadTexture("data/images/ball.png");
	ltex_t* BoxTexture = loadTexture("data/images/box.png");
	ltex_t* CircleCursorTexture = loadTexture("data/images/circle.png");
	ltex_t* RectCursorTexture = loadTexture("data/images/rect.png");

	ltex_getpixels(BeeTexture, TEST_checkPixels);

	
	Sprite Bee(BeeTexture, 1, 1);
	Bee.setPixels(BeeTexture);
	Bee.setScale(Vec2(1, 1));
	Bee.setPivot(Vec2(0, 0));
	Bee.setAngle(0.0f);
	Bee.setBlend(BLEND_ALPHA);	
	Bee.setCollisionType(Sprite::COLLISION_PIXELS);

	Sprite Ball(BallTexture, 1, 1);
	Ball.setScale(Vec2(1, 1));
	Ball.setPivot(Vec2(0, 0));
	Ball.setAngle(0.0f);
	Ball.setFps(1);
	Ball.setBlend(BLEND_ALPHA);
	Ball.setCollisionType(Sprite::COLLISION_CIRCLE);

	Sprite Box(BoxTexture, 1, 1);
	Box.setScale(Vec2(1, 1));
	Box.setPivot(Vec2(0, 0));
	Box.setAngle(0.0f);
	Box.setFps(1);
	Box.setBlend(BLEND_ALPHA);
	Box.setCollisionType(Sprite::COLLISION_RECT);

	Sprite CircleCursor(CircleCursorTexture, 1, 1);
	CircleCursor.setScale(Vec2(1, 1));
	CircleCursor.setPivot(Vec2(0, 0));
	CircleCursor.setAngle(0.0f);
	CircleCursor.setBlend(BLEND_ALPHA);

	Sprite RectCursor(RectCursorTexture, 1, 1);
	RectCursor.setScale(Vec2(1, 1));
	RectCursor.setPivot(Vec2(0, 0));
	RectCursor.setAngle(0.0f);
	RectCursor.setBlend(BLEND_ALPHA);

	Sprite Cursor(CircleCursorTexture, 1, 1);
	Cursor.setScale(Vec2(1, 1));
	Cursor.setPivot(Vec2(0, 0));
	Cursor.setAngle(0.0f);
	Cursor.setBlend(BLEND_ALPHA);
	Cursor.setCollisionType(Sprite::COLLISION_CIRCLE);

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
		Ball.setPosition(Vec2(wXsize / 3, wYsize / 2));
		Bee.setPosition(Vec2((wXsize / 3 * 1.5), wYsize / 2));
		Box.setPosition(Vec2((wXsize / 3 * 2), wYsize / 2));


		//Limpiar el backbuffer
		lgfx_clearcolorbuffer(0.5f, 0.5f, 0.5f);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{

			Cursor = CircleCursor;
			Cursor.setCollisionType(Sprite::COLLISION_CIRCLE);
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{

			Cursor = RectCursor;
			Cursor.setCollisionType(Sprite::COLLISION_RECT);
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
		{

			Cursor = Bee;
			Cursor.setCollisionType(Sprite::COLLISION_PIXELS);
			//ltex_getpixels(BeeTexture, Bee.pPixel);
		}
		Cursor.setPosition(Vec2(xpos, ypos));

	


		lgfx_setblend(Bee.getBlend());
		lgfx_setcolor(Bee.getRed(), Bee.getGreen(), Bee.getBlue(), Bee.getAlpha());
		Bee.draw();

		lgfx_setblend(Ball.getBlend());
		Ball.update(elapsed_seconds);
		lgfx_setcolor(Ball.getRed(), Ball.getGreen(), Ball.getBlue(), Ball.getAlpha());
		
		Ball.draw();
	
		lgfx_setblend(Box.getBlend());
		Box.update(elapsed_seconds);
		lgfx_setcolor(Box.getRed(), Box.getGreen(), Box.getBlue(), Box.getAlpha());
		Box.draw();

		lgfx_setcolor(Cursor.getRed(), Cursor.getGreen(), Cursor.getBlue(), Cursor.getAlpha());
		Cursor.draw();

		if (Cursor.checkCollision(Bee))
		{
			Cursor.setColor(1, 0, 0, 1);
			Bee.setColor(1, 0, 0, 1);
		}
		else
		{
			Cursor.setColor(1, 1, 1, 1);
			Bee.setColor(1, 1, 1, 1);
		}


		if (Cursor.checkCollision(Ball))
		{
			Cursor.setColor(1, 0, 0, 1);
			Ball.setColor(1, 0, 0, 1);
		}
		else if (!Cursor.checkCollision(Bee))
		{
			Cursor.setColor(1, 1, 1, 1);
			Ball.setColor(1, 1, 1, 1);
		}

		if (Cursor.checkCollision(Box))
		{
			Cursor.setColor(1, 0, 0, 1);
			Box.setColor(1, 0, 0, 1);
		}
		else if (!Cursor.checkCollision(Ball) && !Cursor.checkCollision(Ball))
		{
			Cursor.setColor(1, 1, 1, 1);
			Box.setColor(1, 1, 1, 1);
		}
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	ltex_free(BeeTexture);
	ltex_free(BallTexture); 
	ltex_free(BoxTexture); 
	ltex_free(CircleCursorTexture);
	ltex_free(RectCursorTexture);

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


