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

		std::unique_ptr<GLubyte[]> fileData;
		cString fileDataString;

	public:

		File(cString filePath) {
			this->filePath = filePath;
			this->fileName = "";
			this->fileExtension = "";
			this->fileData = nullptr;
			this->fileSize = 0;
			this->isBinary = false;
			fileDataString = "";

		}
		~File() = default;

		cString GetFilePath() { return filePath;}
		cString GetFileName() { return fileName; }
		cString GetFileExtension() { return fileExtension; }

		void SetFilePath(cString filePath) { this->filePath = filePath; }
		void SetFileName(cString fileName) { this->fileName = fileName; }
		void SetFileExtension(cString fileExtension) { this->fileExtension = fileExtension; }

		bool CreateFile(cString fileName, cString fileExtension);
		bool LoadFile();
		bool SaveFile();

		std::unique_ptr<GLubyte[]> GetFileData();
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