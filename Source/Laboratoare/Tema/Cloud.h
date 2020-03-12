#include <Core/Engine.h>
#include "Transform3D.h"
#include "Extensions.h"
#include "CloudCube.h"
#include "MaterialProperties.h"

#define PI 3.14159f

class Cloud
{
public:

	Cloud() { }

	Cloud(float minHeight, float maxHeight)
	{
		this->minHeight = minHeight;
		this->maxHeight = maxHeight;
		
		this->materialProps = new MaterialProperties(glm::vec3(1, 1, 1), 0.5f, 0.5f, 0.0f, 1.0f, 0.75f);
	}

	Cloud GenerateCloud()
	{
		// Cloud height
		this->height = Extensions::RandFloatRange(this->minHeight, this->maxHeight);

		// Angle
		this->theta = Extensions::RandFloatRange(0.0f, 2 * PI);

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

		// Apply rotate to cloud object
		//ApplyTransformations();

		// Generate cubes
		for (int i = 0; i < cubeCount; i++)
			this->cubes.push_back(CloudCube().GenerateCloudCube(this->cloudPos, this->theta));

		return *this;
	}

	void ApplyTransformations()
	{
		this->modelMatrix *= Transform3D::Translate(
			this->cloudPos.x,
			this->cloudPos.y,
			this->cloudPos.z
		);

		this->modelMatrix *= Transform3D::RotateOZ(this->theta);
		std::cout << theta << std::endl;
	}

	std::vector<CloudCube> GetCubes()
	{
		return this->cubes;
	}

	float GetCloudTheta()
	{
		return this->theta;
	}

	float GetCloudHeight()
	{
		return this->height;
	}

	glm::mat4 GetCloudModelMatrix()
	{
		return this->modelMatrix;
	}

	MaterialProperties* GetCloudMatProps()
	{
		return this->materialProps;
	}

	~Cloud() { }

private:
	float minHeight;
	float maxHeight;
	int minCubes = 5;
	int maxCubes = 8;
	int minPosZ = -15.0f;
	int maxPosZ = 15.0f;

	int cubeCount;
	float height;
	float theta;
	float zPos;
	glm::vec3 cloudPos;
	std::vector<CloudCube> cubes;
	MaterialProperties* materialProps;

	glm::mat4 modelMatrix = glm::mat4(1);
};