#pragma once

class Sprite{
    friend class RenderWindow;
public:
    Sprite(std::string name, RenderWindow target);
    SDL_Texture* texture;
    int width;
    int height;
};