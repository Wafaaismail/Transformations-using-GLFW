#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;


/*************************************VARIABLES**********************************************************/
float screenWidth = 700;
float screenHieght = 700;
float step = 0.1f;
float angle = 20.f;
float scale = .3f;
float x = 0.;
float y = 0.;
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawTriangle();
int main() {
	GLFWwindow *window;
	//initilize library
	if (!glfwInit()){
		cout << " Can't initilize the GLFW";
		return -1;
	}
	//Create Window
	window = glfwCreateWindow(screenWidth,screenHieght,"ProjectTest",NULL,NULL);
	if (!window)
	{
		cout << "Can't render the window ";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0.0f, 0.0f, screenWidth, screenHieght); //draw openGl in pixels 
	//glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	//glOrtho(0, screenWidth, 0,screenHieght, 0, 1); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		
		glColor3f(.4, 0.6, .9);
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		drawTriangle();
		glPopMatrix();

		glPushMatrix();

		glColor3f(1., 0.0, 0.0);
		glScalef(scale, scale, scale);
		drawTriangle();
		glPopMatrix();
		glfwSetKeyCallback(window, keyCallback);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	

	glfwTerminate();
	return 0;
}


void drawTriangle() {
	glBegin(GL_TRIANGLES);
	//Triangle
	glVertex3f(0.f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.3f, 0.5f, 0.0f);
	glEnd();
  }

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
	switch (key) {
	case GLFW_KEY_LEFT: //move left
		x -= step;
	
		break;
	case GLFW_KEY_RIGHT: //move right
		x += step;
		break;
	case GLFW_KEY_UP: //move up
		y += step;
		break;
	case GLFW_KEY_DOWN: // move down
		y -= step;
		break;
	case GLFW_KEY_HOME: // to rotate clockwise
		angle += 2.0f;
		if (angle > 360)
			angle -= 360;
		cout << angle;


		break;
	case GLFW_KEY_END: // to rotate anti clockwise
		angle -= 2.0f;
		if (angle < 360)
			angle += 360;
		cout << angle;

		break;
	case GLFW_KEY_PAGE_UP:  //expand
		scale += .5;
	
				break;

	case GLFW_KEY_PAGE_DOWN: //shrink
		scale -= .5;
		break;
	default:
		break;
	}
}
