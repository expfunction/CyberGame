#include "CE_global.hpp"

namespace CyberEngine {
	
	Triangle::Triangle()
	{
		v1 = Vertex();
		v2 = Vertex();
		v3 = Vertex();
		
		normal = cVec3(0.0f);

		color = Color(255, 155, 155, 255);

		transform = cMat4(1.0f);
	}
	Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;

		normal = cVec3(0.0f);

		color = Color(255, 255, 255, 255);

		transform = cMat4(1.0f);
	}

}
