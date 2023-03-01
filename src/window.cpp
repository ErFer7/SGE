#include "../include/window.h"
#include "../include/utils.h"

#pragma region Constructor and Destructor
Window::Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share, double fps)
{
    this->valid = true;
    this->period = 1.0 / fps;
    this->lastTime = 0.0;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Criação da janela
    this->windowPtr = glfwCreateWindow(width, height, title, monitor, share);

    // Handler de erro para a criação da janela
    if (this->windowPtr == NULL)
    {
        glfwTerminate();
        this->valid = false;
    }

    glfwMakeContextCurrent(this->windowPtr);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(this->windowPtr, FramebufferSizeCallback);
}

Window::~Window()
{
    glfwTerminate();
}
#pragma endregion

#pragma region Getters and Setters
void Window::SetWindowPtr(GLFWwindow *windowPtr)
{
    this->windowPtr = windowPtr;
}

GLFWwindow *Window::GetWindowPtr()
{
    return this->windowPtr;
}
#pragma endregion

#pragma region Methods
bool Window::IsValid()
{
    return this->valid;
}

void Window::Render(void (*renderFunc)(), void (*inputFunc)(GLFWwindow *))
{
    // Loop de renderização
    while (!glfwWindowShouldClose(this->windowPtr))
    {
        // Processamento de input
        inputFunc(this->windowPtr);

        double time = glfwGetTime();
        double deltaTime = time - lastTime;

        if (deltaTime >= period)
        {
            lastTime = time;

            renderFunc();

            // Troca os buffers
            glfwSwapBuffers(this->windowPtr);
        }

        // Checa e chama eventos
        glfwPollEvents();
    }
}
#pragma endregion Methods
