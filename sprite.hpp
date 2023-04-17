#pragma once

class Sprite{
    friend class RenderWindow;
public:
    Sprite(std::string name, RenderWindow target);

protected:
    SDL_Texture* texture;

public:
    int width;
    int height;
};
