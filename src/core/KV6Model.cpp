#include "KV6Model.hpp"

#include "Common.hpp"

#include "glm/glm.hpp"

#include <memory>
#include <string>
#include <fstream>
#include <vector>

namespace program {
    struct Voxel {
        bool solidity;
        ByteColor3 color;
    };

    Voxel& KV6Model::GetVoxel(int x, int y, int z) {
        int offset = (size_.x * size_.y) * z + size_.x * y + x;
        return voxels_[offset];
    }

    Voxel& KV6Model::GetVoxel(IntVector3 pos) {
        return GetVoxel(pos.x, pos.y, pos.z);
    }

    KV6Model::KV6Model(IntVector3 size) : size_(size) {
        voxels_.resize(size.x * size.y * size.z);
    }

    KV6Model::KV6Model(int length, int width, int height) : size_(IntVector3(length, width, height)) {
        voxels_.resize(length * width * height);
    }

    KV6Model::~KV6Model() {
        // nothing
    }

    struct KV6Header {
        uint32_t xsize, ysize, zsize;
        float xpivot, ypivot, zpivot;
        uint32_t blocklength;
    };

    struct KV6Block {
        uint32_t color; // 0xLLRRGGBB
        uint16_t zpos;
        uint8_t visfaces; // we don't care about this. Or do we?
        uint8_t lighting; // we don't care about this.
    };

    std::unique_ptr<KV6Model> KV6Model::LoadModel(std::string filename) {
        std::ifstream file(filename, std::ios::binary);

        char magic[4];
        file.read(magic, 4);

        KV6Header header;
        file.read(reinterpret_cast<char*> (&header), sizeof(header));

        int xsize, ysize, zsize;
        xsize = header.xsize, ysize = header.ysize, zsize = header.zsize;
        float xpivot, ypivot, zpivot;
        xpivot = header.xpivot, ypivot = header.ypivot, zpivot = header.zpivot;
        int blocklength;
        blocklength = header.blocklength;

        std::vector<KV6Block> blockdata(blocklength);
        file.read(reinterpret_cast<char*> (blockdata.data()),
                  sizeof(KV6Block) * blocklength);

        std::vector<uint32_t> xoffset(xsize);
        file.read(reinterpret_cast<char*> (xoffset.data()),
                  sizeof(uint32_t) * xsize);

        std::vector<uint16_t> xyoffset(xsize * ysize);
        file.read(reinterpret_cast<char*> (xyoffset.data()),
                  sizeof(uint16_t) * xsize * ysize);

        IntVector3 size = IntVector3(xsize, ysize, zsize);
        Vector3 pivot = Vector3(xpivot, ypivot, zpivot);

        std::unique_ptr<KV6Model> model(new KV6Model(size));
        model->SetPivot(pivot);

        auto colorfromhex = [](uint32_t hex) -> ByteColor3 {
            uint8_t r = hex && 0x000000FF;
            uint8_t g = (hex && 0x0000FF00) >> 2;
            uint8_t b = (hex && 0x00FF0000) >> 4;
            return ByteColor3(r, g, b);
        };

        int readoffset = 0;
        for (int x = 0; x < xsize; x++) {
            for (int y = 0; y < ysize; y++) {
                for (int column = 0; column < xyoffset[x * ysize + y];
                column++, readoffset++) {
                    KV6Block b = blockdata[readoffset];
                    model->SetSolidity(x, y, b.zpos, true);
                    model->SetColor(x, y, b.zpos, colorfromhex(b.color));
                }
            }
        }

        return model;
    }

    bool KV6Model::GetSolidity(int x, int y, int z) {
        return GetVoxel(x, y, z).solidity;
    }

    bool KV6Model::GetSolidity(IntVector3 pos) {
        return GetVoxel(pos).solidity;
    }

    ByteColor3 KV6Model::GetColor(int x, int y, int z) {
        return GetVoxel(x, y, z).color;
    }

    ByteColor3 KV6Model::GetColor(IntVector3 pos) {
        return GetVoxel(pos).color;
    }

    IntVector3 KV6Model::GetSize() {
        return size_;
    }

    Vector3 KV6Model::GetPivot() {
        return pivot_;
    }

    void KV6Model::SetSolidity(int x, int y, int z, bool newsolidity) {
        GetVoxel(x, y, z).solidity = newsolidity;
    }

    void KV6Model::SetSolidity(IntVector3 pos, bool newsolidity) {
        GetVoxel(pos).solidity = newsolidity;
    }

    void KV6Model::SetColor(int x, int y, int z, ByteColor3 newcolor) {
        GetVoxel(x, y, z).color = newcolor;
    }

    void KV6Model::SetColor(IntVector3 pos, ByteColor3 newcolor) {
        GetVoxel(pos).color = newcolor;
    }

    void KV6Model::SetPivot(int x, int y, int z) {
        pivot_ = IntVector3(x, y, z);
    }

    void KV6Model::SetPivot(Vector3 pivot) {
        pivot_ = pivot;
    }    
}
