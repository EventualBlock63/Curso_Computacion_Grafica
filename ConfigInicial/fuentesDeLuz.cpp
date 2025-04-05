/*Práctica 9
Fernando Martínez
05 de Abril 2025
318273745
*/

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow * window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 1480, HEIGHT = 950;
int SCREEN_WIDTH, SCREEN_HEIGHT;
glm::vec3 secondLightPos(0.8f, 0.8f, 0.0f);
float movelightPos = 0.0f;
float activador = 0.0f;
float linterna = 0.0f;
float reloj = 0.0f;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(5.0f,2.0f, 3.3f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica9_Fernando_Martinez", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


	// Setup and compile our shaders
	Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");



	// Load models
	Model dog((char*)"Models/RedDog.obj");
	Model wheel((char*)"Models/Corvette_Wheel_V2_OBJ.obj");
	Model car((char*)"Models/Porsche_911_GT2_v2.obj");
	Model carVerde((char*)"Models/Porsche_911_GT2_v3.obj");
	Model carLAMBO((char*)"Models/Lamborghini_Aventador.obj");
	Model estacionamiento((char*)"Models/ParkingLot.obj");
	Model sol((char*)"Models/Sol.obj");
	Model luna((char*)"Models/Luna.obj");
	Model poste((char*)"Models/PosteLuz.obj");



	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);



		//Load Model
		// Sol: se mueve de izquierda a derecha en parábola
		lightPos.x = cos(reloj) * 10.0f;
		lightPos.y = sin(reloj) * 10.0f;

		// Luna: misma trayectoria, pero opuesta
		secondLightPos.x = cos(reloj) * 10.0f;
		secondLightPos.y = sin(reloj) * 10.0f;


		GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(lightPosLoc, lightPos.x + movelightPos, lightPos.y + movelightPos, lightPos.z + movelightPos);
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.position"), secondLightPos.x, secondLightPos.y, secondLightPos.z);

		// Set lights properties
		// SOL
		if (reloj < 3.1 && reloj > 0 && activador == 1) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "sunLight.position"), lightPos.x + movelightPos, lightPos.y + movelightPos, lightPos.z + movelightPos);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "sunLight.ambient"), 7.0f, 3.5f, 1.4f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "sunLight.diffuse"), 0.2f, 0.7f, 0.4f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "sunLight.specular"), 0.3f, 0.6f, 0.4f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "sunLight.constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "sunLight.linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "sunLight.quadratic"), 0.0075f);
		}
		else {
			// Desactivar la luz del sol
			glUniform3f(glGetUniformLocation(lightingShader.Program, "sunLight.ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "sunLight.diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "sunLight.specular"), 0.0f, 0.0f, 0.0f);
		}

		// LUNA
		if (reloj >= 3.1 || reloj <= 0 || activador == 0) {
			glUniform3f(glGetUniformLocation(lightingShader.Program, "moonLight.position"), secondLightPos.x, secondLightPos.y, secondLightPos.z);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "moonLight.ambient"), 1.5f, 1.5f, 2.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "moonLight.diffuse"), 0.1f, 1.05f, 1.1f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "moonLight.specular"), 0.4f, 0.9f, 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "moonLight.constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "moonLight.linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "moonLight.quadratic"), 0.0075f);
		}
		else {
			// Desactivar la luz de la luna
			glUniform3f(glGetUniformLocation(lightingShader.Program, "moonLight.ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "moonLight.diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "moonLight.specular"), 0.0f, 0.0f, 0.0f);
		}



		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		//GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.0f, 0.0f, 0.0f);


		// Point light 1 //Lampara que se mueve
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.0f);

		// SpotLight 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), -2.75f, 0.3f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 0.0f, 0.0f, 1.0f);
		if (linterna == 1) { // Activar la linterna
			glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 5.0f, 5.0f, 5.0f);
		}
		else // Desactivar la linterna
		{
			glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		}
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"),0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(18.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(25.0f)));

		// SpotLight 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight2.position"), -1.75f, 0.3f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight2.direction"), 0.0f, 0.0f, 1.0f);
		if (linterna == 1) { // Activar la linterna 2
			glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight2.ambient"), 5.0f, 5.0f, 5.0f);
		}
		else { // Desactivar la linterna 2
			glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight2.ambient"), 0.0f, 0.0f, 0.0f);
		}
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight2.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight2.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight2.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight2.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight2.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight2.cutOff"), glm::cos(glm::radians(18.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight2.outerCutOff"), glm::cos(glm::radians(25.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		//glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	

		//Carga de modelo 
        view = camera.GetViewMatrix();	
		// Draw the loaded model
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(0.0f, -0.25f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		dog.Draw(lightingShader);
		//--------------------------------------------------------------------------------------------------
		glm::mat4 modelWheel(1);
		modelWheel = glm::translate(modelWheel, glm::vec3(0.75f, -0.6f, 1.0f));
		modelWheel = glm::scale(modelWheel, glm::vec3(0.05f, 0.05f, 0.05f));
		modelWheel = glm::rotate(modelWheel, 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelWheel));
		wheel.Draw(lightingShader);
		//--------------------------------------------------------------------------------------------------
		glm::mat4 modelCarro(1);
		modelCarro = glm::translate(modelCarro, glm::vec3(-2.3f, -0.15f, 0.6f));
		modelCarro = glm::scale(modelCarro, glm::vec3(0.75f, 0.75f, 0.75f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCarro));
		car.Draw(lightingShader);
		//--------------------------------------------------------------------------------------------------
		glm::mat4 modelCarroVerde(1);
		modelCarroVerde = glm::translate(modelCarroVerde, glm::vec3(5.1f, -0.15f, 1.4f));
		modelCarroVerde = glm::scale(modelCarroVerde, glm::vec3(0.75f, 0.75f, 0.75f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCarroVerde));
		carVerde.Draw(lightingShader);
		//--------------------------------------------------------------------------------------------------
		glm::mat4 modelCarroLAMBO(1);
		modelCarroLAMBO = glm::translate(modelCarroLAMBO, glm::vec3(-5.3f, -0.6f, 0.6f));
		modelCarroLAMBO = glm::scale(modelCarroLAMBO, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCarroLAMBO));
		carLAMBO.Draw(lightingShader);
		//--------------------------------------------------------------------------------------------------
		glm::mat4 modelPark(1);
		modelPark = glm::translate(modelPark, glm::vec3(-15.0f, -0.65f, -3.0f));
		modelPark = glm::scale(modelPark, glm::vec3(0.5f, 0.5f, 0.5f));
		modelPark = glm::rotate(modelPark, 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPark));
		estacionamiento.Draw(lightingShader);
		//--------------------------------------------------------------------------------------------------
		glm::mat4 modelPosteLuz(1);
		modelPosteLuz = glm::translate(modelPosteLuz, glm::vec3(5.0f, -0.75f, 4.0f));
		modelPosteLuz = glm::scale(modelPosteLuz, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPosteLuz));
		poste.Draw(lightingShader);


	
		//model = glm::mat4(1);
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		/*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
	    Dog.Draw(lightingShader);

		glm::mat4 modelpelotita(1);
		modelpelotita = glm::translate(modelpelotita, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelpelotita));
		Pelota.Draw(lightingShader);
		
		glm::mat4 modeltubito(1);
		modeltubito = glm::translate(modeltubito, glm::vec3(-1.0f, -0.3f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modeltubito));
		Tubo.Draw(lightingShader);*/
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);
	
		//================================================================================================CUBO QUE SE MUEVE
		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		//for (GLuint i = 0; i < 4; i++)
		//{
		//	model = glm::mat4(1);
		//	model = glm::translate(model, pointLightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glBindVertexArray(VAO);
		//	//dog.Draw(lightingShader);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		glBindVertexArray(0);
		//================================================================================================CUBO QUE SE MUEVE
		lightingShader.Use();
		if (activador == 1) {
			// Dibujar el sol (Lampara 1)
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos + movelightPos);
			model = glm::scale(model, glm::vec3(0.8f));
			glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			sol.Draw(lightingShader);
		}
		else {
			// Dibujar la luna (Lampara 1)
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos + movelightPos);
			model = glm::scale(model, glm::vec3(0.3f));
			glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			luna.Draw(lightingShader);
		}

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	/*if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z += 0.01f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z -= 0.01f;
	}*/
	
	
}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (reloj < 3 && (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS))
	{
		activador = 1.0f;
		reloj += 0.1f;
	}

	if (reloj > 0 && (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS))
	{
		activador = 0.0f;
		reloj -= 0.1f;
	}

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
	//====================================================================================================
	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 0.0f);
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
	//====================================================================================================
	if (keys[GLFW_KEY_1])
	{
		active = !active;
		if (active)
		{
			linterna = 1.0f;
		}
		else
		{
			linterna = 0.0f;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}