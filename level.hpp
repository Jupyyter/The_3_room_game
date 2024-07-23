#pragma once

struct properties
{
    bool collision = false;
    std::string text = "";
    bool secondLayer = false;
};

struct texture
{
    int refS = 0;
    SDL_Rect srcRect;
    properties Properties;
    texture() = default;
    texture(int refS, SDL_Rect srcRect, properties p_properties)
        : refS(refS), srcRect(srcRect), Properties(p_properties)
    {
    }
};

struct tile
{
    SDL_Rect dstRect;
    texture Texture;
    void setPos(SDL_Rect p_dstRect)
    {
        dstRect = p_dstRect;
    }
};

class level
{
public:
    level(const std::string &name, RenderWindow &window, int scaler);
    ~level();

    void renderLVL(RenderWindow &window);
    void renderLVL2(RenderWindow &window);

    std::map<int, std::map<int, bool>> mapBounds;
    std::map<int, std::map<int, std::string>> interactible;

private:
    void defineTiles(int scaler);
    void defineTextures(RenderWindow &window);
    void clearOldLevelData();

    std::map<int, std::map<int, bool>> secondLayer;
    std::map<int, std::map<int, texture>> spriteSheetTextures;
    std::map<int, std::map<int, tile>> allTiles;
    std::vector<Sprite> alltilesprite;
    rapidjson::Document mapData;

    int totalNumOfTiles = 0;
    int nrOfLayers = 0;
    int mapWidth = 0;
    int mapHeight = 0;
    int tileWidth = 0;
    int tileHeight = 0;
};