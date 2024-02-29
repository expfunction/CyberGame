#pragma once

namespace CyberEngine {
	class Texture : public Asset {
	private:
		GLubyte* localBuffer;
		Color* colorBuffer;
		GLint width, height, BPP;
	public:
		Texture(const cString& path, const cString& name);
		~Texture();
		const GLubyte* GetBuffer() { return localBuffer; };
		const GLint GetWidth() { return width; };
		const GLint GetHeight() { return height; };
		const GLint GetBPP() { return BPP; };
		const GLubyte GetRed(GLint x, GLint y) { return localBuffer[(y * width + x) * BPP]; };
		const GLubyte GetGreen(GLint x, GLint y) { return localBuffer[(y * width + x) * BPP + 1]; };
		const GLubyte GetBlue(GLint x, GLint y) { return localBuffer[(y * width + x) * BPP + 2]; };
		const GLubyte GetAlpha(GLint x, GLint y) { return localBuffer[(y * width + x) * BPP + 3]; };
		GLubyte* GetPixel(GLint x, GLint y) { return localBuffer + (y * width + x) * BPP; };
		Color* GetData();
		GLubyte* GetBufferStart() { return localBuffer; };
		GLubyte* GetBufferEnd() { return localBuffer + (width * height * BPP); };
	};

}