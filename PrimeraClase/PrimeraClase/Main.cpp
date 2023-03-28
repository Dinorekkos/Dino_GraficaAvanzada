#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include<stb/stb_image.h>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(950, 950, "test", NULL, NULL);

    glfwSetTime(0);

    GLfloat squareVertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,    0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,    1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f  // Lower right corner
    };

    GLuint squareIndices[] =
    {
     0, 2, 1,
     0, 3, 2
    };

    glfwMakeContextCurrent(window);
    gladLoadGL();

    //Se crea Textura
    GLuint texture;
    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Se especifican configuraciones de la textura

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Variables para textura

    int widthTx, heightTx, numCol;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* bytes = stbi_load("popCat.jpg", &widthTx, &heightTx, &numCol, 0);

    std::cout << widthTx << std::endl;
    std::cout << heightTx << std::endl;
    std::cout << numCol << std::endl;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTx, heightTx, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    //Se genera Textura

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);


    //se crean shaders

    Shader shaderProgram("waterWave.vert", "waterWave.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(squareVertices, sizeof(squareVertices));

    EBO EBO1(squareIndices, sizeof(squareIndices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

     // GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
     // GLuint tex0uni = glGetUniformLocation(shaderProgram.ID, "tex0");

    //time
    GLfloat seconds = 1.0f;
 
    while (!glfwWindowShouldClose(window))
    {

       
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
     

        shaderProgram.Activate();

        GLfloat time = glfwGetTime() * seconds;
        
        GLuint sampler2D = glGetUniformLocation(shaderProgram.ID, "inputImageTexture");
        GLfloat wave = glGetUniformLocation(shaderProgram.ID, "timeWave");
        GLfloat speed = glGetUniformLocation(shaderProgram.ID, "speed");
        GLfloat amplitude = glGetUniformLocation(shaderProgram.ID, "amplitude");
        GLfloat frequency = glGetUniformLocation(shaderProgram.ID, "frequency");

        glUniform1f(wave, time);
        glUniform1f(speed, 1.0f);
        glUniform1f(amplitude, 0.05f);
        glUniform1f(frequency, 10.0f);
        glUniform1i(sampler2D, 0);
     
         // glUniform1i(uniID, 0.5f);
         // glUniform1i(tex0uni, 0);
     
        std::cout << time << std::endl;

        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();

    glViewport(0, 0, 950, 950);
    glfwSwapBuffers(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}