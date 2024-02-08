#include "Window.h"

Window::Window()
{
	WIDTH = 800;
	HEIGHT = 600;

    ChangeX = 0.0f;
    ChangeY = 0.0f;

    //Inicializamos el arreglo asociado al teclado
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	WIDTH = windowWidth;
	HEIGHT = windowHeight;

    ChangeX = 0.0f;
    ChangeY = 0.0f;

    //Inicializamos el arreglo asociado al teclado
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

int Window::initialize()
{
    /*--- INICIALIZAR GLFW ---*/
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed!" << std::endl;
        glfwTerminate(); //Terminamos cualquier subproceso iniciado
        return 1;
    }

    /*--- CONFIGURAR PROPIEDADES DE VENTANA DE GLFW ---*/
    //Establecemos el contexto de la version de OpenGL (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Core profile = No Backwards Compatibility (Only this version)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Permitimos forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Creamos la ventana como tal
    mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    if (!mainWindow)
    {
        std::cout << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return 1;
    }

    /*--- OBTENER LA INFO DE TAMANO DEL BUFFER ---*/
    /* Nota: El buffer es la parte que esta recibiendo los
       datos de OpenGL para pasarlos a la ventana */
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);


    /*--- ESTABLECER EL CONTEXTO PARA USAR GLEW ---*/
    //Decimos que todo el contexto de OpenGL estara en la ventana creada
    glfwMakeContextCurrent(mainWindow);
    //Handle Key + Mouse Input
    createCallbacks();
    //Bloquear el cursor a la pantalla
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Permitimos las modern extension features
    glewExperimental = GL_TRUE;


    /*--- INICIALIZAR GLEW ---*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initialization failed!" << std::endl;
        glfwDestroyWindow(mainWindow); //Hay que quitar la ventana creada
        glfwTerminate(); //Terminamos cualquier subproceso iniciado
        return 1;
    }

    /*--- DEPTH TEST PARA PROFUNDIDAD EN 3D ---*/
    glEnable(GL_DEPTH_TEST);

    /*--- CONFIGURAR TAMANO DEL VIEWPORT ---*/
    /* Esta funcion se encarga de configurar el tamano de
       la parte de la ventana donde como tal estamos dibujando a
       traves de un sistema de coordenadas, por lo que, si queremos dibujar
       en TODA la ventana, entonces el origen debe ser (0,0) en la funcion
       de abajo.
     */
    glViewport(0, 0, bufferWidth, bufferHeight);

    //Funcion para callback de handleKeys()
    glfwSetWindowUserPointer(mainWindow, this); //Estamos diciendo que *esta* clase es la usuaria de mainWindow
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    //Cerramos la ventana con la tecla escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    //Nos aseguramos de que la tecla sea un caracter valido
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) {
            theWindow->keys[key] = true;
            //printf("Pressed: %d\n", key);
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
            //printf("Released: %d\n", key);
        }
    }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    //Inicializamos variables cuando el mouse se mueve por 1ra vez
    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->ChangeX = xPos - theWindow->lastX;
    theWindow->ChangeY = theWindow->lastY - yPos; //Esto se puede invertir

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;

    //printf("x: %.6f, y: %.6f\n", theWindow->ChangeX, theWindow->ChangeY);
}

GLfloat Window::getXChange()
{
    GLfloat change = ChangeX;
    ChangeX = 0.0f;

    return change;
}

GLfloat Window::getYChange()
{
    GLfloat change = ChangeY;
    ChangeY = 0.0f;

    return change;
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow); //Hay que quitar la ventana creada
    glfwTerminate(); //Terminamos cualquier subproceso iniciado
}


