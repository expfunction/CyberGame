#pragma once

namespace CyberEngine {
	// Color Struct
	struct Color
	{
		GLubyte r, g, b, a;

		Color() = default;
		constexpr Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : r(r), g(g), b(b), a(a) {}

		Color& operator=(const Color& rhs) {
			this->r = rhs.r;
			this->g = rhs.g;
			this->b = rhs.b;
			this->a = rhs.a;
			return *this;
		}

		Color operator+(const Color& rhs) const
		{
			return Color(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
		}

		Color& operator+(const Color& rhs)
		{
			r += rhs.r;
			g += rhs.g;
			b += rhs.b;
			a += rhs.a;
			return *this;
		}

		Color& operator-(const Color& rhs)
		{
			r -= rhs.r;
			g -= rhs.g;
			b -= rhs.b;
			a -= rhs.a;
			return *this;
		}

		Color& operator*(const Color& rhs)
		{
			r *= rhs.r;
			g *= rhs.g;
			b *= rhs.b;
			a *= rhs.a;
			return *this;
		}

		Color operator*(GLfloat rhs) const
		{
			return Color(r * rhs, g * rhs, b * rhs, a * rhs);
		}
	};

	struct Vertex
	{
		cVec3 position = cVec3(0.0f);

		cVec3 normal = cVec3(0.0f);

		cVec2 texCoord = cVec2(0.0f);

		Color color = Color(255, 255, 255, 255);

		Vertex() = default;
		~Vertex() = default;
		Vertex(cVec3 pos, Color col) : position(pos), color(col), texCoord(0.0f) {}
		Vertex(cVec3 pos) : position(pos), color(Color(255, 255, 255, 255)), texCoord(0.0f) {}
		Vertex(cVec3 pos, cVec3 norm) : position(pos), normal(norm), color(Color(255, 255, 255, 255)), texCoord(0.0f) {}
		Vertex(cVec3 pos, cVec3 norm, Color col) : position(pos), normal(norm), color(col), texCoord(0.0f) {}
		Vertex(Color col) : position(cVec3(0.0f)), color(col), texCoord(0.0f) {}
		Vertex(cVec2 tex_coords) : position(cVec3(0.0f)), texCoord(tex_coords), color(Color(255, 255, 255, 255)) {}
		Vertex(cVec3 pos, cVec2 tex_coords) : position(pos), texCoord(tex_coords), color(Color(255, 255, 255, 255)) {}
		Vertex(cVec3 pos, cVec2 tex_coords, Color col) : position(pos), texCoord(tex_coords), color(col) {}
		Vertex(cVec3 pos, cVec3 norm, cVec2 tex_coords, Color col) : position(pos), normal(norm), texCoord(tex_coords), color(col) {}

		Vertex& operator=(const Vertex& rhs) {
			this->position = rhs.position;
			this->color = rhs.color;
			this->texCoord = rhs.texCoord;
			this->normal = rhs.normal;
			return *this;
		}

		Vertex& operator+(const Vertex& rhs) {
			this->position += rhs.position;
			return *this;
		}

		Vertex& operator-(const Vertex& rhs) {
			this->position -= rhs.position;
			return *this;
		}

		Vertex& operator*(const GLfloat& rhs) const {
			Vertex vert(position, color);
			vert.position *= rhs;
			return vert;
		}
	};

	struct Triangle
	{
		Vertex v1;
		Vertex v2;
		Vertex v3;

		cVec3 normal;

		cMat4 transform;

		Color color;

		Triangle();
		Triangle(Vertex v1, Vertex v2, Vertex v3);

	};
}