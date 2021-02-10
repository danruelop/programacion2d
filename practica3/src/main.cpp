#define LITE_GFX_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include "litegfx.h"

#undef LITE_GFX_IMPLEMENTATION

#include "stb_truetype.h"

#undef STB_TRUETYPE_IMPLEMENTATION

#include "glfw3.h"
#include <iostream>
#include <sstream>
#include <Vec2.h>
#include <string>
#include "Font.h"
#include "CPrintedText.h"





using namespace std;

int w_width = 1920;
int w_height = 1080;

int actualWindowsWidth;
int* p_actualWindowsWidth = &actualWindowsWidth;

int actualWindowsHeight;
int* p_actualWindowsHeight = &actualWindowsHeight;

int* bufferN;

CPrintedText textsOnScreen[20];


template <typename T>
std::string stringFromNumber(T val) {
	std::ostringstream stream;
	stream << std::fixed << val;
	return stream.str();
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

		//Font::chargeInMemory("data/Orange.ttf");
		

		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

		int textCounter = 0;

		while (!glfwWindowShouldClose(window))
		{
			glfwGetWindowSize(window, p_actualWindowsWidth, p_actualWindowsHeight);
			lgfx_setup2d(actualWindowsWidth, actualWindowsHeight);

			static float previous_seconds = static_cast<float>(glfwGetTime());
			float current_seconds = static_cast<float>(glfwGetTime());
			float elapsed_seconds = current_seconds - previous_seconds;
			previous_seconds = current_seconds;

			// pintar background

			lgfx_setblend(BLEND_ALPHA);

			//atributos random
			int drawText = rand() % 101;
			
			if(drawText == 0 && textCounter <= 20)
			{

				int randY = rand() % actualWindowsHeight + 1;
				int randSpeed = rand() % 181 + 20;
				unsigned int randFont = rand() % 2;
				unsigned int randColorR = rand() % 256;
				unsigned int randColorG = rand() % 256;
				unsigned int randColorB = rand() % 256;
				const char* selectedFont;

				SColor randColor;
				randColor.r = randColorR;
				randColor.g = randColorG;
				randColor.b = randColorB;

				if (randFont == 0) { selectedFont = "data/Orange.ttf"; }
				else { selectedFont = "data/SFSlapstickComic.ttf"; }

				//creamos CPrintedText
				Font newFont = Font();
				Font* pNewFont = &newFont;
				CPrintedText newText = CPrintedText(pNewFont, 500, randY, selectedFont, randSpeed, randColor, "Hola mundo");
						
				newText.printText();
				
				//guardamos en la lista
				
			}

			//recorremos la lista y vamos cambiando los atributos necesarios
			
			

			//obtener tamaño de la ventana			
			
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
