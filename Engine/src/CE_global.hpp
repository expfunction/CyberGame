#pragma once

#define NOMINMAX

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <chrono>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <Windows.h>

#include <UUID/uuid_v4.h>
 
#define GLM_FORCE_SSE42 // or GLM_FORCE_SSE42 if your processor supports it
#define GLM_FORCE_ALIGNED
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <libpng/include/png.h>

#include <entt/entt.hpp>

#include <freetype/freetype.h>

/* Definitions */
typedef glm::vec2 cVec2;
typedef glm::vec3 cVec3;
typedef glm::vec4 cVec4;

typedef glm::mat4 cMat4;

typedef std::string cString;

typedef UUIDv4::UUID CUID;

// Engine Includes
#include "Core/CE_log.hpp"
#include "Core/ECS/CE_ecs.hpp"
#include "Renderer/CE_geometry.hpp"

#include "Core/ECS/CE_scene_entity.hpp"
#include "Core/ECS/CE_renderable.hpp"

#include "Core/Asset/CE_asset.hpp"
#include "Renderer/CE_texture.hpp"
#include "Core/Asset/CE_asset_manager.hpp"

#include "Renderer/CE_renderer.hpp"
#include "Application/CE_application.hpp"
