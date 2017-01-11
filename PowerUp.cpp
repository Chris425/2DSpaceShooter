/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Power up class will function similarly to enemies and I will model their movement and collision 
*	with the player in the same way. 
*
*	TYPES: 
*	0 = powerUp
*	1 = shieldUp
*	2 = healthUp
*
***/
#include <iostream>

#include "PowerUp.h"
#include "System.h"

PowerUp::PowerUp(const Vec2& pos, const Texture* tex, int type)
: mTex(tex)
, mCenter(pos)
, mVelocity()   
, mType(type)
{
	
}

PowerUp::~PowerUp()
{
	
}

void PowerUp::Update(float dt)
{
	mCenter.x += mVelocity.x * dt;
	mCenter.y += mVelocity.y * dt;
}

void PowerUp::Draw(SDL_Renderer* renderer) const
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
