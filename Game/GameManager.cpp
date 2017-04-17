#include "GameManager.h"

GameManager::GameManager(MeshManagerSingleton* msh)
{

	meshManager = MeshManagerSingleton::GetInstance();
	m_pSystem = SystemSingleton::GetInstance();
	player = new Player(vector3(0.0f), false, vector3(1.0f), meshManager);//Player::GetInstance(meshManager);

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
		
		DisplayData(); //display UI
		
		player->Draw();	// display Player; temporary

		UpdateTimer(); //update timer
	}
	else {
		CheckGoal();
	}
}

// called when player fails to reach round goal
void GameManager::ResetRound()
{
	//as long as player's hp is >0
	if (player->GetLives() > 0) {

		player->SetLives(GetLives() - 1); //player lose 1 health

		SetTotalScore(GetTotalScore() - GetCurrentScore()); //return to original score

		SetCurrentScore(0); //reset current score

		SetCurrentTimer(roundTimer); //seconds //reset current timer

		player->SetBullets(roundAmmo); //Ammo and Goal are the same for the current round
	}
	else {
		GameOver(); //if player health = 0, call GameOver
	}
}

void GameManager::NewGame(void)
{
	fRunTime = 0.0f; //reset run time
	roundTimer = 60; //seconds

	SetLives(3); //reset lives

	SetTotalScore(0); //reset total score
	
	SetCurrentScore(0); //reset current score
	
	SetCurrentTimer(roundTimer); //reset current timer-seconds

	//reset ammo count
	SetAmmo(20);
	roundAmmo = 20;

	SetGoal(5); //reset goal
}

void GameManager::NextRound(void)
{
	SetTotalScore(GetTotalScore() + GetCurrentScore()); //increment total score
	
	SetCurrentScore(0); //reset current score
	
	SetCurrentTimer(roundTimer); //reset current timer-seconds
	
	IncreaseChallenge(); //increase game challenge
}

void GameManager::GameOver(){
	//destroy enemies

	//call new game if player wishes to continue
}

void GameManager::DisplayData()
{
	meshManager->PrintLine(ui->DisplayTotalScore(GetTotalScore())); //display total score

	meshManager->PrintLine(ui->DisplayGoal(GetGoal())); //display current round goal

	meshManager-> PrintLine(ui->DisplayCurrentScore(GetCurrentScore())); //display current score

	meshManager->PrintLine(ui->DisplayAmmoCount(GetAmmo())); //display current bullet count

	meshManager->PrintLine("Current Time: " + std::to_string(currentTimer));

	//display player lives
	meshManager->PrintLine(ui->DisplayLives(GetLives()));
}

void GameManager::UpdateTimer(void)
{
	currentTimer -= fTimeSpan;
}


// at the end of the timer, checks to see if player reached their goal
void GameManager::CheckGoal(void)
{
	if (currentScore >= goal) {
		
		NextRound(); //player goes to a next round
	}
	else {
		
		ResetRound(); //player has to replay round
	}
}

// decrements how many ammo the player starts with in current round
// increments the goal the player needs to reach in current round
void GameManager::IncreaseChallenge()
{
	if (player->GetBullets() > 3) {

		int ranNum = rand() % 3; //get a new rando value

		roundAmmo = GetAmmo() + ranNum; //used for reseting round. 
		SetAmmo(GetAmmo() - ranNum); //decrement ammo

		ranNum = rand() % 3; //get a new rando value

		SetGoal(GetGoal() + ranNum); //increment goal
	}
}

// increments the current score when player hits something
void GameManager::IncrementCurrentScore(int value)
{
	currentScore += value;
}

//returns a percentage based on time that is used for LERPING
float GameManager::Percentage(float scaleOrginalMin, float scaleOriginalMax, float mappedMin, float mappedMax )
{
	float percentage = MapValue(static_cast<float>(fRunTime), scaleOrginalMin, scaleOriginalMax, mappedMin, mappedMax);

	return percentage;
}

void GameManager::MovePlayer(bool left, bool dir)
{
	if (left) {
		player->SetLeft(dir);
	}
	else {
		player->SetUp(dir);
	}
	player->Move();
}

//PROPERTIES---------------------------------------------------------------------------------------------------------------------------------------------------------------

//GOAL properties
int GameManager::GetGoal() {
	return goal;
}

void GameManager::SetGoal(int value) {

	goal = value;
}


// CURRENT SCORE properties
int GameManager::GetCurrentScore() {
	return currentScore;
}

void GameManager::SetCurrentScore(int value) {

	currentScore = value;
}


// TOTAL SCORE properties
int GameManager::GetTotalScore(void)
{
	return totalScore;
}

void GameManager::SetTotalScore(int value)
{
	totalScore = value;
}


//LIVES properties
void GameManager::SetLives(int value)
{
	player->SetLives(value);
}

int GameManager::GetLives(void)
{
	return player->GetLives();
}


// AMMO COUNT properties
int GameManager::GetAmmo(void)
{
	return player->GetBullets();
}

void GameManager::SetAmmo(int value)
{
	player->SetBullets(value);
}


// CURRENT TIMER properties
void GameManager::SetCurrentTimer(float value)
{
	currentTimer = value;
}


// destructor
GameManager::~GameManager()
{
	SafeDelete(ui);
	SafeDelete(player);
	SafeDelete(bullet);
	SafeDelete(enemy);
}
