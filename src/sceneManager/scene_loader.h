#include <string>
#include "scene.h"


#define SCENE_VERSION 0.1

/*
* Loads a scene into memory from a json
*/
Scene loadScene(std::string const& path);

bool versionValidation(float fileVersion);
