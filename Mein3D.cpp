#include <string>
#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Error(const char *Message);

#include "./Headers/input.h"
#include "./Headers/init.h"
#include "./Headers/display.h"

void Error(const char *Message) {
    printf("%s\n", Message); // HI
    glfwWindowShouldClose(Window);
}

int main(int argc, char** argv) {
    if (!glfwInit()) { exit(EXIT_FAILURE);
    } InitOpenGL(); InitWindow();

    while (!glfwWindowShouldClose(Window)) {

        float CurrentFrame = static_cast<float>(glfwGetTime());
                        DeltaTime = CurrentFrame - LastFrame;
                                    LastFrame = CurrentFrame;

        HandleKeyboard();
        glfwGetFramebufferSize(Window, &Width, &Height);
        glfwSetFramebufferSizeCallback(Window, Reshape);

        gluLookAt(CameraF.x, CameraF.y, CameraF.z,
                  CameraP.x, CameraP.y, CameraP.z,
                  CameraU.x, CameraU.y, CameraU.z);

        HandleDisplay();
        glfwPollEvents(); 

    } glfwTerminate(); return EXIT_SUCCESS;
}
