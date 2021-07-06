/*
* Grupo:
* - Renzo Alessandro Sucari Velasquez
* - Karen Alejandra Fernandez Fernandez Davila
*
* Curso:
* - Computación Gráfica - CCOMP7-1
*/

#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Rubikh.h"

#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

/*Path*/
std::string PATH = "C:/Users/Asus/Documents/CompuGrafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/CubeRubik_Final/";

RubikCube* myRubik;

/*Global Camera Values*/
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

/*timing*/
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

/*Global print Values*/
int mode = 0;
bool unit = false;
bool giro = true;
short axis = 0;
short layer = 0;
bool isclock = 0;
bool iscounterclock = 0;

/*Global solver Values*/
std::string commands;
std::vector<std::string> movements;
int movesPos = 0;
bool solving = false;

/*Input*/
bool state = 0; // ir y volver de los estados de visualizacion
bool counter_clock = 0; // Sentido horario o antihorario

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void random_sequence(int number, RubikCube* cube) {
	for (int i = 0; i < number; i++) {
		int r = rand() % 6;
		switch (r) {
		case 0:
			cube->F(1, false);
			commands += "F ";
			break;
		case 1:
			cube->R(1, false);
			commands += "R ";
			break;
		case 2:
			cube->U(1, false);
			commands += "U ";
			break;
		case 3:
			cube->B(1, false);
			commands += "B ";
			break;
		case 4:
			cube->L(1, false);
			commands += "L ";
			break;
		case 5:
			cube->D(1, false);
			commands += "D ";
			break;

		}

	}
}

void stepSolver(RubikCube* cube, int pos) {
	switch (movements[pos][0]) {
	case 'F':
		if (movements[pos].size() == 2) {
			if (movements[pos][1] == '\'')
				cube->F(1, true);
			if (movements[pos][1] == '2')
				cube->F(2, false);
		}
		else {
			cube->F(1, false);
		}
		break;
	case 'R':
		if (movements[pos].size() == 2) {
			if (movements[pos][1] == '\'')
				cube->R(1, true);
			if (movements[pos][1] == '2')
				cube->R(2, false);
		}
		else {
			cube->R(1, false);
		}
		break;
	case 'U':
		if (movements[pos].size() == 2) {
			if (movements[pos][1] == '\'')
				cube->U(1, true);
			if (movements[pos][1] == '2')
				cube->U(2, false);
		}
		else {
			cube->U(1, false);
		}
		break;
	case 'B':
		if (movements[pos].size() == 2) {
			if (movements[pos][1] == '\'')
				cube->B(1, true);
			if (movements[pos][1] == '2')
				cube->B(2, false);
		}
		else {
			cube->B(1, false);
		}
		break;
	case 'L':
		if (movements[pos].size() == 2) {
			if (movements[pos][1] == '\'')
				cube->L(1, true);
			if (movements[pos][1] == '2')
				cube->L(2, false);
		}
		else {
			cube->L(1, false);
		}
		break;
	case 'D':
		if (movements[pos].size() == 2) {
			if (movements[pos][1] == '\'')
				cube->D(1, true);
			if (movements[pos][1] == '2')
				cube->D(2, false);
		}
		else {
			cube->D(1, false);
		}
		break;
	}
}

void whatDraw(RubikCube* cube, int shaderID) {
	switch (mode) {
	case 0:
		cube->drawRubik(shaderID, unit);
		break;
	case 1:
		cube->drawCenters(shaderID);
		break;
	case 2:
		cube->drawCorners(shaderID);
		break;
	case 3:
		cube->drawEdges(shaderID);
		break;
	}
}

void menu()
{
	std::cout << "\n\t\t\tCUBO RUBIK - METODO DE FRIDRICH					   \n";
	std::cout << "\t\t\t-------------------------------						   \n";
	std::cout << "\tAlumnos: Renzo Alessandro Sucari Velasquez                 \n";
	std::cout << "\t         Karen Alejandra Fernandez Fernandez Davila        \n";
	std::cout << "\n\n\t---------------------- MENU -------------------------- \n";
	std::cout << "\tKEY I: Desordenar el Cubo Rubik							   \n";
	std::cout << "\tKEY O: Ordenar el Cubo Rubik							   \n";
	std::cout << "\tKEY G: Visualizacion 360 del Cubo Rubik					   \n";
	std::cout << "\tESC  : SALIR                                               \n";
	std::cout << "\n\t---------------- CAMARA WALK AROUND -------------------  \n";
	std::cout << "\t                    KEY W: Adelante                        \n";
	std::cout << "\t          KEY A: Izquierda     KEY D: Derecha              \n";
	std::cout << "\t                    KEY S: Atras                           \n";
	std::cout << "\n\t------------------- MOVIMIENTOS -----------------------  \n";
	std::cout << "\tKEY RIGHT: Horario            KEY LEFT: Antihorario        \n";
	std::cout << "\tKEY 1: Movimiento FRONT       KEY 2: Movimiento RIGHT      \n";
	std::cout << "\tKEY 3: Movimiento UP          KEY 4: Movimiento LEFT       \n";
	std::cout << "\tKEY 5: Movimiento BACK        KEY 6: Movimiento DOWN       \n";
	std::cout << "\n\t-------------- PROPUESTA DE ANIMACION -----------------  \n";
	std::cout << "\tKEY B: Separacion o Union del Cubo de Rubik                \n";
	std::cout << "\tKEY N: Visualicacion de los Cubos Individualmente:         \n";
	std::cout << "\t     1 PRESS: Dibujar el Cubo de Rubik                     \n";
	std::cout << "\t     2 PRESS: Dibujar los Centros                          \n";
	std::cout << "\t     3 PRESS: Dibujar los Vertices                         \n";
	std::cout << "\t     4 PRESS: Dibujar las Aristas                          \n";
	std::cout << "\tKEY M: Modos de rasterizacion de poligono:                 \n";
	std::cout << "\t     1 PRESS: GL-LINE                                      \n";
	std::cout << "\t     2 PRESS: GL-FILL                                      \n";
	std::cout << "\t-------------------------------------------------------   \n\n";
}

void menu_with_color()
{
	std::cout << "\n\t\t\033[92m   CUBO RUBIK - METODO DE FRIDRICH					   \033[0m\n";
	std::cout << "\t\t\033[92m   -------------------------------					   \033[0m\n";
	std::cout << "\tAlumnos: Renzo Alessandro Sucari Velasquez                 \n";
	std::cout << "\t         Karen Alejandra Fernandez Fernandez Davila        \n";
	std::cout << "\n\n\t\033[93m---------------------- MENU -------------------------- \033[0m\n";
	std::cout << "\t\033[96mKEY I\033[0m: Desordenar el Cubo Rubik							  \n";
	std::cout << "\t\033[96mKEY O\033[0m: Ordenar el Cubo Rubik							      \n";
	std::cout << "\t\033[96mKEY G\033[0m: Visualizacion 360 del Cubo Rubik					  \n";
	std::cout << "\t\033[96mESC  \033[0m: SALIR                                               \n";
	std::cout << "\n\t\033[93m---------------- CAMARA WALK AROUND -------------------  \033[0m\n";
	std::cout << "\t                    \033[96mKEY W\033[0m: Adelante                        \n";
	std::cout << "\t          \033[96mKEY A\033[0m: Izquierda     \033[96mKEY D\033[0m: Derecha \n";
	std::cout << "\t                    \033[96mKEY S\033[0m: Atras                           \n";
	std::cout << "\n\t\033[93m------------------- MOVIMIENTOS -----------------------  \033[0m\n";
	std::cout << "\t\033[96mKEY RIGHT\033[0m: Horario            \033[96mKEY LEFT\033[0m: Antihorario        \n";
	std::cout << "\t\033[96mKEY 1\033[0m: Movimiento FRONT       \033[96mKEY 2\033[0m: Movimiento RIGHT      \n";
	std::cout << "\t\033[96mKEY 3\033[0m: Movimiento UP          \033[96mKEY 4\033[0m: Movimiento LEFT       \n";
	std::cout << "\t\033[96mKEY 5\033[0m: Movimiento BACK        \033[96mKEY 6\033[0m: Movimiento DOWN       \n";
	std::cout << "\n\n\t\033[93m------------- PROPUESTA DE ANIMACION ----------------- \033[0m\n";
	std::cout << "\t\033[96mKEY B\033[0m: Separacion o Union del Cubo de Rubik                \n";
	std::cout << "\t\033[96mKEY N\033[0m: Modos de vizualizar el Cubo de Rubik:               \n";
	std::cout << "\t     \033[96m1 PRESS\033[0m: Dibujar el Cubo de Rubik                     \n";
	std::cout << "\t     \033[96m2 PRESS\033[0m: Dibujar los Centros                          \n";
	std::cout << "\t     \033[96m3 PRESS\033[0m: Dibujar los Vertices                         \n";
	std::cout << "\t     \033[96m4 PRESS\033[0m: Dibujar las Aristas                          \n";
	std::cout << "\t\033[96mKEY M\033[0m: Modos de rasterizacion de poligono:                 \n";
	std::cout << "\t     \033[96m1 PRESS\033[0m: GL-LINE                                      \n";
	std::cout << "\t     \033[96m2 PRESS\033[0m: GL-FILL                                      \n";
	std::cout << "\t\033[93m-------------------------------------------------------   \033[0m\n\n";
}

int main() {
	//menu();
	menu_with_color();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Cubo Rubik - Fridrich Solve", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader myShader((PATH + "shaders/vertexShader.vs").c_str(), (PATH + "shaders/fragmentShader.fs").c_str());

	/*Render Loop*/

	myRubik = new RubikCube;

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);

	unsigned int modelLoc = glGetUniformLocation(myShader.ID, "model");


	unsigned int viewLoc = glGetUniformLocation(myShader.ID, "view");


	unsigned int projLoc = glGetUniformLocation(myShader.ID, "projection");


	/*Matriz view*/
	glm::mat4 view = glm::mat4(1.0f);
	float rotacion = (float)glfwGetTime() * glm::radians(15.f);

	myRubik->setShader(myShader.ID);
	myRubik->setWindow(window);

	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		//glfwSetKeyCallback(window, key_callback);

		//glClearColor(0.5215f, 0.5725f, 0.6196f, 1.0f); //Name: learnopengl
		//glClearColor(0.7333f, 0.8196f, 0.9607f, 1.0f); //Name: Beau Blue
		glClearColor(0.1803f, 0.8117f, 0.7921f, 1.0f);   //Name: Maximum Blue Green
		//glClearColor(0.9764f, 0.9529f, 0.8705f, 1.0f); //Name: Beige
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*Rotación y traslación de una matriz*/
		/*glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/

		myRubik->setUnite(unit);
		myRubik->colors();

		myShader.use();

		whatDraw(myRubik, myShader.ID);


		if (solving) {
			stepSolver(myRubik, movesPos);
			movesPos += 1;
			if (movesPos >= movements.size()) {
				movesPos = 0;
				movements.clear();
				solving = 0;
			}
		}

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		rotacion = giro ? (float)glfwGetTime() * glm::radians(15.f) : rotacion;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, rotacion, glm::vec3(1.0f, 2.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(0);

		//Sleep(50);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	/*Close Window*/
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	/*Camera*/
	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/* Desordenar y Ordenar el cubo*/
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		random_sequence(20, myRubik);
		std::cout << "------------------------------------------------------------------------" << std::endl;
		std::cout << "\033[91mSECUENCIA ALEATORIA:\033[0m " << commands << std::endl;
		//std::cout << "SECUENCIA ALEATORIA: " << commands << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		movements = myRubik->solve(commands);
		commands = "";
		solving = true;
	}

	/*Giro 360 grados del cubo - Pause*/
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		giro = !giro;
	}

	/*Sentido horario o antihorario*/
	if (counter_clock == 1 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		counter_clock = 0;
	}
	if (counter_clock == 0 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		counter_clock = 1;
	}

	/*Movimientos basicos del Cubo F,R,U,L,B,D*/
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		myRubik->F(1, counter_clock);
		commands += "F ";
		std::cout << "\033[33mSECUENCIA ALEATORIA:\033[0m " << commands << std::endl;
		//std::cout << "SECUENCIA ALEATORIA: " << commands << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		myRubik->R(1, counter_clock);
		commands += "R ";
		std::cout << "\033[92mSECUENCIA ALEATORIA:\033[0m " << commands << std::endl;
		//std::cout << "SECUENCIA ALEATORIA: " << commands << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		myRubik->U(1, counter_clock);
		commands += "U ";
		std::cout << "\033[97mSECUENCIA ALEATORIA:\033[0m " << commands << std::endl;
		//std::cout << "SECUENCIA ALEATORIA: " << commands << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		myRubik->L(1, counter_clock);
		commands += "L ";
		std::cout << "\033[94mSECUENCIA ALEATORIA:\033[0m " << commands << std::endl;
		//std::cout << "SECUENCIA ALEATORIA: " << commands << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		myRubik->B(1, counter_clock);
		commands += "B ";
		std::cout << "\033[93mSECUENCIA ALEATORIA:\033[0m " << commands << std::endl;
		//std::cout << "SECUENCIA ALEATORIA: " << commands << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		myRubik->D(1, counter_clock);
		commands += "D ";
		std::cout << "\033[91mSECUENCIA ALEATORIA:\033[0m " << commands << std::endl;
		//std::cout << "SECUENCIA ALEATORIA: " << commands << std::endl;
	}

	/*Animacion Propuesta*/
	else if (state == 0 && key == GLFW_KEY_M && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); state = 1;
	}
	else if (state == 1 && key == GLFW_KEY_M && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  state = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		unit = !unit;
	}
	else if (mode == 0 && key == GLFW_KEY_N && action == GLFW_PRESS) {
		mode = 1;
	}
	else if (mode == 1 && key == GLFW_KEY_N && action == GLFW_PRESS) {
		mode = 2;
	}
	else if (mode == 2 && key == GLFW_KEY_N && action == GLFW_PRESS) {
		mode = 3;
	}
	else if (mode == 3 && key == GLFW_KEY_N && action == GLFW_PRESS) {
		mode = 0;
	}
}


