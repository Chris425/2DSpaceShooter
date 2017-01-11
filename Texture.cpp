/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Texture convenience class which obfuscates the SDL methods required to work with them. 
*	Facilitates the loading and destruction of textures
***/
#include <iostream>

#include <SDL_image.h>

#include "Texture.h"

Texture::Texture(SDL_Texture* tex, int width, int height)
    : mSDLTex(tex)
    , mWidth(width)
    , mHeight(height)
{ }


Texture::~Texture()
{
	//ensure it is not null - which would indicate that it failed to initialize the texture
    if (mSDLTex) {
        SDL_DestroyTexture(mSDLTex);
    }
}


Texture* Texture::Load(const std::string& path, SDL_Renderer* renderer)
{
    // load an image into an SDL_Surface (stored in RAM)
    SDL_Surface* surf = IMG_Load(path.c_str());
    if (!surf) {
        std::cerr << "*** Failed to load image: " << IMG_GetError() << std::endl;
        return NULL;
    }

    // create an SDL_Texture from the surface (stored in GPU DRAM)
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    // free the surface, which is no longer needed
    SDL_FreeSurface(surf);

    if (tex) { //if the texture is valid and loaded properly
        // query texture size
        int width, height;
        SDL_QueryTexture(tex, NULL, NULL, &width, &height);

        // return a dynamically allocated Texture object
        return new Texture(tex, width, height);

    } else {
        // texture creation failed
        std::cerr << "*** Failed to create texture: " << SDL_GetError() << std::endl;
        return NULL;
    }
}


void Texture::Destroy(Texture* tex)
{
    delete tex;
}
