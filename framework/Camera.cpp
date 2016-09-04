#include "Camera.h"


Camera::Camera() :
_front(glm::vec3(0, 0, 1)),
_up(glm::vec3(0, 1, 0)),
_right(glm::vec3(0, 0, 0)),
_worldUp(glm::vec3(0, 1, 0)),
_position(glm::vec3(0, 0, 0)),
_rotation(glm::vec3(0, 0, 0)),
_near(.2f),
_far(1000.f),
_fov(45.f),
_viewDistance(1000.f),
_fogDistance(1200.f),
_fogColor(glm::vec3(0, 0, 0)),
_projection(ProjectionType::Perspective),
_view(glm::mat4(0.f)),
_skyboxView(glm::mat4(0.f)),
_projectionMatrix(glm::mat4(0.f)),
_skyboxProjectionMatrix(glm::mat4(0.f)),
_noRegister(false)
{
	UpdateView();
	UpdateProjection();
	//CameraManager::AddCamera(this);
}

void Camera::Ortho(float left, float right, float top, float bottom, float zNear, float zFar)
{
	_projectionMatrix = glm::ortho(left, right, top, bottom, zNear, zFar);
}

void Camera::LookAt(vec3 eye, vec3 center, vec3 up)
{
	_view = glm::lookAt(eye, center, up);
}

void Camera::UpdateProjection()
{
	// 		if (_projection == ProjectionType::Perspective)
	// 		{
	// 			_projectionMatrix = glm::perspective(_fov, (float)DeferredBuffer::GetWidth() / (float)DeferredBuffer::GetHeight(), _near, _far);
	// 			_skyboxProjectionMatrix = glm::perspective(_fov, (float)DeferredBuffer::GetWidth() / (float)DeferredBuffer::GetHeight(), _near, 10000.f);
	// 		}
	// 		else{
	// 			_projectionMatrix = glm::ortho(0.f, (float)DeferredBuffer::GetWidth(), (float)DeferredBuffer::GetHeight(), 0.f, _near, _far);
	// 
	// 		}
}

void Camera::UpdateView()
{
	vec3 front;

	front.x = glm::cos(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
	front.y = glm::sin(glm::radians(_rotation.x));
	front.z = glm::sin(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));

	_front = normalize(front);
	_right = normalize(cross(_front, _worldUp));
	_up = normalize(cross(_right, _front));

	_view = glm::lookAt(_position, _position + _front, _up);
	_skyboxView = glm::mat4(glm::mat3(_view));
}

