#pragma once

namespace CyberEngine {

	class Renderer : public System
	{
		private:
			// Private Variables
			static Renderer* renderer_;
			std::unique_ptr<Color[]> mainFramebuffer;

			AssetManager* rAssetManager;

			GLFWwindow *windowReference;
			GLint main_viewport[4];
			GLfloat yZoomFactor;
			GLfloat xZoomFactor;

			// Private Functions
			// Constructor
			Renderer()
			{
				// Initialize width and height
				width = 0;
				height = 0;
				yZoomFactor = 1.0f;
				xZoomFactor = 1.0f;
				// Initialize framebuffer
				mainFramebuffer = nullptr;
				windowReference = nullptr;
				rAssetManager = nullptr;
				// Initialize viewport
				main_viewport[0] = 0;
				main_viewport[1] = 0;
				main_viewport[2] = 0;
				main_viewport[3] = 0;
			}
			// Destructor
			~Renderer()
			{
				// Delete framebuffer
				mainFramebuffer.reset();
				
				// Delete window reference
				windowReference = nullptr;
				rAssetManager = nullptr;


				// Terminate GLFW
				glfwTerminate();
			}

		public:
			// Public Variables
			GLint width, height;
			
			// Public Functions 
			Renderer(Renderer& other) = delete;
			void operator=(const Renderer&) = delete;
			// Get Renderer
			static Renderer* GetInstance();
			
			// Initialize Renderer
			void Init(GLint width, GLint height, GLFWwindow *windowReference, AssetManager* assetManager);
			// Set Pixel Zoom for GLFW
			void SetPixelZoomGL(GLfloat xZoomFactor, GLfloat yZoomFactor);
			// Draw Pixel
			void DrawPixel(GLfloat x, GLfloat y, Color p);
			// Bresenhams Line Drawing Algorithm
			void DrawLine(const Vertex& start, const Vertex& end, const Color& p);
			// Draw Edge Function Triangle
			void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
			// Draw Quad
			void DrawQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4, Texture* textureBuffer);
			// Draw Texture Directly
			void DrawTexturedQuad(const cVec2& screenPos, const cVec2& textureSize, Color* textureBuffer);
			// Draw Screen Method
			void DrawScreen();
			// Draw Scene Method
			void DrawScene();
			// Clear Screen Method
			void ClearScreen();

			// Utility Functions
			// Convert GLubyte to Color
			Color GLubyteToColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) { return Color(r, g, b, a); };
			
	};
}