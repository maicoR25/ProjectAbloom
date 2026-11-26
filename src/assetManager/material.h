#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../headers/shader.h"

struct MaterialProperties {
	glm::vec3 albedo = { 1.0f, 1.0f, 1.0f };
	float specular = 0.5f;
	float roughness = 0.5f;
};


class Material {
public:
	
	static std::shared_ptr<Material> createMaterial(Shader *shader, const MaterialProperties *properties);
	
private:
	Shader* shader = nullptr;
	MaterialProperties properties;
};