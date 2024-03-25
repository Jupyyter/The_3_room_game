#pragma once

struct properties
{
    bool collision=false;
    std::string text="";
    bool secondLayer=false;
};

struct texture
{
    int refS = 0;
    SDL_Rect srcRect;
    properties Properties;
    texture(){};
    texture(int refS, SDL_Rect srcRect, properties p_properties)
        : refS(refS), srcRect(srcRect), Properties(p_properties)
    {
    }

};

struct tile
{
    tile(){};
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
    std::map<int, std::map<int, bool>> mapBounds;
    std::map<int, std::map<int, std::string>> interactible;
    // load level
    level(const std::string &name, RenderWindow &window,int scaler);
    // render level :)
    void renderLVL(RenderWindow &window);
    void renderLVL2(RenderWindow &window);

private:
    // saves the tiles position and size for it to be later read and drawn
    void defineTiles(int scaler);
    // saving all the sprites within the map as textures
    void defineTextures(RenderWindow &window);
    std::map<int, std::map<int, bool>> secondLayer;
    std::map<int, std::map<int, texture>> spriteSheetTextures;
    std::map<int, std::map<int, tile>> allTiles;
    std::vector<Sprite> alltilesprite;
    // deal with JSON files
    rapidjson::Document mapData;
    int totalNumOfTiles;
    int nrOfLayers;
    int mapWidth;
    int mapHeight;
    int tileWidth;
    int tileHeight;
};