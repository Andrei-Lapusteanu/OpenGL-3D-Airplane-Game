#include "CloudCube.h"

CloudCube::CloudCube()
{

}

CloudCube CloudCube::GenerateCloudCube(glm::vec3 cloudPos, float theta)
{
	// Translate H and V
	this->translateHoriz = Extensions::RandFloatRange(this->minTranslateHoriz, this->maxTranslateHoriz);
	this->translateVert = Extensions::RandFloatRange(this->minTranslateVert, this->maxTranslateVert);
	this->cubePos = glm::vec3(
		cloudPos.x + (translateHoriz * abs(cos(theta))),
		cloudPos.y + (translateVert * abs(sin(theta))),
		cloudPos.z);

	// Rotate
	this->rotate = glm::vec3(
		Extensions::RandIntRange(0, 360),
		Extensions::RandIntRange(0, 360),
		Extensions::RandIntRange(0, 360)
	);

	// Scale
	this->scale = Extensions::RandFloatRange(this->minScale, this->maxScale);

	ApplyTransformations();

	return *this;
}

void CloudCube::ApplyTransformations()
{
	// Apply translate
	cubeModelMatrix *= Transform3D::Translate(
		this->cubePos.x,
		this->cubePos.y,
		this->cubePos.z);

	// Apply rotate
	cubeModelMatrix *= Transform3D::RotateOX(this->rotate.x);
	cubeModelMatrix *= Transform3D::RotateOY(this->rotate.y);
	cubeModelMatrix *= Transform3D::RotateOZ(this->rotate.z);

	// Apply scale
	cubeModelMatrix *= Transform3D::Scale(this->scale, this->scale, this->scale);
}

glm::vec3 CloudCube::GetCubePos()
{
	return this->cubePos;
}

glm::vec3 CloudCube::GetCubeScale()
{
	return glm::vec3(scale);
}

glm::mat4 CloudCube::GetCubeModelMatrix()
{
	return this->cubeModelMatrix;
}

CloudCube::~CloudCube()
{
}
