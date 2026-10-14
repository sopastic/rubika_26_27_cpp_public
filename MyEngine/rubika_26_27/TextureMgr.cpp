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
    
    try
    {
        doc.parse<0>(xmlFile.data());
    }
    catch (std::exception& e)
    {
        Logger::Warning("Failed to parse XML file");
        std::cerr << e.what() << std::endl;
    }
    
    rapidxml::xml_node<> *firstNode = doc.first_node();
    
    if (strcmp(firstNode->name(), "Animations") == 0)
    {
        std::cout << "Name of my first node is: " << firstNode->name() << "\n";
        TextureData textureData = TextureData(TextureData::Animation);
        AnimationData animationData = AnimationData();
        textureData.animationsData = animationData;
        const sf::Texture texture(path);
        textureData.texture = texture;
    }
    else if (firstNode->name() == "Backgrounds")
    {
        std::cout << "Name of my first node is: " << firstNode->name() << "\n";
        TextureData textureData = TextureData(TextureData::Background);
        const sf::Texture texture(path);
        textureData.texture = texture;
        StaticTileData staticTilesData = StaticTileData();
        fillStaticData(staticTilesData, doc);
        textureData.staticTilesData = staticTilesData;
    }
    else
    {
        Logger::Warning("First node is not valid");
    }

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

void TextureMgr::fillAnimationData(AnimationData animationData)
{
    
}

void TextureMgr::fillStaticData(StaticTileData staticTileData, rapidxml::xml_document<>& xmlDoc)
{
    
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
