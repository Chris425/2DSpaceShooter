/***
* Christopher Di Conza, Final Project Assignment, PROG33921
*
*	Explosion header
***/
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Animation.h"
#include "Vec2.h"

class Explosion
{
	Animation*              mAnim;
	Vec2                    mCenter;
	float                   mScale;

public:
	Explosion(const Vec2& pos, const Texture* tex);
	Explosion(const Vec2& pos, const Texture* tex, float scale, float duration);
	~Explosion();

	void					Update(float dt);

	bool                    IsFinished() const;

	void					Draw(SDL_Renderer* renderer) const;
};

#endif
