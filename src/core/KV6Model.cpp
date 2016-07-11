#include "KV6Model.hpp"

#include "Common.hpp"

namespace core {
    struct Voxel {
        bool solidity;
        math::ByteVector3 color;
    };

    KV6Model::KV6Model(math::IntVector3 size, math::Vector3 pivot) : size_(size), pivot_(pivot) {
        // nothing
    }

    KV6Model::~KV6Model() {
        // nothing
    }

    Voxel& KV6Model::GetVoxel(int x, int y, int z) {
        int offset = (size_.x * size_.y) * z + size_.x * y + x;
        return voxels_[offset];
    }

    Voxel& KV6Model::GetVoxel(math::IntVector3 pos) {
        return GetVoxel(pos.x, pos.y, pos.z);
    }

    bool KV6Model::GetSolidity(int x, int y, int z) {
        return GetVoxel(x, y, z).solidity;
    }

    bool KV6Model::GetSolidity(math::IntVector3 pos) {
        return GetVoxel(pos).solidity;
    }

    math::ByteColor3 KV6Model::GetColor(int x, int y, int z) {
        return GetVoxel(x, y, z).color;
    }

    math::ByteColor3 KV6Model::GetColor(math::IntVector3 pos) {
        return GetVoxel(pos).color;
    }

    void KV6Model::SetSolidity(int x, int y, int z, bool newsolidity) {
        GetVoxel(x, y, z).solidity = newsolidity;
    }

    void KV6Model::SetSolidity(math::IntVector3 pos, bool newsolidity) {
        GetVoxel(pos).solidity = newsolidity;
    }

    void KV6Model::SetColor(int x, int y, int z, math::ByteColor3 newcolor) {
        GetVoxel(x, y, z).color = newcolor;
    }
    void KV6Model::SetColor(math::IntVector3 pos, math::ByteColor3 newcolor) {
        GetVoxel(pos).color = newcolor;
    }
}
