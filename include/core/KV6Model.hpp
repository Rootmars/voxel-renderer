#pragma once

#include "Common.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace core {
    struct Voxel;

    class KV6Model {
    public:
        // size_ and pivot_ must be immutable after creating the object
        KV6Model(math::IntVector3 size, math::Vector3 pivot);
        ~KV6Model();
        bool GetSolidity(int x, int y, int z);
        bool GetSolidity(math::IntVector3 pos);
        math::ByteColor3 GetColor(int x, int y, int z);
        math::ByteColor3 GetColor(math::IntVector3 pos);
        void SetSolidity(int x, int y, int z, bool newsolidity);
        void SetSolidity(math::IntVector3 pos, bool newsolidity);
        void SetColor(int x, int y, int z, math::ByteColor3 newcolor);
        void SetColor(math::IntVector3 pos, math::ByteColor3 newcolor);

    private:
        const math::IntVector3 size_;
        const math::Vector3 pivot_;
        std::vector<Voxel> voxels_;
        Voxel& GetVoxel(int x, int y, int z);
        Voxel& GetVoxel(math::IntVector3 pos);
    };
}
