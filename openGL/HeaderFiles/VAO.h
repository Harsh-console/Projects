#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include<VBO.h>

class VAO{
    public:
        GLuint ID;
        VAO();
        void Bind();
        void Unbind();
        void Delete();
        void LinkAttrib(VBO VBO, GLuint layout, GLuint NumComponents, GLenum type, GLsizeiptr stride, void* offset);
};

#endif