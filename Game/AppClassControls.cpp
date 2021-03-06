#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON_KEY_PRESS_RELEASE
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
		bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
		bLastEscape = false, bLastF = false, bLastSpace = false, bLastO = false, bLastI = false, bLastP = false, bLastReturn = false, bLastC = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	/*if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		gm->ResetPlayer();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		m_pCameraMngr->SetPositionTargetAndView(glm::vec3(-25.0f, 25.0f, 32.0f), glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		m_pCameraMngr->SetPositionTargetAndView(glm::vec3(0.0f, 15.0f, 32.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
	{
		m_pCameraMngr->SetPositionTargetAndView(glm::vec3(25.0f, 25.0f, 32.0f), glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

#pragma endregion

#pragma region Player Movement
	//Use first set of params for standard movement, second set for psuedo-iso movement
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//	gm->MovePlayer(-1, 1); //(-1, 0) (-1, 1)
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//	gm->MovePlayer(1, -1); //(1, 0) (1, -1)
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//	gm->MovePlayer(-1, -1); //(0, -1) (-1, -1)
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//	gm->MovePlayer(1, 1); //(0, 1) (1, 1)

	if (!(gm->GetGameState() == PAUSE || gm->GetGameState() == NEXT_ROUND || gm->GetGameState() == RESTART_ROUND || gm->GetGameState() == TITLE))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			gm->MovePlayer(-1, 0); //(-1, 0) (-1, 1)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			gm->MovePlayer(1, 0); //(1, 0) (1, -1)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			gm->MovePlayer(0, -1); //(0, -1) (-1, -1)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			gm->MovePlayer(0, 1); //(0, 1) (1, 1)
	}

#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	//ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	//ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	//ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	//ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll));

	if (!(gm->GetGameState() == PAUSE || gm->GetGameState() == NEXT_ROUND || gm->GetGameState() == RESTART_ROUND || gm->GetGameState() == TITLE))
	{
		//detect that the spacebar has been released first before firing
		static bool willShoot = false;
		ON_KEY_PRESS_RELEASE(Space, NULL, willShoot = true);

		if (willShoot) {
			gm->FireBullet();
			willShoot = false;
		}
	}

	// Detect whether Octree has been enabled or not
	static bool makeOctree = false;
	ON_KEY_PRESS_RELEASE(O, NULL, makeOctree = true);
	if (makeOctree) {
		gm->octree.SetSOCheck(!gm->octree.GetSOCheck());	// Set the octree's check to the opposite of what it was
		gm->octree.SetOctreeVis(gm->octree.GetSOCheck());	// Set the octree's visibility to whether it's checking
		makeOctree = false;
	}

	// Reset the Octree if it has been enabled
	static bool resetOctree = false;
	ON_KEY_PRESS_RELEASE(I, NULL, resetOctree = true);
	if (resetOctree) {
		if (gm->octree.GetSOCheck()) {
			gm->ResetOctree();
		}
		resetOctree = false;
	}
	static bool pPressed = false;
	static bool returnPressed = false;
	static bool cPressed = false;
	ON_KEY_PRESS_RELEASE(P, NULL, pPressed = true);
	ON_KEY_PRESS_RELEASE(C, NULL, cPressed = true);
	ON_KEY_PRESS_RELEASE(Return, NULL, returnPressed = true);


	if (cPressed) {
		switch (gm->GetGameState()) {
		case TITLE:
			//if 'P' go to Game_Play
			gm->SetGameState(CREDITS);
			cPressed = false;
			break;
		}
	}

	if (returnPressed) {
		switch (gm->GetGameState()) {
		case CREDITS:
			//if 'esc' return to Title
			gm->SetGameState(TITLE);
			returnPressed = false;
			break;

		case PAUSE:
			//if 'esc' return to Title
			gm->SetGameState(TITLE);
			returnPressed = false;
			break;

		case GAME_OVER:
			//if 'esc' return to Title
			gm->SetGameState(TITLE);
			returnPressed = false;
			break;
		}
	}

	if (pPressed) {
		switch (gm->GetGameState()) {
			case TITLE:
				//if 'P' go to Game_Play
				gm->SetGameState(GAME_PLAY);
				gm-> NewGame();
				pPressed = false;
				break;

			case PAUSE:
				//if 'p' return to Game_Play
				gm->SetGameState(GAME_PLAY);
				pPressed = false;
				break;

			case GAME_PLAY:
				//if 'p' pause game
				gm->SetGameState(PAUSE);
				pPressed = false;
				break;

			case NEXT_ROUND:
				//if 'p' return to Game_Play
				gm->SetGameState(GAME_PLAY);
				pPressed = false;
				break;

			case RESTART_ROUND:
				//if 'p' return to Game_Play
				gm->SetGameState(GAME_PLAY);
				pPressed = false;
				break;

			default:
				break;
		}
	}
	
	//if (gm->GetGameState() == PAUSE) {
	//	pPressed = false;
	//}

#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
#pragma region ON_MOUSE_PRESS_RELEASE
	static bool	bLastLeft = false, bLastMiddle = false, bLastRight = false;
#define ON_MOUSE_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion
	bool bLeft = false;
	ON_MOUSE_PRESS_RELEASE(Left, NULL, bLeft = true)
	if (bLeft)
	{
		//Turn off the visibility of all BOs for all instances
		m_pMeshMngr->SetVisibleBO(BD_NONE, "ALL", -1);
		//Get the Position and direction of the click on the screen
		std::pair<vector3, vector3> pair =
			m_pCameraMngr->GetClickAndDirectionOnWorldSpace(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		float fDistance = 0;//Stores the distance to the first colliding object
		m_selection = m_pMeshMngr->IsColliding(pair.first, pair.second, fDistance);

		//If there is a collision
		if (m_selection.first >= 0)
		{
			//Turn on the BO of the group
			m_pMeshMngr->SetVisibleBO(BD_OB, m_selection.first, m_selection.second);

			//Turn of the BO of the instance but not the group
			m_pMeshMngr->SetVisibleBO(BD_NONE, m_selection.first, -2);
		}
	}
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
