#include <vector>
#include <memory>
#include <unordered_map>
#include "scene_object.h"
#include "scene.h"

void Scene::addObject(std::unique_ptr<SceneObject> object, Shader* shader) {
	SceneObject* objPtr = object.get();
	Shader* targetShader = shader;

	renderBatches[targetShader].push_back(objPtr);
	sceneObjects.push_back(std::move(object));
}

void Scene::drawScene() {
	for (auto& [currentShader, shaderObjects] : renderBatches) {
		currentShader->use();

		for (SceneObject* obj : shaderObjects) {
			obj->Draw(*currentShader);
		}
	}
}

const std::vector<std::unique_ptr<SceneObject>>& Scene::getObjects() {
	return sceneObjects;
}

SceneObject* Scene::getObjectByID(unsigned int objectID) {
	for (auto& obj : sceneObjects) {
		if (objectID == obj->id) {
			return obj.get();
		}
	}
	return nullptr;
}