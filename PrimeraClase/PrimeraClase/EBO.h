#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
    GLuint ID;

    // Constructor que genera un Elements Buffer Object y lo enlaza a los indices
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};
#endif