//
// Created by XaDanX on 12/7/2022.
//

#ifndef ASYLLUM_TEXTUREMANAGER_H
#define ASYLLUM_TEXTUREMANAGER_H
#include <d3dx9.h>
#include <iostream>
#include <d3dx9.h>
#include <map>
#include <string>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;
namespace {
    fs::path pngDirectory = "C:/Deployable/icons_spells/";
}

class TextureManager {
private:
    std::unordered_map<std::string, IDirect3DTexture9*> textures;
    bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);

public:
    bool LoadTexture(std::string name, const char *filename);
    IDirect3DTexture9* GetTexture(std::string substr);

    bool LoadDeployables();

};


#endif //ASYLLUM_TEXTUREMANAGER_H
