/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Boss enemy class. Essentially a reskin of the enemy class but it will take more hits to die -
*	thus we implement a health member variable to track enemy hitpoints.
*	It will also spawn enemies to help it.
***/

#include <iostream>

#include "Boss.h"
#include "System.h"

Boss::Boss(const Vec2& pos, const Texture* tex, int health)
: mTex(tex)
, mCenter(pos)
, mVelocity()        // pixels/second
, mHealth(health)
{
	//	std::cout << "Creating Boss" << std::endl;
}

Boss::~Boss()
{
	//	std::cout << "Destroying Boss" << std::endl;
}

void Boss::Update(float dt)
{
	mCenter.x += mVelocity.x * dt;
	mCenter.y += mVelocity.y * dt;
}

void Boss::Draw(SDL_Renderer* renderer) const
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
