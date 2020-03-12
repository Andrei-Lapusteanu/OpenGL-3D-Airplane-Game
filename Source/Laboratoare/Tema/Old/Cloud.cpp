#include "Cloud.h"

Cloud::Cloud()
{
}

Cloud::Cloud(float minHeight, float maxHeight)
{
	this->minHeight = minHeight;
	this->maxHeight = maxHeight;
}

Cloud Cloud::GenerateCloud()
{
	// Cloud height
	this->height = Extensions::RandFloatRange(this->minHeight, this->maxHeight);

	// Angle
	this->theta = Extensions::RandFloatRange(0.0f, 360.0f);

	// Z postion
	this->zPos = Extensions::RandIntRange(this->minPosZ, this->maxPosZ);

	// Cloud position
	this->cloudPos = glm::vec3(
		this->height * sin(this->theta),
		this->height * cos(this->theta),
		zPos
	);

	// Cloud cube count
	this->cubeCount = Extensions::RandIntRange(this->minCubes, this->maxCubes);

	// Generate cubes
	for (int i = 0; i < cubeCount; i++)
		this->cubes.push_back(CloudCube().GenerateCloudCube(this->cloudPos, this->theta));

	// Apply rotate to cloud object
	ApplyTransformations();

	return *this;
}

void Cloud::ApplyTransformations()
{
	this->modelMatrix *= Transform3D::RotateOZ(this->theta * -1);
}

std::vector<CloudCube> Cloud::GetCubes()
{
	return this->cubes;
}

float Cloud::GetCloudTheta()
{
	return this->theta;
}

glm::mat4 Cloud::GetCloudModelMatrix()
{
	return this->modelMatrix;
}

Cloud::~Cloud()
{
}
