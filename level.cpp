#include "sdlLib.hpp"

level::level(const std::string &name, RenderWindow &window, int scaler)
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
    defineTiles(scaler);
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
            Sprite tilesetTexture(spriteSheetPath, window);
            alltilesprite.push_back(tilesetTexture);
            int tilesOnWifth = tilesetTexture.width / tileWidth;
            int tilesOnHeight = tilesetTexture.height / tileHeight;
            for (int y = 0; y < tilesOnHeight; y++)
            {
                for (int x = 0; x < tilesOnWifth; x++)
                {
                    int tileIndexInTheTileset = y * tilesOnWifth + x;

                    SDL_Rect srcRect;

                    // get the tile within the sprite sheet
                    srcRect.x = ((tileIndexInTheTileset) % (tilesOnWifth)) * tileWidth;
                    srcRect.y = ((tileIndexInTheTileset) / (tilesOnWifth)) * tileHeight;

                    srcRect.w = tileHeight;
                    srcRect.h = tileHeight;

                    properties p_properties;
                    // get all the properties
                    for (int k = 0; k < tileSetData["tiles"][tileIndexInTheTileset]["properties"].Size(); k++)
                    {
                        if (tileSetData["tiles"][tileIndexInTheTileset]["properties"][k]["name"].GetString() == (std::string) "collision")
                        {
                            p_properties.collision = tileSetData["tiles"][tileIndexInTheTileset]["properties"][k]["value"].GetBool();
                        }
                        if (tileSetData["tiles"][tileIndexInTheTileset]["properties"][k]["name"].GetString() == (std::string) "interactible")
                        {
                            p_properties.text = tileSetData["tiles"][tileIndexInTheTileset]["properties"][k]["value"].GetString();
                        }
                        if (tileSetData["tiles"][tileIndexInTheTileset]["properties"][k]["name"].GetString() == (std::string) "secondLayer")
                        {
                            p_properties.secondLayer = tileSetData["tiles"][tileIndexInTheTileset]["properties"][k]["value"].GetBool();
                        }
                    }
                    spriteSheetTextures[i][tileIndexInTheTileset] = texture(alltilesprite.size() - 1, srcRect, p_properties);
                }
            }
        }
        else
        { // if collection of immages
            for (int j = 0; j < tileSetData["tiles"].Size(); j++)
            {
                std::string spriteSheetPath = tileSetData["tiles"][j]["image"].GetString();
                Sprite tilesetTexture(spriteSheetPath, window);
                alltilesprite.push_back(tilesetTexture);

                // set the source rectangle
                SDL_Rect srcRect;
                srcRect.x = 0;
                srcRect.y = 0;
                srcRect.w = tileWidth;
                srcRect.h = tileHeight;

                properties p_properties;
                // get all the properties
                for (int k = 0; k < tileSetData["tiles"][j]["properties"].Size(); k++)
                {
                    if (tileSetData["tiles"][j]["properties"][k]["name"].GetString() == (std::string) "collision" && tileSetData["tiles"][j]["properties"][k]["value"].GetBool() == true)
                    {
                        p_properties.collision = tileSetData["tiles"][j]["properties"][k]["value"].GetBool();
                    }
                    if (tileSetData["tiles"][j]["properties"][k]["name"].GetString() == (std::string) "interactible")
                    {
                        p_properties.text = tileSetData["tiles"][j]["properties"][k]["value"].GetString();
                    }
                    if (tileSetData["tiles"][j]["properties"][k]["name"].GetString() == (std::string) "secondLayer")
                    {
                        p_properties.secondLayer = tileSetData["tiles"][j]["properties"][k]["value"].GetBool();
                    }
                }
                spriteSheetTextures[i][j] = texture(alltilesprite.size() - 1, srcRect, p_properties);
            }
        }
    }
}
// saves the lites position and size for it to be later read and drawn
void level::defineTiles(int scaler)
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
                dstRect.x = x * tileWidth * scaler;
                dstRect.y = y * tileHeight * scaler;
                dstRect.w = tileWidth * scaler;
                dstRect.h = tileHeight * scaler;
                allTiles[i][tileIndexInTheMap].Texture = spriteSheetTextures[spriteSheetIndex][tileIndexInSpriteSheet];
                allTiles[i][tileIndexInTheMap].setPos(dstRect);
                mapBounds[y][x] = spriteSheetTextures[spriteSheetIndex][tileIndexInSpriteSheet].Properties.collision;
                interactible[y][x] = spriteSheetTextures[spriteSheetIndex][tileIndexInSpriteSheet].Properties.text;
                secondLayer[i][tileIndexInTheMap] = spriteSheetTextures[spriteSheetIndex][tileIndexInSpriteSheet].Properties.secondLayer;
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
            window.render(alltilesprite[allTiles[i][xy].Texture.refS], allTiles[i][xy].Texture.srcRect, allTiles[i][xy].dstRect);
        }
    }
}
void level::renderLVL2(RenderWindow &window)
{
    for (int i = 0; i < nrOfLayers; i++)
    {
        for (int xy = 0; xy < totalNumOfTiles; xy++)
        {
            if (secondLayer[i][xy])
            {
                window.render(alltilesprite[allTiles[i][xy].Texture.refS], allTiles[i][xy].Texture.srcRect, allTiles[i][xy].dstRect);
            }
        }
    }
}
