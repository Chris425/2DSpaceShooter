/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Shield class - an energy shield is acquired from power ups. It draws a graphic on screen that follows player movement
*	once hit, it will be removed along with the incoming enemy missile and the player is no longer protected
***/
#include <iostream>

#include "Shield.h"
#include "System.h"

Shield::Shield(const Vec2& pos, const Texture* tex)
: mTex(tex)
, mCenter(pos)
, mSpeed(100.0f)        // pixels/second
{
	std::cout << "Shield activated!" << std::endl;
}

Shield::~Shield()
{
	std::cout << "Shield destroyed!" << std::endl;
}

void Shield::Update(float dt) //delta time - amount of time since last frame (in seconds)
{
	const Uint8* keys = System::GetKeyStates();

	if (keys[SDL_SCANCODE_D]) {
		mCenter.x += mSpeed * (2.5 * dt);
	}
	if (keys[SDL_SCANCODE_A]) {
		mCenter.x -= mSpeed * (2.5* dt);
	}
	if (keys[SDL_SCANCODE_W]) {
		mCenter.y -= mSpeed * (2.5 * dt);
	}
	if (keys[SDL_SCANCODE_S]) {
		mCenter.y += mSpeed * (2.5 * dt);
	}
}

//draw method called for all entities
void Shield::Draw(SDL_Renderer* renderer) const
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

	}
	else {
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
