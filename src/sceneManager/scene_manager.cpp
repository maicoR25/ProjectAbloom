#include "scene_manager.h" 
#include "scene_loader.h"

Scene SceneManager::loadSceneFromFile(std::string const& path) {
	return loadScene(path);
}