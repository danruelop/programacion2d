
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include <sstream>
#include <Vec2.h>
#include <cmath>
#include <math.h>
#include <string>
#include <stb_image.h>

using namespace std;

int w_width = 800;
int w_height = 600;

int actualWindowsWidth;
int* p_actualWindowsWidth = &actualWindowsWidth;

int actualWindowsHeight;
int* p_actualWindowsHeight = &actualWindowsHeight;

//tamaño imagen pared
int wall_width;
int wall_height;
//punteros variable tamaño imagen pared
int* p_wall_width = &wall_width;
int* p_wall_height = &wall_height;

//tamaño imagen fuego
int fire_width;
int fire_height;
//punteros variable tamaño imagen fuego
int* p_fire_width = &fire_width;
int* p_fire_height = &fire_height;

//tamaño imagen fuego
int grille_width;
int grille_height;
//punteros variable tamaño imagen fuego
int* p_grille_width = &grille_width;
int* p_grille_height = &grille_height;

//tamaño imagen fuego
int light_width;
int light_height;
//punteros variable tamaño imagen fuego
int* p_light_width = &light_width;
int* p_light_height = &light_height;

int* bufferN;

float angle = 0.f;
float maxAngle = 10.f;
float minAngle = -10.f;
float rotationAngle;
bool rotRight = true;

float maxSize = 1.2f;
float minSize = 0.8f;
float multSize = 1.f;
bool grow = true;



const char* wall = "data/wall.jpg";
const char* fire = "data/fire.png";
const char* grille = "data/grille.png";
const char* light = "data/light.png";
 
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
		

		//carga pared
		ltex_t* wallTexture = loadTexture(wall, p_wall_width, p_wall_height);
		//cargar fuego
		ltex_t* fireTexture = loadTexture(fire, p_fire_width, p_fire_height);
		//cargar grille
		ltex_t* grilleTexture = loadTexture(grille, p_grille_width, p_grille_height);
		//cargar luz
		ltex_t* lightTexture = loadTexture(light, p_light_width, p_light_height);

		while(!glfwWindowShouldClose(window))
		{

			static float previous_seconds = static_cast<float>(glfwGetTime());
			float current_seconds = static_cast<float>(glfwGetTime());
			float elapsed_seconds = current_seconds - previous_seconds;
			previous_seconds = current_seconds;

			lgfx_setup2d(actualWindowsWidth, actualWindowsHeight);

			if (rotRight == true) {
				rotationAngle = 10.f * elapsed_seconds;
				angle += 10.f;
				if( angle >= maxAngle )
				{
					rotRight = false;
				}
			}
			else
			{
				rotationAngle = -10.f * elapsed_seconds;
				angle -= 10.f;
				if (angle <= minAngle) 
				{
					rotRight = true;
				}
			}

			if (grow == true)
			{
				multSize += 0.05f * elapsed_seconds;
			}
			if (grow == false)
			{
				multSize -= 0.05f * elapsed_seconds;
			}

			if (multSize >= maxSize)
			{
				grow = false;
			}
			else if (multSize <= minSize)
			{
				grow = true;
			}

			// pintar background

			lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

			//obtener tamaño de la ventana
			glfwGetWindowSize(window, p_actualWindowsWidth, p_actualWindowsHeight);

			//mezclado SOLID para la pared
			lgfx_setblend(BLEND_ALPHA);

			//pintar pared
			setupBackground(wallTexture, wall_width, wall_height, actualWindowsWidth, actualWindowsHeight);
			
			//pintar fuego
			//ltex_draw(fireTexture, m_xpos, m_ypos);
			lgfx_setblend(BLEND_ADD);
			ltex_drawrotsized(fireTexture, m_xpos, m_ypos,
				rotationAngle, 0.5, 0.5,
				fire_width*multSize, fire_height*multSize,
				0, 0, 1,1);

			//pintar rejas
			lgfx_setblend(BLEND_ALPHA);
			setupBackground(grilleTexture, grille_width, grille_height, actualWindowsWidth, actualWindowsHeight);
			
			lgfx_setblend(BLEND_MUL);
			ltex_drawrotsized(lightTexture, m_xpos, m_ypos,
				0, 0.5, 0.5,
				light_width, light_height,
				0, 0, 1, 1);

			lgfx_setcolor(0, 0, 0, 0);
			lgfx_drawrect(m_xpos + light_width/2, m_ypos -2500, 5000, 5000);
			lgfx_drawrect(m_xpos - light_width/2 -5000, m_ypos - 2500, 5000, 5000);
			lgfx_drawrect(m_xpos - light_width/2, m_ypos - light_height/2 - 5000, 5000, 5000);
			lgfx_drawrect(m_xpos - light_width / 2, m_ypos + light_height / 2 , 5000, 5000);
			
			

			
		
			glfwGetCursorPos(window, pm_xpos, pm_ypos);

			std::string title = 
				+ "-- Angulo: "
				+ stringFromNumber(angle*elapsed_seconds)
				+ "-- Tamaño: "
				+ stringFromNumber(multSize * elapsed_seconds);

			glfwSetWindowTitle(window, title.c_str());


			glfwSwapBuffers(window);

			//check and call events
			glfwPollEvents();


		}
		ltex_free(wallTexture);
		ltex_free(fireTexture);
		ltex_free(grilleTexture);
		ltex_free(lightTexture);
		stbi_image_free(bufferN);

		

	}
	else
	{
		printf("fallo");
	}

	glfwTerminate();
	return 0;
}
