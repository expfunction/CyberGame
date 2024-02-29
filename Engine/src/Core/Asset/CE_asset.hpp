#pragma once

namespace CyberEngine {

	enum class AssetType {
		TEXTURE,
		MODEL,
		SHADER,
		MATERIAL,
		SCRIPT,
		ANIMATION,
		UNKNOWN
	};

	class Asset {
	private:
		CUID id;
		cString path;
		cString name;
		AssetType type;

		// Generate a UUID for the asset
		CUID GenerateUUID();
	public:
		// Default constructor
		Asset() {
			//CE_LOG_INFO("Default constructor for asset!");

			this->path = "";
			this->name = "";
			this->type = AssetType::UNKNOWN;
			this->id = GenerateUUID();
		}

		Asset(const cString& filePath, const cString& name, const AssetType& type) {
			this->path = filePath;
			this->name = name;
			this->type = type;
			this->id = GenerateUUID();
		}

		~Asset() {
			CE_LOG_INFO("Destructor for asset {0}", name);

			this->path = "";
			this->name = "";
			this->type = AssetType::UNKNOWN;
		}

		cString GetPath() { return path; }
		cString GetName() { return name; }
		AssetType GetType() { return type; }
		CUID GetID() { return id; }

		void SetPath(cString path) { this->path = path; }
		void SetName(cString name) { this->name = name; }
		void SetType(AssetType type) { this->type = type; }
	};
}