
#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include <Vec2.h>
#include <cmath>
#include <math.h>

using namespace std;

float rpX;
float rpY;
float npX;
float npY;

int main() {

	

	if (glfwInit())
	{
		double m_xpos;
		double m_ypos; 
		double* pm_xpos = &m_xpos;
		double* pm_ypos = &m_ypos;
		int w_width = 800;
		int w_height = 600;
		float cube_width = 50;
		float cube_height = 50;

		GLFWwindow* window = glfwCreateWindow(w_width, w_height, "OpenGL go brrrrrr", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		lgfx_setup2d(w_width, w_height);
		

			//nuevaPosicionX = puntoDeRotacion.X + distance * Math.sin(angle);
			//nuevaPosicionY = puntoDeRotacion.Y + distance * Math.cos(angle);
		

		do  {

			float angle = (3.14f / 6) * glfwGetTime(); //el ángulo que va aumentando con respecto del tiempo

			float rpX = (float)*pm_xpos - cube_width / 2; // posición X de referencia (del cubo)
			float rpY = (float)*pm_ypos - cube_height / 2; // poisición Y de referencia (del cubo)
			
			Vec2 vecA = Vec2(rpX,rpY);
			Vec2 vecB = Vec2(npX, npY);

			/*float angle = vecA.angleVec2(vecB);
			angle += 0, 55.f;*/

			float npX = rpX + 100.f * sin(angle);  // *sin(vecA.angleVec2(vecB));
			float npY = rpY + 100.f * cos(angle); // *cos(vecA.angleVec2(vecB));
			
			// pintar background
			lgfx_clearcolorbuffer(0.3f, 0.3f, 0.3f);

			//para obtener la posición del ratón
			glfwGetCursorPos(window, pm_xpos, pm_ypos);

			//pintar color cuadrado 1
			lgfx_setcolor(0.1f, 0.1f, 0.1f, 1.f);

			lgfx_drawrect(w_width/2 - cube_width/2, w_height/2 - cube_height/2, (float) cube_width, (float) cube_height);

			lgfx_setcolor(1.f, 0.2f, 0.2f, 1.f);

			//cuadrado que se mueve
			lgfx_drawrect(rpX, rpY, (float)cube_width, (float)cube_height);

			lgfx_setcolor(0.f, 1.2f, 0.2f, 1.f);

			//círculo que orbita
			lgfx_drawoval(npX, npY, 30.f, 30.f);
			
			glfwSwapBuffers(window);

			//check and call events
			glfwPollEvents();
			
		} while (!glfwWindowShouldClose(window));

		

	}
	else
	{
		printf("fallo");
	}

	glfwTerminate();
	return 0;
}
