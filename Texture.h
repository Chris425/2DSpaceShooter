/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Texture header 
***/

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>
#include <SDL.h>

class Texture
{
    SDL_Texture*        mSDLTex;
    int                 mWidth;
    int                 mHeight;

    // note that the constructor and destructor are private!

                        Texture(SDL_Texture* tex, int width, int height);
                        ~Texture();
public:

    // use this factory interface to create/destroy instances

    static Texture*     Load(const std::string& path, SDL_Renderer* renderer); //factory function. it uses a reference!
    static void         Destroy(Texture* tex);

    // instance methods (only getters: immutable class)

    SDL_Texture*        GetSDLTexture() const       { return mSDLTex; }

    int                 GetWidth() const            { return mWidth; }
    int                 GetHeight() const           { return mHeight; }
};

#endif
