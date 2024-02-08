#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stack>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

const float toRadians = 3.14159265f / 180.0f;//Dado que la matriz de rotacion usa radianes
//float curAngle = 0.0f;
//bool direction = true;


/*--- DEFINICION DE ANGULOS PARA PARTES DEL CUERPO---*/
float codoizqangle = 0.0f; 
bool direction1 = true;

float cododerangle = 0.0f;
bool direction2 = true;

float hombroizqangle = 0.0f;
bool direction3 = true;

float hombroderangle = 0.0f;
bool direction4 = true;

float torsoangle = 0.0f;
bool direction5 = true;

float headangle = 0.0f;
bool direction6 = true;

float rodillaizqangle = 0.0f;
bool direction7 = true;

float rodilladerangle = 0.0f;
bool direction8 = true;

float caderaizqangle = 0.0f;
bool direction9 = true;

float caderaderangle = 0.0f;
bool direction10 = true;

//Velocidad con la que cambiara el angulo
float angleSpeed = 0.04f;


Window mainWindow;
std::vector<Mesh*> meshList; //Vector donde almacenaremos las distintas mallas de objetos en la pantalla
std::vector<Shader> shaderList; //Vector donde almacenaremos los shaders del programa
Camera camera; //Camara del programa

//Variables para controlar la velocidad de movimiento de la camara
GLfloat deltaTime = 0.0f;  
GLfloat lastTime = 0.0f;


/*--- VERTEX SHADER ---*/
//Especificamos la ruta donde se encuentran los archivos
static const char* vShader = "Shaders/vertexshader.txt";
/*--- FRAGMENT SHADER ---*/
static const char* fShader = "Shaders/fragmentshader.txt";


/*--- FUNCION PARA CREAR OBJETOS A PARTIR DE VERTICES ---*/
void CreateObjects()
{
    /*--- CUBO ---*/
    GLfloat verticescubo[] = {
        0.0f, 0.0f, 0.0f,//0
        1.0f, 0.0f, 0.0f,//1
        1.0f, 1.0f, 0.0f,//2
        0.0f, 1.0f, 0.0f,//3
        0.0f, 0.0f, 1.0f,//4
        1.0f, 0.0f, 1.0f,//5
        1.0f, 1.0f, 1.0f,//6
        0.0f, 1.0f, 1.0f //7
    };

    unsigned int indicescubo[] = {
        7, 4, 5,
        7, 6, 5,
        3, 0, 1,
        3, 2, 1,
        6, 5, 1,
        6, 2, 1,
        7, 4, 0,
        7, 3, 0,
        3, 7, 6,
        3, 2, 6,
        0, 4, 5,
        0, 1, 5
    };

    //Torso
    Mesh* torso = new Mesh();
    torso->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(torso);

    //Hombros
    Mesh* hombros = new Mesh();
    hombros->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(hombros);

    //UpperArm Izquierdo
    Mesh* upperizq = new Mesh();
    upperizq->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(upperizq);

    //ForeArm Izquierdo
    Mesh* foreizq = new Mesh();
    foreizq->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(foreizq);

    //UpperArm Derecho
    Mesh* upperder = new Mesh();
    upperder->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(upperder);

    //ForeArm Derecho
    Mesh* foreder = new Mesh();
    foreder->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(foreder);

    //Muslo Izquierdo
    Mesh* musloizq = new Mesh();
    musloizq->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(musloizq);

    //Pantorrilla izquierda
    Mesh* pantoizq = new Mesh();
    pantoizq->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(pantoizq);

    //Muslo Derecho
    Mesh* musloder = new Mesh();
    musloder->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(musloder);

    //Pantorrilla Derecha
    Mesh* pantoder = new Mesh();
    pantoder->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(pantoder);

    //Cuello
    Mesh* cuello = new Mesh();
    cuello->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(cuello);

    //Cabeza
    Mesh* cabeza = new Mesh();
    cabeza->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(cabeza);

    //Nariz
    Mesh* nariz = new Mesh();
    nariz->CreateMesh(verticescubo, indicescubo, 24, 36);
    meshList.push_back(nariz);

}

/*--- FUNCION PARA CREAR E INICIALIZAR SHADERS ---*/
void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFile(vShader, fShader);
    shaderList.push_back(*shader1);
}

/*--- FUNCION PARA MODIFICAR ANGULOS DE EXTREMIDADES ---*/
void moveAngles() {
    if (direction1) {
        //El codo izquierdo se mueve con la tecla 4
        if (mainWindow.getKeys()[GLFW_KEY_4]) {
            codoizqangle += angleSpeed;
        }
        if (codoizqangle >= 70) //Limite superior del angulo
        {
            direction1 = !direction1;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_4]) {
            codoizqangle -= angleSpeed;
        }
        if (codoizqangle <= 0) //Limite inferior del angulo
        {
            direction1 = !direction1;
        }
    }

    if (direction2) {
        if (mainWindow.getKeys()[GLFW_KEY_6]) {
            cododerangle += angleSpeed;
        }
        if (cododerangle >= 70)
        {
            direction2 = !direction2;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_6]) {
            cododerangle -= angleSpeed;
        }
        if (cododerangle <= 0)
        {
            direction2 = !direction2;
        }
    }

    if (direction3) {
        if (mainWindow.getKeys()[GLFW_KEY_3]) {
            hombroizqangle += angleSpeed;
        }
        if (hombroizqangle >= 70)
        {
            direction3 = !direction3;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_3]) {
            hombroizqangle -= angleSpeed;
        }
        if (hombroizqangle <= 0)
        {
            direction3 = !direction3;
        }
    }


    if (direction4) {
        if (mainWindow.getKeys()[GLFW_KEY_5]) {
            hombroderangle += angleSpeed;
        }
        if (hombroderangle >= 70)
        {
            direction4 = !direction4;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_5]) {
            hombroderangle -= angleSpeed;
        }
        if (hombroderangle <= 0)
        {
            direction4 = !direction4;
        }
    }


    if (direction5) {
        if (mainWindow.getKeys()[GLFW_KEY_1]) {
            torsoangle += angleSpeed;
        }
        if (torsoangle >= 90)
        {
            direction5 = !direction5;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_1]) {
            torsoangle -= angleSpeed;
        }
        if (torsoangle <= -90)
        {
            direction5 = !direction5;
        }
    }


    if (direction6) {
        if (mainWindow.getKeys()[GLFW_KEY_2]) {
            headangle += angleSpeed;
        }
        if (headangle >= 90)
        {
            direction6 = !direction6;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_2]) {
            headangle -= angleSpeed;
        }
        if (headangle <= -90)
        {
            direction6 = !direction6;
        }
    }


    if (direction7) {
        if (mainWindow.getKeys()[GLFW_KEY_8]) {
            rodillaizqangle += angleSpeed;
        }
        if (rodillaizqangle >= 60)
        {
            direction7 = !direction7;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_8]) {
            rodillaizqangle -= angleSpeed;
        }
        if (rodillaizqangle <= 0)
        {
            direction7 = !direction7;
        }
    }


    if (direction8) {
        if (mainWindow.getKeys()[GLFW_KEY_0]) {
            rodilladerangle += angleSpeed;
        }
        if (rodilladerangle >= 60)
        {
            direction8 = !direction8;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_0]) {
            rodilladerangle -= angleSpeed;
        }
        if (rodilladerangle <= 0)
        {
            direction8 = !direction8;
        }
    }


    if (direction9) {
        if (mainWindow.getKeys()[GLFW_KEY_7]) {
            caderaizqangle += angleSpeed;
        }
        if (caderaizqangle >= 70)
        {
            direction9 = !direction9;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_7]) {
            caderaizqangle -= angleSpeed;
        }
        if (caderaizqangle <= -70)
        {
            direction9 = !direction9;
        }
    }


    if (direction10) {
        if (mainWindow.getKeys()[GLFW_KEY_9]) {
            caderaderangle += angleSpeed;
        }
        if (caderaderangle >= 70)
        {
            direction10 = !direction10;
        }
    }
    else {
        if (mainWindow.getKeys()[GLFW_KEY_9]) {
            caderaderangle -= angleSpeed;
        }
        if (caderaderangle <= -70)
        {
            direction10 = !direction10;
        }
    }
}

int main()
{
    /*--- INICIALIZAR LA VENTANA ---*/
    mainWindow = Window(800, 600);
    mainWindow.initialize();

    /*--- CREAR LOS OBJETOS ---*/
    CreateObjects();
    CreateShaders();

    /*--- INICIALIZAR LA CAMARA ---*/
    camera = Camera(glm::vec3(0.5f, 1.5f, 3.5f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

    /*--- INICIALIZAR VARIABLES PARA ID PROJECTION, MODEL Y VIEW MATRICES---*/
    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

    /*--- CREAR LA PERSPECTIVE PROJECTION ---*/
    glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth()/mainWindow.getBufferHeight(), 0.1f, 100.0f);

    /*--- CREAR LOS STACKS DE MATRICES ---*/
    std::stack<glm::mat4> matrixStack; //Stack para Brazo Izquierdo
    std::stack<glm::mat4> matrixStack2;//Stack para Brazo Derecho
    std::stack<glm::mat4> matrixStack3;//Stack para Pierna Izquierda
    std::stack<glm::mat4> matrixStack4;//Stack para Pierna Derecha
    std::stack<glm::mat4> matrixStack5;//Stack para Cabeza

    /*--- LOOP HASTA CERRAR LA VENTANA ---*/
    //Esto basicamente es lo que hace el programa en cada frame mientras la ventana esta abierta
    while (!mainWindow.getShouldClose())
    {
        //Calculamos deltatime para el movimiento uniforme de la camara
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        moveAngles();

        /*Recibe y manipula los "poll events"
          del input*/
        glfwPollEvents();

        //Con la tecla R reseteamos todos los angulos y la marioneta vuelve a posicion inicial
        if (mainWindow.getKeys()[GLFW_KEY_R]) {
            codoizqangle = 0.0f;
            direction1 = true;
            cododerangle = 0.0f;
            direction2 = true;
            hombroizqangle = 0.0f;
            direction3 = true;
            hombroderangle = 0.0f;
            direction4 = true;
            torsoangle = 0.0f;
            direction5 = true;
            headangle = 0.0f;
            direction6 = true;
            rodillaizqangle = 0.0f;
            direction7 = true;
            rodilladerangle = 0.0f;
            direction8 = true;
            caderaizqangle = 0.0f;
            direction9 = true;
            caderaderangle = 0.0f;
            direction10 = true;
        }

        //Movimiento de camara con teclado y mouse
        camera.keyControl(mainWindow.getKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        //Limpiar la ventana a un color
        glClearColor(0.0f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Usamos el programa de los shaders para los objetos
        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();

        //Creamos las Model Matrix
        glm::mat4 model(1.0f); //Model Matrix para Brazo Izquierdo
        glm::mat4 model2(1.0f); //Model Matrix para Brazo Derecho
        glm::mat4 model3(1.0f); //Model Matrix para Pierna Izquierda
        glm::mat4 model4(1.0f); //Model Matrix para Pierna Derecha
        glm::mat4 model5(1.0f); //Model Matrix para Cabeza

        //Inicializamos Stacks con la matriz identidad
        matrixStack.push(model);
        matrixStack2.push(model2);
        matrixStack3.push(model3);
        matrixStack4.push(model4);
        matrixStack5.push(model5);

        /*--- BRAZO IZQUIERDO ---*/
        //TORSO Y TODO EL BRAZO
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.5f)); //Trasladar joint del torso a posicion original
        model = glm::rotate(model, torsoangle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); //Rotar por angulo del torso
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, -0.5f)); //Trasladar joint del torso al origen
        model2 = model;
        model3 = model;
        model4 = model;
        matrixStack.push(model);
        matrixStack2.push(model2);
        matrixStack3.push(model3);
        matrixStack4.push(model4);

        //BRAZO, ANTEBRAZO Y HOMBROS
        model = glm::translate(model, glm::vec3(0.25f, 2.0f, 0.5f)); //Trasladar joint-torso de hombros al torso
        model = glm::translate(model, glm::vec3(-0.75f, 0.0f, -0.5f)); //Trasladar joint-torso de hombros al origen
        model2 = model;
        model5 = model;
        matrixStack.push(model);
        matrixStack2.push(model2);
        matrixStack5.push(model5);

        //BRAZO Y ANTEBRAZO IZQUIERDOS
        model = glm::translate(model, glm::vec3(1.75f, -0.15f, 0.5f)); //Trasladar joint-hombro del brazo al hombro
        model = glm::rotate(model, hombroizqangle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f)); //Rotar por angulo del hombro
        model = glm::translate(model, glm::vec3(-0.25f, -0.7f, -0.25f)); //Trasladar joint-hombro del brazo al origen
        matrixStack.push(model);

        //SOLO ANTEBRAZO IZQUIERDO
        model = glm::translate(model, glm::vec3(0.25f, 0.1f, 0.5f)); //Juntar los codos de brazo y antebrazo
        model = glm::rotate(model, codoizqangle * 1.5f * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f)); //Rotar por angulo del codo
        model = glm::translate(model, glm::vec3(-0.25f, -0.95f, -0.5f));//Llevar codo de antebrazo al origen
        matrixStack.push(model);

        //DIBUJAR ANTEBRAZO IZQUIERDO
        glm::mat4 modelsc = matrixStack.top(); //Es necesario escalar antes de todas las transformaciones
        modelsc = glm::scale(modelsc, glm::vec3(0.5f, 1.25f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[2]->RenderMesh();

        //DIBUJAR BRAZO IZQUIERDO
        matrixStack.pop();
        modelsc = matrixStack.top();
        modelsc = glm::scale(modelsc, glm::vec3(0.5f, 1.0f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        meshList[3]->RenderMesh();


        /*--- BRAZO DERECHO ---*/
        //BRAZO Y ANTEBRAZO DERECHOS
        model2 = glm::translate(model2, glm::vec3(0.25f, -0.15f, 0.5f)); //Trasladar joint-hombro del brazo al hombro
        model2 = glm::rotate(model2, hombroderangle * toRadians, glm::vec3(0.0f, 0.0f, -1.0f)); //Rotar por angulo del hombro
        model2 = glm::translate(model2, glm::vec3(-0.25f, -0.7f, -0.25f)); //Trasladar joint-hombro del brazo al origen
        matrixStack2.push(model2);

        //SOLO ANTEBRAZO DERECHO
        model2 = glm::translate(model2, glm::vec3(0.25f, 0.1f, 0.5f)); //Juntar los codos de brazo y antebrazo
        model2 = glm::rotate(model2, cododerangle * 1.5f * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f)); //Rotar por angulo del codo
        model2 = glm::translate(model2, glm::vec3(-0.25f, -0.95f, -0.5f));//Llevar codo de antebrazo al origen
        matrixStack2.push(model2);

        //DIBUJAR ANTEBRAZO DERECHO
        modelsc = matrixStack2.top(); //Es necesario escalar antes de todas las transformaciones
        modelsc = glm::scale(modelsc, glm::vec3(0.5f, 1.25f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[4]->RenderMesh();

        //DIBUJAR BRAZO DERECHO
        matrixStack2.pop();
        modelsc = matrixStack2.top();
        modelsc = glm::scale(modelsc, glm::vec3(0.5f, 1.0f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        meshList[5]->RenderMesh();


        /*--- PIERNA IZQUIERDA ---*/
        //MUSLO Y PANTORRILLA IZQUIERDOS
        model3 = glm::translate(model3, glm::vec3(0.75f, 0.15f, 0.5f)); //Trasladar joint-cadera del muslo al torso
        model3 = glm::rotate(model3, caderaizqangle * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f)); //Rotar por angulo de la cadera
        model3 = glm::translate(model3, glm::vec3(-0.25f, -1.6f, -0.25f)); //Trasladar joint-cadera del muslo al origen
        matrixStack3.push(model3);

        //SOLO PANTORRILLA IZQUIERDA
        model3 = glm::translate(model3, glm::vec3(0.25f, 0.075f, 0.5f)); //Juntar las rodillas de pantorrilla y muslo
        model3 = glm::rotate(model3, rodillaizqangle * 1.5f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f)); //Rotar por angulo de la rodilla
        model3 = glm::translate(model3, glm::vec3(-0.25f, -1.2f, -0.5f));//Llevar rodilla de pantorrilla al origen
        matrixStack3.push(model3);

        //DIBUJAR PANTORRILLA IZQUIERDA
        modelsc = matrixStack3.top(); //Es necesario escalar antes de todas las transformaciones
        modelsc = glm::scale(modelsc, glm::vec3(0.45f, 1.25f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[6]->RenderMesh();

        //DIBUJAR MUSLO IZQUIERDO
        matrixStack3.pop();
        modelsc = matrixStack3.top();
        modelsc = glm::scale(modelsc, glm::vec3(0.45f, 1.75f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        meshList[7]->RenderMesh();


        /*--- PIERNA DERECHA ---*/
        //MUSLO Y PANTORRILLA DERECHOS
        model4 = glm::translate(model4, glm::vec3(0.25f, 0.15f, 0.5f)); //Trasladar joint-cadera del muslo al torso
        model4 = glm::rotate(model4, caderaderangle * toRadians, glm::vec3(1.0f, 0.0f, 0.0f)); //Rotar por angulo de la cadera
        model4 = glm::translate(model4, glm::vec3(-0.25f, -1.6f, -0.25f)); //Trasladar joint-cadera del muslo al origen
        matrixStack4.push(model4);

        //SOLO PANTORRILLA DERECHA
        model4 = glm::translate(model4, glm::vec3(0.25f, 0.075f, 0.5f)); //Juntar las rodillas de pantorrilla y muslo
        model4 = glm::rotate(model4, rodilladerangle * 1.5f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f)); //Rotar por angulo de la rodilla
        model4 = glm::translate(model4, glm::vec3(-0.25f, -1.2f, -0.5f));//Llevar rodilla de pantorrilla al origen
        matrixStack4.push(model4);

        //DIBUJAR PANTORRILLA DERECHA
        modelsc = matrixStack4.top(); //Es necesario escalar antes de todas las transformaciones
        modelsc = glm::scale(modelsc, glm::vec3(0.45f, 1.25f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[8]->RenderMesh();

        //DIBUJAR MUSLO DERECHO
        matrixStack4.pop();
        modelsc = matrixStack4.top();
        modelsc = glm::scale(modelsc, glm::vec3(0.45f, 1.75f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        meshList[9]->RenderMesh();


        /*--- CABEZA ---*/
        //CUELLO Y CABEZA
        model5 = glm::translate(model5, glm::vec3(1.25f, 0.25f, 0.75f)); //Trasladar joint-torso del cuello al torso
        model5 = glm::translate(model5, glm::vec3(-0.5f, 0.0f, -0.5f)); //Trasladar joint-torso del cuello al origen
        matrixStack5.push(model5);


        //CABEZA Y NARIZ
        model5 = glm::translate(model5, glm::vec3(0.25f, 0.1f, 0.25f)); //Juntar los joints de cuello y cabeza
        model5 = glm::rotate(model5, headangle * 0.5f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); //Rotar por angulo deL cuello
        model5 = glm::translate(model5, glm::vec3(-0.5f, 0.0f, -0.5f));//Llevar joint-cuello de cabeza al origen
        matrixStack5.push(model5);

        //SOLO NARIZ
        model5 = glm::translate(model5, glm::vec3(0.5f, 0.5f, 1.0f)); //Juntar los joints de nariz y cabeza
        model5 = glm::translate(model5, glm::vec3(-0.125f, -0.125f, -0.0f));//Llevar joint-cabeza de nariz al origen
        matrixStack5.push(model5);

        //DIBUJAR NARIZ
        modelsc = matrixStack5.top(); //Es necesario escalar antes de todas las transformaciones
        modelsc = glm::scale(modelsc, glm::vec3(0.25f, 0.15f, 0.25f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        meshList[12]->RenderMesh();
        
        //DIBUJAR CABEZA
        matrixStack5.pop();
        modelsc = matrixStack5.top(); //Es necesario escalar antes de todas las transformaciones
        modelsc = glm::scale(modelsc, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        meshList[10]->RenderMesh();
        
        //DIBUJAR CUELLO
        matrixStack5.pop();
        modelsc = matrixStack5.top();
        modelsc = glm::scale(modelsc, glm::vec3(0.5f, 0.1f, 0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        meshList[11]->RenderMesh();


        /*--- TRONCO ---*/
        //DIBUJAR HOMBROS
        matrixStack.pop();
        modelsc = matrixStack.top();
        modelsc = glm::scale(modelsc, glm::vec3(2.0f, 0.25f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        meshList[1]->RenderMesh();

        //DIBUJAR TORSO
        matrixStack.pop();
        modelsc = matrixStack.top();
        modelsc = glm::scale(modelsc, glm::vec3(1.0f, 2.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelsc));
        meshList[0]->RenderMesh();


        glUseProgram(0); //Cerramos

        //Intercambiar los buffers para ver en pantalla lo que se dibuja
        mainWindow.swapBuffers();
    }

    return 0;
}

