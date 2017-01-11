/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Animation class
*	@author Lukasz
***/
#include "Animation.h"

#include <cmath>

Animation::Animation(const Texture* tex, int numCells, float duration, bool loopable)
: mTex(tex)
, mNumCells(numCells)
, mCellWidth(tex->GetWidth() / numCells)
, mCellHeight(tex->GetHeight())
, mDuration(duration)
, mTime(0.0f)
, mIsLoopable(loopable)
{
}

Animation::~Animation()
{
	// nothing to destroy
}

void Animation::AddTime(float dt)
{
	mTime += dt;

	// see if we've reached or passed the end
	if (mTime >= mDuration) {
		if (mIsLoopable) {
			// wrap around
			mTime = std::fmod(mTime, mDuration);
		}
		else {
			// cap
			mTime = mDuration;
		}
	}
}

bool Animation::FinishedPlaying() const
{
	return mTime == mDuration;
}

void Animation::DrawCurrentCell(SDL_Renderer* renderer, const SDL_Rect* dstRect)
{
	// figure out which cell we should be showing
	int cellIndex;
	if (mTime <= 0.0f) {
		cellIndex = 0;
	}
	else if (mTime >= mDuration) {
		cellIndex = mNumCells - 1;
	}
	else {
		cellIndex = (int)(mTime / mDuration * mNumCells);
	}

	// compute source rectangle of cell in the texture
	SDL_Rect srcRect;
	srcRect.x = cellIndex * mCellWidth;
	srcRect.y = 0;
	srcRect.w = mCellWidth;
	srcRect.h = mCellHeight;

	// draw current cell in the specified screen rectangle
	SDL_RenderCopy(renderer, mTex->GetSDLTexture(), &srcRect, dstRect);
}
