#include <poplin/graphics/assets/textureasset.h>

namespace Poplin
{
    namespace TextureLoader
    {
        std::shared_ptr<Texture> LoadFromBMP(const Char* filePath)
        {
            std::shared_ptr<Texture> createdTexture{};
            FILE* file{ nullptr };
            fopen_s(&file, filePath, "rb");
            if (file != nullptr)
            {
                static const u32 bitmapHeaderSize{ 54 };
                u8 header[bitmapHeaderSize];
                if (fread(header, 1, bitmapHeaderSize, file) == bitmapHeaderSize)
                {
                    PoplinError(header[0] == 'B' && header[1] == 'M', "Incorrect BMP File Content.");
                    PoplinError((*(int*)&(header[0x1E]) == 0), "Incorrect BMP File Content.");
                    PoplinError((*(int*)&(header[0x1C]) == 24), "Incorrect BMP File Content.");

                    u32 dataPos = *(int*)&(header[0x0A]);
                    u32 imageSize = *(int*)&(header[0x22]);
                    u32 width = *(int*)&(header[0x12]);
                    u32 height = *(int*)&(header[0x16]);

                    static const u32 colorComponentCount{ 3 };
                    if (imageSize == 0) imageSize = width * height * colorComponentCount;
                    if (dataPos == 0) dataPos = bitmapHeaderSize;

                    std::vector<u8> bmpData;
                    bmpData.resize(imageSize);
                    fread(bmpData.data(), 1, imageSize, file);

                    createdTexture = std::make_shared<Texture>(bmpData.data(), width, height);
                }
                else
                {
                    PoplinError(false, "Failed to load BMP Header.");
                }
                fclose(file);
            }
            else
            {
                PoplinError(false, "Failed to open BMP file.");
            }
            return createdTexture;
        }
    }

    void TextureAsset::OnAssetLoaded()
    {
        Texture = TextureLoader::LoadFromBMP(FilePath.c_str());
    }
}