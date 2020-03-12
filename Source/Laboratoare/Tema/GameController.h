# pragma once
#include <Core/Engine.h>
#include <Component/SimpleScene.h>
#include <iostream>
#include <limits>
#include "Transform2D.h"
#include "Transform3D.h"
#include "Cloud.h"
#include "Bomb.h"

#define PI 3.14159f
#define MIN_THETA_ANGLE 0
#define MAX_THETA_ANGLE 2*PI
#define PLANE_DIST_TOLERANCE 0.1f
#define PLANE_PITCH_FACTOR 7.0f
#define PLANE_COLLISION_DIST 1.2f
#define EXPL_FORCE_ATT 100.0f
constexpr auto BOMB_ROT_SPEED = 0.05f;
constexpr auto CLOUD_CUBE_ROT_SPEED = 0.015f;

class GameController : public SimpleScene
{
	public:
		// Ctor and Dtor
		GameController();
		~GameController();

		// Methods
		// Inits
		void LoadGameMehses();
		void LoadGameShaders();
		void LoadGameTextures();
		void GenerateSceneObjects();
		void GenerateClouds();
		void BindCloudBuffers(glm::mat4* cloudModelMatrices);
		void GenerateBombs();

		// Updates
		void UpdateThetaAngle();
		void CheckPlaneCollision();
		void DestroyBombObject();
		void PushBackPlaneExplosion();
		void UpdatePlanePosAndRot(float deltaTimeSeconds, glm::vec3 pos = glm::vec3(0), float theta = 0.0f);
		void UpdateCameraPosAndRot();
		void UpdateSeaTransform();
		void UpdateBombRotate();
		void CheckGameOver();

		// Set shader uniforms
		void SetUniform(Shader* shader, const GLchar* paramName, int paramVal);
		void SetUniform(Shader* shader, const GLchar* paramName, unsigned int paramVal);
		void SetUniform(Shader* shader, const GLchar* paramName, float paramVal);
		void SetUniform(Shader* shader, const GLchar* paramName, glm::vec3 paramVal);
		void SetUniform(Shader* shader, const GLchar* paramName, bool paramVal);

		// Renders
		void RenderScene();
		void RenderClouds(Mesh* mesh, Shader* shader, const glm::vec3& color);
		void RenderSea(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
		void RenderBombs(Mesh* mesh, Shader* shader, int index);
		void RenderUI(Mesh* mesh, Shader* shader, int idx);
		void RenderWithShader(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
		
		// Other
		glm::mat4 SetUIModelMatrices();
		void ResetNecessaryVars();
		void PlaneOffsetUpward(float mouseY);
		void FrameEnd() override;

		void SetFirstPerson(bool val);
		bool GetFirstPerson();

	private:
		// General
		float thetaAngle;
		float infThetaAngle;
		float seaSphereRadius;
		float planeMouseSensY;
		int lives;
		SYSTEMTIME time;

		// Props
		int cloudCount;
		int bombCount;
		std::vector<Cloud> clouds;

		// Sea
		glm::mat4 seaModelMatrix;

		//Plane
		float planeHoverDist;
		float planePathRadius;
		float defaultPlanePathRadius;
		float targetPlanePathRadius;
		float planeAngularSpeed;
		float planeSpeedVert;
		float planePropelerRotSpeed;
		glm::vec3 planePos;
		glm::mat4 planeModelMatrix;
		glm::mat4 planePropelerModelMatrix;

		// Collision
		float pushBackTheta;
		float pushBackThetaGrowthRate;
		float explosionPushForce;
		bool hasJustExploded;

		// Bombs
		std::vector<Bomb> bombs;

		// Camera
		float cameraPathRadius;
		float thirdPersonCamDistZ;
		glm::vec3 cameraPos;
		glm::vec3 thirdPersonCamDistance;
		glm::quat camQuaternion;

		// Light
		glm::vec3 lightPos;
		float materialKa;
		float materialKd;
		float materialKs;
		unsigned int shininess;

		// UI
		glm::mat4 uiModelMat4;
		std::unordered_map<std::string, Texture2D*> mapTextures;

		bool isFirstPerson;
};