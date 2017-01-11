/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Strong enemy class. Essentially a reskin of the enemy class but it will take more hits to die - 
*	thus we implement a health member variable to track enemy hitpoints.
***/

#include <iostream>

#include "StrongEnemy.h"
#include "System.h"

StrongEnemy::StrongEnemy(const Vec2& pos, const Texture* tex, int health)
: mTex(tex)
, mCenter(pos)
, mVelocity()        // pixels/second
, mHealth(health)
{
//	std::cout << "Creating StrongEnemy" << std::endl;
}

StrongEnemy::~StrongEnemy()
{
//	std::cout << "Destroying StrongEnemy" << std::endl;
}

void StrongEnemy::Update(float dt)
{
	mCenter.x += mVelocity.x * dt;
	mCenter.y += mVelocity.y * dt;
}

void StrongEnemy::Draw(SDL_Renderer* renderer) const
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
