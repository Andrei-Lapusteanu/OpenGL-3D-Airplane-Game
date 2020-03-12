#include "GameController.h"
#include "Object2D.h"

GameController::GameController()
{
	// General
	this->thetaAngle = 0.0f;
	this->seaSphereRadius = 40.0f;
	this->planeMouseSensY = 0.01f;
	this->lives = 5;

	// Props
	this->cloudCount = 30;
	this->bombCount = 40;

	// Sea
	seaModelMatrix = glm::mat4(1);

	// Plane
	this->planeHoverDist = 4.0f;
	this->planePathRadius = this->seaSphereRadius + this->planeHoverDist;
	this->defaultPlanePathRadius = this->planePathRadius;
	this->targetPlanePathRadius = this->planePathRadius;
	this->planeAngularSpeed = 5.0f;
	this->planeSpeedVert = 3.0f;
	this->planePropelerRotSpeed = 30.0f;
	this->planePos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->planeModelMatrix = glm::mat4(1);
	this->planePropelerModelMatrix = glm::mat4(1);

	// Collision
	this->pushBackTheta = PI;
	this->pushBackThetaGrowthRate = 0.1f;
	this->explosionPushForce = 8.0f;
	this->hasJustExploded = false;

	// Camera
	this->cameraPathRadius = this->planePathRadius;
	this->thirdPersonCamDistZ = 12.5f;
	this->cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->thirdPersonCamDistance = this->planePos + glm::vec3(0.0f, 0.0f, this->thirdPersonCamDistZ);
	this->camQuaternion = glm::quat(glm::vec3(0));

	// Light
	this->lightPos = glm::vec3(0);
	this->materialKa = 0.25f;
	this->materialKd = 0.5f;
	this->materialKs = 0.5f;
	this->shininess = 65;

	// UI
	uiModelMat4 = glm::mat4(1);
}

GameController::~GameController()
{

}

void GameController::LoadGameMehses()
{
	// Load plane body mesh (created in Maya)
	Mesh* meshPlaneBody = new Mesh("PlaneBody");
	meshPlaneBody->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "plane_colors.obj", true);
	meshPlaneBody->SetRGBA(glm::vec4(0.0f, 0.8f, 0.2f, 1.0f));
	meshes[meshPlaneBody->GetMeshID()] = meshPlaneBody;

	// Load plane body mesh (created in Maya)
	Mesh* meshPlaneNose = new Mesh("PlaneNose");
	meshPlaneNose->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "plane_nose.obj", true);
	meshPlaneNose->SetRGBA(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes[meshPlaneNose->GetMeshID()] = meshPlaneNose;

	// Load plane body mesh (created in Maya)
	Mesh* meshPropeler = new Mesh("PlanePropeler");
	meshPropeler->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "plane_propeler.obj", true);
	meshPropeler->SetRGBA(glm::vec4(0.3f, 0.2f, 0.2f, 1.0f));
	meshes[meshPropeler->GetMeshID()] = meshPropeler;

	Mesh* meshPilot = new Mesh("PlanePilot");
	meshPilot->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "plane_pilot.obj", true);
	meshPilot->SetRGBA(glm::vec4(0.9f, 0.8f, 0.6f, 1.0f));
	meshes[meshPilot->GetMeshID()] = meshPilot;

	Mesh* meshWindow = new Mesh("PlaneWindow");
	meshWindow->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "plane_window.obj", true);
	meshWindow->SetRGBA(glm::vec4(0.9f, 0.9f, 0.9f, 0.35f));
	meshes[meshWindow->GetMeshID()] = meshWindow;

	Mesh* meshWheels = new Mesh("PlaneWheels");
	meshWheels->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "plane_wheels.obj", true);
	meshWheels->SetRGBA(glm::vec4(0.3f, 0.2f, 0.2f, 1.0f));
	meshes[meshWheels->GetMeshID()] = meshWheels;

	// Load sea (sphere)
	Mesh* meshSea = new Mesh("Sea");
	meshSea->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere_2.obj", true);
	meshSea->SetRGBA(glm::vec4(0.25f, 0.75f, 1.0f, 1.0f));
	meshes[meshSea->GetMeshID()] = meshSea;

	// Load cloud cube mesh
	Mesh* meshCube = new Mesh("CloudCube");
	meshCube->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj", true);
	meshes[meshCube->GetMeshID()] = meshCube;

	// Load bomb mesh
	Mesh* meshBomb = new Mesh("Bomb");
	meshBomb->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "bomb.obj", true);
	meshBomb->SetRGBA(glm::vec4(0.9f, 0.0f, 0.1f, 1.0f));
	meshes[meshBomb->GetMeshID()] = meshBomb;

	// UI square
	//Mesh* meshSquare = new Mesh("Square");

	auto posX = Extensions::MapRange(50.0f, 0.0f, 1280.0f, -1.0f, 1.0f);
	auto posY = Extensions::MapRange(50.0f, 0.0f, 780.0f, 1.0f, -1.0f);
	auto length = Extensions::MapRange(50.0f, 0.0f, 1280.0f, -1.0f, 1.0f);

	//meshSquare = Object_2D::CreateSquare("Square", glm::vec3(posX, posY, -1.0f), length, glm::vec3(1, 0, 0), true);
	//meshSquare->InitFromData(meshSquare->vertices, meshSquare->indices);
	////meshSquare->InitFromData(meshSquare->positions, meshSquare->normals, meshSquare->texCoords, meshSquare->indices);
	//meshSquare->SetRGBA(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	//for (int i = 0; i < meshSquare->vertices.size(); i++)
	//{
	//	if (i == 0)
	//		meshSquare->texCoords.push_back(glm::vec2(0, 0));
	//	else if (i == 1)
	//		meshSquare->texCoords.push_back(glm::vec2(0, 1));
	//	else if (i == 2)
	//		meshSquare->texCoords.push_back(glm::vec2(1, 1));
	//	else
	//		meshSquare->texCoords.push_back(glm::vec2(1, 0));
	//}

	//meshes[meshSquare->GetMeshID()] = meshSquare;

		// Create a simple quad
	{
		std::vector<glm::vec3> vertices
		{
			glm::vec3(posX + length, posY + length, -1.0f),	// Top Right
			glm::vec3(posX + length, posY		  , -1.0f),	// Bottom Right
			glm::vec3(posX,          posY		  , -1.0f),	// Bottom Left
			glm::vec3(posX,          posY + length, -1.0f),	// Top Left
		};

		std::vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		std::vector<glm::vec2> textureCoords
		{
			-glm::vec2(0.0f, 0.0f),
			-glm::vec2(0.0f, 1.0f),
			-glm::vec2(1.0f, 1.0f),
			-glm::vec2(1.0f, 0.0f)
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* mesh = new Mesh("Square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void GameController::LoadGameShaders()
{
	// Load shaders
	Shader* shader = new Shader("MyShader");
	shader->AddShader("Source/Laboratoare/Tema/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	Shader* bombShader = new Shader("BombShader");
	bombShader->AddShader("Source/Laboratoare/Tema/Shaders/Bomb/BombVS.glsl", GL_VERTEX_SHADER);
	bombShader->AddShader("Source/Laboratoare/Tema/Shaders/Bomb/BombGS.glsl", GL_GEOMETRY_SHADER);
	bombShader->AddShader("Source/Laboratoare/Tema/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	bombShader->CreateAndLink();
	shaders[bombShader->GetName()] = bombShader;

	Shader* cloudShader = new Shader("CloudShader");
	cloudShader->AddShader("Source/Laboratoare/Tema/Shaders/Cloud/CloudVS.glsl", GL_VERTEX_SHADER);
	cloudShader->AddShader("Source/Laboratoare/Tema/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	cloudShader->CreateAndLink();
	shaders[cloudShader->GetName()] = cloudShader;

	Shader* seaShader = new Shader("SeaShader");
	seaShader->AddShader("Source/Laboratoare/Tema/Shaders/Sea/SeaVS.glsl", GL_VERTEX_SHADER);
	seaShader->AddShader("Source/Laboratoare/Tema/Shaders/Sea/SeaFS.glsl", GL_FRAGMENT_SHADER);
	seaShader->CreateAndLink();
	shaders[seaShader->GetName()] = seaShader;

	Shader* uiShader = new Shader("UIShader");
	uiShader->AddShader("Source/Laboratoare/Tema/Shaders/UI/UI_VS.glsl", GL_VERTEX_SHADER);
	uiShader->AddShader("Source/Laboratoare/Tema/Shaders/UI/UI_FS.glsl", GL_FRAGMENT_SHADER);
	uiShader->CreateAndLink();
	shaders[uiShader->GetName()] = uiShader;
}

void GameController::LoadGameTextures()
{
	// Load texture for UI
	//TextureManager::LoadTexture(RESOURCE_PATH::TEXTURES, "noise.png");

	const std::string textureLoc = "Source/Laboratoare/Tema/Textures/";

	Texture2D* texture = new Texture2D();
	texture->Load2D((textureLoc + "heart_1.png").c_str(), GL_REPEAT);
	mapTextures["grass"] = texture;
}

void GameController::GenerateSceneObjects()
{
	GenerateClouds();
	GenerateBombs();
}

int cubesCount = 0;
glm::mat4* cloudModelMatrices;

void GameController::GenerateClouds()
{
	for (int i = 0; i < this->cloudCount; i++)
	{
		// Create clodus
		this->clouds.push_back(Cloud(this->seaSphereRadius + 1.0, this->seaSphereRadius + 15.0f).GenerateCloud());

		// Get total number of cubes to be generated
		cubesCount += clouds[i].GetCubes().size();
	}

	// Create model matrices
	cloudModelMatrices = new glm::mat4[cubesCount];

	// Get model matrices for each cloud cube
	int matIdx = 0;
	for (int i = 0; i < clouds.size(); i++)
		for (int j = 0; j < clouds[i].GetCubes().size(); j++)
			cloudModelMatrices[matIdx++] = clouds[i].GetCubes()[j].GetCubeModelMatrix();

	BindCloudBuffers(cloudModelMatrices);
}

void GameController::BindCloudBuffers(glm::mat4* cloudModelMatrices)
{
	// VBO (Vertex Buffer Object)
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, cubesCount * sizeof(glm::mat4), &cloudModelMatrices[0], GL_STATIC_DRAW);

	//glBufferSubData(GL_ARRAY_BUFFER, 0, cubesCount * sizeof(glm::mat4), &cloudModelMatrices[0]);

	for (unsigned int i = 0; i < meshes["CloudCube"]->GetMeshEntries().size(); i++)
	{
		// Bind VAO
		glBindVertexArray(meshes["CloudCube"]->GetBuffers()->VAO);

		// Vertex attribs
		GLsizei vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)vec4Size);
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		// Set when to update the content of a vertex attribute to the next element
		// 0 = update the content of the vertex attribute each iteration of the vertex shader 
		// 1 = update the content of the vertex attribute when we start to render a new instance
		// 2 = every 2 instances...
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
}

void GameController::GenerateBombs()
{
	for (int i = 0; i < this->bombCount; i++)
		bombs.push_back(Bomb(this->defaultPlanePathRadius + 6, this->defaultPlanePathRadius - 2.5f).GenerateBomb());
}

void GameController::UpdateThetaAngle()
{
	// Reset theta angle if larger that maximum
	if (this->thetaAngle > MAX_THETA_ANGLE)
		this->thetaAngle = MIN_THETA_ANGLE;

	// Set theta angle using plane speed
	this->thetaAngle += this->planeAngularSpeed / 1000.0f;
	this->infThetaAngle += this->planeAngularSpeed / 1000.0f;
}

void GameController::CheckPlaneCollision()
{
	for (int i = 0; i < bombs.size(); i++)
		if (glm::distance(this->planePos, bombs[i].GetBombPosition()) < PLANE_COLLISION_DIST)
		{
			if (bombs[i].HasExploded() == false)
			{
				// Decrease lives
				this->lives--;

				// Start explosion timer (used for animation in geometry shader)
				bombs[i].Explode();

				// Push back plane
				this->hasJustExploded = true;

				// Spawn another bomb object
				bombs.push_back(Bomb(this->defaultPlanePathRadius + 6, this->defaultPlanePathRadius - 2.5f).GenerateBomb(this->thetaAngle, 180.0f));
			}
		}

	DestroyBombObject();
}

void GameController::DestroyBombObject()
{
	for (int i = 0; i < bombs.size(); i++)
		if (bombs[i].HasExploded() == true)
		{
			bombs[i].DecreaseExplodeTimer();

			if (bombs[i].GetExplodeTimer() <= 0.0f)
				bombs.erase(bombs.begin() + i);
		}
}

void GameController::PushBackPlaneExplosion()
{
	this->pushBackTheta += this->pushBackThetaGrowthRate;

	// PI <= pushBackTheta <= 2 * PI, because sin() between PI and 2 * PI is 0...-1...0 (negative)
	if (this->pushBackTheta <= 2 * PI)
	{
		this->planePos = glm::vec3(
			(this->planePathRadius * sin(this->thetaAngle + sin(this->pushBackTheta) * this->explosionPushForce / EXPL_FORCE_ATT)),	// X
			(this->planePathRadius * cos(this->thetaAngle + sin(this->pushBackTheta) * this->explosionPushForce / EXPL_FORCE_ATT)),	// Y
			0.0f																													// Z
		);
	}
	else
	{
		this->pushBackTheta = PI;
		this->hasJustExploded = false;
	}
}


void GameController::UpdatePlanePosAndRot(float deltaTimeSeconds, glm::vec3 pos, float theta)
{
	// Update plane position on up/down direction
	if (abs(this->planePathRadius - this->targetPlanePathRadius) > PLANE_DIST_TOLERANCE)
		if (this->planePathRadius < this->targetPlanePathRadius)
			this->planePathRadius += (deltaTimeSeconds * abs(this->planePathRadius - this->targetPlanePathRadius) * this->planeSpeedVert);

		else if (this->planePathRadius > this->targetPlanePathRadius)
			this->planePathRadius -= (deltaTimeSeconds * abs(this->planePathRadius - this->targetPlanePathRadius) * this->planeSpeedVert);

	// Update plane position on circular palth
	this->planePos = glm::vec3(
		this->planePathRadius * sin(this->thetaAngle),
		this->planePathRadius * cos(this->thetaAngle),
		0.0f
	);

	// Update lisght pos (MAKE ANOTHER METHOD)
	this->lightPos = glm::vec3(
		(this->planePathRadius + 10) * sin(this->thetaAngle),
		(this->planePathRadius + 10) * cos(this->thetaAngle),
		20.0f
	);

	// Push back plane if it just hit a bomb
	if (this->hasJustExploded)
		PushBackPlaneExplosion();

	// Apply plane position and rotation
	this->planeModelMatrix *= Transform3D::Translate(this->planePos.x, this->planePos.y, this->planePos.z);
	this->planeModelMatrix *= Transform3D::RotateOZ((this->thetaAngle * -1) + (this->targetPlanePathRadius - this->planePathRadius) / PLANE_PITCH_FACTOR);

	// Apply propeler position (relative to plane) and rotation (relative to self)
	this->planePropelerModelMatrix = this->planeModelMatrix * Transform3D::RotateOX(this->thetaAngle * this->planePropelerRotSpeed);
}

void GameController::UpdateCameraPosAndRot()
{
	float pathDiff = 0.0f;

	if (isFirstPerson == false)
	{
		// Get difference between plane path radius and camera path radius
		if (this->lives > 0)
			pathDiff = this->planePathRadius - this->cameraPathRadius;
		else
			pathDiff = this->defaultPlanePathRadius - this->cameraPathRadius;

		// Update camera position (make camera follow plane, but only slightly)
		this->cameraPos = glm::vec3(
			(this->cameraPathRadius + pathDiff / 3) * sin(this->thetaAngle + PI / 64),
			(this->cameraPathRadius + pathDiff / 3) * cos(this->thetaAngle + PI / 64),
			0.0f
		);

		this->GetSceneCamera()->SetPosition(this->cameraPos + this->thirdPersonCamDistance);

		// Calculate camera rotation
		glm::quat camQuaternion = glm::quat(glm::vec3(0.0f, 0.0f, this->thetaAngle * -1));

		// Apply camera rotation
		this->GetSceneCamera()->SetRotation(camQuaternion);
	}
	else
	{
		// Get difference between plane path radius and camera path radius
		if (this->lives > 0)
			pathDiff = this->planePathRadius - this->cameraPathRadius;
		else
			pathDiff = this->defaultPlanePathRadius - this->cameraPathRadius;

		// Update camera position (make camera follow plane, but only slightly)
		this->cameraPos = glm::vec3(
			this->planePathRadius * sin(this->thetaAngle),
			this->planePathRadius * cos(this->thetaAngle),
			0.0f
		);

		this->GetSceneCamera()->SetPosition(this->cameraPos);

		// Calculate camera rotation
		glm::quat camQuaternion = glm::quat(glm::vec3(-(PI / 2), -(PI / 2), thetaAngle * -1 + (PI / 2)));

		// Apply camera rotation
		this->GetSceneCamera()->SetRotation(camQuaternion);
	}
}

// INEFFICIENT
void GameController::UpdateSeaTransform()
{
	this->seaModelMatrix = glm::mat4(1);
	this->seaModelMatrix *= Transform3D::Translate(0, 0, 0);
	this->seaModelMatrix *= Transform3D::Scale(
		this->seaSphereRadius * 2,
		this->seaSphereRadius * 2,
		this->seaSphereRadius * 2);

	this->seaModelMatrix *= Transform3D::RotateOX(PI / 2);

}

void GameController::UpdateBombRotate()
{
	for (int i = 0; i < this->bombs.size(); i++)
		bombs[i].SetModelMatrixTransform(Transform3D::RotateOY(BOMB_ROT_SPEED));
}

void GameController::CheckGameOver()
{
	if (this->lives <= 0)
		if (this->planePathRadius >= 0)
			this->targetPlanePathRadius -= 0.1f;
}

void GameController::SetUniform(Shader* shader, const GLchar* paramName, int paramVal)
{
	int param = glGetUniformLocation(shader->program, paramName);
	glUniform1i(param, paramVal);
}

void GameController::SetUniform(Shader* shader, const GLchar* paramName, unsigned int paramVal)
{
	int param = glGetUniformLocation(shader->program, paramName);
	glUniform1i(param, paramVal);
}

void GameController::SetUniform(Shader* shader, const GLchar* paramName, float paramVal)
{
	int param = glGetUniformLocation(shader->program, paramName);
	glUniform1f(param, paramVal);
}

void GameController::SetUniform(Shader* shader, const GLchar* paramName, glm::vec3 paramVal)
{
	int param = glGetUniformLocation(shader->program, paramName);
	glUniform3f(param, paramVal.x, paramVal.y, paramVal.z);
}

void GameController::SetUniform(Shader* shader, const GLchar* paramName, bool paramVal)
{
	int param = glGetUniformLocation(shader->program, paramName);
	glUniform1i(param, paramVal);
}

// Render clouds in geom shader!
void GameController::RenderScene()
{
	GetLocalTime(&this->time);

	// Render square
	//GetSceneCamera()->GetViewMatrix();
	//glm::mat4 squareCamSpace = glm::mat4(1);
	//squareCamSpace *= Transform3D::Translate(
	//	(this->cameraPathRadius) * sin(this->thetaAngle + PI / 64),
	//	(this->cameraPathRadius) * cos(this->thetaAngle + PI / 64),
	//	0.0f);

	//RenderUI(meshes["Square"], shaders["UIShader"], squareCamSpace);

	// Render sea (sphere)
	RenderSea(meshes["Sea"], shaders["SeaShader"], this->seaModelMatrix, glm::vec3(0.25f, 0.75f, 1.0f));

	// Render clouds
	RenderClouds(meshes["CloudCube"], shaders["CloudShader"], glm::vec3(0.9, 0.9, 0.9));

	if (isFirstPerson == false)
	{
		// Render plane (body)
		RenderWithShader(meshes["PlaneBody"], shaders["MyShader"], this->planeModelMatrix, glm::vec3(0, 0.8, 0.2));

		// Render nose
		RenderWithShader(meshes["PlaneNose"], shaders["MyShader"], this->planeModelMatrix, glm::vec3(1, 1, 1));

		// Render plane propeler
		RenderWithShader(meshes["PlanePropeler"], shaders["MyShader"], this->planePropelerModelMatrix, glm::vec3(1, 1, 1));

		// Render plane pilot
		RenderWithShader(meshes["PlanePilot"], shaders["MyShader"], this->planeModelMatrix, glm::vec3(1, 1, 1));

		// Render plane window
		RenderWithShader(meshes["PlaneWindow"], shaders["MyShader"], this->planeModelMatrix, glm::vec3(1, 1, 1));

		// Render plane wheels
		RenderWithShader(meshes["PlaneWheels"], shaders["MyShader"], this->planeModelMatrix, glm::vec3(1, 1, 1));
	}
	// Render bombs
	for (int i = 0; i < bombs.size(); i++)
		RenderBombs(meshes["Bomb"], shaders["BombShader"], i);

	// Render UI
	for (int i = 0; i < this->lives; i++)
		RenderUI(meshes["Square"], shaders["UIShader"], i);
}

void GameController::RenderClouds(Mesh* mesh, Shader* shader, const glm::vec3& color)
{
	// Use cloud shader
	glUseProgram(shader->program);

	// Set uniforms
	SetUniform(shader, "object_color", clouds[0].GetCloudMatProps()->GetColor());
	SetUniform(shader, "light_pos", this->lightPos);
	SetUniform(shader, "eye_pos", this->cameraPos);
	SetUniform(shader, "material_ka", clouds[0].GetCloudMatProps()->GetKa());
	SetUniform(shader, "material_kd", clouds[0].GetCloudMatProps()->GetKd());
	SetUniform(shader, "material_ks", clouds[0].GetCloudMatProps()->GetKs());
	SetUniform(shader, "material_shininess", clouds[0].GetCloudMatProps()->GetShininess());
	SetUniform(shader, "alpha", clouds[0].GetCloudMatProps()->GetAlpha());

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));

	// Alter model matrix (rotate)
	for (int i = 0; i < cubesCount; i++)
	{
		if (i % 2 == 0)
		{
			cloudModelMatrices[i] *= Transform3D::RotateOX(CLOUD_CUBE_ROT_SPEED);
			cloudModelMatrices[i] *= Transform3D::Translate(
				sin(this->thetaAngle * 10) / 50.0f,
				0.0f,
				0.0f
			);
		}

		if (i % 3 == 0)
			cloudModelMatrices[i] *= Transform3D::RotateOY(CLOUD_CUBE_ROT_SPEED);
	}

	// Rebind buffers
	glBufferData(GL_ARRAY_BUFFER, cubesCount * sizeof(glm::mat4), &cloudModelMatrices[0], GL_DYNAMIC_DRAW);

	// Draw
	for (unsigned int i = 0; i < mesh->GetMeshEntries().size(); i++)
	{
		glBindVertexArray(mesh->GetBuffers()->VAO);
		glDrawArraysInstanced(GL_QUADS, 0, mesh->indices.size(), cubesCount);
		glBindVertexArray(0);
	}
}

void GameController::RenderSea(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	// Use sea shader
	glUseProgram(shader->program);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Set uniforms
	SetUniform(shader, "object_color", mesh->GetColor());
	SetUniform(shader, "theta", this->infThetaAngle);
	SetUniform(shader, "msTime", this->time.wMilliseconds);
	SetUniform(shader, "extRand", Extensions::RandFloatRange(-PI, PI));
	SetUniform(shader, "light_pos", this->lightPos);
	SetUniform(shader, "eye_pos", this->cameraPos);
	SetUniform(shader, "material_ka", this->materialKa);
	SetUniform(shader, "material_kd", this->materialKd);
	SetUniform(shader, "material_ks", this->materialKs);
	SetUniform(shader, "material_shininess", this->shininess);
	SetUniform(shader, "alpha", 0.75f);

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void GameController::RenderBombs(Mesh* mesh, Shader* shader, int index)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// Use shader
	glUseProgram(shader->program);

	SetUniform(shader, "explode_timer", bombs[index].GetExplodeTimer());
	SetUniform(shader, "has_exploded", bombs[index].HasExploded());
	SetUniform(shader, "object_color", mesh->GetColor());
	SetUniform(shader, "light_pos", this->lightPos);
	SetUniform(shader, "eye_pos", this->cameraPos);
	SetUniform(shader, "material_ka", this->materialKa);
	SetUniform(shader, "material_kd", this->materialKd);
	SetUniform(shader, "material_ks", this->materialKs);
	SetUniform(shader, "material_shininess", this->shininess);
	SetUniform(shader, "alpha", 1.0f);

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(bombs[index].GetModelMatrix()));

	mesh->Render();
}

float xDist = 0.0f;

void GameController::RenderUI(Mesh* mesh, Shader* shader, int idx)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// Use shader
	glUseProgram(shader->program);

	// Set UI model matrises
	this->uiModelMat4 = SetUIModelMatrices();

	// Alter matrices for UI
	this->uiModelMat4 = glm::translate(this->uiModelMat4, glm::vec3(-0.75f + ((float)idx / 6), 0.4f, 0.0f));
	this->uiModelMat4 = glm::scale(this->uiModelMat4, glm::vec3(0.1, 0.1, 1));

	this->GetSceneCamera();
	SetUniform(shader, "object_color", mesh->GetColor());
	SetUniform(shader, "alpha", 1.0f);

	// Bind texrture to shader
	//TextureManager::GetTexture("particle.png")->BindToTextureUnit(GL_TEXTURE0);

	//TODO : activate texture location 0
	glActiveTexture(GL_TEXTURE0);

	//TODO : Bind the texture1 ID
	glBindTexture(GL_TEXTURE_2D, mapTextures["grass"]->GetTextureID());

	//TODO : Send texture uniform value
	glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(this->uiModelMat4));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void GameController::RenderWithShader(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// Use shader
	glUseProgram(shader->program);

	SetUniform(shader, "object_color", mesh->GetColor());
	SetUniform(shader, "light_pos", this->lightPos);
	SetUniform(shader, "eye_pos", this->cameraPos);
	SetUniform(shader, "material_ka", this->materialKa);
	SetUniform(shader, "material_kd", this->materialKd);
	SetUniform(shader, "material_ks", this->materialKs);
	SetUniform(shader, "material_shininess", this->shininess);
	SetUniform(shader, "alpha", mesh->GetAlpha());

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

glm::mat4 GameController::SetUIModelMatrices()
{
	glm::mat3 mm = glm::mat4(1);

	glm::mat4 model = glm::mat4(
		mm[0][0], mm[0][1], mm[0][2], 0.f,
		mm[1][0], mm[1][1], mm[1][2], 0.f,
		0.f, 0.f, mm[2][2], 0.f,
		mm[2][0], mm[2][1], 0.f, 1.f);

	return model;
}

void GameController::ResetNecessaryVars()
{
	// Reset plane's model matrix
	this->planeModelMatrix = glm::mat4(1);
}

void GameController::PlaneOffsetUpward(float deltaY)
{
	glm::ivec2 resolution = window->GetResolution();

	if (this->lives > 0)
		this->targetPlanePathRadius = Extensions::MapRange(deltaY, 0, resolution.y, this->defaultPlanePathRadius + 6, this->defaultPlanePathRadius - 2.5f);
}

void GameController::FrameEnd()
{
	this->DrawCoordinatSystem();
}



void GameController::SetFirstPerson(bool val)
{
	this->isFirstPerson = val;
}

bool GameController::GetFirstPerson()
{
	return this->isFirstPerson;
}
