#include "CE_global.hpp"

using namespace CyberEngine;

Renderer* Renderer::GetInstance()
{
	if (renderer_ == nullptr)
	{
		renderer_ = new Renderer();
	}
	return renderer_;
}

void Renderer::Init(GLint width, GLint height, GLFWwindow* window_reference, AssetManager* aMgr)
{
	this->width = width; 
	this->height = height;

	// Set Asset Manager
	rAssetManager = aMgr;

	// Initialize framebuffer
	mainFramebuffer = std::unique_ptr<Color[]>(new Color[width * height]);

	// Set window reference
	this->windowReference = window_reference;

	// Get window size
	GLint winWidth, winHeight;
	glfwGetWindowSize(windowReference, &winWidth, &winHeight);

	// Set viewport keeping aspect ratio of framebuffer
	if ((GLfloat)winWidth / (GLfloat)winHeight > (GLfloat)width / (GLfloat)height)
	{
		main_viewport[0] = (winWidth - (winHeight * width / height)) / 2;
		main_viewport[1] = 0;
		main_viewport[2] = winHeight * width / height;
		main_viewport[3] = winHeight;
	}
	else
	{
		main_viewport[0] = 0;
		main_viewport[1] = (winHeight - (winWidth * height / width)) / 2;
		main_viewport[2] = winWidth;
		main_viewport[3] = winWidth * height / width;
	}

	// Set viewport scaling
	xZoomFactor = (GLfloat)main_viewport[2] / (GLfloat)width;
	yZoomFactor = (GLfloat)main_viewport[3] / (GLfloat)height;

	// Set viewport
	glViewport(main_viewport[0], main_viewport[1], main_viewport[2], main_viewport[3]);
	
	// Move framebuffer to center of viewport
	glRasterPos2f(-1.0f, -1.0f);	

	// Set pixel zoom
	SetPixelZoomGL(xZoomFactor, yZoomFactor);
}

void Renderer::SetPixelZoomGL(GLfloat xZoomFactor, GLfloat yZoomFactor)
{
	glPixelZoom(xZoomFactor, yZoomFactor);
}

void Renderer::DrawPixel(GLfloat x, GLfloat y, Color p)
{
	// Check if pixel is out of bounds
	if (x < -1.0f || x > 1.0f || y < -1.0f || y > 1.0f)
	{
		CE_LOG_ERROR("Pixel out of bounds x:{} y:{}", x, y);
		return;
	}

	// Convert normalized coordinates to screen coordinates
	x = static_cast<GLuint>(glm::floor((x + 1.0f) * (GLfloat)(width  / 2)));
	y = static_cast<GLuint>(glm::floor((y + 1.0f) * (GLfloat)(height / 2)));

	// Draw pixel to framebuffer
	mainFramebuffer[y * width + x] = p;
}

void Renderer::DrawLine(const Vertex& start, const Vertex& end, const Color& p)
{
	// Draw line using Bresenham's line algorithm
	GLint x1 = static_cast<GLint>(glm::floor((start.position.x + 1.0f) * (GLfloat)(width / 2)));
	GLint y1 = static_cast<GLint>(glm::floor((start.position.y + 1.0f) * (GLfloat)(height / 2)));
	
	GLint x2 = static_cast<GLint>(glm::floor((end.position.x + 1.0f) * (GLfloat)(width  / 2)));
	GLint y2 = static_cast<GLint>(glm::floor((end.position.y + 1.0f) * (GLfloat)(height / 2)));
	
	GLfloat dx = abs(x2 - x1);
	GLfloat dy = abs(y2 - y1);
	
	GLint sx = (x1 < x2) ? 1 : -1;
	GLint sy = (y1 < y2) ? 1 : -1;
	
	GLint err = dx - dy;

	while (true)
	{
		// Draw pixel to framebuffer
		mainFramebuffer[y1 * width + x1] = p;

		if (x1 == x2 && y1 == y2) break;

		GLint e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void Renderer::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	// Check if triangle is out of bounds
	if (v1.position.x < -1.0f || v1.position.x > 1.0f || v1.position.y < -1.0f || v1.position.y > 1.0f ||
		v2.position.x < -1.0f || v2.position.x > 1.0f || v2.position.y < -1.0f || v2.position.y > 1.0f ||
		v3.position.x < -1.0f || v3.position.x > 1.0f || v3.position.y < -1.0f || v3.position.y > 1.0f)
	{
		return;
	}

	// Convert vertices into screen coordinates
	GLfloat x1 = (glm::floor((v1.position.x + 1.0f) * (GLfloat)(width / 2)));
	GLfloat y1 = (glm::floor((v1.position.y + 1.0f) * (GLfloat)(height / 2)));
				 
	GLfloat x2 = (glm::floor((v2.position.x + 1.0f) * (GLfloat)(width / 2)));
	GLfloat y2 = (glm::floor((v2.position.y + 1.0f) * (GLfloat)(height / 2)));
				
	GLfloat x3 = (glm::floor((v3.position.x + 1.0f) * (GLfloat)(width / 2)));
	GLfloat y3 = (glm::floor((v3.position.y + 1.0f) * (GLfloat)(height / 2)));

	// Get the bounding box of triangle
	GLuint xMin = glm::min(glm::min(x1, x2), x3);
	GLuint xMax = glm::max(glm::max(x1, x2), x3);

	GLuint yMin = glm::min(glm::min(y1, y2), y3);
	GLuint yMax = glm::max(glm::max(y1, y2), y3);

	// Generate edge vectors
	cVec3 v12(x2 - x1, y2 - y1, 0.0f); // = triangle.B.position - triangle.A.position
	cVec3 v13(x3 - x1, y3 - y1, 0.0f); // = triangle.C.position - triangle.A.position;

	// Calculate dot product values
	GLfloat d00 = glm::dot(v12, v12);
	GLfloat d01 = glm::dot(v12, v13);
	GLfloat d11 = glm::dot(v13, v13);

	// Calculate denominator for normalizing u, v and w
	GLfloat denom = d00 * d11 - d01 * d01;

	// Loop bounding box
	for (GLuint y = yMin; y < yMax; y++) {
		for (GLuint x = xMin; x < xMax; x++) {

			// Generate P vectors
			cVec3 v1p(x - x1, y - y1, 0.0f); // = P.position - triangle.A.position;

			// Calculate dot product values
			GLfloat d20 = glm::dot(v1p, v12);
			GLfloat d21 = glm::dot(v1p, v13);

			// Calculate weights of vertices at P(x,y) using barycentric coordinates
			const GLfloat v = (d11 * d20 - d01 * d21) / denom;
			const GLfloat w = (d00 * d21 - d01 * d20) / denom;
			const GLfloat u = 1.0f - v - w;

			if (u>=0.0f && v >= 0.0f && w >= 0.0f) {
				const Color col1 = v1.color * u;
				const Color col2 = v2.color * v;
				const Color col3 = v3.color * w;
				const Color fcol = (col1 + col2) + col3;
				mainFramebuffer[y * width + x] = fcol;
			}
		}
	}
}

void Renderer::DrawQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4, Texture* texture)
{
	// Check if triangle is out of bounds
	if (v1.position.x < -1.0f || v1.position.x > 1.0f || v1.position.y < -1.0f || v1.position.y > 1.0f ||
		v2.position.x < -1.0f || v2.position.x > 1.0f || v2.position.y < -1.0f || v2.position.y > 1.0f ||
		v3.position.x < -1.0f || v3.position.x > 1.0f || v3.position.y < -1.0f || v3.position.y > 1.0f ||
		v4.position.x < -1.0f || v4.position.x > 1.0f || v4.position.y < -1.0f || v4.position.y > 1.0f)
	{
		return;
	}

}

/// <summary>
/// Draw a textured quad on screen (alpha blending supported)
/// </summary>
/// <param name="screenPos">: origin position of texture</param>
/// <param name="textureSize">: size of texture</param>
/// <param name="textureBuffer">: color buffer of texture data</param>
void Renderer::DrawTexturedQuad(const cVec2& screenPos, const cVec2& textureSize, Color* textureBuffer)
{
	// Check if texture is valid
	if (textureBuffer == nullptr)
	{
		CE_LOG_ERROR("Texture is null");
		return;
	}

	// Check if texture is out of bounds of screen space (normalized coordinates)
	if (screenPos.x < -1.0f || screenPos.x > 1.0f || screenPos.y < -1.0f || screenPos.y > 1.0f)
	{
		CE_LOG_ERROR("Texture is out of bounds");
		return;
	}
	

	// Convert normalized coordinates to screen coordinates centered at (0, 0)
	const GLint x1 = static_cast<GLint>(glm::floor((screenPos.x + 1.0f) * (GLfloat)(width / 2)));
	const GLint y1 = static_cast<GLint>(glm::floor((screenPos.y + 1.0f) * (GLfloat)(height / 2)));

	// Get texture width and height
	const GLint tWidth = static_cast<GLint>(textureSize.x);
	const GLint tHeight = static_cast<GLint>(textureSize.y);

	// Check if texture is out of bounds of screen space (screen coordinates)
	if (x1 < 0 || x1 + tWidth > width || y1 < 0 || y1 + tHeight > height)
	{
		CE_LOG_ERROR("Texture is out of bounds on screen coord!");
		return;
	}

	// Copy texture data to framebuffer
	for (GLint y = 0; y < tHeight; y++)
	{
		for (GLint x = 0; x < tWidth; x++)
		{
			// Get color data from texture
			Color color = textureBuffer[y * tWidth + x];

			// If alpha is 0, skip pixel
			if (color.a == 0) continue;

			// If alpha is 255, set pixel directly
			if (color.a == 255)
			{
				mainFramebuffer[(y + y1) * width + (x + x1)] = color;
				continue;
			}

			// If alpha is between 0 and 255, blend pixel
			// Get pixel from framebuffer
			Color pixel = mainFramebuffer[(y + y1) * width + (x + x1)];

			// Calculate alpha
			GLfloat alpha = (GLfloat)color.a / 255.0f;

			// Calculate blended color
			Color blendedColor = (color * alpha) + (pixel * (1.0f - alpha));

			// Set blended color to framebuffer
			mainFramebuffer[(y + y1) * width + (x + x1)] = blendedColor;
		}
	}
}

void Renderer::DrawMesh(Mesh* mesh, Texture* texture, cVec3 cameraPosition, cVec3 cameraDirection, cMat4 modelMatrix)
{
	// Get triangle list
	std::vector<Triangle> triangles = mesh->GetTriangles();
 
	// Transform vertices
	for (auto& triangle : triangles)
	{
		// Transform vertices
		triangle.v1.position = cVec3(modelMatrix * cVec4(triangle.v1.position, 1.0f));
		triangle.v2.position = cVec3(modelMatrix * cVec4(triangle.v2.position, 1.0f));
		triangle.v3.position = cVec3(modelMatrix * cVec4(triangle.v3.position, 1.0f));

		// Update normals
		triangle.v1.normal = cVec3(modelMatrix * cVec4(triangle.v1.normal, 0.0f));
		triangle.v2.normal = cVec3(modelMatrix * cVec4(triangle.v2.normal, 0.0f));
		triangle.v3.normal = cVec3(modelMatrix * cVec4(triangle.v3.normal, 0.0f));
	}

	// Eliminate back faces
	triangles.erase(std::remove_if(triangles.begin(), triangles.end(), [&](Triangle& t) {
		// Calculate normal
		cVec3 normal = glm::normalize(glm::cross(t.v2.position - t.v1.position, t.v3.position - t.v1.position));
		// Calculate camera vector
		cVec3 cameraVector = glm::normalize(cameraPosition - t.v1.position);
		// Calculate dot product
		GLfloat dotProduct = glm::dot(normal, cameraVector);
		// If dot product is less than 0, triangle is back face
		return dotProduct < 0.0f;
	}), triangles.end());

	// Sort triangles by depth depending on camera direction
	std::sort(triangles.begin(), triangles.end(), [&](Triangle& t1, Triangle& t2) {
		// Calculate depth
		GLfloat depth1 = glm::dot(cameraDirection, t1.v1.position);
		GLfloat depth2 = glm::dot(cameraDirection, t2.v1.position);
		// Return depth comparison
		return depth1 > depth2;
	});

	// Loop through triangles
	for (auto& triangle : triangles)
	{
		// Draw triangle
		DrawTriangle(triangle.v1, triangle.v2, triangle.v3);
	}
}

void Renderer::DrawScreen()
{
	/* Testing Area */
	std::chrono::duration<GLdouble> dt;

	CE_STOPWATCH w1 = CE_STOPWATCH::stopwatch();

	const GLfloat ttime = (GLfloat)glfwGetTime();

	// Test rectangle
	const Vertex v1(cVec3(0.5f, 0.5f, 0.0f), Color(255, 0, 0, 255));
	const Vertex v2(cVec3(0.5f, -0.5f, 0.0f), Color(0, 255, 0, 255));
	const Vertex v3(cVec3(-0.5f, -0.5f, 0.0f), Color(0, 0, 255, 255));
	const Vertex v4(cVec3(-0.5f, 0.5f, 0.0f), Color(255, 255, 255, 255));
	Triangle t1 = Triangle(v1, v2, v3);
	
	// Basic transformations workflow
	// Model vector data
	const cVec3 position(0.0f);
	const cVec3 rotationD(0.0f);
	const cVec3 scale(1.0f);
	// Model Matrices
	const cMat4 m_model	= cMat4(1.0f); // Identity matrix
	const cMat4 m_translate	= glm::translate(m_model,	cVec3(0.0f, -0.5f, 0.0f)); // Translation Matrix
	const cMat4 m_scale		= glm::scale	(m_model,	cVec3(0.4f)); // Scaling Matrix
	const cMat4 m_rotate	= glm::rotate	(m_model, ttime, cVec3(0.0f, 1.0f, 0.0f)); // Rotation Matrix
	/* End Testing Area */

	/*3D Projection Test Area */
	// Set Up Camera Properties
	const cVec3 cameraPos	= cVec3(0.0f, 0.0f, 3.0f);
	const cVec3 cameraFront = cVec3(0.0f, 0.0f, -1.0f);
	const cVec3 cameraUp	= cVec3(0.0f, 1.0f, 0.0f);

	// Setup MVP starting with Projection
	// Set Up Projection
	const GLfloat fov			= 90.0f;
	const GLfloat nearPlane		= 0.1f;
	const GLfloat farPlane		= 100.0f;
	const GLfloat aspectRatio	= (GLfloat)width / (GLfloat)height;
	
	cMat4 m_view(1.0f); // view identity matrix
	m_view = glm::translate(m_view, cameraPos);
	const cMat4 m_perspective = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
	/**************************/

	/* Fill the back buffer */
	/* Transformations Test Area */
	const cMat4 m_MVP = m_perspective * m_view * m_translate * m_rotate * m_scale;


	// Transform texture coordinates
	/*Vertex tv1((cVec3)(m_MVP * cVec4(v1.position, 1.0f))); tv1.color = v1.color; tv1.texCoord = cVec2(1.0f, 1.0f);
	Vertex tv2((cVec3)(m_MVP * cVec4(v2.position, 1.0f))); tv2.color = v2.color; tv2.texCoord = cVec2(1.0f, 0.0f);
	Vertex tv3((cVec3)(m_MVP * cVec4(v3.position, 1.0f))); tv3.color = v3.color; tv3.texCoord = cVec2(0.0f, 0.0f);
	Vertex tv4((cVec3)(m_MVP * cVec4(v4.position, 1.0f))); tv4.color = v4.color; tv4.texCoord = cVec2(0.0f, 1.0f);*/

	/* Clear Color Framebuffer */
	ClearScreen();

	// Draw Mesh
	DrawMesh(rAssetManager->GetMesh("quaddamage"), rAssetManager->GetTexture("skin0"), cameraPos, cameraFront, m_MVP);

	/*
	DrawTriangle(tv1, tv2, tv3);
	DrawTriangle(tv4, tv1, tv3);
	//DrawQuad(tv1, tv2, tv3, tv4, r_asset_manager_->GetTexture("1222"));
	// Get Texture Data and Properties
	Color* textureData = rAssetManager->GetTexture("1222")->GetData();
	GLint textureWidth = rAssetManager->GetTexture("1222")->GetWidth();
	GLint textureHeight = rAssetManager->GetTexture("1222")->GetHeight();

	DrawTexturedQuad(cVec2(-1.0f, -1.0f), cVec2(textureWidth, textureHeight), textureData);
	textureData = rAssetManager->GetTexture("grntst")->GetData();
	textureWidth = rAssetManager->GetTexture("grntst")->GetWidth();
	textureHeight = rAssetManager->GetTexture("grntst")->GetHeight();

	DrawTexturedQuad(cVec2(0.85f, -1.0f), cVec2(textureWidth, textureHeight), textureData);
	/**************************/
	
	/* Draw Framebuffer */
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, mainFramebuffer.get());

	/* Get delta time */
	dt = w1.elapsed();

	/* Swap front and back buffers */
	glfwSwapBuffers(windowReference);

	/* Reset Stopwatch */
	w1.reset();

	/* Print Elapsed Time On Console */
	//CE_LOG_INFO("Loop Time: {} \nElapsed Time: {}\r", dt.count(), ttime);
}

void Renderer::ClearScreen()
{
	// Clear Screen
	memset(mainFramebuffer.get(), (GLubyte)0, width * height * sizeof(Color));
}
