#include "sdlLib.hpp"

Sprite::Sprite(std::string name, RenderWindow target) {
    this->texture = IMG_LoadTexture(target.renderer, name.c_str()); // loading texture

    if (texture == nullptr)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height); // obtaining texture dimensions
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}