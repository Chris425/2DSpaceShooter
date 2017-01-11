/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Star class; essentially a copy of missile. Small stars will be instantiated and added just over the background layer,
*	but below the player and enemies.
*	They will move down the screen at various speeds to give the illusion of movement as the player moves across space, with
*	a background containing many stars at various distances
***/

#include <iostream>

#include "Star.h"
#include "System.h"

Star::Star(const Vec2& pos, const Texture* tex)
: mTex(tex)
, mCenter(pos)
, mVelocity()        // pixels/second
{
}

Star::~Star()
{
	//std::cout << "Destroying Shooting Star" << std::endl;
}

void Star::Update(float dt)
{
	mCenter.x += mVelocity.x * dt;
	mCenter.y += mVelocity.y * dt;
}

void Star::Draw(SDL_Renderer* renderer) const
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
