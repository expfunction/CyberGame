#include "CE_global.hpp"

using namespace CyberEngine;

// Constructor
Texture::Texture(const cString& path, const cString& name)
{
	// Initialize variables
	width = 0;
	height = 0;
	BPP = 0;
	localBuffer = nullptr;
	colorBuffer = nullptr;

	// Set name, path and type
	this->SetName(name);
	this->SetPath(path);
	this->SetType(AssetType::TEXTURE);


	// Load image using libpng
	png_image image;
	memset(&image, 0, sizeof(image));
	image.version = PNG_IMAGE_VERSION;

	if (!png_image_begin_read_from_file(&image, path.c_str()))
	{
		CE_LOG_ERROR("Failed to load texture: {0}", path);
		return;
	}

	image.format = PNG_FORMAT_RGBA;
	png_bytep buffer = (png_bytep)malloc(PNG_IMAGE_SIZE(image));

	if (!png_image_finish_read(&image, NULL, buffer, 0, NULL))
	{
		CE_LOG_ERROR("Failed to load texture: {0}", path);
		return;
	}

	// Copy image data to localBuffer
	width = image.width;
	height = image.height;
	BPP = PNG_IMAGE_PIXEL_SIZE(image.format);
	localBuffer = (GLubyte*)malloc(width * height * BPP);

	for (int i = 0; i < height; i++) {
		GLubyte* row = localBuffer + (width * BPP * i);
		GLubyte* row1 = buffer + (width * BPP * (height - i - 1));
		memcpy(row, row1, width * BPP);
	}

	// Set Color Buffer
	colorBuffer = (Color*)malloc(width * height * sizeof(Color));
	for (GLuint i = 0; i < width * height; i++)
	{
		colorBuffer[i].r = localBuffer[i * BPP];
		colorBuffer[i].g = localBuffer[i * BPP + 1];
		colorBuffer[i].b = localBuffer[i * BPP + 2];
		colorBuffer[i].a = localBuffer[i * BPP + 3];
	}

	// Free memory
	png_image_free(&image);
	free(buffer);
}

Texture::~Texture()
{
	// Free memory
	CE_LOG_INFO("Texture {0} deleted", this->GetName());
}

Color* Texture::GetData()
{
	return colorBuffer;
}
