#include "material.h"

std::shared_ptr<Material> Material::createMaterial(Shader* shader, const MaterialProperties* properties) {
	if (!shader || !properties) {
		return nullptr;
	}
	std::shared_ptr<Material> newMaterial = std::make_shared<Material>();
	newMaterial->shader = shader;
	newMaterial->properties = *properties;
	return newMaterial;
}