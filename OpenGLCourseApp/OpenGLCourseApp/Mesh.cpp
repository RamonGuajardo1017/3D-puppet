#include "Mesh.h"

//Constructor default de la malla
Mesh::Mesh()
{
	//Simplemente inicializamos todas las variables a 0
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numVertices, unsigned int numIndices)
{
	indexCount = numIndices; //Variable que cuenta la cantidad total de indices que usara la malla (caras del objeto * 3)

    //Generamos el VAO
    glGenVertexArrays(1, &VAO); //Creamos *1* arreglo y su ID se almacena en VAO
    glBindVertexArray(VAO); //Importante hacer binding

    //Crear el Buffer para el IBO (para Indexed Draws)
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*numIndices, indices, GL_STATIC_DRAW);


    //Generamos el VBO (para Vertex Array)
    glGenBuffers(1, &VBO); //Creamos *1* buffer y su ID se almacena en VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Triangulo estatico  (ultimo parametro)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*numVertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    //Un-binding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::RenderMesh()
{
    //Volvemos a hacer binding
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    //Esta funcion es para dibujar con los indices y no con el vertex array
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
    if (IBO != 0)
    {
        glDeleteBuffers(1, &IBO); //Borramos el buffer asociado al Indexed Draw (vaciar memoria)
        IBO = 0;
    }

    //Hacemos lo mismo con el Vertex Buffer Object
    if (VBO != 0)
    {
        glDeleteBuffers(1, &VBO); 
        VBO = 0;
    }

    //Borramos tambien el Vertex Array
    if (VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO); 
        VAO = 0;
    }

    indexCount = 0;
}

Mesh::~Mesh()
{
    ClearMesh();
}
