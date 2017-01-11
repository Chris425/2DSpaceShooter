/***
TODO:
-MUSIC AND SOUND EFFECTS!!! important.
-scripted events for spawning instead of RNG - use timer and arrays - in boss
-Different missile types (ex. big ball of energy after you've maxed laser power ups - new missile class, texture and hit detection)
-^Boss should probably shoot these things too in addition to spawning enemies
-Title screen - choose your character!! (Font - Castellar bold in word)
-more cheats using F1-12 keys


-Far future - hire artist to redo assets so you can monetize it??




* Christopher Di Conza, Final Project, PROG33921
*
*The main Game class, contains essential methods such as the constructor, initialize, draw, shutdown, and update.
*This is where all of the logic is for the game at runtime!
***/
#include <iostream>

#include "Game.h"
#include "Timer.h"

//GLOBALS
char stringTitle[60] = "Final Project!     Diconzac 991 134 374";
bool playerAlive = true;
bool boss = false;
bool isBossOnScreen = false;
bool isShieldUp = false;

int playerPower = 1;
int score = 0;

Game::Game()
	: mExplosionTex(NULL)
	, mShuttleTex(NULL)
    , mShotTex(NULL)
	, mShot2Tex(NULL)
	, mBackTex(NULL)
	, mStarTex(NULL)
	, mAlienTex(NULL)
	, mStrongAlienTex(NULL)
	, mCrusherAlienTex(NULL)
	, mBossTex(NULL)
	, mBonusAlienTex(NULL)
	, mPowerUpTex(NULL)
	, mShieldUpTex(NULL)
	, mHealthUpTex(NULL)
	, mShieldTex(NULL)
	, mHeartTex(NULL)
	, m1Tex(NULL)
	, m2Tex(NULL)
	, m3Tex(NULL)
	, m4Tex(NULL)
	, mGUITex(NULL)

    , mMissiles() //empty vector
	, mEnemies()
	, mShootingStars()
	, mStrongEnemies()
	, mCrusherEnemies()
	, mBosses()
	, mBonusEnemies()
	, mPowerUps()
{
    // nothing to do: all setup should be done in Initialize method
}

Game::~Game()
{
    // nothing to do: all cleanup should be done in Shutdown method
}

bool Game::Initialize() //return false if something goes wrong
{
	
    std::cout << "Initializing game" << std::endl;

    // set some window properties
    System::SetWindowSize(800,600);
    System::SetWindowTitle(stringTitle);

    // get renderer
    SDL_Renderer* renderer = System::GetRenderer();

    //
    // load all textures
    //
	mExplosionTex = Texture::Load("media/explosion.tga", renderer);
	if (!mExplosionTex)	{
		std::cerr << "*** failed to load explosion texture" << std::endl; //error checking
		return false;
	}
    mShuttleTex = Texture::Load("media/shuttle.png", renderer);
	if (!mShuttleTex)	{
		std::cerr << "*** failed to load shuttle texture" << std::endl; 
		return false;	}

    mShotTex = Texture::Load("media/shot.png", renderer);
	if (!mShotTex)		{
		std::cerr << "*** failed to load shot texture" << std::endl; 
		return false;	}

	mShot2Tex = Texture::Load("media/shot2.png", renderer);
	if (!mShot2Tex)		{
		std::cerr << "*** failed to load shot2 texture" << std::endl;
		return false;
	}

	mBackTex = Texture::Load("media/spacePurple.jpg", renderer);
	if (!mShotTex)		{
		std::cerr << "*** failed to load background texture" << std::endl;
		return false;
	}

	mStarTex = Texture::Load("media/shootingStar.png", renderer);
	if (!mStarTex)		{
		std::cerr << "*** failed to load shooting star texture" << std::endl;
		return false;
	}
	
	mAlienTex = Texture::Load("media/alien.png", renderer);
	if (!mAlienTex)		{
		std::cerr << "*** failed to load alien texture" << std::endl;
		return false;
	}

	mStrongAlienTex = Texture::Load("media/strongAlien.png", renderer);
	if (!mStrongAlienTex)		{
		std::cerr << "*** failed to load Strong alien texture" << std::endl;
		return false;
	}
	mCrusherAlienTex = Texture::Load("media/crusherAlien.png", renderer);
	if (!mCrusherAlienTex)		{
		std::cerr << "*** failed to load crusher alien texture" << std::endl;
		return false;
	}

	//all credit to Darke / lt. JG for these sprite images
	mBossTex = Texture::Load("media/ltjg_design.png", renderer);
	if (!mBossTex)		{
		std::cerr << "*** failed to load boss texture" << std::endl;
		return false;
	}

	mBonusAlienTex = Texture::Load("media/BonusAlien.png", renderer);
	if (!mBonusAlienTex)		{
		std::cerr << "*** failed to load bonus alien texture" << std::endl;
		return false;
	}


	mPowerUpTex = Texture::Load("media/powerUp.png", renderer);
	if (!mPowerUpTex)		{
		std::cerr << "*** failed to load power up texture" << std::endl;
		return false;
	}
	mShieldUpTex = Texture::Load("media/shieldUp.png", renderer);
	if (!mShieldUpTex)		{
		std::cerr << "*** failed to load shield power up texture" << std::endl;
		return false;
	}
	mHealthUpTex = Texture::Load("media/healthUp.png", renderer);
	if (!mHealthUpTex)		{
		std::cerr << "*** failed to load health power up texture" << std::endl;
		return false;
	}

	mShieldTex = Texture::Load("media/shield.png", renderer);
	if (!mShieldTex)		{
		std::cerr << "*** failed to load health shield texture" << std::endl;
		return false;
	}

	mHeartTex = Texture::Load("media/heart.png", renderer);
	if (!mHeartTex)		{
		std::cerr << "*** failed to load heart texture" << std::endl;
		return false;
	}

	m1Tex = Texture::Load("media/1.png", renderer);
	m2Tex = Texture::Load("media/2.png", renderer);
	m3Tex = Texture::Load("media/3.png", renderer);
	m4Tex = Texture::Load("media/4.png", renderer); //Meh... code bloat with error checking

	mGUITex = Texture::Load("media/GUI.png", renderer);
	if (!mGUITex)		{
		std::cerr << "*** failed to load GUI texture" << std::endl;
		return false;
	}
    //
    // spawn player
    //

    Vec2 spawnPos;
    spawnPos.x = 0.5f * System::GetWindowWidth();
    spawnPos.y = 0.95f * System::GetWindowHeight();

    mPlayer = new Player(spawnPos, mShuttleTex, 3);

    mPlayer->SetSpeed(150.0f);
	

	Vec2 shieldSpawnPos(mPlayer->Center());

	mShield = new Shield(shieldSpawnPos, mShieldTex);

	return true;
}

void Game::Shutdown() //this is the best spot to remove stuff to ensure no memory leaks
{
    std::cout << ">>>Shutting down game" << std::endl;

    //
    // delete all entities
    //

    // delete player
	if (playerAlive)
	{
		delete mPlayer;
	}
	if (isShieldUp)
	{
		delete mShield;
	}

    // delete missiles
    for (unsigned i = 0; i < mMissiles.size(); i++) {
        delete mMissiles[i];
    }
    mMissiles.clear();
	
	// delete enemies
	for (unsigned i = 0; i < mEnemies.size(); i++) {
		delete mEnemies[i];
	}
	mEnemies.clear();
	
	// delete Bonus enemies
	for (unsigned i = 0; i < mBonusEnemies.size(); i++) {
		delete mBonusEnemies[i];
	}
	mBonusEnemies.clear();
	
	// delete strong enemies
	for (unsigned i = 0; i < mStrongEnemies.size(); i++) {
		delete mStrongEnemies[i];
	}
	mStrongEnemies.clear();

	// delete crusher enemies
	for (unsigned i = 0; i < mCrusherEnemies.size(); i++) {
		delete mCrusherEnemies[i];
	}
	mCrusherEnemies.clear();

	// delete boss
	for (unsigned i = 0; i < mBosses.size(); i++) {
		delete mBosses[i];
	}
	mBosses.clear();

	// delete shooting stars
	for (unsigned i = 0; i < mShootingStars.size(); i++) {
		delete mShootingStars[i];
	}
	mShootingStars.clear();

	//delete all power ups
	for (unsigned i = 0; i < mPowerUps.size(); i++) {
		delete mPowerUps[i];
	}
	mExplosions.clear();

	//delete all explosions
	for (unsigned i = 0; i < mExplosions.size(); i++) {
		delete mExplosions[i];
	}
	mExplosions.clear();

    //
    // destroy all textures
    //
    Texture::Destroy(mShuttleTex);
    Texture::Destroy(mShotTex);
	Texture::Destroy(mShot2Tex);
	Texture::Destroy(mBackTex);
	Texture::Destroy(mStarTex);
	Texture::Destroy(mAlienTex);
	Texture::Destroy(mExplosionTex);
	Texture::Destroy(mStrongAlienTex);
	Texture::Destroy(mCrusherAlienTex);
	Texture::Destroy(mBossTex);
	Texture::Destroy(mBonusAlienTex);
	Texture::Destroy(mPowerUpTex);
	Texture::Destroy(mHealthUpTex);
	Texture::Destroy(mShieldUpTex);
	Texture::Destroy(mShieldTex);
	Texture::Destroy(mHeartTex);
	Texture::Destroy(m1Tex);
	Texture::Destroy(m2Tex);
	Texture::Destroy(m3Tex);
	Texture::Destroy(m4Tex);
	Texture::Destroy(mGUITex);
}



void Game::Draw(SDL_Renderer* renderer)
{
	// clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);


	

	//draw background
		Vec2 mBackground(0, 0);
		if (mBackTex) {		
			SDL_Rect screenRect;
			screenRect.w = mBackTex->GetWidth();
			screenRect.h = mBackTex->GetHeight();
			screenRect.x = (int)(mBackground.x - mBackTex->GetWidth() / 2);
			screenRect.y = (int)(mBackground.y - mBackTex->GetHeight() / 2);
			SDL_RenderCopy(renderer, mBackTex->GetSDLTexture(), NULL, NULL);
		}
		else {
			SDL_Rect screenRect;
			screenRect.w = 64;
			screenRect.h = 64;
			screenRect.x = (int)(mBackground.x - screenRect.w / 2);
			screenRect.y = (int)(mBackground.y - screenRect.h / 2);
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			SDL_RenderFillRect(renderer, &screenRect);
		}

		
	
	// draw shooting stars
	for (unsigned i = 0; i < mShootingStars.size(); i++) {
		mShootingStars[i]->Draw(renderer);
	}
	

	// draw player first so missiles appear over cannon
	if (playerAlive)
	{
		mPlayer->Draw(renderer);
	}

	if (isShieldUp)
	{
		SDL_Rect screenRect;
		screenRect.w = mShieldTex->GetWidth();
		screenRect.h = mShieldTex->GetHeight();
		screenRect.x = (int)(mPlayer->Center().x - 40);
		screenRect.y = (int)(mPlayer->Center().y - 55);

		// draw textured rectangle
		SDL_RenderCopy(renderer, mShieldTex->GetSDLTexture(), NULL, &screenRect);
	}



	// draw missiles
    for (unsigned i = 0; i < mMissiles.size(); i++) {
        mMissiles[i]->Draw(renderer);
    }

	// draw enemies
	for (unsigned i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Draw(renderer);
	}

	// draw Strong enemies
	for (unsigned i = 0; i < mStrongEnemies.size(); i++) {
		mStrongEnemies[i]->Draw(renderer);
	}

	// draw crusher enemies
	for (unsigned i = 0; i < mCrusherEnemies.size(); i++) {
		mCrusherEnemies[i]->Draw(renderer);
	}

	// draw boss
	for (unsigned i = 0; i < mBosses.size(); i++) {
		mBosses[i]->Draw(renderer);
	}

	// draw Bonus enemies
	for (unsigned i = 0; i < mBonusEnemies.size(); i++) {
		mBonusEnemies[i]->Draw(renderer);
	}

	// draw Power Ups
	for (unsigned i = 0; i < mPowerUps.size(); i++) {
		mPowerUps[i]->Draw(renderer);
	}
	

	// draw explosions
 	for (unsigned i = 0; i < mExplosions.size(); i++) {
		mExplosions[i]->Draw(renderer);
	}

	//draw GUI
	SDL_Rect GUIRect;
	GUIRect.w = mBackTex->GetWidth();
	GUIRect.h = mBackTex->GetHeight();
	GUIRect.x = (int)(mBackground.x - mBackTex->GetWidth() / 2);
	GUIRect.y = (int)(mBackground.y - mBackTex->GetHeight() / 2);
	SDL_RenderCopy(renderer, mGUITex->GetSDLTexture(), NULL, NULL);


#pragma region player hearts
	//draw player hearts
	Vec2 mHeartLoc(0, 0);
	if (playerAlive)
	{
		if (mPlayer->getHealth() >= 3)
		{
			SDL_Rect heart1;
			heart1.w = mHeartTex->GetWidth();
			heart1.h = mHeartTex->GetHeight();
			heart1.x = (int)(System::GetWindowWidth() - 65);
			heart1.y = (int)(System::GetWindowHeight() - 77);
			SDL_RenderCopy(renderer, mHeartTex->GetSDLTexture(), NULL, &heart1);

			SDL_Rect heart2;
			heart2.w = mHeartTex->GetWidth();
			heart2.h = mHeartTex->GetHeight();
			heart2.x = (int)(System::GetWindowWidth() - 130);
			heart2.y = (int)(System::GetWindowHeight() - 77);
			SDL_RenderCopy(renderer, mHeartTex->GetSDLTexture(), NULL, &heart2);

			SDL_Rect heart3;
			heart3.w = mHeartTex->GetWidth();
			heart3.h = mHeartTex->GetHeight();
			heart3.x = (int)(System::GetWindowWidth() - 195);
			heart3.y = (int)(System::GetWindowHeight() - 77);
			SDL_RenderCopy(renderer, mHeartTex->GetSDLTexture(), NULL, &heart3);
		}

		else if (mPlayer->getHealth() == 2)
		{
			SDL_Rect heart1;
			heart1.w = mHeartTex->GetWidth();
			heart1.h = mHeartTex->GetHeight();
			heart1.x = (int)(System::GetWindowWidth() - 65);
			heart1.y = (int)(System::GetWindowHeight() - 77);
			SDL_RenderCopy(renderer, mHeartTex->GetSDLTexture(), NULL, &heart1);

			SDL_Rect heart2;
			heart2.w = mHeartTex->GetWidth();
			heart2.h = mHeartTex->GetHeight();
			heart2.x = (int)(System::GetWindowWidth() - 130);
			heart2.y = (int)(System::GetWindowHeight() - 77);
			SDL_RenderCopy(renderer, mHeartTex->GetSDLTexture(), NULL, &heart2);

		}

		else if (mPlayer->getHealth() == 1)
		{
			SDL_Rect heart1;
			heart1.w = mHeartTex->GetWidth();
			heart1.h = mHeartTex->GetHeight();
			heart1.x = (int)(System::GetWindowWidth() - 65);
			heart1.y = (int)(System::GetWindowHeight() - 77);
			SDL_RenderCopy(renderer, mHeartTex->GetSDLTexture(), NULL, &heart1);


		}


	}

#pragma endregion player hearts
	

#pragma region  player power
	//draw player power level
	Vec2 mPowerLoc(0, 0);
	if (playerAlive)
	{
		if (playerPower >= 4) //it's over.... 4?
		{
			SDL_Rect power4;
			power4.w = m4Tex->GetWidth();
			power4.h = m4Tex->GetHeight();
			power4.x = (int)(20);
			power4.y = (int)(System::GetWindowHeight() - 75);
			SDL_RenderCopy(renderer, m4Tex->GetSDLTexture(), NULL, &power4);
		}

		else if (playerPower == 3)
		{
			SDL_Rect power3;
			power3.w = m4Tex->GetWidth();
			power3.h = m4Tex->GetHeight();
			power3.x = (int)(20);
			power3.y = (int)(System::GetWindowHeight() - 75);
			SDL_RenderCopy(renderer, m3Tex->GetSDLTexture(), NULL, &power3);
		}
		else if (playerPower == 2)
		{
			SDL_Rect power2;
			power2.w = m4Tex->GetWidth();
			power2.h = m4Tex->GetHeight();
			power2.x = (int)(20);
			power2.y = (int)(System::GetWindowHeight() - 75);
			SDL_RenderCopy(renderer, m2Tex->GetSDLTexture(), NULL, &power2);
		}
		else if (playerPower == 1)
		{
			SDL_Rect power1;
			power1.w = m4Tex->GetWidth();
			power1.h = m4Tex->GetHeight();
			power1.x = (int)(20);
			power1.y = (int)(System::GetWindowHeight() - 75);
			SDL_RenderCopy(renderer, m1Tex->GetSDLTexture(), NULL, &power1);
		}

	}

#pragma endregion player power
}

void Game::Update(float dt)
{
	

    //std::cout << dt << std::endl;

    // get world bounds
    float worldLeft = WorldLeft();
    float worldRight = WorldRight();
    float worldTop = WorldTop();
    float worldBottom = WorldBottom();

	float horiMov = rand() % 40;
	float vertiMov = rand() % 100;

	//for bonus enemy that drops power up
	float bonusHoriMov = 100;
	float bonusVertiMov = 200;
	
	int alienStartXPos = rand() % System::GetWindowWidth();
	
	// consider making it spawn directly on top of the player using mPlayer's x coord... or is that too evil? >:) --cdc
	int crusherStartXPos = rand() % (System::GetWindowWidth() - 200) + 100;
	int ifSpawn = rand() % 950; 
	
	//random spawning until boss enters the arena
	if (!boss){
		Vec2 alientStartVec = Vec2(alienStartXPos, 0);
		if (ifSpawn <=5) //move right
		{
			Enemy* myEnemy = new Enemy(alientStartVec, mAlienTex);
			myEnemy->SetVelocity(horiMov, vertiMov);
			mEnemies.push_back(myEnemy);
		}

		if (ifSpawn >5 && ifSpawn <=10) //move left
		{
			Enemy* myEnemy = new Enemy(alientStartVec, mAlienTex);
			myEnemy->SetVelocity(-(horiMov), vertiMov);
			mEnemies.push_back(myEnemy);
		}

		if (ifSpawn == 600 || ifSpawn == 700) //strong enemy!
		{
			StrongEnemy* myStrongEnemy = new StrongEnemy(alientStartVec, mStrongAlienTex, 10);
			myStrongEnemy->SetVelocity(-(horiMov), vertiMov);
			mStrongEnemies.push_back(myStrongEnemy);
		}

		if (ifSpawn == 650) //crusher enemy!
		{
			Vec2 crusherStartVec = Vec2(crusherStartXPos, 60);
			CrusherEnemy* myCrusherEnemy = new CrusherEnemy(crusherStartVec, mCrusherAlienTex, 35);
			myCrusherEnemy->SetVelocity(0, 275);
			mCrusherEnemies.push_back(myCrusherEnemy);
		}

		if (ifSpawn == 850 || ifSpawn == 849) // Bonus enemy!!
		{
			BonusEnemy* myBonusEnemy = new BonusEnemy(alientStartVec, mBonusAlienTex);
			myBonusEnemy->SetVelocity(-(horiMov - 100), vertiMov + 100);
			mBonusEnemies.push_back(myBonusEnemy);
		}
	}
	else if (boss)
	{

		int bossSpawnTimer = rand() %  500;
		Vec2 alientStartVec = Vec2(alienStartXPos, 0);
		if (bossSpawnTimer == 490)
		{
			Vec2 alientStartVec = Vec2(alienStartXPos, 0);
			BonusEnemy* myBonusEnemy = new BonusEnemy(alientStartVec, mBonusAlienTex);
			myBonusEnemy->SetVelocity(-(horiMov - 100), vertiMov + 100);
			mBonusEnemies.push_back(myBonusEnemy);
		}
		if (!isBossOnScreen)
		{
			Boss* myBoss = new Boss(Vec2(System::GetWindowWidth() / 2, 120), mBossTex, 600);
			myBoss->SetVelocity(0, 0);
			mBosses.push_back(myBoss);
			isBossOnScreen = true;
		}
	}
	
	float vertiStarMov = rand() % 100;

	int shootingStarXPos = rand() % System::GetWindowWidth();

	Vec2 starStartVec = Vec2(shootingStarXPos, 0);
	if (ifSpawn < 50)
	{
		Star* myShootingStar = new Star(starStartVec, mStarTex);
		myShootingStar->SetVelocity(0, vertiMov);
		mShootingStars.push_back(myShootingStar);
	}

	

	//boss laser
	if (boss)
	{
		for (int i = 0; i < mBosses.size(); i++)
		{
			int BossShootChance = rand() % 18; 
			if (BossShootChance == 1)
			{
				int bossShootLoc = rand() % 500;
				Vec2 aliMisSpawn = Vec2(mBosses[i]->Left() + 120 + bossShootLoc, mBosses[i]->Center().y);
				Missile* bossMissile = new Missile(aliMisSpawn, mShot2Tex);
				bossMissile->SetVelocity(0.0f, 150.0f);
				mMissiles.push_back(bossMissile);
			}
		}
	}
	
	for (int i = 0; i < mEnemies.size(); i++)
	{	
		//alien lasers here
		int alienShootChance = rand() % 240; //shoot once every 4 seconds on average
		if (alienShootChance == 1)
		{
			Vec2 aliMisSpawn = Vec2(mEnemies[i]->Center());
			Missile* alienMissile = new Missile(aliMisSpawn, mShot2Tex);
			alienMissile->SetVelocity(0.0f, 150.0f);
			mMissiles.push_back(alienMissile);
		}
	}

	for (int i = 0; i < mStrongEnemies.size(); i++)
	{
		int alienShootChance = rand() % 120; //shoot once every 2 second on average
		if (alienShootChance == 1)
		{
			Vec2 strAliMisSpawn1 = Vec2(mStrongEnemies[i]->Center().x - 10, mStrongEnemies[i]->Center().y + 50);
			Missile* am1 = new Missile(strAliMisSpawn1, mShot2Tex);
			am1->SetVelocity(0.0f, 150.0f);
			mMissiles.push_back(am1);

			Vec2 strAliMisSpawn2 = Vec2(mStrongEnemies[i]->Center().x + 10, mStrongEnemies[i]->Center().y + 50);
			Missile* am2 = new Missile(strAliMisSpawn2, mShot2Tex);
			am2->SetVelocity(0.0f, 150.0f);
			mMissiles.push_back(am2);
		}
	}



	if (playerAlive)
	{
		// update player
		mPlayer->Update(dt);

		// keep the player within world bounds
		if (mPlayer->Left() < worldLeft) {
			mPlayer->SetLeft(worldLeft);
		}
		else if (mPlayer->Right() > worldRight) {
			mPlayer->SetRight(worldRight);
		}
		if (mPlayer->Top() < worldTop) {
			mPlayer->SetTop(worldTop);
		}
		else if (mPlayer->Bottom() > worldBottom) {
			mPlayer->SetBottom(worldBottom);
		}
	}

	if (isShieldUp)
	{
		mShield->Update(dt);
	}

	
    // update missiles
    for (unsigned i = 0; i < mMissiles.size();   ) {
        Missile* m = mMissiles[i];
        
        // update missile
        m->Update(dt);

//MISSILE COLLISIONS HERE
		//so if the center of missile minus center of an object < certain threshold, we will consider it a collision

		
		//ENEMY-MISSILE COLLISION -> check both x and y for each enemy in enemy array
		for (int i = 0; i < mEnemies.size(); i++){
			//bit of trial and error for these numbers :)
			float thresholdX = (m->Center().x - mEnemies[i]->Center().x) + 20;
			float thresholdY = (m->Center().y - mEnemies[i]->Center().y) + 20;
			
			//I originally wanted to check the missile based on texture but instead
			//it would be easier to look at velocity (- or + direction) to determine if it's an enemy or player missile
			if (m->Velocity().y < 0.0f && (thresholdX <= 55 && thresholdX > 0 && thresholdY <= 55 && thresholdY > 0))
			{
				//collision occurs; delete
				
				//create new enemy explosion. therefore medium size
				float explSize = (0.8f, 1.0f);
				float explDuration = (0.5f, 0.6f);
				Explosion* e = new Explosion(Vec2(mEnemies[i]->Center().x, mEnemies[i]->Center().y), mExplosionTex, explSize, explDuration);
				mExplosions.push_back(e);
				
				std::cout << ">>>Enemy hit!" << std::endl;
				Vec2 despawn = Vec2(-1000, -1000);
				//This is probably a stupid way to do it; I teleport the enemy offscreen which then triggers the delete. 
				//The more obvious way of just using the destructor and deleting it here was giving me issues for some reason
				mEnemies[i]->SetCenter(despawn);
				m->SetCenter(despawn);

			}
			
		}


		//STRONGENEMY-MISSILE COLLISION 
		for (int i = 0; i < mStrongEnemies.size(); i++){
			float thresholdX = (m->Center().x - mStrongEnemies[i]->Center().x) + 50;
			float thresholdY = (m->Center().y - mStrongEnemies[i]->Center().y) + 50;

			if (m->Velocity().y < 0.0f && (thresholdX <= 100 && thresholdX > 0 && thresholdY <= 100 && thresholdY > 0))
			{
				float explSize = (0.8f, 1.0f);
				float explDuration = (0.5f, 0.6f);
				Explosion* e = new Explosion(Vec2(mStrongEnemies[i]->Center().x, mStrongEnemies[i]->Center().y), mExplosionTex, explSize, explDuration);
				mExplosions.push_back(e);

				int myStrongEnemyHealth = (mStrongEnemies[i]->getHealth() - 1);

				std::cout << ">>>Strong Enemy hit! Life left: " << myStrongEnemyHealth << std::endl;
				Vec2 despawn = Vec2(-1000, -1000);

				mStrongEnemies[i]->setHealth(myStrongEnemyHealth);
				if (myStrongEnemyHealth == 0)
				{
					//strong enemy death generates a really big explosion :)
					float explSize2 = (3.0f, 3.5f);
					float explDuration2 = (1.0f, 1.0f);
					Explosion* e2 = new Explosion(Vec2(mStrongEnemies[i]->Center().x, mStrongEnemies[i]->Center().y), mExplosionTex, explSize2, explDuration2);
					mExplosions.push_back(e2);
					mStrongEnemies[i]->SetCenter(despawn);
					
					
				}

				m->SetCenter(despawn);


			}


		}

		//CRUSHERENEMY-MISSILE COLLISION 
		for (int i = 0; i < mCrusherEnemies.size(); i++){
			float thresholdX = (m->Center().x - mCrusherEnemies[i]->Center().x) + 50;
			float thresholdY = (m->Center().y - mCrusherEnemies[i]->Center().y) + 50;

			if (m->Velocity().y < 0.0f && (thresholdX <= 80 && thresholdX > 0 && thresholdY <= 80 && thresholdY > 0))
			{
				float explSize = (0.8f, 1.0f);
				float explDuration = (0.5f, 0.6f);
				Explosion* e = new Explosion(Vec2(mCrusherEnemies[i]->Center().x, mCrusherEnemies[i]->Center().y), mExplosionTex, explSize, explDuration);
				mExplosions.push_back(e);

				int myCrusherEnemyHealth = (mCrusherEnemies[i]->getHealth() - 1);

				std::cout << ">>>Crusher Enemy hit! Life left: " << myCrusherEnemyHealth << std::endl;
				
				Vec2 despawn = Vec2(-1000, -1000);
				mCrusherEnemies[i]->setHealth(myCrusherEnemyHealth);
				if (myCrusherEnemyHealth == 0)
				{					
					//Crusher enemy death generates a really big explosion :)
					float explSize2 = (3.0f, 4.5f);
					float explDuration2 = (1.0f, 1.5f);
					Explosion* e2 = new Explosion(Vec2(mCrusherEnemies[i]->Center().x, mCrusherEnemies[i]->Center().y), mExplosionTex, explSize2, explDuration2);
					mExplosions.push_back(e2);
					mCrusherEnemies[i]->SetCenter(despawn);
				
				}

				m->SetCenter(despawn);

			}

		}


		//BOSS-MISSILE COLLISION 
		if (boss)
		{
			for (int i = 0; i < mBosses.size(); i++){
				float thresholdX = (m->Center().x - mBosses[i]->Center().x + 10);
				float thresholdY = (m->Center().y - mBosses[i]->Bottom() + 10);

				if (m->Velocity().y < 0.0f && (thresholdX <= 250 && thresholdX > -250 && thresholdY <= 10 && thresholdY > 0))
				{
					float explSize = (0.8f, 1.0f);
					float explDuration = (0.5f, 0.6f);
					int explLocX = rand() % 500;
					int explLocY = rand() % 500;
					Explosion* e = new Explosion(Vec2(mBosses[i]->Left() + 120 + explLocX, mBosses[i]->Bottom() - explLocY), mExplosionTex, explSize, explDuration);
					mExplosions.push_back(e);

					int myBossHealth = (mBosses[i]->getHealth() - 1);

					std::cout << ">>> Boss hit! Life left: " << myBossHealth << std::endl;
					Vec2 despawn = Vec2(-1000, -1000);

					mBosses[i]->setHealth(myBossHealth);
					if (myBossHealth == 0)
					{
						//Boss enemy death generates MANY EXPLOSIONS!!:)
						for (int j = 0; j < 35; j++)
						{
							int explLocX2 = rand() % 500;
							int explLocY2 = rand() % 500;
							float explSize2 = (3.0f, 3.5f);
							float explDuration2 = (1.0f, 1.0f);
							Explosion* exp = new Explosion(Vec2(mBosses[i]->Left() + 120 + explLocX2, mBosses[i]->Bottom() - explLocY2), mExplosionTex, explSize2, explDuration2);
							mExplosions.push_back(exp);
						}
						mBosses[i]->SetCenter(despawn);
						boss = false;
						isBossOnScreen = false;
					}

					m->SetCenter(despawn);

				}
			}
		}

		//BONUSENEMY-MISSILE COLLISION 
		for (int i = 0; i < mBonusEnemies.size(); i++){
			float thresholdX = (m->Center().x - mBonusEnemies[i]->Center().x) + 15;
			float thresholdY = (m->Center().y - mBonusEnemies[i]->Center().y) + 15;

			if (m->Velocity().y < 0.0f && (thresholdX <= 55 && thresholdX > 0 && thresholdY <= 55 && thresholdY > 0))
			{
				float explSize = (0.8f, 1.0f);
				float explDuration = (0.5f, 0.6f);
				Explosion* e = new Explosion(Vec2(mBonusEnemies[i]->Center().x, mBonusEnemies[i]->Center().y), mExplosionTex, explSize, explDuration);
				mExplosions.push_back(e);

				
				Vec2 despawn = Vec2(-1000, -1000);

				float powerUpRNG = rand() % 6;
				if (powerUpRNG <= 2)
				{
					std::cout << ">>>Bonus Enemy hit!! GET YOUR POWER UP!! " <<  powerUpRNG << std::endl;
					//Laser Power Up
					PowerUp* myPowerUp = new PowerUp(mBonusEnemies[i]->Center(), mPowerUpTex, 0);
					mPowerUps.push_back(myPowerUp);
				}
				else if (powerUpRNG == 3)
				{
					std::cout << ">>>Bonus Enemy hit!! GET YOUR SHIELD POWER UP!! " << powerUpRNG << std::endl;
					//Shield Power Up	
					PowerUp* myPowerUp = new PowerUp(mBonusEnemies[i]->Center(), mShieldUpTex, 1);
					mPowerUps.push_back(myPowerUp);				
				}
				else 
				{
					std::cout << ">>>Bonus Enemy hit!! GET YOUR HEALTH PACK!! " << powerUpRNG << std::endl;
					//Health Power Up
					PowerUp* myPowerUp = new PowerUp(mBonusEnemies[i]->Center(), mHealthUpTex, 2);
					mPowerUps.push_back(myPowerUp);
				
				}

				
				
				
				mBonusEnemies[i]->SetCenter(despawn);

				m->SetCenter(despawn);



			}

		}



		//MISSILE-MISSILE COLLISION
		//going to do a nested for loop. For each missile, compare its center to every other missile.
		//if the centers are close enough, AND their velocities are negative, that is a missile-missile collision!
		for (int j = 0; j < mMissiles.size(); j++)
		{
			Vec2 missile1Pos = Vec2(mMissiles[i]->Center());
			for (int i = 0; i < mMissiles.size(); i++)
			{
				Vec2 missile2Pos = Vec2(mMissiles[i]->Center());
				float thresholdX = (missile1Pos.x - missile2Pos.x );
				float thresholdY = (missile1Pos.y - missile2Pos.y );
				Vec2 despawn = Vec2(-1000, -1000);
				if ((thresholdX <= 15 && thresholdX > 0 && thresholdY <= 15 && thresholdY > 0))
				{
					//collision occurs; delete

					// create new missile-enemymissile explosion. therefore smallest size
					float explSize = (0.2f, 0.5f);
					float explDuration = (0.2f, 0.5f);
					Explosion* e = new Explosion(Vec2(missile1Pos.x, missile1Pos.y), mExplosionTex, explSize, explDuration);
					mExplosions.push_back(e);
					m->SetCenter(despawn);
				}
			}
		}



		//PLAYER-ENEMYMISSILE COLLISION 

		if (playerAlive)
		{
			float thresholdX = (mPlayer->Center().x - mMissiles[i]->Center().x + 20);
			float thresholdY = (mPlayer->Center().y - mMissiles[i]->Center().y + 20);
			//positive velocity means it's an enemy missile
			if (m->Velocity().y > 0.0f && (thresholdX <= 55 && thresholdX > 0 && thresholdY <= 55 && thresholdY > 0))
			{
				Vec2 despawn = Vec2(-1000, -1000);
				m->SetCenter(despawn);

				// create new player-enemymissile explosion. therefore large size
				float explSize = (1.0f, 1.0f);
				float explDuration = (0.5f, 1.25f);
				Explosion* e = new Explosion(Vec2(mPlayer->Center().x, mPlayer->Center().y), mExplosionTex, explSize, explDuration);
				mExplosions.push_back(e);

				//collision occurs; lower if no shield
				int myPlayerHealth = mPlayer->getHealth();
				if (isShieldUp)
				{
					//delete shield because it takes the hit   
					isShieldUp = false;
					std::cout << ">>>Shield down! You still have " << myPlayerHealth << " life left." << std::endl;

				}
				else 
				{
					myPlayerHealth -= 1;
					mPlayer->setHealth(myPlayerHealth);
					std::cout << ">>>You were hit! Life left: " << myPlayerHealth << std::endl;

					if (myPlayerHealth == 0)
					{
						// create new player-enemymissile explosion. therefore large size
						float explSize = (2.0f, 2.0f);
						float explDuration = (0.5f, 1.25f);
						Explosion* e = new Explosion(Vec2(mPlayer->Center().x, mPlayer->Center().y), mExplosionTex, explSize, explDuration);
						mExplosions.push_back(e);

						std::cout << ">>>You died to an enemy missile!" << std::endl;
						std::cout << ">>>YOU LOSE! Press r to play again...?" << std::endl;
						mPlayer->~Player();

						playerAlive = false;
						delete mPlayer;

					}
				}



				
				
			}
		}
		
			// remove the missile if it went off screen
			if (m->Left() > worldRight || m->Right() < worldLeft || m->Top() > worldBottom || m->Bottom() < worldTop) {
				// missile is out of world bounds: remove it
				delete m;
				mMissiles[i] = mMissiles.back();
				mMissiles.pop_back();
			}
			else {
				// missile is still within world bounds: keep it and move on to the next one
				++i;
			}
		
    }

	

	// update explosions
	for (unsigned i = 0; i < mExplosions.size();) {
		Explosion* e = mExplosions[i];
		e->Update(dt);
		if (e->IsFinished()) {
			delete e;
			mExplosions[i] = mExplosions.back();
			mExplosions.pop_back();
		}
		else {
			++i;
		}
	}

	if (playerAlive)
	{
		//STRONGENEMY-PLAYER COLLISION
		for (int i = 0; i < mStrongEnemies.size(); i++)
		{
			float thresholdX = (mPlayer->Center().x - mStrongEnemies[i]->Center().x) + 20;
			float thresholdY = (mPlayer->Center().y - mStrongEnemies[i]->Center().y) + 20;
			if (thresholdX <= 100 && thresholdX > 0 && thresholdY <= 100 && thresholdY > 0)
			{
				//collision occurs; delete
				std::cout << ">>>You crashed into the enemy!" << std::endl;
				std::cout << ">>>YOU LOSE! Press r to play again...?" << std::endl;

				// create new enemy-player explosion. therefore large size
				float explSize = (2.0f, 2.0f);
				float explDuration = (0.5f, 1.25f);
				Explosion* e = new Explosion(Vec2(mPlayer->Center().x, mPlayer->Center().y), mExplosionTex, explSize, explDuration);
				mExplosions.push_back(e);

				Vec2 despawn = Vec2(-1000, -1000);
				mStrongEnemies[i]->SetCenter(despawn);

				//System::Quit();
				mPlayer->~Player();

				playerAlive = false;
				delete mPlayer;

			}
		}
	}

	if (playerAlive)
	{
		//CRUSHERENEMY-PLAYER COLLISION
		for (int i = 0; i < mCrusherEnemies.size(); i++)
		{
			float thresholdX = (mPlayer->Center().x - mCrusherEnemies[i]->Center().x) + 20;
			float thresholdY = (mPlayer->Center().y - mCrusherEnemies[i]->Center().y) + 20;
			if (thresholdX <= 100 && thresholdX > 0 && thresholdY <= 100 && thresholdY > 0)
			{
				//collision occurs; delete
				std::cout << ">>>You crashed into the enemy!" << std::endl;
				std::cout << ">>>YOU LOSE! Press r to play again...?" << std::endl;

				// create new enemy-player explosion. therefore large size
				float explSize = (2.0f, 2.0f);
				float explDuration = (0.5f, 1.25f);
				Explosion* e = new Explosion(Vec2(mPlayer->Center().x, mPlayer->Center().y), mExplosionTex, explSize, explDuration);
				mExplosions.push_back(e);

				mPlayer->~Player();

				playerAlive = false;
				delete mPlayer;

			}
		}
	}


	//POWERUP-PLAYER COLLISION
	for (int i = 0; i < mPowerUps.size(); i++)
	{
		float thresholdX = (mPlayer->Center().x - mPowerUps[i]->Center().x) + 20;
		float thresholdY = (mPlayer->Center().y - mPowerUps[i]->Center().y) + 20;
		if (thresholdX <= 80 && thresholdX > 0 && thresholdY <= 80 && thresholdY > 0)
		{
			//collision occurs; power up obtained!
			if (mPowerUps[i]->getType() == 0)
			{
				playerPower += 1;
				std::cout << ">>>POWER UP!!! Energy Level: " << playerPower << std::endl;
				if (playerPower == 5)
				{
					boss = true;
				}
			}
			else if (mPowerUps[i]->getType() == 1)
			{
				isShieldUp = true;
				std::cout << ">>>Shield up!!" << std::endl;
			}
			else if (mPowerUps[i]->getType() == 2)
			{

				//bring player health back up to max
				mPlayer->setHealth(3);
				std::cout << ">>>Health up!! You are back at " << mPlayer->getHealth() << " health." << std::endl;


				
			}
			
			Vec2 despawn = Vec2(-1000, -1000);
			mPowerUps[i]->SetCenter(despawn);

		}
	}

	if (playerAlive)
	{
		//ENEMY-PLAYER COLLISION
		for (int i = 0; i < mEnemies.size(); i++)
		{
			float thresholdX = (mPlayer->Center().x - mEnemies[i]->Center().x) + 20;
			float thresholdY = (mPlayer->Center().y - mEnemies[i]->Center().y) + 20;
			if (thresholdX <= 55 && thresholdX > 0 && thresholdY <= 55 && thresholdY > 0)
			{
				//collision occurs; delete
				std::cout << ">>>You crashed into the enemy!" << std::endl;
				std::cout << ">>>YOU LOSE! Press r to play again...?" << std::endl;

				// create new enemy-player explosion. therefore large size
				float explSize = (2.0f, 2.0f);
				float explDuration = (0.5f, 1.25f);
				Explosion* e = new Explosion(Vec2(mPlayer->Center().x, mPlayer->Center().y), mExplosionTex, explSize, explDuration);
				mExplosions.push_back(e);

				Vec2 despawn = Vec2(-1000, -1000);
				mEnemies[i]->SetCenter(despawn);

				//System::Quit();
				mPlayer->~Player();

				playerAlive = false;
				delete mPlayer;

			}
		}
	}


	// update enemies
	for (unsigned i = 0; i < mEnemies.size();) {
		Enemy* e = mEnemies[i];
		e->Update(dt);
		if (e->Left() > worldRight || e->Right() < worldLeft || e->Top() > worldBottom || e->Bottom() < worldTop) {
			delete e;
			mEnemies[i] = mEnemies.back();
			mEnemies.pop_back();
		}
		else {
			++i;
		}
	}

	// update boss
	if (boss)
	{
		for (unsigned i = 0; i < mBosses.size();) {
			Boss* bo = mBosses[i];
			bo->Update(dt);
			if (bo->Left() > worldRight || bo->Right() < worldLeft || bo->Top() > worldBottom || bo->Bottom() < worldTop) {
				delete bo;
				mBosses[i] = mBosses.back();
				mBosses.pop_back();
			}
			else {
				++i;
			}
		}
	}

	// update strong enemies
	for (unsigned i = 0; i < mStrongEnemies.size();) {
		StrongEnemy* se = mStrongEnemies[i];
		se->Update(dt);
		if (se->Left() > worldRight || se->Right() < worldLeft || se->Top() > worldBottom || se->Bottom() < worldTop) {
			delete se;
			mStrongEnemies[i] = mStrongEnemies.back();
			mStrongEnemies.pop_back();
		}
		else {
			++i;
		}
	}

	// update crusher enemies
	for (unsigned i = 0; i < mCrusherEnemies.size();) {
		CrusherEnemy* ce = mCrusherEnemies[i];
		ce->Update(dt);
		
		// keep the crusher within world bounds
		/*if (ce->Left() < worldLeft) {
			ce->SetLeft(worldLeft);
		}
		else if (ce->Right() > worldRight) {
			ce->SetRight(worldRight);
		}*/
		if (ce->Top() < worldTop) {
			ce->SetTop(worldTop);
			ce->SetVelocity(0, 275);
		}
		else if (ce->Bottom() > worldBottom) {
			ce->SetBottom(worldBottom);
			ce->SetVelocity(0, -60);
		}
		else
		{
			++i;
		}

		
	}


	// update bonus enemies
	for (unsigned i = 0; i < mBonusEnemies.size();) {
		BonusEnemy* be = mBonusEnemies[i];
		be->Update(dt);
		if (be->Left() > worldRight || be->Right() < worldLeft || be->Top() > worldBottom || be->Bottom() < worldTop) {
			delete be;
			mBonusEnemies[i] = mBonusEnemies.back();
			mBonusEnemies.pop_back();
		}
		else {
			++i;
		}
	}



	// update shooting stars
	for (unsigned i = 0; i < mShootingStars.size();) {
		Star* s = mShootingStars[i];
		s->Update(dt);
		if (s->Left() > worldRight || s->Right() < worldLeft || s->Top() > worldBottom || s->Bottom() < worldTop) {
			delete s;
			mShootingStars[i] = mShootingStars.back();
			mShootingStars.pop_back();
		}
		else {
			++i;
		}
	}

}

void Game::OnKeyDown(const SDL_KeyboardEvent& kbe)
{
    switch (kbe.keysym.sym) {
    case SDLK_ESCAPE:
        // tell the system that we want to quit
		playerAlive = false;
		System::Quit();
		
        break;
	
//CHEATS!!
	//Power overwhelming
	case SDLK_F1:
		playerPower = 4;
		isShieldUp = true;
		mPlayer->setHealth(10);
		break;
	//
	case SDLK_F2:
		
		break;
	case SDLK_F10:
		boss = true;
		//isBossOnScreen = true;
		break;
	case SDLK_F11:
		if (boss){
			mBosses.clear();
			boss = false;
			isBossOnScreen = false;
		}
		
		break;
    case SDLK_SPACE:
        // fire a missile
		{
			if (playerAlive)
			{
				if (playerPower == 1)
				{
					Missile* missile = new Missile(mPlayer->Center(), mShotTex);
					missile->SetVelocity(0.0f, -450.0f);
					mMissiles.push_back(missile);
					break;
				}
				else if (playerPower == 2)
				{
					Vec2 playerMissileSP1 = Vec2(mPlayer->Center().x - 8, mPlayer->Center().y);
					Missile* missile1 = new Missile(playerMissileSP1, mShotTex);
					missile1->SetVelocity(0.0f, -600.0f);
					mMissiles.push_back(missile1);
					
					Vec2 playerMissileSP2 = Vec2(mPlayer->Center().x + 8, mPlayer->Center().y);
					Missile* missile2 = new Missile(playerMissileSP2, mShotTex);
					missile2->SetVelocity(0.0f, -600.0f);
					mMissiles.push_back(missile2);
					break;
				}
				else if (playerPower == 3)
				{
					Vec2 playerMissileSP1 = Vec2(mPlayer->Center().x - 18, mPlayer->Center().y + 10);
					Missile* missile1 = new Missile(playerMissileSP1, mShotTex);
					missile1->SetVelocity(0.0f, -750.0f);
					mMissiles.push_back(missile1);

					Vec2 playerMissileSP2 = Vec2(mPlayer->Center().x + 0, mPlayer->Center().y);
					Missile* missile2 = new Missile(playerMissileSP2, mShotTex);
					missile2->SetVelocity(0.0f, -750.0f);
					mMissiles.push_back(missile2);
					
					Vec2 playerMissileSP3 = Vec2(mPlayer->Center().x + 18, mPlayer->Center().y + 10);
					Missile* missile3 = new Missile(playerMissileSP3, mShotTex);
					missile3->SetVelocity(0.0f, -750.0f);
					mMissiles.push_back(missile3);
					break;
				}
				else if (playerPower == 4)
				{
					Vec2 playerMissileSP1 = Vec2(mPlayer->Center().x - 24, mPlayer->Center().y + 10);
					Missile* missile1 = new Missile(playerMissileSP1, mShotTex);
					missile1->SetVelocity(-150.0f, -850.0f);
					mMissiles.push_back(missile1);

					Vec2 playerMissileSP2 = Vec2(mPlayer->Center().x + -8, mPlayer->Center().y);
					Missile* missile2 = new Missile(playerMissileSP2, mShotTex);
					missile2->SetVelocity(0.0f, -850.0f);
					mMissiles.push_back(missile2);

					Vec2 playerMissileSP3 = Vec2(mPlayer->Center().x + 8, mPlayer->Center().y);
					Missile* missile3 = new Missile(playerMissileSP3, mShotTex);
					missile3->SetVelocity(0.0f, -850.0f);
					mMissiles.push_back(missile3);

					Vec2 playerMissileSP4 = Vec2(mPlayer->Center().x + 24, mPlayer->Center().y  + 10);
					Missile* missile4 = new Missile(playerMissileSP4, mShotTex);
					missile4->SetVelocity(150.0f, -850.0f);
					mMissiles.push_back(missile4);
				}
				else
				{
					//can't go higher than 4 for now. use 4's implementation
					Vec2 playerMissileSP1 = Vec2(mPlayer->Center().x - 24, mPlayer->Center().y - 25);
					Missile* missile1 = new Missile(playerMissileSP1, mShotTex);
					missile1->SetVelocity(-150.0f, -850.0f);
					mMissiles.push_back(missile1);

					Vec2 playerMissileSP2 = Vec2(mPlayer->Center().x + -8, mPlayer->Center().y - 35);
					Missile* missile2 = new Missile(playerMissileSP2, mShotTex);
					missile2->SetVelocity(0.0f, -850.0f);
					mMissiles.push_back(missile2);

					Vec2 playerMissileSP3 = Vec2(mPlayer->Center().x + 8, mPlayer->Center().y - 35);
					Missile* missile3 = new Missile(playerMissileSP3, mShotTex);
					missile3->SetVelocity(0.0f, -850.0f);
					mMissiles.push_back(missile3);

					Vec2 playerMissileSP4 = Vec2(mPlayer->Center().x + 24, mPlayer->Center().y - 25);
					Missile* missile4 = new Missile(playerMissileSP4, mShotTex);
					missile4->SetVelocity(150.0f, -850.0f);
					mMissiles.push_back(missile4);
				}


				
			}
			break;
        }
	case SDLK_r:
		// Restart the game!
	{
		//Player re-initialization
		playerPower = 1;
		Vec2 spawnPos;
		spawnPos.x = 0.5f * System::GetWindowWidth();
		spawnPos.y = 0.95f * System::GetWindowHeight();
		mPlayer = new Player(spawnPos, mShuttleTex, 3);
		mPlayer->SetSpeed(150.0f);
		//get rid of all missiles and enemies   
		
		mEnemies.clear();
		mMissiles.clear(); askjdh
		mStrongEnemies.clear();
		mCrusherEnemies.clear();
		mBonusEnemies.clear();
		mPowerUps.clear();
		//mShootingStars.clear();    
		playerAlive = true;

		mBosses.clear();
		boss = false;
		isBossOnScreen = false;


		std::cout << "GAME RESTARTED!" << std::endl;
		break;
	}

		
    }
}

void Game::OnKeyUp(const SDL_KeyboardEvent& kbe)
{
}

void Game::OnMouseDown(const SDL_MouseButtonEvent& mbe)
{
}

void Game::OnMouseUp(const SDL_MouseButtonEvent& mbe)
{
}

void Game::OnMouseMotion(const SDL_MouseMotionEvent& mme)
{
}

void Game::OnWindowResized(int w, int h)
{
    std::cout << "Window resized to " << w << 'x' << h << std::endl;
}
