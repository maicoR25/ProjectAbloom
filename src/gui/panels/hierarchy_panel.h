#pragma once


#include <vector>
#include <memory>
#include <string>
#include "../gui_panel.h"
#include "../../sceneManager/scene.h"
#include "../../editor_context.h"

class Scene;
class SceneObject;
class InspectorPanel;

class HierarchyPanel : public GUIPanel {
public:
	void draw(Scene* scene, EditorContext& context) override {
		ImGui::Begin("Hierarchy Panel");
		for (const auto& obj : scene->getObjects()) {
			if (ImGui::Button(obj->name.c_str())) {
				context.selectedObjectID = obj->id;
				ImGui::Text("Im a button! ID: %f", obj->id);
			}
		}
		ImGui::End();
	}
};