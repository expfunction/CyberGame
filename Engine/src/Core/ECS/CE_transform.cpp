#include "CE_global.hpp"

namespace CyberEngine {
	Transform::Transform()
	{
		position = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
	}
	Transform::Transform(const Transform& other)
	{
		position = other.position;
		rotation = other.rotation;
		scale = other.scale;
	}
}

