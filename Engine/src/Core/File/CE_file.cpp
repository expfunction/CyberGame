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
			fileData = std::make_unique<GLubyte*>(fileSize);
			file.read(reinterpret_cast<char*>(fileData.get()), fileSize);
			file.close();
		} else {
			// Read file into buffer
			std::string line;
			while (std::getline(file, line))
			{
				fileDataString += line + "\n";
			}
			file.close();
		}

	}

	bool File::SaveFile(const cString& fileNameAndPath, bool isBinary)
	{
		// Check if file exists
		if (!std::filesystem::exists(filePath))
		{
			CE_LOG_ERROR("File does not exist: {0}", filePath);
			return false;
		}

		if(isBinary) {
			// Try Open file as binary
			std::ofstream file(filePath, std::ios::binary);
			if (!file.is_open())
			{
				CE_LOG_ERROR("Failed to open file: {0}", filePath);
				return false;
			}

			// Write file into buffer
			file.write(reinterpret_cast<char*>(fileData.get()), fileSize);
			file.close();
		} else {
			// Read file into buffer
			std::ofstream file(filePath);
			if (!file.is_open())
			{
				CE_LOG_ERROR("Failed to open file: {0}", filePath);
				return false;
			}

			// Write file into buffer
			file << fileDataString;
			file.close();
		}
		return true;
	}

	std::unique_ptr<GLubyte*> File::GetFileData()
	{
		if (isBinary)
			return std::move(fileData);
		else
			return nullptr;
	}

	void File::SetFileData(GLubyte* fileData)
	{
		if (isBinary)
			this->fileData = std::unique_ptr<GLubyte*>(fileData);
		else
			CE_LOG_ERROR("Cannot set file data for text file {0}", fileName);
	}
}