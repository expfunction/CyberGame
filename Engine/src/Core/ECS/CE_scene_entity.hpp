#pragma once

namespace CyberEngine {
	struct SceneEntity : public Entity {
	public:
		cVec3 position = cVec3(0.0f);
		cVec3 rotation = cVec3(0.0f);
		cVec3 scale	= cVec3(1.0f);
	};
}