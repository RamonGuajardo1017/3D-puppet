#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	//Constructor por default
	Window();

	//Constructor con parametros
	Window(GLint windowWidth, GLint windowHeight);

	int initialize();

	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();

private:
	GLFWwindow* mainWindow;
	GLint WIDTH, HEIGHT;
	GLint bufferWidth, bufferHeight;

	//En este arreglo almacenaremos el estado de cada tecla (true: tecla presionada, false: tecla suelta)
	bool keys[1024]; //1024 por la cantidad de ASCII characters

	//Variables para llevar un control sobre la posicion del Mouse
	GLfloat lastX;
	GLfloat lastY;
	GLfloat ChangeX;
	GLfloat ChangeY;
	bool mouseFirstMoved;

	//Funcion para crear todas las "callback functions" 
	void createCallbacks();

	//Funcion que nos permite recibir y manejar las presiones de teclas
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);

	//Funcion que nos permite recibir y manejar el movimiento del teclado
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

