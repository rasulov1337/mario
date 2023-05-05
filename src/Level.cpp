#include "Level.h"

#include <iostream>
#include "tinyxml2.h"

using namespace tinyxml2;

int Object::GetPropertyInt(std::string name)
{
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name)
{
    return properties[name];
}


 Level::Level(const char* filename) {
    XMLDocument levelFile;

    int errorCode = levelFile.LoadFile(filename);
    if (errorCode != XML_SUCCESS) {
        std::cerr << "Error! Couldn't open the map file! Error code: " << errorCode << std::endl;
        exit(-1);
    }

    XMLElement* map = levelFile.FirstChildElement("map");

    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    // ����� �������� �������� � ������������� ������� �����
    XMLElement* tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    // source - ���� �� �������� � ���������� image
    XMLElement* image = tilesetElement->FirstChildElement("image");
    std::string imagepath = "assets/" +std::string(image->Attribute("source"));

    // �������� ��������� �������
    sf::Image img;
    if (!img.loadFromFile(imagepath))
    {
        std::cerr << "Failed to load tile sheet." << std::endl;
        exit(-1);
    }

    // ������ �������� �� �����������
    tilesetImage.loadFromImage(img);
    // �������������� ���������
    tilesetImage.setSmooth(false);

    // �������� ���������� �������� � ����� ��������
    int columns = tilesetImage.getSize().x / tileWidth;
    int rows = tilesetImage.getSize().y / tileHeight;

    // �������, ���� ���
    // � �� ��� ���� ���� ����� ����, � ��� ���� ��� �������
    columns = 33;
    rows = 28;

    // ������ �� ��������������� ����������� (TextureRect)
    std::map<int, sf::Rect<int>> subRects;
    //std::vector<sf::Rect<int>> subRects;

    int id = 0;
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
        {
            sf::Rect<int> rect;

            rect.top = y * tileHeight + (y + 1) * 2 - 1;
            rect.height = tileHeight;
            rect.left = x * tileWidth + (x + 1) * 2 - 1;
            rect.width = tileWidth;

            //std::cout << "ID=" << id << "(" << rect.left << "; " << rect.top << ")\n";

            //subRects.push_back(rect);
            subRects[id] = rect;
            ++id;
        }

    // ������ �� ������
    XMLElement* layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;

        // ���� ������������ opacity, �� ������ ������������ ����, ����� �� ��������� �����������
        if (layerElement->Attribute("opacity") != NULL)
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;
        }

        // ��������� <data>
        XMLElement* layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        // ��������� <tile> - �������� ������ ������� ����
        XMLElement* tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            exit(-1);
        }

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            int tileGID = 0;

            if (tileElement->Attribute("gid"))
                tileGID = std::atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            // ������������� TextureRect ������� �����
            if (subRectToUse >= 0)
            {
                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                //sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width)
            {
                x = 0;
                y++;
                if (y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }
    // ������ � ���������
    XMLElement* objectGroupElement;
    // ���� ���� ���� ��������
    if (map->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            // ��������� <object>
            XMLElement* objectElement = objectGroupElement->FirstChildElement("object");
            std::string groupName = objectGroupElement->Attribute("name");


            while (objectElement)
            {
                // �������� ��� ������ - ���, ���, �������, etc
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != NULL)
                {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                }
                else
                {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                // ��������� �������
                Object object;
                object.name = groupName;
                object.sprite = sprite;

                sf::FloatRect objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                // "����������" �������
                XMLElement* properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    XMLElement* prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while (prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                // ������ ������ � ������
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }
}



Object Level::GetObject(std::string name)
{
    // ������ ������ ������ � �������� ������
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
    // ��� ������� � �������� ������
    std::vector<Object> vec;
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            vec.push_back(objects[i]);

    return vec;
}

sf::Vector2i Level::GetTileSize()
{
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow& window)
{
    // ������ ��� ����� (������� �� ������!)
    for (int layer = 0; layer < layers.size(); layer++)
        for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
            window.draw(layers[layer].tiles[tile]);
}
