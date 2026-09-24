#pragma once

#include <string>
#include <memory>
#include "scene.h"


#define SCENE_VERSION 1

/*
* Loads a scene into memory from a json
*/
std::unique_ptr<Scene> loadScene(std::string const& path);

bool versionValidation(float fileVersion);
