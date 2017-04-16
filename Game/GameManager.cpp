#include "GameManager.h"



GameManager::GameManager()
{
}


void GameManager::ResetRound()
{
	//increment total score
	SetTotalScore(GetTotalScore() + GetCurrentScore());

	//reset current score
	SetCurrentScore(0);

	//reset current timer
	SetCurrentTimer(30); //seconds

	//increment goal play has to reach
	ChangeGoalAmount();

	//change the ammount of bullets the player has
	ChangeAmmoAmount();
}

void GameManager::ResetGame(void)
{
	//reset total score
	SetTotalScore(0);
	//reset current score
	SetCurrentScore(0);
	//reset current timer
	SetCurrentTimer(30); //seconds
	//rset ammo count
	SetAmmo(15);
	//reset goal
	SetGoal(5);
}

void GameManager::DisplayData(MeshManagerSingleton* meshManager)
{
	//these return a string
	meshManager-> PrintLine(ui->DisplayCurrentScore(GetCurrentScore()));

	//method to display total score
	meshManager->PrintLine(ui->DisplayTotalScore(GetTotalScore()));

	//method to display current bullet count
	meshManager->PrintLine(ui->DisplayAmmoCount(GetAmmo()));


	//method to display current goal
	meshManager->PrintLine(ui->DisplayGoal(GetGoal()));
}


// decrements how many ammo the player starts with in current round
void GameManager::ChangeAmmoAmount()
{
	//randomly decrement by a certain amount
	int ranNum = rand() % 3; //0-3

	player->SetAmmo(GetAmmo() + ranNum);

	SetAmmo(GetAmmo() + ranNum);
}

// increments the goal the player needs to reach in current round
void GameManager::ChangeGoalAmount()
{
	//randomly decrement by a certain amount
	int ranNum = rand() % 3; //0-3

	//randomly increment by a certain amount
	SetGoal(GetGoal() + ranNum);
}

// increments the current score when player hits something
void GameManager::IncrementCurrentScore(int value)
{
	currentScore += value;
}


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


// AMMO COUNT properties
int GameManager::GetAmmo(void)
{
	return ammo;
}

void GameManager::SetAmmo(int value)
{
	ammo = value;
}


// CURRENT TIMER properties
void GameManager::SetCurrentTimer(int value)
{
	currentTimer = value;
}




// destructor
GameManager::~GameManager()
{
}
