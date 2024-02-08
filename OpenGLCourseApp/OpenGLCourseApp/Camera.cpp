#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw,
	           GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpped)
{
	//Inicializamos las variables globales a los parametros iniciales
	position = startPosition;
	worldup = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpped;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	//W: Mover hacia adelante
	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	//S: Mover hacia atras
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	//A: Mover hacia la izquierda
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	//D: Mover hacia la derecha
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}

}

void Camera::mouseControl(GLfloat changeX, GLfloat changeY)
{
	changeX *= turnSpeed;
	changeY *= turnSpeed;

	yaw += changeX;
	pitch += changeY;

	//Limitamos que tanto se puede girar hacia arriba
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	//Usamos GLM para calcular la matriz
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldup));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}