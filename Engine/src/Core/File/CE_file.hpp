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

		std::unique_ptr<char> *fileData;

	public:

		File(cString filePath) {
			this->filePath = filePath;
			this->fileName = "";
			this->fileExtension = "";
			this->fileData = nullptr;
			this->fileSize = 0;
		}
		~File() = default;

		cString GetFilePath() { return filePath;}
		cString GetFileName() { return fileName; }
		cString GetFileExtension() { return fileExtension; }

		void SetFilePath(cString filePath) { this->filePath = filePath; }
		void SetFileName(cString fileName) { this->fileName = fileName; }
		void SetFileExtension(cString fileExtension) { this->fileExtension = fileExtension; }

		bool LoadFile();
		bool SaveFile();

		GLubyte *GetFileData();
		void SetFileData(GLubyte *fileData);
	};
}