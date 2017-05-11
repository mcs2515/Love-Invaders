#include "GameManager.h"
Player* Player::instance = nullptr;

GameManager* GameManager::GetInstance(MeshManagerSingleton* mesh) {
	if (instance == nullptr) {
		instance = new GameManager(mesh);

	}
	return instance;
}

void GameManager::ReleaseInstance(void) {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void GameManager::DisplayGameStates() {


	switch (gameState)
	{
	case TITLE: 
		ui.DisplayMainMenu();
		//if 'P' call new game()
		break;

	case CREDITS:
		ui.DisplayCredits();

		//if 'esc' return to Title
		break;

	case PAUSE:
		ui.GenericSingleLine("Paused");

		//if 'p' return to Game_Play
		//if 'esc' return to Title

		break;

	case GAME_PLAY:
		Update(); //continue to update the game

		//if 'p' pause game

		break;

	case NEXT_ROUND:
		ui.GenericSingleLine("Next Round!");
		NextRound(); //increase challenge
		ui.GenericSingleLine("Enchant" + std::to_string(GetGoal()) + "humans.");
		//wait a few secs
		//return to Game_Play

		break;

	case RESTART_ROUND:
		ui.GenericSingleLine("Failed to enchant" + std::to_string(GetGoal()) + "humans.");

		ResetRound(); //player has to replay round

		//wait a few secs
		//return to Game_Play
		break;

	case GAME_OVER:
		GameOver();

		//wait a few secs
		//return to Title

		break;

	default:
		break;
	}
}

void GameManager::Update() {
	//Lets us know how much time has passed since the last call
	fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	fRunTime += fTimeSpan; //How much time has passed since the program started

	if (currentTimer > 0) {
		//draw E,P,B and background
		//move E,B
		//detect collision
		DetectCollision();

		DisplayData(); //display UI	
		RenderBullets(); //render bullets if active

						 //drawing background
		DrawPlanes();
		DrawBunkers();

		player->Draw();	// display Player;
		RenderEnemy();

		UpdateTimer(); //update timer
	}
	else {
		CheckGoal();
	}
}

#pragma region Game_Loop_Functions
void GameManager::ResetRound() {
	//as long as player's hp is >0
	if (player->GetLives() > 0) {

		player->SetLives(GetLives() - 1); //player lose 1 health

		//SetTotalScore(GetTotalScore() - GetCurrentScore()); //return to original score

		SetCurrentScore(0); //reset current score

		SetCurrentTimer(roundTimer); //seconds //reset current timer

		player->SetBullets(roundAmmo); //Ammo and Goal are the same for the current round
		
		ResetObjects(roundAmmo, enemyLSize, true);
	}
	else {
		gameState = GAME_OVER; //if player health = 0, call GameOver
	}
}

void GameManager::NewGame(void) {

	fRunTime = 0.0f; //reset run time
	roundTimer = 20; //seconds
	bulletSize = vector3(0.2f, 0.2f, 0.2f);
	humanSize = vector3(1.0f,1.0f,1.0f);
	//bulletInitialPos = vector3();

	SetLives(3); //reset lives

	SetTotalScore(0); //reset total score

	SetCurrentScore(0); //reset current score

	SetCurrentTimer(roundTimer); //reset current timer-seconds

	//reset ammo count
	roundAmmo = 15;
	
	/*SetPlayerAmmo(roundAmmo);
	SpawnEnemies(enemyLSize);*/
	// Previously-commented code replaced with this:
	ResetObjects(roundAmmo, enemyLSize, true);

	SetGoal(5); //reset goal
}

void GameManager::NextRound(void) {
	SetTotalScore(GetTotalScore() + GetCurrentScore()); //increment total score

	SetCurrentScore(0); //reset current score

	SetCurrentTimer(roundTimer); //reset current timer-seconds

	IncreaseChallenge(); //increase game challenge
}

void GameManager::GameOver(){
	ResetObjects(0, 0, false);
	//call new game if player wishes to continue
}

void GameManager::ResetObjects(int playerBullets, int numEnemies, bool addObjs)
{
	for (int i = 0; i < enemyList.size(); i++) {
		DestroyEnemy(i);
	}
	for (int i = 0; i < bulletList.size(); i++) {
		DestroyBullet(bulletList[i]);
	}
	if (!addObjs)
		return;

	SetPlayerAmmo(playerBullets);
	SpawnEnemies(numEnemies);
	ResetPlayer();
}
#pragma endregion

#pragma region Functions Called_By_NextRound()
void GameManager::IncreaseChallenge() {
	if (player->GetBullets() > 3) {

		int ranNum = rand() % 3; //get a new rando value

		roundAmmo = GetPlayerAmmo() + ranNum; //used for reseting round. 
		//SetPlayerAmmo(GetPlayerAmmo() - ranNum); //decrement ammo

		ranNum = rand() % 3; //get a new rando value

		SetGoal(GetGoal() + ranNum); //increment goal

		enemyLSize = GetGoal() + ranNum;
	}
	ResetObjects(roundAmmo, enemyLSize, true);
}

void GameManager::IncrementCurrentScore(int value) {
	currentScore += value;
}

void GameManager::ResetPlayer()
{
	player->SetPosition(vector3(0.0f, 3.0f, 0.0f));
}
#pragma endregion

void GameManager::MovePlayer(int left, int up) {
	// X AXIS movement
	if (left == -1)
		player->position.x -= player->GetMoveSpeed();
	else if (left == 1)
		player->position.x += player->GetMoveSpeed();

	// Z AXIS movement
	if (up == -1)
		player->position.z -= player->GetMoveSpeed();
	else if (up == 1)
		player->position.z += player->GetMoveSpeed();

	player->Move();
}

void GameManager::DetectCollision()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		for (int j = 0; j < enemyList.size(); j++)
		{
			if (bulletList[i].IsColliding(&enemyList[j]) && !bulletList[i].GetReturn() /*&& bulletList[i].GetIsActive()*/) //dont get for collision if bullet is bouncing back
			{
				enemyList.erase(enemyList.begin()+j);
				j--;
				IncrementCurrentScore(1);
			}

			if (bulletList[i].IsColliding(player) && bulletList[i].GetReturn()) //is returning/bouncing back
			{
				bulletList[i].Reset(); //reset timer, isactive bool , returning bool
				SetPlayerAmmo(GetPlayerAmmo()+1); //increment player bullet
			}
		}
	}
}

void GameManager::FireBullet()
{
	if(GetPlayerAmmo() !=0) {
		bulletList.push_back(player->FireBullet(bulletList.size()));
		SetPlayerAmmo(GetPlayerAmmo() - 1);
	}
}


#pragma region Other_Helper_Functions
void GameManager::UpdateTimer(void) {
	currentTimer -= fTimeSpan;
}

void GameManager::DrawPlanes(void) {

	//floor
	floorPlane = glm::rotate(IDENTITY_M4, 90.0f, vector3(1.0f, 0.0f, 0.0f));
	floorPlane = glm::translate(floorPlane, vector3(0.0f, 0.0f, 0.5f));
	floorPlane = glm::scale(floorPlane, vector3(40.0f, 25.0f, 1.0f));
	meshManager->AddPlaneToRenderList(floorPlane, REPURPLE);

	//floor box (OPTIONAL)
	floorBox = glm::rotate(IDENTITY_M4, 90.0f, vector3(1.0f, 0.0f, 0.0f));
	floorBox = glm::translate(floorBox, vector3(0.0f, 0.0f, 1.7f));
	floorBox = glm::scale(floorBox, vector3(40.0f, 25.0f, 2.0f));
	meshManager->AddCubeToRenderList(floorBox, REGREEN);

	//wall1Plane
	wall1Plane = glm::translate(IDENTITY_M4, vector3(0.0f, 4.5f, -12.5f));
	wall1Plane = glm::scale(wall1Plane, vector3(40.0f, 10.0f, 1.0f));
	meshManager->AddPlaneToRenderList(wall1Plane, REMAGENTA);

	//wall2Plane
	wall2Plane = glm::rotate(IDENTITY_M4, 90.0f, vector3(0.0f, 1.0f, 0.0f));
	wall2Plane = glm::translate(wall2Plane, vector3(0.0f, 4.5f, 20.0f));
	wall2Plane = glm::scale(wall2Plane, vector3(25.0f, 10.0f, 0.0f));
	meshManager->AddPlaneToRenderList(wall2Plane, REBLUE);
}

void GameManager::DrawBunkers(void) {
	
	bunker = glm::translate(IDENTITY_M4, vector3(-15.0f, 0.2f, -9.0f));
	bunker = glm::scale(bunker, vector3(1.5f, 1.5f, 1.5f));
	meshManager->AddCubeToRenderList(bunker, REYELLOW);

	bunker2 = glm::translate(IDENTITY_M4, vector3(-15.0f, 0.2f, 9.0f));
	bunker2 = glm::scale(bunker2, vector3(1.5f, 1.5f, 1.5f));
	meshManager->AddCubeToRenderList(bunker2, REYELLOW);

	bunker3 = glm::translate(IDENTITY_M4, vector3(15.0f, 0.2f, 9.0f));
	bunker3 = glm::scale(bunker3, vector3(1.5f, 1.5f, 1.5f));
	meshManager->AddCubeToRenderList(bunker3, REYELLOW);

	bunker4 = glm::translate(IDENTITY_M4, vector3(15.0f, 0.2f, -9.0f));
	bunker4 = glm::scale(bunker4, vector3(1.5f, 1.5f, 1.5f));
	meshManager->AddCubeToRenderList(bunker4, REYELLOW);
}

void GameManager::SpawnEnemies(int numEnemies)
{
	//create numEnemies number of enemies
	for (int i = 0; i < numEnemies; i++) {
		//get random values for Start, End and Percent
		vector3 newStart = bunkerVecs[rand() % 4];

		vector3 newEnd = newStart;
		while (newEnd == newStart)
		{
			newEnd = bunkerVecs[rand() % 4];
		}

		float newPercent = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		//pushback the new enemy

		enemyList.push_back(Enemy(vector3(0, 0, 0), false, humanSize, newStart, newEnd, meshManager, bunkerVecs, newPercent));
	}
}

void GameManager::CheckGoal(void) {
	if (currentScore >= goal) {

		gameState = NEXT_ROUND;
		
	}
	else {

		gameState = RESTART_ROUND;
	}
}

void GameManager::DisplayData() {
	ui.DisplayTotalScore(GetTotalScore()); //display total score
	ui.DisplayGoal(GetGoal()); //display current round goal
	ui.DisplayCurrentScore(GetCurrentScore()); //display current score
	ui.DisplayAmmoCount(GetPlayerAmmo()); //display current bullet count
	ui.DisplayCurrentTime(currentTimer);	// CHANGE FROM SYSTEM TIME TO CURRENT TIME LATER
	ui.DisplayLives(GetLives());	//display player lives

	//meshManager->PrintLine(player->GetStringPosition(), RERED);
}

//float GameManager::Percentage(float scaleOriginalMin, float scaleOriginalMax, float mappedMin, float mappedMax) {
//	float percentage = MapValue(static_cast<float>(fRunTime), scaleOriginalMin, scaleOriginalMax, mappedMin, mappedMax);
//
//	return percentage;
//}
#pragma endregion

#pragma region Destroying_Objects
void GameManager::DestroyEnemy(int enemy) {
	// destroy the enemy that we want
}

void GameManager::DestroyBullet(Bullet bullet) {
	// destroy the bullet that we want

}
#pragma endregion

#pragma region Rendering_Objects
void GameManager::RenderEnemy() {
	// render the enemy
	for (int i = 0; i < enemyList.size(); i++) {
		enemyList[i].TimeTick(fTimeSpan);
		float enemyLerp = MapValue(enemyList[i].GetTime(), 0.0f, 5.0f, 0.0f, 1.0f);
		enemyList[i].Move(enemyLerp);
		enemyList[i].Draw();
	}
}

void GameManager::RenderBullets()
{
	//for loop for bullet rendering
	for (int i = 0; i < bulletList.size(); i++)
	{
		if (bulletList[i].GetIsActive())
		{
			bulletList[i].TimeTick(fTimeSpan);
			float bulletLerp = MapValue(bulletList[i].GetTime(), 0.0f, 2.0f, 0.0f, 1.0f);
			bulletList[i].Move(bulletLerp);
			//std::cout << bulletLerp << std::endl;
			bulletList[i].Draw();
		}
		else
		{
			bulletList[i].Draw();
		}
	}
}

#pragma endregion

#pragma region Properties
// GOAL properties
int GameManager::GetGoal() {return goal;}
void GameManager::SetGoal(int value) {goal = value;}

// CURRENT SCORE properties
int GameManager::GetCurrentScore() {return currentScore;}
void GameManager::SetCurrentScore(int value) {currentScore = value;}

// TOTAL SCORE properties
int GameManager::GetTotalScore() {return totalScore;}
void GameManager::SetTotalScore(int value) {totalScore = value;}

// LIVES properties
int GameManager::GetLives() {return player->GetLives();}
void GameManager::SetLives(int value) {player->SetLives(value);}

// AMMO COUNT properties
int GameManager::GetPlayerAmmo(void) {return player->GetBullets();}
void GameManager::SetPlayerAmmo(int value) {player->SetBullets(value);}

int GameManager::GetGameState(void){return gameState;}

void GameManager::SetGameState(GameState value)
{
	gameState = value;
}

// CURRENT TIMER properties
void GameManager::SetCurrentTimer(float value) {currentTimer = value;}
#pragma endregion