#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }
	GLfloat getarticulacion1() { return articulacion1; }
	GLfloat getarticulacion2() { return articulacion2; }
	GLfloat getarticulacion3() { return articulacion3; }
	GLfloat getarticulacion4() { return articulacion4; }
	GLfloat getrueda1() { return rueda1; }
	GLfloat getrueda2() { return rueda2; }
	GLfloat getrueda3() { return rueda3; }
	GLfloat getrueda4() { return rueda4; }
	GLfloat getpata1() { return pata1; }
	GLfloat getpatita1() { return patita1; }
	GLfloat getpata2() { return pata2; }
	GLfloat getpatita2() { return patita2; }
	GLfloat getpata3() { return pata3; }
	GLfloat getpatita3() { return patita3; }
	GLfloat getpata4() { return pata4; }
	GLfloat getpatita4() { return patita4; }
	GLfloat getcola() { return cola; }

	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotax,rotay,rotaz, articulacion1, articulacion2, articulacion3, articulacion4,
		rueda1, rueda2, rueda3, rueda4, pata1, patita1, pata2, patita2, pata3, patita3, pata4, patita4, cola;
	GLint a1, a2, a3, a4, r1, r2, r3, r4, P1, p1, P2, p2, P3, p3, P4, p4, c0;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};

