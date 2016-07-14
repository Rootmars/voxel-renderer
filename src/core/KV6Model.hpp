#pragma once

#include "Math.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <vector>

namespace program {
    struct Voxel;

    class KV6Model {
    public:
        KV6Model(IntVector3 size);
        KV6Model(int length, int width, int heigth);

        ~KV6Model();

        static std::unique_ptr<KV6Model> LoadModel(std::string filename);

        bool GetSolidity(IntVector3 pos);
        ByteColor3 GetColor(IntVector3 pos);
        uint8_t GetFaceBits(IntVector3 pos);
        IntVector3 GetSize();
        Vector3 GetPivot();
        void SetSolidity(IntVector3 pos, bool newsolidity);
        void SetColor(IntVector3 pos, ByteColor3 newcolor);
        void SetFaceBits(IntVector3 pos, uint8_t newfacebits);
        void SetPivot(Vector3 pivot);

    private:
        const IntVector3 size_;
        Vector3 pivot_;
        std::vector<Voxel> voxels_;

        Voxel& GetVoxel(int x, int y, int z);
        Voxel& GetVoxel(IntVector3 pos);
    };
}
