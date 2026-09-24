#include "scene_manager.h" 
#include "scene_loader.h"

std::unique_ptr<Scene> SceneManager::loadSceneFromFile(std::string const& path) {
	std::unique_ptr<Scene> scene(loadScene(path));
	Scene* sceneptr = scene.get();
	sceneList.push_back(std::move(scene));
	return scene;
}