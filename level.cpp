#include "level.hpp"
level::level(const std::string &name, RenderWindow &window)
{
    // open the file
    std::ifstream mapFile(name);

    // read the file into a string
    std::string mapJson((std::istreambuf_iterator<char>(mapFile)),
                        std::istreambuf_iterator<char>());

    mapData.Parse(mapJson.c_str());

    mapWidth = mapData["width"].GetInt();
    mapHeight = mapData["height"].GetInt();
    tileWidth = mapData["tilewidth"].GetInt();
    tileHeight = mapData["tileheight"].GetInt();
    totalNumOfTiles = mapHeight * mapWidth;

    defineTextures(window);
    defineTiles();
}
// saving all the sprites within the map as textures
void level::defineTextures(RenderWindow &window)
{
    for (int i = 0; i < mapData["tilesets"].Size(); i++)
    {
        // obtaining the details of each png
        std::string tileSetFilePath = mapData["tilesets"][i]["source"].GetString();
        std::ifstream tileSetFile(tileSetFilePath);
        std::string tileSetJson((std::istreambuf_iterator<char>(tileSetFile)),
                                std::istreambuf_iterator<char>());
        rapidjson::Document tileSetData;
        tileSetData.Parse(tileSetJson.c_str());

        if (tileSetData["columns"].GetInt() != 0)
        { // if 1 sprite sheet with multiple immages
            std::string spriteSheetPath = tileSetData["image"].GetString();
            SDL_Texture *tilesetTexture = window.loadTexture(spriteSheetPath.c_str());
            int spriteSheetWifth;
            int spriteSheetHeight;
            SDL_QueryTexture(tilesetTexture, NULL, NULL, &spriteSheetWifth, &spriteSheetHeight);
            int tilesOnWifth = spriteSheetWifth / tileWidth;
            int tilesOnHeight = spriteSheetHeight / tileHeight;
            for (int y = 0; y < tilesOnHeight; y++)
            {
                for (int x = 0; x < tilesOnWifth; x++)
                {
                    SDL_Rect srcRect;

                    // get the tile within the sprite sheet
                    srcRect.x = ((y * tilesOnWifth + x) % (tilesOnWifth)) * tileWidth;
                    srcRect.y = ((y * tilesOnWifth + x) / (tilesOnWifth)) * tileHeight;

                    srcRect.w = tileHeight;
                    srcRect.h = tileHeight;

                    spriteSheetTextures[i][y * tilesOnWifth + x] = texture(tilesetTexture, srcRect);
                }
            }
        }
        else
        { // if collection of immages
            isDynamicTileSet[i] = true;
            for (int j = 0; j < tileSetData["tiles"].Size(); j++)
            {
                std::string spriteSheetPath = tileSetData["tiles"][j]["image"].GetString();
                SDL_Texture *tilesetTexture = window.loadTexture(spriteSheetPath.c_str());

                // set the source rectangle
                SDL_Rect srcRect;
                srcRect.x = 0;
                srcRect.y = 0;
                srcRect.w = tileWidth;
                srcRect.h = tileHeight;

                spriteSheetTextures[i][j] = texture(tilesetTexture, srcRect);
            }
        }
    }
}
// saves the lites position and size for it to be later read and drawn
void level::defineTiles()
{
    // loop through all the layers
    nrOfLayers = mapData["layers"].Size();
    for (int i = 0; i < nrOfLayers; i++)
    {
        // Extract the necessary information
        const rapidjson::Value &layerInInstance = mapData["layers"][i]["data"];

        // if this layer isn't a tile layer, continue
        std::string type = mapData["layers"][i]["type"].GetString();
        if (type != "tilelayer")
        {
            continue;
        }

        // set up all the tile classes within allTiles
        for (int y = 0; y < mapHeight; y++)
        {
            for (int x = 0; x < mapWidth; x++)
            {
                int tileIndexInTheMap = y * mapWidth + x;

                int tileIdInJsonFile = layerInInstance[tileIndexInTheMap].GetInt();
                if (tileIdInJsonFile == 0)
                { // 0 means no tile to waste time with
                    continue;
                }

                // to know what tileSet i use
                int spriteSheetIndex = 0;
                for (int j = 0; j < mapData["tilesets"].Size(); j++)
                {
                    if (tileIdInJsonFile >= mapData["tilesets"][j]["firstgid"].GetInt())
                    {
                        spriteSheetIndex = j;
                    }
                }

                // tileIndexInSpriteSheet
                int tileIndexInSpriteSheet = tileIdInJsonFile - mapData["tilesets"][spriteSheetIndex]["firstgid"].GetInt();

                SDL_Rect dstRect;
                dstRect.x = x * tileWidth;
                dstRect.y = y * tileHeight;
                dstRect.w = tileWidth;
                dstRect.h = tileHeight;
                allTiles[i][tileIndexInTheMap].Texture = spriteSheetTextures[spriteSheetIndex][tileIndexInSpriteSheet];
                allTiles[i][tileIndexInTheMap].setPos(dstRect);
                allTiles[i][tileIndexInTheMap].getBetterSkillIssue();
            }
        }
    }
}
void level::renderLVL(RenderWindow &window)
{
    for (int i = 0; i < nrOfLayers; i++)
    {
        for (int xy = 0; xy < totalNumOfTiles; xy++)
        {
            allTiles[i][xy].draw(window);
            // allTiles[i][vector2(x,y)].draw(window);
        }
    }
}
