/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Bonus Enemy class - this is a special, elusive enemy that moves quickly but drops a power up if you can catch it!
*	This class is verbose and will announce in std::cout when an enemy is being created or destroyed
*
***/
#include <iostream>

#include "BonusEnemy.h"
#include "System.h"

BonusEnemy::BonusEnemy(const Vec2& pos, const Texture* tex)
: mTex(tex)
, mCenter(pos)
, mVelocity()        // pixels/second
{
	//std::cout << ">>>CREATING BONUS ENEMY!!!" << std::endl;
}

BonusEnemy::~BonusEnemy()
{
//	std::cout << "Bonus enemy died!" << std::endl;
}

void BonusEnemy::Update(float dt)
{
	mCenter.x += mVelocity.x * dt;
	mCenter.y += mVelocity.y * dt;
}

void BonusEnemy::Draw(SDL_Renderer* renderer) const
{
	if (mTex) {
		SDL_Rect screenRect;
		screenRect.w = mTex->GetWidth();
		screenRect.h = mTex->GetHeight();
		screenRect.x = (int)(mCenter.x - mTex->GetWidth() / 2);
		screenRect.y = (int)(mCenter.y - mTex->GetHeight() / 2);
		SDL_RenderCopy(renderer, mTex->GetSDLTexture(), NULL, &screenRect);

	}
	else {
		SDL_Rect screenRect;
		screenRect.w = 64;
		screenRect.h = 64;
		screenRect.x = (int)(mCenter.x - screenRect.w / 2);
		screenRect.y = (int)(mCenter.y - screenRect.h / 2);

		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderFillRect(renderer, &screenRect);
	}
}
