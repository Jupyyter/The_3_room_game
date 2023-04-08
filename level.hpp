#pragma once
#include "SDL2/SDL.h"
#include <string>
#include <vector>
#include <map>
#include <fstream> //dealing with files
#include "rapidjson/document.h"
#include "renderWindow.hpp"
#include "vector2.hpp"

struct texture
{
    SDL_Texture *sheet = NULL;
    SDL_Rect srcRect;
    texture(){};
    texture(SDL_Texture *tset, SDL_Rect p_srcRect)
        : sheet(tset), srcRect(p_srcRect)
    {
    }
};

struct tile
{
    tile(){};
    SDL_Texture *sheet = NULL;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    texture Texture;
    void getBetterSkillIssue()
    {
        sheet = Texture.sheet;
        srcRect = Texture.srcRect;
    }
    void draw(RenderWindow &window)
    {
        window.render(sheet, srcRect, dstRect);
    }
    void setPos(SDL_Rect p_dstRect)
    {
        dstRect = p_dstRect;
    }
};

class level
{
public:
    // load level
    level(const std::string &name, RenderWindow &window);
    // render level :)
    void renderLVL(RenderWindow &window);

private:
    // saves the lites position and size for it to be later read and drawn
    void defineTiles();
    // saving all the sprites within the map as textures
    void defineTextures(RenderWindow &window);
    std::map<int, bool> isDynamicTileSet;
    std::map<int, std::map<int, texture>> spriteSheetTextures;
    std::map<int, std::map<int, tile>> allTiles;
    // deal with JSON files
    rapidjson::Document mapData;
    int totalNumOfTiles;
    int nrOfLayers;
    int mapWidth;
    int mapHeight;
    int tileWidth;
    int tileHeight;
};
