#include <string>
#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
        HandleKeyboard();

        glfwGetFramebufferSize(Window, &Width, &Height);
        glfwSetFramebufferSizeCallback(Window, Reshape);

        gluLookAt(AngleEX, AngleEY, AngleEZ,
        CharacterX, CharacterY, CharacterZ,
        /*:> :>*/AngleUX, AngleUY, AngleUZ);

        HandleDisplay();
        glfwPollEvents();   

    } glfwTerminate(); return EXIT_SUCCESS;
}
