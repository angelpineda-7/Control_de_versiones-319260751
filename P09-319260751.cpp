/*
Animación:
Sesión 1:
Simple o básica:Por banderas y condicionales (más de 1 transformación geométrica se ve modificada
Sesión 2
Compleja: Por medio de funciones y algoritmos.
Textura Animada
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movDragon;
float movOffset;
float distanciaDragon;
bool ida;
float angulovaria = 0.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
std::vector<glm::vec2> mensajeLetrero;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture FlechaTexture;
Texture NumerosTexture;
Texture Numero1Texture;
Texture Numero2Texture;
Texture snoopyLetras;

Model Kitt_M;
Model Llanta_M;
Model Dragon_M;
Model Tiamat_M;
Model dragonCuerpo;
Model alaDerecha;
Model alaIzquierda;
Model cabeza1;
Model cabeza2;
Model cabeza3;
Model cabeza4;
Model cabeza5;
Model arco;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};


	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,	0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,	0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,	0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int letreroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat letreroVertices[] = {
		-0.5f, 0.0f, 0.0f,		0.01f, 0.6666f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.0f,		0.10f, 0.6666f,		0.0f, -1.0f, 0.0f,
		0.5f, 1.0f, 0.0f,		0.10f, 0.9555f,		0.0f, -1.0f, 0.0f,
		-0.5f, 1.0f, 0.0f,		0.01f, 0.9555f,		0.0f, -1.0f, 0.0f,

	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7);

	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(letreroVertices, letreroIndices, 32, 6);
	meshList.push_back(obj8);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}




int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();
	snoopyLetras = Texture("Textures/snoopyLetras.png");
	snoopyLetras.LoadTextureA();


	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Dragon_M = Model();
	Dragon_M.LoadModel("Models/17174_Tiamat_new.obj");
	dragonCuerpo = Model();
	dragonCuerpo.LoadModel("Models/dragonCuerpo.obj");
	alaDerecha = Model();
	alaDerecha.LoadModel("Models/alaDerecha.obj");
	alaIzquierda = Model();
	alaIzquierda.LoadModel("Models/alaIzquierda.obj");
	cabeza1 = Model();
	cabeza1.LoadModel("Models/cabeza1.obj");
	cabeza2 = Model();
	cabeza2.LoadModel("Models/cabeza2.obj");
	cabeza3 = Model();
	cabeza3.LoadModel("Models/cabeza3.obj");
	cabeza4 = Model();
	cabeza4.LoadModel("Models/cabeza4.obj");
	cabeza5 = Model();
	cabeza5.LoadModel("Models/cabeza5.obj");
	arco = Model();
	arco.LoadModel("Models/arco.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales

	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual

	unsigned int spotLightCount = 0;
	//linterna
	/*spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;*/

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movDragon = 0.0f;
	movOffset = 0.1f;
	distanciaDragon = 20.0f;
	ida = true;

	float tiempo = 50.0f;
	float tiempoTranscurrido = 0.0f;

	mensajeLetrero.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	mensajeLetrero.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	mensajeLetrero.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	mensajeLetrero.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	mensajeLetrero.push_back(glm::vec2(0.6666f, -0.3333f)); //P
	mensajeLetrero.push_back(glm::vec2(0.8888f, -0.3333f)); //R
	mensajeLetrero.push_back(glm::vec2(0.5555f, -0.3333f)); //O
	mensajeLetrero.push_back(glm::vec2(0.6666f, -0.6666f)); //Y
	mensajeLetrero.push_back(glm::vec2(0.4444f, 0.0f));		//E
	mensajeLetrero.push_back(glm::vec2(0.2222f, 0.0f));		//C
	mensajeLetrero.push_back(glm::vec2(0.1111f, -0.6666f)); //T
	mensajeLetrero.push_back(glm::vec2(0.5555f, -0.3333f)); //O
	mensajeLetrero.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	mensajeLetrero.push_back(glm::vec2(0.2222f, 0.0f));		//C
	mensajeLetrero.push_back(glm::vec2(0.6666f, 0.0f));		//G
	mensajeLetrero.push_back(glm::vec2(0.4444f, 0.0f));		//E
	mensajeLetrero.push_back(glm::vec2(0.8888f, 0.0f));		//I
	mensajeLetrero.push_back(glm::vec2(0.7777f, 0.0f));		//H
	mensajeLetrero.push_back(glm::vec2(0.2222f, 0.0f));		//C
	mensajeLetrero.push_back(glm::vec2(0.8888f, -0.6666f)); //
	mensajeLetrero.push_back(glm::vec2(0.5555f, 0.0f));		//F
	mensajeLetrero.push_back(glm::vec2(0.4444f, 0.0f));		//E
	mensajeLetrero.push_back(glm::vec2(0.8888f, -0.3333f)); //R
	mensajeLetrero.push_back(glm::vec2(0.8888f, 0.0f));		//I
	mensajeLetrero.push_back(glm::vec2(0.0f, 0.0f));		//A

	int posicionLetrero = 0;
	int tamanoLetrero = mensajeLetrero.size() - 1;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		angulovaria += 0.5f * deltaTime;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		if (movDragon > -distanciaDragon && ida == true){
			movDragon -= movOffset * deltaTime;
		}
		else if (movDragon < -distanciaDragon) {
			movDragon += movOffset * deltaTime;
			ida = false;
		}
		else if (movDragon < distanciaDragon && ida == false) {
			movDragon += movOffset * deltaTime;
		}
		else {
			movDragon -= movOffset * deltaTime;
			ida = true;
		}

		//Dragón cuerpo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movDragon, 5.0f, 6.0));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		if (ida == false)
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dragonCuerpo.RenderModel();

		//Dragón ala derecha
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.1f, 0.75f, -0.2));
		model = glm::rotate(model, 0.5f * (-sin(glm::radians(angulovaria))), glm::vec3(1.0f, 0.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		alaDerecha.RenderModel();
		model = modelaux;

		//Dragón ala izquierda 
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.1f, 0.75f, 0.2));
		model = glm::rotate(model, 0.5f * (sin(glm::radians(angulovaria))), glm::vec3(1.0f, 0.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		alaIzquierda.RenderModel();
		model = modelaux;

		//Dragón cabeza 1 ESPIRAL DE ARQUIMEDES
		modelaux = model;
		model = glm::translate(model, glm::vec3(-1.1f, 0.9f, -0.35));
		model = glm::rotate(model, 0.05f *((0.0f + 0.01f) * angulovaria * cos(glm::radians(angulovaria))), 
			glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 0.05f * ((0.0f + 0.01f) * angulovaria * sin(glm::radians(angulovaria))), 
			glm::vec3(0.0f, 1.0f, 0.0f));

		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cabeza1.RenderModel();
		model = modelaux;

		//Dragón cabeza 2 MOVIMIENTO SENOIDAL
		modelaux = model;
		model = glm::translate(model, glm::vec3(-1.1f, 1.0f, 0.45));
		model = glm::rotate(model, 0.05f * (angulovaria * 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 0.05f * (2.0f * sin(0.5f * angulovaria + 0.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cabeza2.RenderModel();
		model = modelaux;

		//Dragón cabeza 3 LEMNISCATA
		modelaux = model;
		model = glm::translate(model, glm::vec3(-1.5f, 0.1f, 0.65));
		model = glm::rotate(model, 0.05f * ((10.0f * cos(angulovaria * 0.2f)) / (1.0f + (sin(angulovaria * 0.2f) 
			* sin(angulovaria * 0.2f)))), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 0.05f * ((10.0f * cos(angulovaria * 0.2f) * sin(angulovaria * 0.2f)) / (1.0f 
			+ (sin(angulovaria * 0.2f) * sin(angulovaria * 0.2f)))), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cabeza3.RenderModel();
		model = modelaux;

		//Dragón cabeza 4 CARDIOIDE
		modelaux = model;
		model = glm::translate(model, glm::vec3(-1.8f, 0.2f, 0.0));
		model = glm::rotate(model, 0.05f * (10.0f * (2 * cos(angulovaria * 0.1f) - cos(2 * angulovaria * 0.1f))), 
			glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 0.05f * (10.0f * (2 * sin(angulovaria * 0.1f) - sin(2 * angulovaria * 0.1f))), 
			glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cabeza4.RenderModel();
		model = modelaux;

		//Dragón cabeza 5 MOVIMIENTO CIRCULAR
		modelaux = model;
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, -0.65));
		model = glm::rotate(model, 0.5f * cos(angulovaria * 0.1f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 0.5f * sin(angulovaria * 0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		color = glm::vec3(0.502f, 0.251f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cabeza5.RenderModel();
		model = modelaux;

		//Arco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 25.0));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arco.RenderModel();

		//Letrero
		if (tiempoTranscurrido >= tiempo) {
			posicionLetrero += 1;
			tiempoTranscurrido = 0.0f;
			if (posicionLetrero > tamanoLetrero)
				posicionLetrero = 0;
		}

		tiempoTranscurrido += deltaTime;

		toffset = mensajeLetrero[posicionLetrero];

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.1f, 8.2f, 29.0f));
		model = glm::scale(model, glm::vec3(1.6f, 1.75f, 3.f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		snoopyLetras.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[7]->RenderMesh();

		if (posicionLetrero + 1 > tamanoLetrero)
			toffset = mensajeLetrero[0];
		else
			toffset = mensajeLetrero[posicionLetrero + 1];
		model = glm::translate(model, glm::vec3(0.7f, 0.0f, 0.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[7]->RenderMesh();

		if (posicionLetrero + 2 > tamanoLetrero)
			toffset = mensajeLetrero[0];
		else
			toffset = mensajeLetrero[posicionLetrero + 2];
		model = glm::translate(model, glm::vec3(0.7f, 0.0f, 0.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[7]->RenderMesh();

		if (posicionLetrero + 3 > tamanoLetrero)
			toffset = mensajeLetrero[0];
		else
			toffset = mensajeLetrero[posicionLetrero + 3];
		model = glm::translate(model, glm::vec3(0.7f, 0.0f, 0.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[7]->RenderMesh();

		if (posicionLetrero + 4 > tamanoLetrero)
			toffset = mensajeLetrero[0];
		else
			toffset = mensajeLetrero[posicionLetrero + 4];
		model = glm::translate(model, glm::vec3(0.7f, 0.0f, 0.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[7]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
