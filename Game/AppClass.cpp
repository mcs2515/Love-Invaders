#include "AppClass.h"

GameManager* GameManager::instance = nullptr;

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Love Invaders"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	m_pSystem->SetWindowResolution(RESOLUTIONS::C_1280x720_16x9_HD);
	//m_pSystem->SetWindowFullscreen(); //Sets the window to be fullscreen
	//m_pSystem->SetWindowBorderless(true); //Sets the window to not have borders

}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	//m_pCameraMngr->SetPositionTargetAndView(
	//	vector3(0.0f, 2.5f, 15.0f),//Camera position
	//	vector3(0.0f, 2.5f, 0.0f),//What Im looking at
	//	REAXISY);//What is up

	//default lighting
	//m_pLightMngr->SetPosition(glm::vec3(0, 0, 10), 1);
	//m_pLightMngr->SetIntensity(5.00f, 1);
	//m_pLightMngr->SetColor(glm::vec3(1, 1, 1), 1);
	//m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 0.0f));
	m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 20.0f));

	//camera position, looking at, camera orientation
	m_pCameraMngr->SetPositionTargetAndView(glm::vec3(-25.0f, 25.0f, 32.0f), glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Load a model onto the Mesh manager
	gm = GameManager::GetInstance(m_pMeshMngr);
	gm->NewGame();
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	m_pMeshMngr->PrintLine("");
	gm->Update();

	/* OLD:
	m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);
	*/
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	//m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}