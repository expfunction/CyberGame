#pragma once

namespace CyberEngine
{
    // Forward Declarations
class Log;
class AssetManager;
class Renderer;
    class Application
    {
    private:
        // Private Variables
        GLFWwindow* main_window_;
        GLint window_width = 1280, window_height = 960;
        GLint render_width = 320, render_height = 240;

        static Application* app_;
        AssetManager* asset_manager_;
        Renderer* renderer_;
        

        // Private Functions
        Application(const uint16_t window_width,
            const uint16_t window_height,
            const uint16_t render_width,
            const uint16_t render_height)
                                        :window_width(window_width),
                                         window_height(window_height),
                                         render_width(render_width),
                                         render_height(render_height)
        {
			// Initialize Manager Pointers
            main_window_ = nullptr;
            asset_manager_ = nullptr;
            renderer_ = nullptr;
        }

    public:
        // Public Functions
        Application(Application& other) = delete;
        void operator=(const Application&) = delete;
        static Application* GetInstance(const GLint window_width = 1280,
                                        const GLint window_height = 960,
                                        const GLint render_width = 320,
                                        const GLint render_height = 240);
        void Init();
        void Run();

        // Callback Functions
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void GLAPIENTRY error_message_callback(GLint error, const char* description);
    };
}