#pragma once
namespace CyberEngine {
	class File
	{
	private:
		cString filePath;
		cString fileName;
		cString fileExtension;

		GLuint fileSize;

		bool isBinary;

		std::unique_ptr<GLbyte*> fileData;
		cString fileDataString;

	public:

		File(cString fileNameAndPath) {
			// Parse file name and extension
			filePath = fileNameAndPath;
			fileName = std::filesystem::path(fileNameAndPath).filename().string();
			fileExtension = std::filesystem::path(fileNameAndPath).extension().string();
			this->fileData = nullptr;
			this->fileSize = 0;
			this->isBinary = false;
			fileDataString = "";
			LoadFile();
		}

		

		~File() = default;

		cString GetFilePath() { return filePath;}
		cString GetFileName() { return fileName; }
		cString GetFileExtension() { return fileExtension; }

		void SetFilePath(cString filePath) { this->filePath = filePath; }
		void SetFileName(cString fileName) { this->fileName = fileName; }
		void SetFileExtension(cString fileExtension) { this->fileExtension = fileExtension; }

		bool LoadFile();
		bool SaveFile(const cString& fileNameAndPath, bool isBinary);

		std::unique_ptr<GLubyte*> GetFileData();
		void SetFileData(GLubyte *fileData);
		bool IsBinary() { return isBinary; }
		GLuint GetFileSize() { return fileSize; }
		cString GetFileDataString() { return fileDataString; }
		bool IsFileLoaded() { return fileData != nullptr; }
		bool IsFileLoadedString() { return !fileDataString.empty(); }
		bool IsFileLoadedBinary() { return isBinary; }
		bool IsFileLoadedText() { return !isBinary; }
		
	};
}