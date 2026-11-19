#pragma once

#include <string>
#include "scene.h"
#include "scene_loader.h"

class SceneManager {
public:
	EngineContext* engineContext;

	void setEngineContext(EngineContext* context) {
		if (context == NULL) {
			std::cout << "Error: Engine pointer null!" << std::endl;
			return;
		}
		engineContext = context;
	}

	Scene* loadSceneFromFile(std::string const& path);

private: 
	std::vector<std::unique_ptr<Scene>> sceneList;
};