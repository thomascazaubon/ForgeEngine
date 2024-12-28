#include "CartographUtils.h"

#include "engine/components/MeshComponent.h"
#include "engine/core/World.h"
#include "engine/io/FileUtils.h"
#include "engine/render/MeshUtils.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/debug/DebugUtils.h"
#endif //FORGE_DEBUG_ENABLED

#include <map>

namespace ForgeEngine
{
    namespace CartographUtils
    {
        void LoadMap(World& world, const std::string& filePath, Vector3& spawnPosition)
        {
            std::string source;
            std::map<char, std::string> legend;

            int dimensions = 0;
            int layoutRowIndex = 0;
            float xOffset = 0.5f;
            float zOffset = 0.5f;
            bool processLayout = false;
            bool spawnPointSet = false;

            if (FileUtils::TryLoadFileContent(filePath, source))
            {
                const std::vector<std::string> lines = FileUtils::Split("\n", source);
                for (const std::string& line : lines)
                {
                    const std::vector<std::string> splittedLine = FileUtils::Split("=", line);

                    if (processLayout)
                    {
                        if (line.size() == dimensions)
                        {
                            for (int i = 0.f; i < dimensions; i++)
                            {
                                if (line[i] != 'x')
                                {
                                    auto it = legend.find(line[i]);
                                    if (it != legend.end())
                                    {
                                        const std::string& value = legend[line[i]];
                                        if (value == "spawnPosition")
                                        {
                                            spawnPosition = Vector3(xOffset, 0.f, zOffset);
                                            spawnPointSet = true;
                                        }
                                        else
                                        {
                                            Entity* entity = world.RegisterEntity();
                                            entity->RegisterComponent(new MeshComponent(MeshUtils::MakeSprite(legend[line[i]].c_str(), 1.8, Pivot::Bottom), "assets\\shaders\\billboard"));
                                            entity->GetTransform().SetPosition(Vector3(xOffset, 0.f, zOffset));
                                        }
                                    }
#ifdef FORGE_DEBUG_ENABLED
                                    else
                                    {
                                        DebugUtils::LogWarning("MapLoader: \"{}\" Layout Row {}, Column {}: Unknown key '{}' will be ignored", filePath, layoutRowIndex, i, line[i]);
                                    }
#endif //FORGE_DEBUG_ENABLED
                                }
                                xOffset++;
                            }
                        }
#ifdef FORGE_DEBUG_ENABLED
                        else
                        {
                            DebugUtils::LogError("MapLoader: \"{}\" Invalid dimension on row {}, expected {} got {}, row will be ignored.", filePath, layoutRowIndex, dimensions, line.size());
                        }
#endif //FORGE_DEBUG_ENABLED
                        layoutRowIndex++;
                        xOffset = 0.5f;
                        zOffset++;
                    }
                    else if (splittedLine.size() == 2)
                    {
                        const std::string& attributeName = splittedLine[0];
                        const std::string& attributeValue = splittedLine[1];

                        if (attributeName == "dimensions")
                        {
                            dimensions = stoi(attributeValue);
                        }
                        else if (attributeName == "ground")
                        {
                            Entity* ground = world.RegisterEntity("Ground");
                            ground->RegisterComponent(new MeshComponent(MeshUtils::MakePlane(dimensions, attributeValue.c_str()), "assets\\shaders\\lit"));
                            ground->GetTransform().Translate(VECTOR3_RIGHT * (dimensions / 2.f) + VECTOR3_FORWARD * (dimensions / 2.f));
#ifdef FORGE_DEBUG_ENABLED
                            if (dimensions <= 0.f)
                            {
                                DebugUtils::LogError("MapLoader: \"{}\": Invalid or missing dimensions.", filePath);
                                return;
                            }
#endif //FORGE_DEBUG_ENABLED
                        }
                        else if (attributeName.size() == 1)
                        {
                            legend[attributeName[0]] = attributeValue;
                        }
#ifdef FORGE_DEBUG_ENABLED
                        else
                        {
                            DebugUtils::LogError("MapLoader: \"{}\": Invalid attribute \"{}\" on line \"\{}\". Entity keys must be single chars.", filePath, attributeName, line);
                        }
#endif //FORGE_DEBUG_ENABLED
                    }
                    else if (splittedLine.size() == 1 && splittedLine[0] == "layout")
                    {
                        processLayout = true;
                    }
#ifdef FORGE_DEBUG_ENABLED
                    else if (!line.empty())
                    {
                        DebugUtils::LogError("MapLoader: \"{}\": Unkown syntax on line \"\{}\".", filePath, line);
                    }
#endif //FORGE_DEBUG_ENABLED
                }
            }
#ifdef FORGE_DEBUG_ENABLED
            if (!spawnPointSet)
            {
                DebugUtils::LogError("MapLoader: \"{}\": spawnPosition is missing.", filePath);
            }
#endif //FORGE_DEBUG_ENABLED
        }
    }
}