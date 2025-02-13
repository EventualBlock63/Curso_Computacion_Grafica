#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Práctica 2 Fernando", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		-1,  -0.5f, 0.0f,    0.67f,0.90f,0.42f,  // T1 0
		-0.75f, -0.35f, 0.0f,    0.67f,0.90f,0.42f,  // T1 1
		-0.7f, -0.45f, 0.0f,   0.67f,0.90f,0.42f,  // T1 2

		-0.75f, -0.35f, 0.0f,    0.67f,0.90f,0.42f,  // T2 1
		-0.65f, -0.55f, 0.0f,    0.67f,0.90f,0.42f,  // T2 3
		-0.05f, 0.05f, 0.0f,   0.67f,0.90f,0.42f,  // T2 4

		-0.65f, -0.55f, 0.0f,    0.67f,0.90f,0.42f,  // T3 3
		-0.05f, 0.05f, 0.0f,   0.67f,0.90f,0.42f,  // T3 4
		 0.5f, -0.4f, 0.0f,   0.67f,0.90f,0.42f,  // T3 5

		 0.55f, 0, 0.0f,    0.67f,0.90f,0.42f,  // T4 6
		-0.05f, 0.05f, 0.0f,   0.67f,0.90f,0.42f,  // T4 4
		 0.5f, -0.4f, 0.0f,   0.67f,0.90f,0.42f,  // T4 5

		 0.55f, 0, 0.0f,    1.0f,0.98f,0.0f,  // T5 6
		-0.05f, 0.05f, 0.0f,   1.0f,0.98f,0.0f,  // T5 4
		 0.45f, 0.5f, 0.0f,   1.0f,0.98f,0.0f,  // T5 7

		 0.55f, 0, 0.0f,    1.0f,0.98f,0.0f,  // T6 6
		 0.70f, 0.45f, 0.0f,   1.0f,0.98f,0.0f,  // T6 8
		 0.45f, 0.5f, 0.0f,   1.0f,0.98f,0.0f,  // T6 7

		 0.75f, 0.47f, 0.0f,    0.76f,0.7529f,0.16f,  // T7 9
		 0.70f, 0.45f, 0.0f,   0.76f,0.7529f,0.16f,  // T7 8
		 0.45f, 0.5f, 0.0f,   0.76f,0.7529f,0.16f,  // T7 7

		 0.75f, 0.47f, 0.0f,    0.76f,0.7529f,0.16f,  // T8 9
		 0.70f, 0.45f, 0.0f,   0.76f,0.7529f,0.16f,  // T8 8
		 0.77f, 0.25f, 0.0f,   0.76f,0.7529f,0.16f,  // T8 10

		 0.64f, 0.27f, 0.0f,    0.8549f,0.8431f,0.2f,  // T9 11
		 0.70f, 0.45f, 0.0f,   0.8549f,0.8431f,0.2f,  // T9 8
		 0.77f, 0.25f, 0.0f,   0.8549f,0.8431f,0.2f,  // T9 10

		 0.64f, 0.27f, 0.0f,    0.76f,0.7529f,0.16f,  // T10 11
		 0.55f, 0, 0.0f,    0.76f,0.7529f,0.16f,  // T10 6
		 0.70f, 0.26f, 0.0f,   0.76f,0.7529f,0.16f,  // T10 12

		 0.67f, 0, 0.0f,    0.76f,0.7529f,0.16f,  // T11 13
		 0.55f, 0, 0.0f,    0.76f,0.7529f,0.16f,  // T11 6
		 0.70f, 0.26f, 0.0f,   0.76f,0.7529f,0.16f,  // T11 12

		 0.67f, 0, 0.0f,    0.5843f,0.7647f,0.1608f,  // T12 13
		 0.55f, 0, 0.0f,    0.5843f,0.7647f,0.1608f,  // T12 6
		 0.5f, -0.4f, 0.0f,   0.5843f,0.7647f,0.1608f,  // T12 5

		 0.67f, 0, 0.0f,    0.5843f,0.7647f,0.1608f,  // T13 13
		 0.5f, -0.4f, 0.0f,   0.5843f,0.7647f,0.1608f,  // T13 5
		 0.63f, -0.38f, 0.0f,   0.5843f,0.7647f,0.1608f,  // T13 14

		 0.18f, -0.44f, 0.0f,    0.67f,0.90f,0.42f,  // T14 15
		 0.5f, -0.4f, 0.0f,   0.67f,0.90f,0.42f,  // T14 5
		 0.20f, -0.5f, 0.0f,   0.67f,0.90f,0.42f,  // T14 16

		 0.77f, -0.52f, 0.0f,    0.67f,0.90f,0.42f,  // T15 17
		 0.5f, -0.4f, 0.0f,   0.67f,0.90f,0.42f,  // T15 5
		 0.20f, -0.5f, 0.0f,   0.67f,0.90f,0.42f,  // T15 16

		 0.74f, -0.51f, 0.0f,    0.5843f,0.7647f,0.1608f,  // T16 18
		 0.5f, -0.4f, 0.0f,   0.5843f,0.7647f,0.1608f,  // T16 5
		 0.63f, -0.38f, 0.0f,   0.5843f,0.7647f,0.1608f,  // T16 14

		 0.63f, -0.38f, 0.0f,   0.5843f,0.7647f,0.1608f, // T17 14
		 0.74f, -0.51f, 0.0f,    0.5843f,0.7647f,0.1608f,  // T17 18
		 0.80f, -0.51f, 0.0f,   0.5843f,0.7647f,0.1608f,  // T17 19

		 -1,  -0.5f, 0.0f,    1.0f,1.0f,1.0f,  // 0
		-0.75f, -0.35f, 0.0f,    1.0f,1.0f,1.0f,  // 1
		-0.7f, -0.45f, 0.0f, 1.0f, 1.0f, 1.0f,  // 2

		-0.75f, -0.35f, 0.0f,    1.0f,1.0f,1.0f,  // 1
		-0.05f, 0.05f, 0.0f,   1.0f,1.0f,1.0f,  // 4
		0.55f, 0, 0.0f,    1.0f,1.0f,1.0f,  // 6
		0.5f, -0.4f, 0.0f,   1.0f,1.10f,1.0f,  // 5
		-0.65f, -0.55f, 0.0f,    1.0f,1.10f,1.0f,  // 3

		-0.05f, 0.05f, 0.0f,   1.0f,1.0f,1.0f,  // 4
		0.45f, 0.5f, 0.0f,   1.0f,1.0f,1.0f,  // 7
		0.70f, 0.45f, 0.0f,   1.0f,1.0f,1.0f,  // 8
		0.55f, 0, 0.0f,    1.0f,1.0f,1.0f,  // 6
		 
		0.45f, 0.5f, 0.0f,   1.0f,1.0f,1.0f,  // 7
		0.75f, 0.47f, 0.0f,    1.0f,1.0f,1.0f,  // 9
		 0.77f, 0.25f, 0.0f,   1.0f,1.0f,1.0f,  // 10
		 0.70f, 0.45f, 0.0f,   1.0f,1.0f,1.0f,  // 8
		 
		  0.70f, 0.45f, 0.0f,   1.0f,1.0f,1.0f,  // 8
		  0.77f, 0.25f, 0.0f,   1.0f,1.0f,1.0f,  // 10
		  0.64f, 0.27f, 0.0f,    1.0f,1.0f,1.0f,  // 11

		  0.64f, 0.27f, 0.0f,    1.0f,1.0f,1.0f,  // 11
		  0.70f, 0.26f, 0.0f,   1.0f,1.0f,1.0f,  // 12
		  0.67f, 0, 0.0f,    1.0f,1.0f,1.0f,  // 13
		  0.55f, 0, 0.0f,    1.0f,1.0f,1.0f,  // 6

		  0.55f, 0, 0.0f,    1.0f,1.0f,1.0f,  // 6
		  0.67f, 0, 0.0f,    1.0f,1.0f,1.0f,  // 13
		  0.63f, -0.38f, 0.0f,   1.0f,1.0f,1.0f,  // 14
		  0.5f, -0.4f, 0.0f, 1.0f, 1.10f, 1.0f,  // 5

		  0.18f, -0.44f, 0.0f, 1.0f, 1.0f, 1.0f,  // 15
			0.5f, -0.4f, 0.0f, 1.0f, 1.0f, 1.0f,  // 5
			0.20f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // 16
		 
  		  0.20f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // 16
			0.5f, -0.4f, 0.0f, 1.0f, 1.10f, 1.0f,  // 5
			0.77f, -0.52f, 0.0f, 1.0f, 1.10f, 1.0f,  // 17

			0.5f, -0.4f, 0.0f, 1.0f, 1.0f, 1.0f,  // 5
			 0.63f, -0.38f, 0.0f, 1.0f, 1.0f, 1.0f,  // 14
			 0.80f, -0.51f, 0.0f, 1.0f, 1.0f, 1.0f,  // 19
			 0.74f, -0.51f, 0.0f, 1.0f, 1.0f, 1.0f,  // 18
	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        glPointSize(1);
        //glDrawArrays(GL_POINTS,0,1);
        
        //glDrawArrays(GL_LINES,0,2);
        glDrawArrays(GL_LINE_LOOP, 51, 3);
		glDrawArrays(GL_LINE_LOOP, 54, 5);
		glDrawArrays(GL_LINE_LOOP, 59, 4);
		glDrawArrays(GL_LINE_LOOP, 63, 4);
		glDrawArrays(GL_LINE_LOOP, 67, 3);
		glDrawArrays(GL_LINE_LOOP, 70, 4);
		glDrawArrays(GL_LINE_LOOP, 74, 4);
		glDrawArrays(GL_LINE_LOOP, 78, 3);
		glDrawArrays(GL_LINE_LOOP, 81, 3);
		glDrawArrays(GL_LINE_LOOP, 84, 4);
        
        glDrawArrays(GL_TRIANGLES,0,3); //T1
		glDrawArrays(GL_TRIANGLES, 3, 3); //T2
		glDrawArrays(GL_TRIANGLES, 6, 3); //T3
		glDrawArrays(GL_TRIANGLES, 9, 3); //T4
		glDrawArrays(GL_TRIANGLES, 12, 3); //T5
		glDrawArrays(GL_TRIANGLES, 15, 3); //T6
		glDrawArrays(GL_TRIANGLES, 18, 3); //T7
		glDrawArrays(GL_TRIANGLES, 21, 3); //T8
		glDrawArrays(GL_TRIANGLES, 24, 3); //T9
		glDrawArrays(GL_TRIANGLES, 27, 3); //T10
		glDrawArrays(GL_TRIANGLES, 30, 3); //T11
		glDrawArrays(GL_TRIANGLES, 33, 3); //T12
		glDrawArrays(GL_TRIANGLES, 36, 3); //T13
		glDrawArrays(GL_TRIANGLES, 39, 3); //T14
		glDrawArrays(GL_TRIANGLES, 42, 3); //T15
		glDrawArrays(GL_TRIANGLES, 45, 3); //T16
		glDrawArrays(GL_TRIANGLES, 48, 3); //T17
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);
		
        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}