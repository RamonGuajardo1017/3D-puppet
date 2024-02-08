#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, 
		   GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpped);

	//Funciones para controlar la camara con el teclado + mouse
	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat changeX, GLfloat changeY);

	//Funcion para generar la View Matrix
	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	//Variables para definir la localizacion de la camara
	glm::vec3 position;
	glm::vec3 front; //tambien llamada direction
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldup;

	//Variables para definir el angulo de la camara
	GLfloat yaw;
	GLfloat pitch;

	//Variables para mover la camara
	GLfloat moveSpeed;
	GLfloat turnSpeed;

	//Funcion para actualizar los parametros de la camara en cada frame
	void update();
};

