#include <Core/Engine.h>
#include <iostream>
#include "Transform3D.h"
#include "Extensions.h"

#define PI 3.14159f
#define MAX_EXPLODE_TIMER PI / 2

class Bomb
{
public:
	Bomb() { }

	Bomb(float minHeight, float maxHeight)
	{
		this->minHeight = minHeight;
		this->maxHeight = maxHeight;
	}

	Bomb GenerateBomb(float planeTheta = 0.0f, float thetaOffset = 0.0f)
	{
		// Bomb height
		this->height = Extensions::RandFloatRange(this->minHeight, this->maxHeight);

		// Angle
		if (thetaOffset != 0.0f)
			// If a bomb was exploded, spawn another one at an angle out of view
			this->theta = planeTheta + thetaOffset;
		else
			// Init bomb spawning
			this->theta = Extensions::RandFloatRange(0.0f, 360.0f);

		// Bomb position
		this->bombPos = glm::vec3(
			this->height * sin(this->theta),
			this->height * cos(this->theta),
			zPos
		);

		ApplyTransformations();

		return *this;
	}

	void ApplyTransformations()
	{
		this->modelMatrix *= Transform3D::Translate(this->bombPos.x, this->bombPos.y, this->bombPos.z);
		this->modelMatrix *= Transform3D::RotateOZ(this->theta * -1);
		this->modelMatrix *= Transform3D::Scale(this->scale, this->scale, this->scale);
	}

	void Explode()
	{
		this->hasExploded = true;
	}

	void DecreaseExplodeTimer()
	{
		this->explodeTimer -= this->explodeDecreaseRate;
	}

	float GetExplodeTimer()
	{
		return this->explodeTimer;
	}

	bool HasExploded()
	{
		return this->hasExploded;
	}

	glm::vec3 GetBombPosition()
	{
		return this->bombPos;
	}

	glm::mat4 GetModelMatrix()
	{
		return this->modelMatrix;
	}

	void SetModelMatrixTransform(glm::mat4 matrix)
	{
		this->modelMatrix *= matrix;
	}

	glm::float32 GetRadius()
	{
		return this->scale / 2.0f;
	}

	~Bomb() { }

private:
	float minHeight;
	float maxHeight;

	float height;
	float theta;
	float zPos = 0.0f;
	float scale = 1.0f;
	glm::vec3 bombPos;
	glm::mat4 modelMatrix = glm::mat4(1);
	float explodeTimer = 1.0f;
	float explodeDecreaseRate = 0.03f;
	bool hasExploded = false;
};