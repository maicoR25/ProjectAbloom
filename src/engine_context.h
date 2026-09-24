#pragma once

class Renderer;
class AssetManager;
class SceneManager;

struct EngineContext {
	Renderer* renderer;
	AssetManager* assetManager;
	SceneManager* sceneManager;
};
