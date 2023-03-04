//
// Created by XaDanX on 12/7/2022.
//

#include "TextureManager.h"
#include "../../Locator/Locator.h"
#include "../../../Protection/XorStr.h"

bool TextureManager::LoadTextureFromFile(const char *filename, PDIRECT3DTEXTURE9 *out_texture, int *out_width,
                                         int *out_height) {
    PDIRECT3DTEXTURE9 texture;
    HRESULT hr = D3DXCreateTextureFromFileA(locator->GetHookingService()->GetDevice(), filename, &texture);
    if (hr != S_OK)
        return false;
    D3DSURFACE_DESC my_image_desc;
    texture->GetLevelDesc(0, &my_image_desc);
    *out_texture = texture;
    *out_width = (int) my_image_desc.Width;
    *out_height = (int) my_image_desc.Height;
    return true;
}

bool TextureManager::LoadTexture(std::string name, const char *filename) {
    /*int my_image_width = 0;
    int my_image_height = 0;
    PDIRECT3DTEXTURE9 my_texture = NULL;
    bool ret = LoadTextureFromFile(filename, &my_texture, &my_image_width, &my_image_height);
    this->textures[name] = my_texture;*/

    IDirect3DTexture9 *texture = nullptr;
    if (FAILED(D3DXCreateTextureFromFile(locator->GetHookingService()->GetDevice(), filename, &texture))) {
        return false;
    }

    if (textures.find(name) != textures.end()) {
        textures[name]->Release();
    }

    textures[name] = texture;
    return true;
}

IDirect3DTexture9 *TextureManager::GetTexture(std::string substr) {
    /*
    for (const auto& [name, texture] : textures) {
        if (name.find(substr) != std::string::npos) {
            return texture;
        }
    }
    return nullptr;*/

    auto it = textures.find(substr);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr;

}

bool TextureManager::LoadDeployables() {

    for (const auto &entry: fs::directory_iterator(pngDirectory)) {
        fs::path filePath = entry.path();

        if (filePath.extension() == XorStr(".png").c_str()) {
            std::string fileName = filePath.stem().string();
            LoadTexture(fileName, filePath.string().c_str());
        }
    }
    return true;

}
