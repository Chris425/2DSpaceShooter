/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Missile class. This is shared between player and enemy missiles.
*	A vector will be maintained for each missile and will be dynamically updated during the game's update method.
***/

#include <iostream>

#include "Missile.h"
#include "System.h"

Missile::Missile(const Vec2& pos, const Texture* tex)
    : mTex(tex)
    , mCenter(pos)
    , mVelocity()        // pixels/second
{
	//std::cout << "Creating Missile" << std::endl;
}

Missile::~Missile()
{
   // std::cout << "Destroying Missile" << std::endl;
}

void Missile::Update(float dt)
{
    mCenter.x += mVelocity.x * dt;
    mCenter.y += mVelocity.y * dt;
}

void Missile::Draw(SDL_Renderer* renderer) const
{
    // check if we have a valid texture
    if (mTex) {

        // compute rectangle on screen
        SDL_Rect screenRect;
        screenRect.w = mTex->GetWidth();
        screenRect.h = mTex->GetHeight();
        screenRect.x = (int)(mCenter.x - mTex->GetWidth() / 2);
        screenRect.y = (int)(mCenter.y - mTex->GetHeight() / 2);

        // draw textured rectangle
        SDL_RenderCopy(renderer, mTex->GetSDLTexture(), NULL, &screenRect);

    } else {
        // draw a placeholder
        SDL_Rect screenRect;
        screenRect.w = 64;
        screenRect.h = 64;
        screenRect.x = (int)(mCenter.x - screenRect.w / 2);
        screenRect.y = (int)(mCenter.y - screenRect.h / 2);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &screenRect);
    }
}
