#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>  

template <typename Resource, typename Identifier = std::string>
class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void load(const Identifier& id, const std::string& filename) {
        std::unique_ptr<Resource> resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename)) {
            throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
        }
        resourceMap[id] = std::move(resource);
        std::cout << "Loaded resource: " << filename << " with id: " << id << std::endl;
    }

    Resource& get(const Identifier& id) {
        auto found = resourceMap.find(id);
        if (found == resourceMap.end()) {
            throw std::runtime_error("ResourceManager::get - Failed to find resource with id: " + id);
        }
        return *found->second;
    }

    const Resource& get(const Identifier& id) const {
        auto found = resourceMap.find(id);
        if (found == resourceMap.end()) {
            throw std::runtime_error("ResourceManager::get - Failed to find resource with id (const): " + id);
        }
        return *found->second;
    }

private:
    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
};

using TextureManager = ResourceManager<sf::Texture, std::string>;
using FontManager = ResourceManager<sf::Font, std::string>;

#endif // RESOURCEMANAGER_H