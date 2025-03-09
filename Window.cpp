#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	rueda1 = 0.0f;
	rueda2 = 0.0f;
	rueda3 = 0.0f;
	rueda4 = 0.0f;
	pata1 = 0.0f;
	patita1 = 0.0f;
	pata2 = 0.0f;
	patita2 = 0.0f;
	pata3 = 0.0f;
	patita3 = 0.0f;
	pata4 = 0.0f;
	patita4 = 0.0f;
	cola = 0.0f;
	a1 = 0;
	a2 = 0;
	a3 = 0;
	a4 = 0;
	r1 = 0;
	r2 = 0;
	r3 = 0;
	r4 = 0;
	P1 = 0;
	p1 = 0;
	P2 = 0;
	p2 = 0;
	P3 = 0;
	p3 = 0;
	P4 = 0;
	p4 = 0;
	c0 = 0;

	
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica 04: Modelado Jerarquico ", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}
	if (key == GLFW_KEY_F)
	{
		if (theWindow->articulacion1 < 45.0 && theWindow->a1 == 0) 
		{
			theWindow->articulacion1 += 5.0;
		}
		else if (theWindow->articulacion1 == 45.0) 
		{
			theWindow->a1 = 1;
			theWindow->articulacion1 -= 5.0;
		}
		else if (theWindow->articulacion1 > -45.0 && theWindow->a1 == 1) 
		{
			theWindow->articulacion1 -= 5.0;
		}
		else 
		{
			theWindow->a1 = 0;
			theWindow->articulacion1 += 5.0;
		}
	}
	if (key == GLFW_KEY_G)
	{
		if (theWindow->articulacion2 < 45.0 && theWindow->a2 == 0)
		{
			theWindow->articulacion2 += 5.0;
		}
		else if (theWindow->articulacion2 == 45.0)
		{
			theWindow->a2 = 1;
			theWindow->articulacion2 -= 5.0;
		}
		else if (theWindow->articulacion2 > -45.0 && theWindow->a2 == 1)
		{
			theWindow->articulacion2 -= 5.0;
		}
		else
		{
			theWindow->a2 = 0;
			theWindow->articulacion2 += 5.0;
		}
	}
	if (key == GLFW_KEY_H)
	{
		if (theWindow->articulacion3 < 45.0 && theWindow->a3 == 0)
		{
			theWindow->articulacion3 += 5.0;
		}
		else if (theWindow->articulacion3 == 45.0)
		{
			theWindow->a3 = 1;
			theWindow->articulacion3 -= 5.0;
		}
		else if (theWindow->articulacion3 > -45.0 && theWindow->a3 == 1)
		{
			theWindow->articulacion3 -= 5.0;
		}
		else
		{
			theWindow->a3 = 0;
			theWindow->articulacion3 += 5.0;
		}
	}
	if (key == GLFW_KEY_J)
	{
		if (theWindow->articulacion4 < 45.0 && theWindow->a4 == 0)
		{
			theWindow->articulacion4 += 5.0;
		}
		else if (theWindow->articulacion4 == 45.0)
		{
			theWindow->a4 = 1;
			theWindow->articulacion4 -= 5.0;
		}
		else if (theWindow->articulacion4 > -45.0 && theWindow->a4 == 1)
		{
			theWindow->articulacion4 -= 5.0;
		}
		else
		{
			theWindow->a4 = 0;
			theWindow->articulacion4 += 5.0;
		}
	}
	if (key == GLFW_KEY_V)
	{
		theWindow->rueda1 -= 10.0;
	}
	if (key == GLFW_KEY_B)
	{
		theWindow->rueda2 -= 10.0;
	}
	if (key == GLFW_KEY_N)
	{
		theWindow->rueda3 -= 10.0;
	}
	if (key == GLFW_KEY_M)
	{
		theWindow->rueda4 -= 10.0;
	}
	if (key == GLFW_KEY_E)
	{
		if (theWindow->pata1 < 30.0 && theWindow->P1 == 0)
		{
			theWindow->pata1 += 5.0;
		}
		else if (theWindow->pata1 == 30.0)
		{
			theWindow->P1 = 1;
			theWindow->pata1 -= 5.0;
		}
		else if (theWindow->pata1 > -30.0 && theWindow->P1 == 1)
		{
			theWindow->pata1 -= 5.0;
		}
		else
		{
			theWindow->P1 = 0;
			theWindow->pata1 += 5.0;
		}
	}
	if (key == GLFW_KEY_R)
	{
		if (theWindow->patita1 < 15.0 && theWindow->p1 == 0)
		{
			theWindow->patita1 += 5.0;
		}
		else if (theWindow->patita1 == 30.0)
		{
			theWindow->p1 = 1;
			theWindow->patita1 -= 5.0;
		}
		else if (theWindow->patita1 > -15.0 && theWindow->p1 == 1)
		{
			theWindow->patita1 -= 5.0;
		}
		else
		{
			theWindow->p1 = 0;
			theWindow->patita1 += 5.0;
		}
	}
	if (key == GLFW_KEY_T)
	{
		if (theWindow->pata2 < 30.0 && theWindow->P2 == 0)
		{
			theWindow->pata2 += 5.0;
		}
		else if (theWindow->pata2 == 30.0)
		{
			theWindow->P2= 1;
			theWindow->pata2 -= 5.0;
		}
		else if (theWindow->pata2> -30.0 && theWindow->P2 == 1)
		{
			theWindow->pata2 -= 5.0;
		}
		else
		{
			theWindow->P2 = 0;
			theWindow->pata2 += 5.0;
		}
	}
	if (key == GLFW_KEY_Y)
	{
		if (theWindow->patita2 < 15.0 && theWindow->p2 == 0)
		{
			theWindow->patita2 += 5.0;
		}
		else if (theWindow->patita2 == 30.0)
		{
			theWindow->p2 = 1;
			theWindow->patita2 -= 5.0;
		}
		else if (theWindow->patita2 > -15.0 && theWindow->p2 == 1)
		{
			theWindow->patita2 -= 5.0;
		}
		else
		{
			theWindow->p2 = 0;
			theWindow->patita2 += 5.0;
		}
	}
	if (key == GLFW_KEY_U)
	{
		if (theWindow->pata3 < 30.0 && theWindow->P3 == 0)
		{
			theWindow->pata3 += 5.0;
		}
		else if (theWindow->pata3 == 30.0)
		{
			theWindow->P3 = 1;
			theWindow->pata3 -= 5.0;
		}
		else if (theWindow->pata3 > -30.0 && theWindow->P3 == 1)
		{
			theWindow->pata3 -= 5.0;
		}
		else
		{
			theWindow->P3 = 0;
			theWindow->pata3 += 5.0;
		}
	}
	if (key == GLFW_KEY_I)
	{
		if (theWindow->patita3 < 15.0 && theWindow->p3 == 0)
		{
			theWindow->patita3 += 5.0;
		}
		else if (theWindow->patita3 == 30.0)
		{
			theWindow->p3 = 1;
			theWindow->patita3 -= 5.0;
		}
		else if (theWindow->patita3 > -15.0 && theWindow->p3 == 1)
		{
			theWindow->patita3 -= 5.0;
		}
		else
		{
			theWindow->p3 = 0;
			theWindow->patita3 += 5.0;
		}
	}
	if (key == GLFW_KEY_O)
	{
		if (theWindow->pata4 < 30.0 && theWindow->P4 == 0)
		{
			theWindow->pata4 += 5.0;
		}
		else if (theWindow->pata4 == 30.0)
		{
			theWindow->P4 = 1;
			theWindow->pata4 -= 5.0;
		}
		else if (theWindow->pata4 > -30.0 && theWindow->P4 == 1)
		{
			theWindow->pata4 -= 5.0;
		}
		else
		{
			theWindow->P4 = 0;
			theWindow->pata4 += 5.0;
		}
	}
	if (key == GLFW_KEY_P)
	{
		if (theWindow->patita4 < 15.0 && theWindow->p4 == 0)
		{
			theWindow->patita4 += 5.0;
		}
		else if (theWindow->patita4 == 30.0)
		{
			theWindow->p4 = 1;
			theWindow->patita4 -= 5.0;
		}
		else if (theWindow->patita4 > -15.0 && theWindow->p4 == 1)
		{
			theWindow->patita4 -= 5.0;
		}
		else
		{
			theWindow->p4 = 0;
			theWindow->patita4 += 5.0;
		}
	}
	if (key == GLFW_KEY_Q)
	{
		if (theWindow->cola < 50.0 && theWindow->c0 == 0)
		{
			theWindow->cola += 10.0;
		}
		else if (theWindow->cola == 50.0)
		{
			theWindow->c0 = 1;
			theWindow->cola -= 10.0;
		}
		else if (theWindow->cola > -50.0 && theWindow->c0 == 1)
		{
			theWindow->cola -= 10.0;
		}
		else
		{
			theWindow->c0 = 0;
			theWindow->cola += 10.0;
		}
	}


	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
