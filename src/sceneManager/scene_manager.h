#pragma once

#include <string>
#include "scene.h"
#include "scene_loader.h"

class SceneManager {
public:
	std::unique_ptr<Scene> loadSceneFromFile(std::string const& path);

private: 
	std::vector<std::unique_ptr<Scene>> sceneList;
};