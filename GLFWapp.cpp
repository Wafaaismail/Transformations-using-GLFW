

#include <glad\glad.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GLFW/glfw3.h>	
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
GLuint vertexbuffer ;
void gladPointers()
{

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}
const GLfloat vertices[] = {
	0.f, 0.f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.3f,  0.5f, 0.0f
};

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawTriangle();
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0.0f, 0.0f, screenWidth, screenHieght); //draw openGl in pixels
}

int main(int &argc, char **argv) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window;
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	 
	//glLoadIdentity();
	gladPointers();
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	//	glPushMatrix();
		
		
	//	glColor3f(.4, 0.6, .9);
		//glTranslatef(x, y, 0);
		//glRotatef(angle, 0, 0, 1);
		drawTriangle();
	///glPopMatrix();

	//	glPushMatrix();
		
	//	glColor3f(1., 0.0, 0.0);
		//glScalef(scale, scale, scale);
		drawTriangle();
		//glPopMatrix();
		glfwSetKeyCallback(window, keyCallback);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	

	glfwTerminate();
	return 0;
}


void drawTriangle() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

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
