/***
* Christopher Di Conza, Final Project, PROG33921
*
*Header file containing method definitions for game class
***/

#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>

#include <vector>

#include "System.h"
#include "Player.h"
#include "Missile.h"
#include "Enemy.h"
#include "Star.h"
#include "Explosion.h"
#include "StrongEnemy.h"
#include "CrusherEnemy.h"
#include "Boss.h"
#include "BonusEnemy.h"
#include "PowerUp.h"
#include "Shield.h"


class Game
{
	Texture*				mExplosionTex;	//pointers to textures
	Texture*                mShuttleTex; 
    Texture*                mShotTex;
	Texture*                mShot2Tex;
	Texture*                mBackTex;
	Texture*                mStarTex;
	Texture*                mAlienTex;
	Texture*                mStrongAlienTex;
	Texture*				mCrusherAlienTex;
	Texture*                mBossTex;
	Texture*                mBonusAlienTex;
	Texture*                mPowerUpTex;
	Texture*                mShieldUpTex;
	Texture*                mHealthUpTex;
	Texture*				mShieldTex;
	Texture*				mHeartTex;
	Texture*				m1Tex;
	Texture*				m2Tex;
	Texture*				m3Tex;
	Texture*				m4Tex;
	Texture*				mGUITex;

    Player*					mPlayer;
	Shield*					mShield;

    std::vector<Missile*>		mMissiles;
	std::vector<Explosion*>		mExplosions;
	std::vector<Enemy*>			mEnemies;
	std::vector<Star*>			mShootingStars;
	std::vector<StrongEnemy*>	mStrongEnemies;
	std::vector<CrusherEnemy*>	mCrusherEnemies;
	std::vector<Boss*>			mBosses;
	std::vector<BonusEnemy*>	mBonusEnemies;
	std::vector<PowerUp*>		mPowerUps;
	


public:
                            Game();
                            ~Game();

    bool				    Initialize();
    void				    Shutdown();

    void				    Update(float dt);
    void				    Draw(SDL_Renderer* renderer);
    
    void				    OnWindowResized(int w, int h);
    void				    OnKeyDown(const SDL_KeyboardEvent& kbe);
    void				    OnKeyUp(const SDL_KeyboardEvent& kbe);
    void				    OnMouseDown(const SDL_MouseButtonEvent& mbe);
    void				    OnMouseUp(const SDL_MouseButtonEvent& mbe);
    void				    OnMouseMotion(const SDL_MouseMotionEvent& mme);

    float                   WorldLeft() const       { return 0.0f; }
    float                   WorldRight() const      { return (float)System::GetWindowWidth(); }
    float                   WorldTop() const        { return 0.0f; }
    float                   WorldBottom() const     { return (float)System::GetWindowHeight(); }
};

#endif
