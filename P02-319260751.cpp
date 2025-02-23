//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

//shaders nuevos se crearían acá
static const char* vShaderRojo =		"shaders/Rojo.vert";
static const char* vShaderVerde =		"shaders/Verde.vert";
static const char* vShaderAzul =		"shaders/Azul.vert";
static const char* vShaderCafe =		"shaders/Cafe.vert";
static const char* vShaderVerdeOscuro = "shaders/VerdeOscuro.vert";


float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{

	//0
	GLfloat vertices_letras[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		/*1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/

	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 18);
	meshColorList.push_back(letras);


	//1
	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);


	//2
	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);


	//3
	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);


	//4
	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	//5
	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);


	//6
	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);

	//7
	GLfloat vertices_A[] = {
		//X			Y			Z			R		G		B
		-0.85,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.85f,		-0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.65f,		-0.4f,		0.0f,		0.1529,	0.6824,	0.3765,

		-0.85,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.65f,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.65f,		-0.4f,		0.0f,		0.1529,	0.6824,	0.3765,

		-0.55,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.55f,		-0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.35f,		-0.4f,		0.0f,		0.1529,	0.6824,	0.3765,

		-0.55,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.35f,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.35f,		-0.4f,		0.0f,		0.1529,	0.6824,	0.3765,

		-0.65,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.65f,		0.2f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.55f,		0.2f,		0.0f,		0.1529,	0.6824,	0.3765,

		-0.65,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.55f,		0.4f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.55f,		0.2f,		0.0f,		0.1529,	0.6824,	0.3765,

		-0.65,		0.1f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.65f,		-0.1f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.55f,		-0.1f,		0.0f,		0.1529,	0.6824,	0.3765,

		-0.65,		0.1f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.55f,		0.1f,		0.0f,		0.1529,	0.6824,	0.3765,
		-0.55f,		-0.1f,		0.0f,		0.1529,	0.6824,	0.3765,

	};

	MeshColor* A = new MeshColor();
	A->CreateMeshColor(vertices_A, 144);
	meshColorList.push_back(A);

	//8
	GLfloat vertices_U[] = {
		//X			Y			Z			R		G		B
		-0.25,		0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		-0.25f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		-0.05f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,

		-0.25,		0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		-0.05f,		0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		-0.05f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,

		0.05,		0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		0.05f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		0.25f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,

		0.05,		0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		0.25f,		0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		0.25f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,

		-0.05,		-0.2f,		0.0f,		0.5569f,0.2627f,0.6784f,
		-0.05f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,
		0.05f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,

		-0.05,		-0.2f,		0.0f,		0.5569f,0.2627f,0.6784f,
		0.05f,		-0.2f,		0.0f,		0.5569f,0.2627f,0.6784f,
		0.05f,		-0.4f,		0.0f,		0.5569f,0.2627f,0.6784f,

	};

	MeshColor* U = new MeshColor();
	U->CreateMeshColor(vertices_U, 108);
	meshColorList.push_back(U);

	//9
	GLfloat vertices_P[] = {
		//X			Y			Z			R		G		B
		0.35,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.35f,		-0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.55f,		-0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,

		0.35,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.55f,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.55f,		-0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,

		0.65,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.65f,		-0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.85f,		-0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,

		0.65,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.85f,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.85f,		-0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,

		0.55,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.55f,		0.2f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.65f,		0.2f,		0.0f,		0.2039f,0.5961f,0.8588f,

		0.55,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.65f,		0.4f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.65f,		0.2f,		0.0f,		0.2039f,0.5961f,0.8588f,

		0.55,		0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.55f,		-0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.65f,		-0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,

		0.55,		0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.65f,		0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,
		0.65f,		-0.1f,		0.0f,		0.2039f,0.5961f,0.8588f,

	};

	MeshColor* P = new MeshColor();
	P->CreateMeshColor(vertices_P, 144);
	meshColorList.push_back(P);

}


void CreateShaders()
{

	//0
	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	//1
	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	//2
	Shader* shader3 = new Shader();//shader rojo
	shader3->CreateFromFiles(vShaderRojo, fShader);
	shaderList.push_back(*shader3);

	//3
	Shader* shader4 = new Shader();//shader verde
	shader4->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shader4);

	//4
	Shader* shader5 = new Shader();//shader azul
	shader5->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shader5);

	//5
	Shader* shader6 = new Shader();//shader cafe
	shader6->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shader6);

	//6
	Shader* shader7 = new Shader();//shader verde oscuro
	shader7->CreateFromFiles(vShaderVerdeOscuro, fShader);
	shaderList.push_back(*shader7);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -3.5f));
		model = glm::scale(model, glm::vec3(1.0f, 0.6f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -3.5f));
		model = glm::scale(model, glm::vec3(1.0f, 0.6f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[8]->RenderMeshColor();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -3.5f));
		model = glm::scale(model, glm::vec3(1.0f, 0.6f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[9]->RenderMeshColor();


		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.85f, -4.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.85f, -4.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.45f, -3.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.45f, -3.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.55f, -4.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.9f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, -3.9f));
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, -0.3f, -3.9f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, -0.3f, -3.9f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.175f, -3.9f));
		model = glm::scale(model, glm::vec3(0.95f, 0.55f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/