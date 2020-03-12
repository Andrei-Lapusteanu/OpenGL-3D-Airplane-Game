#include <Core/Engine.h>
#include "Transform3D.h"
#include "Extensions.h"
#define PI 3.15159
class CloudCube {

	public:

		CloudCube() { }

		CloudCube GenerateCloudCube(glm::vec3 cloudPos, float theta)
		{
			// Translate H and V
			this->translateHoriz = Extensions::RandFloatRange(-1.0f, 1.0f);
			this->translateVert = Extensions::RandFloatRange(-1.0f, 1.0f);
			this->cubePos = glm::vec3(
				cloudPos.x + translateHoriz,
				cloudPos.y + translateVert,
				cloudPos.z
			);

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

		void ApplyTransformations()
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

		glm::vec3 GetCubePos()
		{
			return this->cubePos;
		}

		glm::vec3 GetCubeScale()
		{
			return glm::vec3(scale);
		}

		glm::mat4 GetCubeModelMatrix()
		{
			return this->cubeModelMatrix;
		}

		~CloudCube() { }
	
	private:
		float minTranslateHoriz = -2.0f;
		float maxTranslateHoriz = -2.0f;
		float minTranslateVert  = -2.0f;
		float maxTranslateVert =  -2.0f;
		float minScale = 0.8f;
		float maxScale = 1.5f;
	
		glm::vec3 cubePos;
		glm::vec3 rotate = glm::vec3(0);
		float translateHoriz;
		float translateVert;
		float scale;
		glm::mat4 cubeModelMatrix = glm::mat4(1);
};