#include "CE_global.hpp"

namespace CyberEngine {

    bool Scene::LoadScene(const cString& path)
    {
        File sceneFile(path);

        if (!sceneFile.IsFileLoaded())
        {
			CE_LOG_ERROR("Failed to load scene file: {0}", path);
			return false;
		}


        return false;
    }

    bool Scene::SaveScene(const cString& path)
    {
        // Create a new scene file


        return false;
    }
}