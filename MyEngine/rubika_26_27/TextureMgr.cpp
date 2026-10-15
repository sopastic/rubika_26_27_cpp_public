#include "TextureMgr.h"
#include "Globals.h"
#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>
#endif
#include <iostream>

#include "Logger.h"

void TextureMgr::Init()
{
    gData.DebugMgr->RegisterDebugableWindow("Texture", this);
}

void TextureMgr::Shut()
{
    gData.DebugMgr->UnregisterDebugableWindow("Texture");
}

bool TextureMgr::LoadTexture(const std::filesystem::path& path)
{
    if (!isFileExists(path))
    {
        Logger::Warning("Texture doesn't exist");
        return false;
    }
    Logger::Info("Texture exist");
    
    std::string pathStr = path.string();
    pathStr.replace(pathStr.length()-3, 3, "xml");
    if (!isMetaExists(pathStr))
    {
        Logger::Warning("Metadata doesn't exist");
        return false;
    }
    Logger::Info("Metadata exist");
    
    const char* pathXmlChar = pathStr.c_str();
    rapidxml::file<> xmlFile = rapidxml::file<>(pathXmlChar);
    rapidxml::xml_document<> doc;
    
    try{doc.parse<0>(xmlFile.data());}
    catch (std::exception& e)
    {
        Logger::Warning("Failed to parse XML file");
        std::cerr << e.what() << std::endl;
    }
    
    TextureData textureData = createTextureData(doc);
    const sf::Texture texture(path);
    textureData.texture = texture;
    
    std::string fileName = path.filename().string();
    fileName.erase(fileName.find_last_of('.'));
    textures.insert({fileName, textureData});

    return true;
}

bool TextureMgr::isFileExists(const std::filesystem::path& path)
{
    return std::filesystem::exists(path);
}

bool TextureMgr::isMetaExists(const std::string& path)
{
    return std::filesystem::exists(path);
}

TextureData TextureMgr::createTextureData(rapidxml::xml_document<>& doc)
{
    TextureData* textureData = new TextureData();
    rapidxml::xml_node<> *firstNode = doc.first_node();
    
    if (strcmp(firstNode->name(), "Animations") != 0 && strcmp(firstNode->name(), "Backgrounds") != 0)
    {
        Logger::Warning("First node is not valid");
        return *textureData;
    }
    
    if (strcmp(firstNode->name(), "Animations") == 0)
    {
        textureData->type = TextureData::Animation;
        parseAnimData(*textureData, firstNode);
        std::cout << textureData->animationsData.size() << "\n";
    }
    else if (strcmp(firstNode->name(), "Backgrounds") == 0)
    {
        textureData->type = TextureData::Background;
        parseStaticData(*textureData, firstNode);
    }
    return *textureData;
}

void TextureMgr::parseStaticData(TextureData& textureData, const rapidxml::xml_node<>* firstNode)
{
    rapidxml::xml_node<> *firstTile = firstNode->first_node(); //first tile
    rapidxml::xml_node<> *previousTile;
    rapidxml::xml_node<> *newTile = firstTile;
        
    bool isDone = false;
    while (!isDone)
    {
        StaticTileData staticTileData;
        std::string tileName = newTile->first_attribute()->value();
            
        rapidxml::xml_node<> *valueX = newTile->first_node(); //1 value
        staticTileData.StartX = int(valueX->value());
            
        rapidxml::xml_node<> *valueY = valueX->next_sibling(); //2 value
        staticTileData.StartY = int(valueY->value());
            
        rapidxml::xml_node<> *valueSizeX = valueY->next_sibling(); //3 value
        staticTileData.SizeX = int(valueSizeX->value());
            
        rapidxml::xml_node<> *valueSizeY = valueSizeX->next_sibling(); //4 value
        staticTileData.SizeY = int(valueSizeY->value());
            
        rapidxml::xml_node<> *valueRevertedX = valueSizeY->next_sibling(); //5 value
        staticTileData.IsRevertedX = bool(valueRevertedX->value());
            
        rapidxml::xml_node<> *valueRevertedY = valueRevertedX->next_sibling(); //6 value
        staticTileData.IsRevertedY = bool(valueRevertedY->value());
            
        previousTile = newTile;
        newTile = previousTile->next_sibling();
            
        //end
        textureData.staticTilesData.insert({tileName, staticTileData});
            
        if (newTile == 0){isDone = true;}
    }
    Logger::Info("Parse Static Data done.");
}

void TextureMgr::parseAnimData(TextureData& textureData, const rapidxml::xml_node<>* firstNode)
{
    rapidxml::xml_node<> *firstTile = firstNode->first_node(); //first tile
    rapidxml::xml_node<> *previousTile;
    rapidxml::xml_node<> *newTile = firstTile;
        
    bool isDone = false;
    while (!isDone)
    {
        AnimationData animationData;
        std::string tileName = newTile->first_attribute()->value();
            
        rapidxml::xml_node<> *valueX = newTile->first_node(); //1 value
        animationData.StartX = int(valueX->value());
            
        rapidxml::xml_node<> *valueY = valueX->next_sibling(); //2 value
        animationData.StartY = int(valueY->value());
            
        rapidxml::xml_node<> *valueSizeX = valueY->next_sibling(); //3 value
        animationData.SizeX = int(valueSizeX->value());
            
        rapidxml::xml_node<> *valueSizeY = valueSizeX->next_sibling(); //4 value
        animationData.SizeY = int(valueSizeY->value());
            
        rapidxml::xml_node<> *valueOffsetX = valueSizeY->next_sibling(); //5 value
        animationData.OffsetX = int(valueOffsetX->value());
            
        rapidxml::xml_node<> *valueOffsetY = valueOffsetX->next_sibling(); //6 value
        animationData.OffsetY = int(valueOffsetY->value());
        
        rapidxml::xml_node<> *valueSpriteNum = valueOffsetY->next_sibling(); //7 value
        animationData.AnimationSpriteCount = int(valueSpriteNum->value());
        
        rapidxml::xml_node<> *valueSpritesOnLine = valueSpriteNum->next_sibling(); //8 value
        animationData.SpriteOnLine = int(valueSpritesOnLine->value());
        
        rapidxml::xml_node<> *valueReverted = valueSpritesOnLine->next_sibling(); //9 value
        animationData.IsReverted = bool(valueReverted->value());
        
        rapidxml::xml_node<> *valueTimeBetweenAnim = valueReverted->next_sibling(); //10 value
        animationData.TimeBetweenAnimationInS = int(valueTimeBetweenAnim->value());
            
        previousTile = newTile;
        newTile = previousTile->next_sibling();
            
        //end
        textureData.animationsData.insert({tileName, animationData});
            
        if (newTile == 0){isDone = true;}
    }
    Logger::Info("Parse Anim Data done.");
}

const TextureData& TextureMgr::GetTextureData(const std::string& name) const
{
    if (!textures.empty())
    {
        // if (textures.find(name))
        // {
        //     //TODO: I NEED VAL LINE LOL
        // }
    }
    Logger::Warning("Could not find texture \"" + name + "\"");
}

void TextureMgr::DrawDebug()
{
#ifdef _USE_IMGUI
    if (ImGui::BeginTable("Logs##LogConsole", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupColumn("Texture");
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();
        ImVec4 color = ImVec4(1, 0.58, 0.77, 1);
        ImGui::TableSetColumnIndex(0);
        ImGui::TextColored(color, "SDFDFSF");
        // std::filesystem::path path = "C:/Users/s.laurain/Documents/GitHub/rubika_26_27_cpp_public/MyEngine/rubika_26_27/69ee824f3313ed.jpg";
        // const sf::Texture texture(path);
        // ImGui::Image(texture, ImVec2(100, 100));

        ImGui::EndTable();
    }
#endif
}
