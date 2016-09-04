#pragma once
#include "Util.h"
using namespace glm;
enum class ProjectionType : unsigned short
{
	Perspective = 0,
	Ortographic = 1
};
class Camera
{
public:
	Camera();
	virtual ~Camera();

	glm::vec3 &GetFogColor() { return _fogColor; }
	glm::vec3 &GetForward() { return _front; }
	glm::vec3 &GetRight() { return _right; }
	glm::vec3 &GetPosition() { return _position; }
	glm::vec3 &GetRotation() { return _rotation; }
	glm::mat4 &GetView() { return _drawSkybox ? _skyboxView : _view; }
	glm::mat4 &GetProjectionMatrix() { return _drawSkybox ? _skyboxProjectionMatrix : _projectionMatrix; }
	float GetNear() { return _near; }
	float GetFar() { return _far; }
	float GetFOV() { return _fov; }
	float GetViewDistance() { return _viewDistance; }
	float GetFogDistance() { return _fogDistance; }
	ProjectionType GetProjection() { return _projection; }

	void SetPosition(glm::vec3 &position, bool update = true) { _position = position; if (update) UpdateView(); }
	void SetRotation(glm::vec3 &rotation, bool update = true) { _rotation = rotation; if (update) UpdateView(); }
	void SetNear(float Near) { _near = Near; }
	void SetFar(float Far) { _far = Far; }
	void SetFOV(float fov) { _fov = fov; }
	void SetFogColor(glm::vec3 &color) { _fogColor = color; }
	void SetViewDistance(float distance) { _viewDistance = distance; }
	void SetFogDistance(float distance) { _fogDistance = distance; }
	void SetProjection(ProjectionType projection) { _projection = projection; }

	void EnableSkybox(bool enable) { _drawSkybox = enable; }

	void Ortho(float left, float right, float top, float bottom, float zNear, float zFar);
	void LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	void UpdateProjection();
	void UpdateView();

	void MoveForward(float distance) { _position += _front * distance; }
	void MoveRight(float distance) { _position += _right * distance; }
	void MoveUp(float distance) { _position += _up * distance; }

	void RotateX(float angle) { _rotation.x += angle; }
	void RotateY(float angle) { _rotation.y += angle; }
	void RotateZ(float angle) { _rotation.z += angle; }
private:
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	glm::vec3 _position;
	glm::vec3 _rotation;

	float _near;
	float _far;
	float _fov;

	float _viewDistance;
	float _fogDistance;
	glm::vec3 _fogColor;

	ProjectionType _projection;

	glm::mat4 _view, _skyboxView;
	glm::mat4 _projectionMatrix, _skyboxProjectionMatrix;
	bool _noRegister, _drawSkybox;
};
