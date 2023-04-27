#ifndef MAZEGAME_TEXTURE_LOADER_HPP
#define MAZEGAME_TEXTURE_LOADER_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class CustomTextureLoader {
public:
    static std::shared_ptr<Texture> load(const std::string &path) {
        auto textureLoader = std::make_shared<threepp::TextureLoader>();
        return textureLoader->load(path);
    }
};

#endif // MAZEGAME_TEXTURE_LOADER_HPP
