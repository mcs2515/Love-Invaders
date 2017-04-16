#include "GameManager.h"



GameManager::GameManager()
{
	m_pSystem = SystemSingleton:: GetInstance;
}

//called when player fails to reach round goal
void GameManager::ResetRound()
{
	if (player->GetLives() > 0) {
		player->SetLives(GetLives() - 1);


		//return to original score
		SetTotalScore(GetTotalScore() - GetCurrentScore());

		//reset current score
		SetCurrentScore(0);

		//reset current timer
		SetCurrentTimer(30); //seconds

		//Ammo and Goal are the same for the current round
	}
	else {
		GameOver();
	}
}

void GameManager::ResetGame(void)
{
	//reset lives
	SetLives(3);

	//reset total score
	SetTotalScore(0);
	//reset current score
	SetCurrentScore(0);
	//reset current timer
	SetCurrentTimer(30); //seconds
	//reset ammo count
	SetAmmo(20);
	//reset goal
	SetGoal(5);
}

void GameManager::NextRound(void)
{
	//increment total score
	SetTotalScore(GetTotalScore() + GetCurrentScore());

	//reset current score
	SetCurrentScore(0);

	//reset current timer
	SetCurrentTimer(30); //seconds

	//increment goal player has to reach
	ChangeGoalAmount();

	//decrement the ammount of bullets the player has
	ChangeAmmoAmount();
}

void GameManager::GameOver(){
	
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


//at the end of the timer, checks to see if player reached their goal
bool GameManager::CheckGoal(void)
{
	if (currentTimer <= 0) {
		
		if (currentScore >= goal) {
			//make a new round
			NextRound();
		}
		else {
			if (player -> GetLives() > 0) {
				player->SetLives(GetLives() - 1);
				//player has to play the round again but with 1 less health
				ResetRound();
			}
		}
	}


	return false;
}

// decrements how many ammo the player starts with in current round
void GameManager::ChangeAmmoAmount()
{
	if (player->GetBullets() > 3) {
		//randomly decrement by a certain amount
		int ranNum = rand() % 3; //0-3

		SetAmmo(GetAmmo() + ranNum);
	}
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

float GameManager::Percentage(float valueToMap, float scaleOrginalMin, float scaleOriginalMax, float mappedMin, float mappedMax )
{
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan;


	float percentage = MapValue(static_cast<float>(valueToMap), scaleOrginalMin, scaleOriginalMax, mappedMin, mappedMax);

	return percentage;
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

//LIVES properties
void GameManager::SetLives(int value)
{
	player -> SetLives(value);
}

int GameManager::GetLives(void)
{
	player->GetLives(lives);
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
void GameManager::SetCurrentTimer(int value)
{
	currentTimer = value;
}




// destructor
GameManager::~GameManager()
{
}
