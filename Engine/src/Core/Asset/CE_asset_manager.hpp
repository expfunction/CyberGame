#pragma once
#include "CE_global.hpp"

namespace CyberEngine {

	class AssetManager
	{
	protected:
		// Default Constructor
		AssetManager() {}

		// Private Variables
		static AssetManager* asset_manager_;
		std::unordered_map<CUID, Asset> assets;
		std::unordered_map<CUID, Texture> textures;

	public:
		AssetManager(AssetManager& other) = delete;
		void operator=(const AssetManager&) = delete;
		static AssetManager* GetInstance();

		// Public Functions
		void Init();
		void LoadAssets();
		void AddAsset(cString path, cString name, AssetType type);
		void RemoveAsset(cString name);
		Asset GetAsset(cString name);
		Texture* GetTexture(cString name);
	};
}