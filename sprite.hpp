#pragma once

class Sprite{
    friend class RenderWindow;
public:
Sprite() : texture(nullptr){}
    Sprite(std::string name, RenderWindow target);
    ~Sprite(); // Destructor
    SDL_Texture* texture;
    int width;
    int height;
};