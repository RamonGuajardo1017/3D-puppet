#include "Shader.h"

Shader::Shader()
{
	//Simplemente inicializamos todas las variables a 0
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
    uniformView = 0;
}

void Shader::CreateFromString(const char* vertexShader, const char* fragmentShader)
{
	CompileShader(vertexShader, fragmentShader);
}

void Shader::CreateFromFile(const char* vshaderLocation, const char* fshaderLocation)
{
    std::string vShaderString = ReadFile(vshaderLocation);
    std::string fShaderString = ReadFile(fshaderLocation);

    const char* vertexShader = vShaderString.c_str();
    const char* fragmentShader = fShaderString.c_str();

    CompileShader(vertexShader, fragmentShader);
}

std::string Shader::ReadFile(const char* fileLocation)
{
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if (!fileStream.is_open())
    {
        std::cout << "Failed to read or open " << fileLocation << "! File doesn't exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::CompileShader(const char* vertexShader, const char* fragmentShader)
{
    //ID de los shader programs
    shaderID = glCreateProgram();

    if (!shaderID)
    {
        std::cout << "Error creating shader program!" << std::endl;
        return;
    }

    AddShader(shaderID, vertexShader, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentShader, GL_FRAGMENT_SHADER);

    //Deteccion de errores
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        std::cout << "Error linking program: " << eLog << std::endl;
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        std::cout << "Error validating program: " << eLog << std::endl;
        return;
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    //Deteccion de errores
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        std::cout << "Error compiling the " << shaderType << " shader: " << eLog << std::endl;
        return;
    }

    glAttachShader(theProgram, theShader);
}

void Shader::UseShader()
{
    glUseProgram(shaderID);
}

void Shader::ClearShader()
{
    if (shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
    uniformView = 0;
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return uniformModel;
}

GLuint Shader::GetViewLocation()
{
    return uniformView;
}

Shader::~Shader()
{
    ClearShader();
}

