#include <string>
#include "scene.h"
#include "scene_loader.h"

class SceneManager {
public:
	Scene loadSceneFromFile(std::string const& path);
};