
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include <sstream>
#include <Vec2.h>
#include <cmath>
#include <math.h>
#include <string>
#include <stb_image.h>
#include "stb_truetype.h"

using namespace std;

int w_width = 800;
int w_height = 600;

int actualWindowsWidth;
int* p_actualWindowsWidth = &actualWindowsWidth;

int actualWindowsHeight;
int* p_actualWindowsHeight = &actualWindowsHeight;

int* bufferN;

 
void setupBackground(ltex_t* texture, float texture_width, float texture_height, float windows_width, float windows_height)
{
	float biggestW = windows_width > windows_height ? windows_width : windows_height;
	float biggestT = texture_width > texture_height ? texture_width : texture_height;
	int tempSize = (biggestW / biggestT) + 1;
	int i = 0;

	while (tempSize >= i)
	{
		int j = 0;
		while (j <= tempSize)
		{
			ltex_draw(texture, i * texture_width, j * texture_height);
			j++;
		}
		i++;
	}
}

template <typename T>
std::string stringFromNumber(T val) {
  std::ostringstream stream;
  stream << std::fixed << val;
  return stream.str();
}

ltex_t* loadTexture(const char* filename, int* i_width, int* i_height) {

	ltex_t* tex;
	unsigned char* arrayBytes;
	arrayBytes = stbi_load(filename, i_width, i_height, bufferN, 4);
	
	int tempX = *i_width;
	int tempY = *i_height;

	if (arrayBytes != nullptr)
	{
		tex = ltex_alloc(tempX, tempY, 0);
		if(tex != nullptr)
		{
			ltex_setpixels(tex, arrayBytes);
		}
	}
	else {
		tex = nullptr;
	}
	return tex;
}






int main() {

	if (glfwInit())
	{
		double m_xpos;
		double m_ypos; 
		double* pm_xpos = &m_xpos;
		double* pm_ypos = &m_ypos;
		
		GLFWwindow* window = glfwCreateWindow(w_width, w_height, "OpenGL go brrrrrr", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		//lgfx_setup2d(w_width, w_height);

		

	
		while(!glfwWindowShouldClose(window))
		{

			static float previous_seconds = static_cast<float>(glfwGetTime());
			float current_seconds = static_cast<float>(glfwGetTime());
			float elapsed_seconds = current_seconds - previous_seconds;
			previous_seconds = current_seconds;

			lgfx_setup2d(actualWindowsWidth, actualWindowsHeight);


			// pintar background

			lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

			/*int stbtt_BakeFontBitmap(const unsigned char* data, int offset, float
				pixel_height, unsigned char* pixels, int pw, int ph,
				int first_char, int num_chars, stbtt_bakedchar *
				chardata);*/

			

			//obtener tamaño de la ventana
			glfwGetWindowSize(window, p_actualWindowsWidth, p_actualWindowsHeight);
		
			glfwGetCursorPos(window, pm_xpos, pm_ypos);

			glfwSwapBuffers(window);

			//check and call events
			glfwPollEvents();


		}

		

	}
	else
	{
		printf("fallo");
	}

	glfwTerminate();
	return 0;
}
