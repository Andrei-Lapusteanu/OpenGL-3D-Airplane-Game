#pragma once

#include <Core/Engine.h>

class MaterialProperties
{
	public:
		MaterialProperties() { }

		MaterialProperties(glm::vec3 color, float ka, float kd, float ks, float shin, float alpha)
		{
			this->materialColor = color;
			this->materialKa = ka;
			this->materialKd = kd;
			this->materialKs = ks;
			this->shininess = shin;
			this->alpha = alpha;
		}

		glm::vec3 GetColor() {
			return this->materialColor;
		}

		float GetKa() {
			return this->materialKa;
		}

		float GetKd() {
			return this->materialKd;
		}

		float GetKs() {
			return this->materialKs;
		}

		unsigned int GetShininess() {
			return this->shininess;
		}

		float GetAlpha() {
			return this->alpha;
		}

		~MaterialProperties() { }


	private:
		glm::vec3 materialColor;
		float materialKa;
		float materialKd;
		float materialKs;
		unsigned int shininess;
		float alpha;
};
