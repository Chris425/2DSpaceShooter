/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Animation header
***/
#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SDL.h>

#include "Texture.h"

class Animation
{
	const Texture*              mTex;

	int                         mNumCells;
	int                         mCellWidth;
	int                         mCellHeight;

	float                       mDuration;          // total duration in seconds
	float                       mTime;              // current time position (in seconds)

	bool                        mIsLoopable;

public:
	Animation(const Texture* tex, int numCells, float duration, bool loopable);
	~Animation();

	int                         CellWidth() const           { return mCellWidth; }
	int                         CellHeight() const          { return mCellHeight; }

	void                        AddTime(float dt);

	bool                        FinishedPlaying() const;

	void                        DrawCurrentCell(SDL_Renderer* renderer, const SDL_Rect* dstRect);
};

#endif
