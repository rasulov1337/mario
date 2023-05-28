#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


struct Object
{
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::FloatRect rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};


struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

class LevelData
{
public:
    bool LoadFromFile(const std::string filename);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
    void Draw(sf::RenderWindow& window);
    sf::Vector2i GetTileSize();
    sf::Sprite GetTile(int id);

    int GetMapWidth() const;
    int GetMapHeight() const;

private:
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;

    std::vector<sf::Rect<int>> subRects;

};

#endif
