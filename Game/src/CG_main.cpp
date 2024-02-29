#include <CE_global.hpp>

using namespace CyberEngine;

// Static Variable
Log* Log::log_ = nullptr;
Application* Application::app_ = nullptr;

// Main Function
int main(int argc, char** argv)
{
    // Initialize log
    Log* log = Log::GetInstance();
    CE_LOG_INFO("CyberEngine(Software) v0.1.0");

    // Testing area
    // End Testing area

    // Create Application
    CE_LOG_INFO("Creating Application");
    Application* main_app = Application::GetInstance(1280, 720, 800, 600);
    main_app->Init();
    main_app->Run();

    CE_LOG_INFO("Application Terminated");

    return 0;
}