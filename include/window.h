#pragma once

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GLFW/glfw3.h>

class Window
{
private:
    bool valid;
    double period;
    double lastTime;
    GLFWwindow *windowPtr;

public:
    Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share, double fps);
    ~Window();
    bool IsValid();
    void SetWindowPtr(GLFWwindow *windowPtr);
    GLFWwindow *GetWindowPtr();
    void Render(void (*renderFunc)(), void (*inputFunc)(GLFWwindow *));
};
