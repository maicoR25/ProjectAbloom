#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <format>
#include <memory>

#include "engine_context.h"
#include "headers/renderer.h"
#include "headers/shader.h"
#include "headers/camera.h"
#include "headers/model.h"
#include "sceneManager/scene_manager.h"
#include "sceneManager/scene.h"
#include "assetManager/asset_manager.h"
#include "gui/gui_manager.h"
#include "gui/panels/inspector_panel.h"
#include "gui/panels/hierarchy_panel.h"

const int INITIAL_WINDOW_WIDTH = 800;
const int INITIAL_WINDOW_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callBack(GLFWwindow* window, double xpos, double ypos);
void scroll_callBack(GLFWwindow* window, double xOffSet, double yOffSet);
void key_callBack(GLFWwindow* window, int key, int scanCode, int action, int mods);

int windowWidth = INITIAL_WINDOW_WIDTH;
int windowHeight = INITIAL_WINDOW_HEIGHT;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX;
float lastY;
float fov = 45;
bool firstMouse = true;
bool cameraMovementEnabled = true;
Camera camera;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "ProjectAbloom", NULL, NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callBack);
	glfwSetScrollCallback(window, scroll_callBack);
	glfwSetKeyCallback(window, key_callBack);

	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Setup stbi flags
	stbi_set_flip_vertically_on_load(true);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	
	// Initialize engine
	Renderer renderer;
	AssetManager assetManager;
	SceneManager sceneManager;

	EngineContext engineContext(&renderer, &assetManager, &sceneManager);

	renderer.initRenderer(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
	unsigned int cameraUBO = renderer.createCameraUBO();
	std::unique_ptr<Scene> currentScene = sceneManager.loadSceneFromFile("assets/scenes/example_scene1.json");

	// Initialize Editor tools
	GUIManager guiManager(window);
	guiManager.SetEngine(&engineContext);
	guiManager.AddPanel(std::make_unique<InspectorPanel>());
	guiManager.AddPanel(std::make_unique<HierarchyPanel>());
	

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		processInput(window);

		//guiManager.CreateNewFrame();
		renderer.clearFrame(glm::vec4(0.0f));
		
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		//std::cout << std::string("FPS: ") << 1 / deltaTime << std::endl;

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(fov), ((float)windowWidth / windowHeight), 0.1f, 100.0f);

		CameraData cameraData(projection, view, camera.Position);
		renderer.bindCameraUBOData(cameraUBO, cameraData);

		//cubeShader.use();
		//cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		//cubeShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		//cubeShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
		//cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		//cubeShader.setVec3("light.position", 1.0f, 2.0f, 1.0f);

		//scene.drawScene();

		//guiManager.DrawGUI();

		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processInput(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processInput(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processInput(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processInput(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.processInput(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.processInput(DOWN, deltaTime);
}

void mouse_callBack(GLFWwindow* window, double xpos, double ypos) {
	if (!cameraMovementEnabled) {
		return;
	}
	std::cout << xpos << ", " << ypos << std::endl;
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.processMouseInput(xOffset, yOffset);
}

void scroll_callBack(GLFWwindow* window, double xOffSet, double yOffSet) {
	fov -= (float)yOffSet;
	if (fov < 1.0f) {
		fov = 1.0f;
	} 
	if (fov > 45.0f) {
		fov = 45.0f;
	}
}

void key_callBack(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if (key == GLFW_KEY_LEFT_ALT) {
		if (action == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			if (cameraMovementEnabled == true) {
				glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
				cameraMovementEnabled = false;
			}
			firstMouse = true;
		}
		else if (action == GLFW_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
			cameraMovementEnabled = true;
		}
	}
}
