#include "CE_global.hpp"

using namespace CyberEngine;

Mesh::Mesh(const cString& path, const cString& mName)
{
	// Set Name
	name = mName;

	// Initialize buffers
	vertices = std::vector<Vertex>();
	indices = std::vector<GLuint>();
	triangles = std::vector<Triangle>();
	texCoords = std::vector<cVec2>();
	normals = std::vector<cVec3>();

	// Open file
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "Error: File not found" << std::endl;
		return;
	}

	// Read file
	std::string line;
	GLuint vertexIndex = 0;
	GLuint texCoordIndex = 0;
	GLuint triangleId = 0;

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		cString type;
		iss >> type;
		if (type == "v") {
			Vertex vertex;
			iss >> vertex.position.x >> vertex.position.y >> vertex.position.z;
			vertices.push_back(vertex);
		}
		else if (type == "f") {
			// Create Triangle
			Triangle triangle;
				
			// Read Vertex Data
			GLuint v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3;
			iss >> v1; iss.ignore(1); iss >> vt1; iss.ignore(1); iss >> vn1;
			iss >> v2; iss.ignore(1); iss >> vt2; iss.ignore(1); iss >> vn2;
			iss >> v3; iss.ignore(1); iss >> vt3; iss.ignore(1); iss >> vn3;

			// Set Vertex Data
			triangle.v1 = vertices[v1 - 1];
			triangle.v2 = vertices[v2 - 1];
			triangle.v3 = vertices[v3 - 1];

			// Set Texture Data
			triangle.v1.texCoord = texCoords[vt1 - 1];
			triangle.v2.texCoord = texCoords[vt2 - 1];
			triangle.v3.texCoord = texCoords[vt3 - 1];

			// Set Normal Data
			triangle.v1.normal = normals[vn1 - 1];
			triangle.v2.normal = normals[vn2 - 1];
			triangle.v3.normal = normals[vn3 - 1];

			triangle.id = triangleId;
			triangleId++;

			// Add Triangle to Triangles
			triangles.push_back(triangle);
				
		}
		else if (type == "vt") {
			cVec2 texCoord;
			iss >> texCoord.x >> texCoord.y;

			texCoords.push_back(texCoord);
		}
		else if (type == "vn") {
			cVec3 normal;
			iss >> normal.x >> normal.y >> normal.z;
				
			normals.push_back(normal);
		}
	}

	// Close file
	file.close();
}

Mesh::~Mesh()
{
	// Clear Triangles
	triangles.clear();

	// Delete Vertices
	vertices.clear();

	// Delete Indices
	indices.clear();
}