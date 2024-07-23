#pragma once

class Sprite {
    friend class RenderWindow;
public:
    Sprite() : texture(nullptr), renderer(nullptr), width(0), height(0) {}
    Sprite(std::string name, RenderWindow& target);
    Sprite(const Sprite& other); // Copy constructor
    Sprite& operator=(const Sprite& other); // Copy assignment operator
    Sprite(Sprite&& other) noexcept; // Move constructor
    Sprite& operator=(Sprite&& other) noexcept; // Move assignment operator
    ~Sprite(); // Destructor
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int width;
    int height;
};