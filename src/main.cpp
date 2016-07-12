#include "./core/KV6Model.hpp"

#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<program::KV6Model> m = program::KV6Model::LoadModel("assets/sphere.kv6");
    std::cout << m->GetSize().x << std::endl;
    std::cout << m->GetSize().y << std::endl;
    std::cout << m->GetSize().z << std::endl;
    std::cout << m->GetPivot().x << std::endl;
    std::cout << m->GetPivot().y << std::endl;
    std::cout << m->GetPivot().z << std::endl;

    for (int z = 0; z < m->GetSize().z; z++) {
        for (int y = 0; y < m->GetSize().y; y++) {
            for (int x = 0; x < m->GetSize().x; x++) {
                if (m->GetSolidity(x, y, z)) {
                    std::cout << "X";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "----------------" << std::endl;
    }

	return 0;
}
