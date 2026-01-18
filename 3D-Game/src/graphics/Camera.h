#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

class Camera
{
private:
	glm::vec3 m_CamPosition, m_CamDirection;
	glm::mat4 m_ViewMatrix;

	float m_lastMouseX, m_lastMouseY;

	const glm::vec3 m_WorldUp;
	bool m_FirstFrame;

	const float m_CameraSpeed = 50.0f;
	const float m_CameraMovementSpeed = 10.0f;

public:
	Camera(const glm::vec3& camPosition, const glm::vec3& camDirection);
	~Camera();

	void Update(int mouseX, int mouseY, double deltaTime);
	// Yes, there are much better ways to do this but this is just a test camera class....
	void MoveForward(double deltaTime);
	void MoveBackward(double deltaTime);
	void MoveLeft(double deltaTime);
	void MoveRight(double deltaTime);

	inline glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
	inline glm::vec3& GetCameraPosition() { return m_CamPosition; }
	inline glm::vec3& GetCameraDirection() { return m_CamDirection; }
};