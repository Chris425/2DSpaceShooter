/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Explosion class  
*	@author Lukasz
***/
#include <iostream>

#include "Explosion.h"
#include "System.h"

Explosion::Explosion(const Vec2& pos, const Texture* tex)
: Explosion(pos, tex, 1.0f, 0.85f)  // delegate construction
{
}

Explosion::Explosion(const Vec2& pos, const Texture* tex, float scale, float duration)
: mAnim(NULL)
, mCenter(pos)
, mScale(scale)
{
	if (tex) {
		mAnim = new Animation(tex, 16, duration, false);
	}
	//std::cout << "Creating Explosion" << std::endl;
}

Explosion::~Explosion()
{
	//std::cout << "Destroying Explosion" << std::endl;

	delete mAnim;   // ok even if NULL
}

void Explosion::Update(float dt)
{
	if (mAnim) {
		mAnim->AddTime(dt);
	}
}

bool Explosion::IsFinished() const
{
	if (mAnim) {
		return mAnim->FinishedPlaying();
	}
	else {
		return true;
	}
}

void Explosion::Draw(SDL_Renderer* renderer) const
{
	if (mAnim) {

		// apply scaling
 		float scaledWidth = mScale * mAnim->CellWidth();
		float scaledHeight = mScale * mAnim->CellHeight();

		// compute rectangle on screen
		SDL_Rect screenRect;
		screenRect.w = (int)scaledWidth;
		screenRect.h = (int)scaledHeight;
		screenRect.x = (int)(mCenter.x - scaledWidth / 2);
		screenRect.y = (int)(mCenter.y - scaledHeight / 2);

		// draw current animation cell
		mAnim->DrawCurrentCell(renderer, &screenRect);

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
