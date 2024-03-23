#pragma once

namespace CyberEngine {
	class Mesh : public Asset
	{
	private:
		// Triangle vertices
		std::vector<Vertex> vertices;
		// Triangle indices
		std::vector<GLuint> indices;
		// Triangles List
		std::vector<Triangle> triangles;
		// Vertex Normals
		std::vector<cVec3> normals;
		// Texture Coords
		std::vector<cVec2> texCoords;
	
	public:

		// Constructor
		Mesh(const cString& path, const cString& name);

		// Destructor
		~Mesh();

		// Getters
		std::vector<Vertex> GetVertices() const { return vertices; }
		std::vector<GLuint> GetIndices() const { return indices; }
		std::vector<Triangle> GetTriangles() const { return triangles; }
	};
}