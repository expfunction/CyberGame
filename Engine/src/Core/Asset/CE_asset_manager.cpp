#include "CE_global.hpp"

using namespace CyberEngine;

AssetManager* AssetManager::GetInstance()
{
	if (asset_manager_ == nullptr)
	{
		asset_manager_ = new AssetManager();
	}
	return asset_manager_;
}

void AssetManager::Init()
{
	CE_LOG_INFO("Asset Manager Initialized, Loading Assets in Resources Folder");

	// Check if the resources folder exists
#if _DEBUG
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::wstring resourcesPath = currentPath.append("Game\\resources");
#else
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::wstring resourcesPath = currentPath.append("..\\..\\Game\\resources");
#endif

	if (!std::filesystem::exists(resourcesPath))
	{
		CE_LOG_ERROR("Resources Folder does not exist");
		return;
	}

	// Get all files in the resources folder recursively
	std::vector<cString> fileList;
	for (auto& p : std::filesystem::recursive_directory_iterator(resourcesPath))
	{
		if(!p.is_directory())
			fileList.push_back(p.path().string());
	}

	// Load all assets
	for (auto& file : fileList)
	{
		CE_LOG_INFO("Loading Asset: " + file);
		// Parse the file extension
		std::string extension = file.substr(file.find_last_of(".") + 1);

		// Check if the file is a texture
		if (extension == "png" || extension == "jpg" || extension == "jpeg" || extension == "tga")
		{
			// Get the file name without the path and extension
			std::string fileName = file.substr(file.find_last_of("\\") + 1, file.find_last_of(".") - file.find_last_of("\\") - 1);

			CE_LOG_INFO("Loading Texture: " + file);

			// Create texture asset
			Texture *tmpTexture = new Texture(file, fileName);

			// Add asset to assets
			assets.insert(std::pair<CUID, Asset>(tmpTexture->GetID(), *tmpTexture));

			// Add asset to the textures map
			textures.insert(std::pair<CUID, Texture>(tmpTexture->GetID(), *tmpTexture));

		}
	}

	CE_LOG_INFO("Asset Manager Initialized");
}

Texture* CyberEngine::AssetManager::GetTexture(cString name)
{
	// Search for the texture in the textures map
	for (auto& texture : textures)
	{
		if (texture.second.GetName() == name)
		{
			return &texture.second;
		}
	}

	// If texture is not found, return a default texture
	CE_LOG_ERROR("Texture {0} not found", name);
	return nullptr;
}
