#include "CE_global.hpp"

using namespace CyberEngine;

// Initialize static pointers
AssetManager* AssetManager::asset_manager_ = nullptr;
Renderer* Renderer::renderer_ = nullptr;

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Close window on escape key press
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void GLAPIENTRY Application::error_message_callback(GLint error, const char* description)
{
	CE_LOG_ERROR("GLFW Error: {}", description);
	return;
}

Application* Application::GetInstance(const GLint window_width, const GLint window_height,
    const GLint render_width, const GLint render_height)
{
    if (app_ == nullptr)
        app_ = new Application(window_width, window_height, render_width, render_height);
    return app_;
}

void Application::Init()
{
    // Initialize System
    CE_LOG_INFO("Initializing Application");

    // Set debug callback
    glEnable(GL_DEBUG_OUTPUT);
    glfwSetErrorCallback(error_message_callback);

    /* Initialize GLFW */
    CE_LOG_INFO("Initializing GLFW");
    if (!glfwInit())
    {
        CE_LOG_ERROR("Error initializing GLFW");
        return;
    }

    /* Add window hints to configure */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    CE_LOG_INFO("Creating Engine Window");
    main_window_ = glfwCreateWindow(window_width, window_height, "CyberEngine(Software)", NULL, NULL);
    if (!main_window_)
    {
        CE_LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(main_window_);

    // Set callback functions
    glfwSetFramebufferSizeCallback(main_window_, framebuffer_size_callback);
    glfwSetKeyCallback(main_window_, key_callback);
    //glfwSetMouseButtonCallback(main_window, mouse_callback);

    /* Initialize GLEW */
    CE_LOG_INFO("Initializing GLEW");
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        CE_LOG_ERROR("Failed to initialize GLEW: {}", CE_FMT_PTR(glewGetErrorString(err)));
        return;
    }

    // Initialize asset manager
    CE_LOG_INFO("Initializing Asset Manager");
    asset_manager_ = AssetManager::GetInstance();
    asset_manager_->Init();

    // Initialize renderer
    CE_LOG_INFO("Initializing Renderer");
    renderer_ = Renderer::GetInstance();
    renderer_->Init(render_width, render_height, main_window_, asset_manager_);
    return;
}

void Application::Run()
{
    CE_LOG_INFO("Starting Application");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(main_window_))
    {
        // Get input
        glfwPollEvents();

        // Update

        // Render
        renderer_->DrawScreen();
        //renderer_->Update(); // Update renderable objects in scene (i.e. camera)
        //renderer_->Render(); // Render frame to screen (i.e. draw all renderable objects)
    }

    // Terminate GLFW
    glfwTerminate();

    return;
}