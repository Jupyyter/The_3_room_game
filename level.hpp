#pragma once

struct texture
{
    bool collider = false;
    int refS = 0;
    SDL_Rect srcRect;
    texture(){};
    texture(int refS, SDL_Rect srcRect, bool p_collider)
        : refS(refS), srcRect(srcRect), collider(p_collider)
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
    // load level
    level(const std::string &name, RenderWindow &window);
    // render level :)
    void renderLVL(RenderWindow &window);

private:
    // saves the tiles position and size for it to be later read and drawn
    void defineTiles();
    // saving all the sprites within the map as textures
    void defineTextures(RenderWindow &window);
    std::map<int, bool> isDynamicTileSet;
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
