#include "Tema.h"

Tema::Tema()
{
}

Tema::~Tema()
{
}

void Tema::Init()
{
	this->gameCtrl = new GameController();
	this->gameCtrl->LoadGameMehses();
	this->gameCtrl->LoadGameShaders();
	this->gameCtrl->LoadGameTextures();
	this->gameCtrl->GenerateSceneObjects();
	this->isFirstFrame = true;
}

void Tema::FrameStart()
{
	// Clear screen
	glClearColor(1.0f, 0.6f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Get resolution
	glm::ivec2 resolution = window->GetResolution();

	// Set screen area
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema::Update(float deltaTimeSeconds)
{
	glLineWidth(2);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	this->gameCtrl->CheckGameOver();
	this->gameCtrl->UpdateThetaAngle();
	this->gameCtrl->CheckPlaneCollision();
	this->gameCtrl->UpdatePlanePosAndRot(deltaTimeSeconds);
	this->gameCtrl->UpdateCameraPosAndRot();
	this->gameCtrl->UpdateSeaTransform();
	this->gameCtrl->UpdateBombRotate();
	this->gameCtrl->RenderScene();
	this->gameCtrl->ResetNecessaryVars();

	this->isFirstFrame = false;
}

void Tema::FrameEnd()
{
	gameCtrl->FrameEnd();
}

void Tema::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_F)
	{
		if (gameCtrl->GetFirstPerson() == true)
		{
			gameCtrl->SetFirstPerson(false);
		}
		else
			gameCtrl->SetFirstPerson(true);

	}
}

void Tema::OnKeyRelease(int key, int mods)
{
}

void Tema::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (!this->isFirstFrame)
		gameCtrl->PlaneOffsetUpward((float)mouseY);
}

void Tema::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema::OnWindowResize(int width, int height)
{
}
