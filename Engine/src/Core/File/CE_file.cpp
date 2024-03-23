#include "CE_global.hpp"

namespace CyberEngine {
	bool File::LoadFile()
	{
		// Check if file exists
		if (!std::filesystem::exists(filePath))
		{
			CE_LOG_ERROR("File does not exist: {0}", filePath);
			return false;
		}

		// Try Open file as binary
		std::ifstream file(filePath, std::ios::binary);
		if (!file.is_open())
		{
			CE_LOG_ERROR("Failed to open file: {0}", filePath);
			isBinary = false;
		}
		else
		{
			CE_LOG_INFO("Opened file: {0}", filePath);
			isBinary = true;
		}

		if (isBinary) {
			// Get file size
			file.seekg(0, std::ios::end);
			fileSize = file.tellg();
			file.seekg(0, std::ios::beg);

			// Read file into buffer
			fileData = new GLubyte[fileSize];
			file.read(fileData, fileSize);
			file.close();
		} else {
			// Read file into buffer
			std::string line;
			while (std::getline(file, line))
			{
				fileBuffer += line + "\n";
			}
			file.close();
		}

	}
	bool File::SaveFile()
	{
		return false;
	}
	GLubyte* File::GetFileData()
	{
		if (isBinary)
			return fileData;
		else
		return nullptr;
	}
}