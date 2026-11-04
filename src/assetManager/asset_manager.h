#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../headers/model.h"

class AssetManager {
public:
	struct Material {
		std::vector<std::unique_ptr<Shader>> materialShaders;
		
	};
	std::shared_ptr<Model> getModel(std::string const path);
	std::shared_ptr<Material> getMaterial();
private:
	std::vector<std::shared_ptr<Model>> loadedModels;
};
