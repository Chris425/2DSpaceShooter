/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Crusher enemy class. Has hitpoints and different AI such that it will attempt to crush the player. 
*	Therefore it also doesn't despawn when it reaches the world edges!
***/

#include <iostream>

#include "CrusherEnemy.h"
#include "System.h"

CrusherEnemy::CrusherEnemy(const Vec2& pos, const Texture* tex, int health)
: mTex(tex)
, mCenter(pos)
, mVelocity()        // pixels/second
, mHealth(health)
{
	//	std::cout << "Creating CrusherEnemy" << std::endl;
}

CrusherEnemy::~CrusherEnemy()
{
	//	std::cout << "Destroying CrusherEnemy" << std::endl;
}

void CrusherEnemy::Update(float dt)
{
	mCenter.x += mVelocity.x * dt;
	mCenter.y += mVelocity.y * dt;
}

void CrusherEnemy::Draw(SDL_Renderer* renderer) const
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
