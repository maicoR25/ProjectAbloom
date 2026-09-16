#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "headers/renderer.h"


void Renderer::initRenderer(int width, int height) {
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::clearFrame(glm::vec4 color) {
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int Renderer::createCameraUBO() {
	unsigned int cameraUBO;
	glGenBuffers(1, &cameraUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);

	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, cameraUBO);

	return cameraUBO;
}

void Renderer::bindCameraUBOData(unsigned int cameraUBO, CameraData cameraData) {
	glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(cameraData.projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(cameraData.view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}