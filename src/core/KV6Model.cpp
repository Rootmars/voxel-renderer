#include "KV6Model.hpp"

#include "Math.hpp"

#include "glm/glm.hpp"

#include <memory>
#include <string>
#include <fstream>
#include <vector>

namespace program {
    struct Voxel {
        bool solidity;
        uint8_t facebits;
        ByteColor3 color;
    };

    enum FaceFlags {
        LEFT = 0x01,
        RIGHT = 0x02,
        BACK = 0x04,
        FRONT = 0x08,
        UP = 0x10,
        DOWN = 0x20
    };

    Voxel& KV6Model::GetVoxel(IntVector3 pos) {
        int offset = (size_.x * size_.y) * pos.z + size_.x * pos.y + pos.x;
        return voxels_[offset];
    }

    KV6Model::KV6Model(IntVector3 size) : size_(size) {
        voxels_.resize(size.x * size.y * size.z);
    }

    KV6Model::KV6Model(int length, int width, int height) :
    size_(IntVector3{length, width, height}) {
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
        uint8_t visfaces; // 0x00zZyYxX, small letter being the positive
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

        IntVector3 size = IntVector3{xsize, ysize, zsize};
        Vector3 pivot = Vector3{xpivot, ypivot, zpivot};

        std::unique_ptr<KV6Model> model(new KV6Model(size));
        model->SetPivot(pivot);

        auto colorfromhex = [](uint32_t hex) -> ByteColor3 {
            uint8_t r = hex && 0x000000FF;
            uint8_t g = (hex && 0x0000FF00) >> 2;
            uint8_t b = (hex && 0x00FF0000) >> 4;
            return ByteColor3(r, g, b);
        };

        int readoffset = 0;
        for (auto x = 0; x < xsize; x++) {
            for (auto y = 0; y < ysize; y++) {
                for (auto column = 0; column < xyoffset[x * ysize + y];
                column++, readoffset++) {
                    const KV6Block& b = blockdata[readoffset];
                    IntVector3 pos = IntVector3{x, y, b.zpos};
                    model->SetSolidity(pos, true);
                    model->SetColor(pos, colorfromhex(b.color));
                    model->SetFaceBits(pos, b.visfaces);
                }
            }
        }

        return model;
    }

    bool KV6Model::GetSolidity(IntVector3 pos) {
        return GetVoxel(pos).solidity;
    }

    ByteColor3 KV6Model::GetColor(IntVector3 pos) {
        return GetVoxel(pos).color;
    }

    uint8_t KV6Model::GetFaceBits(IntVector3 pos) {
        return GetVoxel(pos).facebits;
    }

    IntVector3 KV6Model::GetSize() {
        return size_;
    }

    Vector3 KV6Model::GetPivot() {
        return pivot_;
    }

    void KV6Model::SetSolidity(IntVector3 pos, bool newsolidity) {
        GetVoxel(pos).solidity = newsolidity;
    }

    void KV6Model::SetColor(IntVector3 pos, ByteColor3 newcolor) {
        GetVoxel(pos).color = newcolor;
    }

    void KV6Model::SetFaceBits(IntVector3 pos, uint8_t newfacebits) {
        GetVoxel(pos).facebits = newfacebits;
    }

    void KV6Model::SetPivot(Vector3 pivot) {
        pivot_ = pivot;
    }
}
