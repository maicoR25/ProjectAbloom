#include <string>
#include <fstream>
#include <memory>
#include <nlohmann-json/json.hpp>
#include "../headers/model.h"
#include "scene.h"
#include "scene_loader.h"
#include "scene_object.h"
using json = nlohmann::json;

Scene loadScene(std::string const& path) {
	Scene scene;
	std::ifstream f(path);
	json data = json::parse(f);
	std::cout << data;

	std::shared_ptr backpackModel = std::make_shared<Model>("assets/models/backpack/backpack.obj");
	std::shared_ptr cubeModel = std::make_shared<Model>("assets/models/cube.obj");
	Shader cubeShader("assets/shaders/cubeVertexShader.vert", "assets/shaders/lightingShader.frag");
	cubeShader.bindUniformBlock("CameraData", 0);
	Shader lightShader("assets/shaders/simpleVertexShader.vert", "assets/shaders/lightSourceShader.frag");
	Shader modelShader("assets/shaders/modelVertexShader.vert", "assets/shaders/modelFragmentShader.frag");
	modelShader.bindUniformBlock("CameraData", 0);

	scene.addObject(std::make_unique<SceneObject>(backpackModel), &modelShader);
	scene.addObject(std::make_unique<SceneObject>(cubeModel), &cubeShader);
	return scene;
}