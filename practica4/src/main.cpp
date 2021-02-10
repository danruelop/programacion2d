#define STB_IMAGE_IMPLEMENTATION
#define LITE_GFX_IMPLEMENTATION

#include <iostream>
#include "Sprite.h"

using namespace std;

int w_width = 1920;
int w_height = 1080;

int actualWindowsWidth;
int* p_actualWindowsWidth = &actualWindowsWidth;

int actualWindowsHeight;
int* p_actualWindowsHeight = &actualWindowsHeight;

ltex_t* loadTexture(const char* filename);

int main()
{
	if (glfwInit()) 
	{
		GLFWwindow* window = glfwCreateWindow(w_width, w_height, "OpenGL go brrrrrr", nullptr, nullptr);

		double m_xpos;
		double m_ypos;
		double* pm_xpos = &m_xpos;
		double* pm_ypos = &m_ypos;

		glfwMakeContextCurrent(window);

		lgfx_setup2d(1920, 1080);

		float bkgImagesRepeated, angle = 0, scale = 1;

		int fps = 60;
		int frameTime = 0.0;
		int setUpdateFrames = (60 - 4) / 8;

		//load bee texture
		ltex_t* loadedTexture = loadTexture("data/bee_anim.png");

		//create sprite
		Sprite BeeSprite(loadedTexture, 8, 1);

		//set initial values of the sprite
		BeeSprite.setScale(Vec2(1, 1));
		BeeSprite.setPivot(Vec2(0.5, 0.5));
		BeeSprite.setAngle(0.0f);
		BeeSprite.setBlend(BLEND_ALPHA);
		BeeSprite.setFps(8);

		while (!glfwWindowShouldClose(window))
		{
			static float previous_seconds = static_cast<float>(glfwGetTime());
			float current_seconds = static_cast<float>(glfwGetTime());
			float elapsed_seconds = current_seconds - previous_seconds;
			previous_seconds = current_seconds;

			glfwGetCursorPos(window, pm_xpos, pm_ypos);

			glfwGetWindowSize(window, p_actualWindowsWidth, p_actualWindowsHeight);

			lgfx_setup2d(actualWindowsWidth, actualWindowsHeight);

			lgfx_clearcolorbuffer(0.2f, 0.2f, 1.f);

			lgfx_setblend(BeeSprite.getBlend());
			BeeSprite.update(elapsed_seconds);
			BeeSprite.draw();
			BeeSprite.setPosition(Vec2(m_xpos, m_ypos));

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
		ltex_free(loadedTexture);
		return 0;
	}
	else {

		printf("error loading GLFW library");

	}
}

ltex_t* loadTexture(const char* filename)
{
	int widthSize;
	int heightSize; 
	int Buffer;

	//load image
	stbi_uc* Image = stbi_load(filename, &widthSize, &heightSize, &Buffer, 4);
	
	if (!Image)
	{
		printf("error loading image");
	}

	//allocate space in memory for texture
	ltex_t* texture = ltex_alloc(widthSize, heightSize, 1);
	if (texture == nullptr)
	{
		printf("error allocating texture");
	}

	ltex_setpixels(texture, Image);
	return texture;
}
