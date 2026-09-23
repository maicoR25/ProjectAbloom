#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "scene_object.h"

/**
 * @brief Container that manages scene object lifetimes and batch rendering.
 *
 * Groups objects by their associated Shader to minimize GPU state changes.
 */
class Scene {
public:

	/**
	 * @brief Adds an object to the scene and assigns its render shader.
	 *
	 * Takes unique ownership of the object and registers a non-owning
	 * reference in the internal render batch.
	 *
	 * @param object Unique pointer transferring ownership of the SceneObject.
	 * @param shader Raw pointer to the shader used to render this object.
	 */
	void addObject(std::unique_ptr<SceneObject> object, Shader* shader);


	/**
	 * @brief Renders all objects in the scene grouped by shader.
	 */
	void drawScene();

	/**
	 * @brief Provides read-only access to all scene objects.
	 *
	 * @return A const reference to the vector containing all owning pointers.
	 */
	const std::vector<std::unique_ptr<SceneObject>>& getObjects();
	/**
	 * @brief Searches the scene for an object matching the specified ID.
	 *
	 * @param objectID The unique identifier of the target object.
	 * @return SceneObject* Non-owning pointer to the matching object, or nullptr if not found.
	 */
	SceneObject* getObjectByID(unsigned int objectID);
private:
	std::unordered_map<Shader*, std::vector<SceneObject*>> renderBatches;
	std::vector<std::unique_ptr<SceneObject>> sceneObjects;
};