#include <bits/stdc++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// Function to check for OpenGL errors
void GLCheckError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error " << err << " at " << fname << ":" << line << " - for " << stmt << std::endl;
        exit(1);
    }
}
#define GL_CHECK(stmt) do { stmt; GLCheckError(#stmt, __FILE__, __LINE__); } while(0)

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int WIDTH = 800;
    int HEIGHT = 800;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Harsh Singh", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

	float scale = 0.5f; // inner triangle size relative to outer
	GLfloat vertices[] = {
		// Outer triangle (countzer-clockwise)
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // 0: bottom-left (red)
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // 1: bottom-right (green)
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // 2: top (blue)

		// Inner inverted triangle (centered)
		-0.25f,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  // 3: left (yellow)
		0.25f,  0.0f, 0.0f,  0.0f, 1.0f, 1.0f,  // 4: right (cyan)
		0.0f,  -0.25f, 0.0f, 1.0f, 0.0f, 1.0f   // 5: bottom (magenta)
	};



	GLuint indices[] = {
		// Outer triangle
		0, 1, 2, 

		// Inner inverted triangle
		3, 4, 5
	};


    // Shader
    Shader shaderProgram("ResourceFiles/Shaders/default.vert",
                         "ResourceFiles/Shaders/default.frag");

    // Check if shader compiled successfully
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram.ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram.ID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // VAO, VBO, EBO
    VAO VAO1;
    GL_CHECK(VAO1.Bind());

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); // position
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // color

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
    if (uniID == -1)
        std::cerr << "WARNING: uniform 'scale' not found!" << std::endl;

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

        shaderProgram.Activate();
        glUniform1f(uniID, scale);
        GL_CHECK(VAO1.Bind());

        GL_CHECK(glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0));

        glfwSwapBuffers(window);
    }

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
