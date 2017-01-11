/***
* Christopher Di Conza, Final Project, PROG33921
*
*	PowerUp header
***/
#ifndef POWERUP_H_
#define POWERUP_H_

#include "Texture.h"
#include "Vec2.h"

class PowerUp
{
	const Texture*          mTex;
	Vec2                    mCenter;
	Vec2                    mVelocity;
	int						mType;

public:
	PowerUp(const Vec2& pos, const Texture* tex, int type);
	~PowerUp();

	int						getType()						{ return mType; }
	const Vec2&             Center() const                  { return mCenter; }
	void                    SetCenter(const Vec2& pos)      { mCenter = pos; }
	void                    SetCenter(float x, float y)     { mCenter = Vec2(x, y); }

	const Vec2&             Velocity() const                { return mVelocity; }
	void                    SetVelocity(const Vec2& vel)    { mVelocity = vel; }
	void                    SetVelocity(float x, float y)   { mVelocity = Vec2(x, y); }

	float                   Width() const                   { return (float)mTex->GetWidth(); }
	float                   Height() const                  { return (float)mTex->GetHeight(); }

	float                   Left() const                    { return mCenter.x - 0.5f * Width(); }
	float                   Right() const                   { return mCenter.x + 0.5f * Width(); }
	float                   Top() const                     { return mCenter.y - 0.5f * Height(); }
	float                   Bottom() const                  { return mCenter.y + 0.5f * Height(); }

	void                    SetLeft(float x)                { mCenter.x = x + 0.5f * Width(); }
	void                    SetRight(float x)               { mCenter.x = x - 0.5f * Width(); }
	void                    SetTop(float y)                 { mCenter.y = y + 0.5f * Height(); }
	void                    SetBottom(float y)              { mCenter.y = y - 0.5f * Height(); }

	void					Update(float dt);

	void					Draw(SDL_Renderer* renderer) const;
};

#endif
