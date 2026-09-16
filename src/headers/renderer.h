#pragma once

#include <glm/glm.hpp>
	
struct CameraData {
	glm::mat4 projection;
	glm::mat4 view;
};

class Renderer {
public:
	void initRenderer(int width, int height);

	//void createUBO();

	unsigned int createCameraUBO();

	void bindCameraUBOData(unsigned int cameraUBO, CameraData cameraData);

	void clearFrame(glm::vec4 color);
private:
};