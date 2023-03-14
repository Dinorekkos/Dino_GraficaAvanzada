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
    GLFWwindow* window = glfwCreateWindow(900, 900, "test", NULL, NULL);


    GLfloat scale = 0.5f;
    int widthTx, heightTx , numCol;
    
    unsigned char* bytes = stbi_load("lava_512x512.png", &widthTx, &heightTx, &numCol, 0);
    
    // GLfloat factor = float(sqrt(3));

    GLuint texture;
    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTx, heightTx, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);


    GLfloat squareVertices[] =
    {
        //s     t     r          r    g     b           coordenada
        -0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,        0.0f, 0.0f, 1.0f,      1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,       1.0f, 1.0f, 1.0f,      1.0f, 0.0f
    };

    // Indices para el orden de los triangulos
    GLuint squareIndices[] =
    {
        0, 2, 1,
        0, 3, 2
    };

    glfwMakeContextCurrent(window);
    gladLoadGL();

    //se crean shaders
    Shader shaderProgram("default.vert", "default.frag");
    
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(squareVertices, sizeof(squareVertices));
    EBO EBO1(squareIndices, sizeof(squareIndices)); 
  
    // VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*) (3 * sizeof(float)));

    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
   
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    // GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    GLuint tex0uni = glGetUniformLocation(shaderProgram.ID, "tex0");
   

    glViewport(0, 0, 900, 900);
    glfwSwapBuffers(window);

   

    while (!glfwWindowShouldClose(window))
    {
        
        //background color
        glClearColor(0.0471f, 0.8471f, 0.9569f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // shaderProgram.Activate();

        // glUniform1f(uniID, scale);

        
        shaderProgram.Activate();
        glUniform1i(tex0uni, 0);
       
        
        

        glBindTexture(GL_TEXTURE_2D, texture);
        stbi_set_flip_vertically_on_load(true);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        
        
      
       glfwSwapBuffers(window);
       glfwPollEvents();


       
    }

   
    

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}