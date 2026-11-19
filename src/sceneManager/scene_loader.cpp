#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <nlohmann-json/json.hpp>
#include "../headers/model.h"
#include "scene.h"
#include "scene_loader.h"
#include "scene_object.h"
using json = nlohmann::json;

const std::string modelFilePath = "assets/models/";

std::unique_ptr<Scene> loadScene(std::string const& path) {
	std::unique_ptr<Scene> scene;
	std::ifstream f(path);
	json data = json::parse(f);
	std::vector<SceneObject*> sceneObjects;

	if (data["objects"].is_array())
		std::cout << " \nobjects is an array" ;
	for (size_t i = 0; i < data["objects"].size(); i++) {
		std::string objectName = data["objects"][i]["name"].get<std::string>();
		std::string objectModelPath = data["objects"][i]["path"].get<std::string>();
		std::shared_ptr objectModel = std::make_shared<Model>(modelFilePath + objectModelPath);
		std::string objectShaderpath;
		
		//newObject->name = objectName;
		Shader objectShader("", "");

		std::unique_ptr newObject = std::make_unique<SceneObject>(objectModel);
		newObject->name = objectName;

		scene->addObject(std::move(newObject), &objectShader);
		//sceneObjects.push_back(newObject);
		//std::cout << "\n" << sceneObjects[i]->name;
	}

	//std::shared_ptr backpackModel = std::make_shared<Model>("assets/models/backpack/backpack.obj");
	//std::shared_ptr cubeModel = std::make_shared<Model>("assets/models/cube.obj");
	//Shader cubeShader("assets/shaders/cubeVertexShader.vert", "assets/shaders/lightingShader.frag");
	//cubeShader.bindUniformBlock("CameraData", 0);
	//Shader lightShader("assets/shaders/simpleVertexShader.vert", "assets/shaders/lightSourceShader.frag");
	//Shader modelShader("assets/shaders/modelVertexShader.vert", "assets/shaders/modelFragmentShader.frag");
	//modelShader.bindUniformBlock("CameraData", 0);
	// 
	//scene->addObject(std::make_unique<SceneObject>(backpackModel), &modelShader);
	//scene->addObject(std::make_unique<SceneObject>(cubeModel), &cubeShader);
	return scene;
}