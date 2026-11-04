#pragma once

#include <string>
#include <memory>
#include "scene.h"
#include "../engine_context.h"


#define SCENE_VERSION 1

EngineContext* engineContext;

std::unique_ptr<Scene> loadScene(std::string const& path);

void setEngineContext(EngineContext* context);

bool versionValidation(float fileVersion);

