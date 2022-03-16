#include <string>
#include <errno.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "Headers/stb_image.h"

GLFWwindow *Window; void Error(const char *Error_Message, int Way) {
    if (Way == 0) {
        std::cout << "Error: " << Error_Message << "\\" << std::endl << strerror(errno) << std::endl;; exit(-1);
    } else {glfwTerminate(); std::cout << "Error: " << Error_Message << "\\" << std::endl << strerror(errno) << std::endl;}}

#include "Headers/input.h"

int main(void) {
    if (!glfwInit()) {Error("Unable to init GLFW3!", 0);}
    InitMein3D(); InitOpenGL();
    while (!glfwWindowShouldClose(Window)) {

        glfwPollEvents();
    } glfwTerminate(); return EXIT_SUCCESS;
} 
