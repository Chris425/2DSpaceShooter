/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Enemy class - similar to missile and they will also be stored in a vector which is dynamically updated at run time.
*	
***/
#include <iostream>

#include "Enemy.h"
#include "System.h"

Enemy::Enemy(const Vec2& pos, const Texture* tex)
: mTex(tex)
, mCenter(pos)
, mVelocity()        // pixels/second
{
	//std::cout << "Creating Enemy" << std::endl;
}

Enemy::~Enemy()
{
	//std::cout << "Destroying Enemy" << std::endl;
}

void Enemy::Update(float dt)
{
	mCenter.x += mVelocity.x * dt;
	mCenter.y += mVelocity.y * dt;
}

void Enemy::Draw(SDL_Renderer* renderer) const
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
