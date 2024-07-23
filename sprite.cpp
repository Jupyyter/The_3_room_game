#include "sdlLib.hpp"

Sprite::Sprite(const std::string name, RenderWindow& target) {
    this->renderer = target.renderer;
    this->texture = IMG_LoadTexture(target.renderer, name.c_str()); // loading texture

    if (texture == nullptr) {
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    } else {
        SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height); // obtaining texture dimensions
        // Enable blending for the loaded texture
        SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    }
}

// Helper function to duplicate a texture
SDL_Texture* duplicateTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture, int width, int height) {
    // Create a new texture with the same format and dimensions
    SDL_Texture* newTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!newTexture) {
        std::cout << "Failed to create new texture. Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Enable blending for the new texture
    SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

    // Set the target texture to newTexture
    SDL_SetRenderTarget(renderer, newTexture);

    // Clear the new texture with transparent color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Copy the source texture to the new texture
    SDL_RenderCopy(renderer, srcTexture, nullptr, nullptr);

    // Reset the render target to the default
    SDL_SetRenderTarget(renderer, nullptr);

    return newTexture;
}

// Copy constructor
Sprite::Sprite(const Sprite& other) : width(other.width), height(other.height), renderer(other.renderer) {
    if (other.texture) {
        // Use a helper function to duplicate the texture
        texture = duplicateTexture(other.renderer, other.texture, other.width, other.height);
    } else {
        texture = nullptr;
    }
}

// Copy assignment operator
Sprite& Sprite::operator=(const Sprite& other) {
    if (this == &other) {
        return *this;
    }

    // Clean up existing texture
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    width = other.width;
    height = other.height;
    renderer = other.renderer;

    if (other.texture) {
        // Use a helper function to duplicate the texture
        texture = duplicateTexture(other.renderer, other.texture, other.width, other.height);
    } else {
        texture = nullptr;
    }

    return *this;
}

// Move constructor
Sprite::Sprite(Sprite&& other) noexcept : texture(other.texture), renderer(other.renderer), width(other.width), height(other.height) {
    other.texture = nullptr;
    other.renderer = nullptr;
    other.width = 0;
    other.height = 0;
}

// Move assignment operator
Sprite& Sprite::operator=(Sprite&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    // Clean up existing texture
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    texture = other.texture;
    renderer = other.renderer;
    width = other.width;
    height = other.height;

    other.texture = nullptr;
    other.renderer = nullptr;
    other.width = 0;
    other.height = 0;

    return *this;
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}