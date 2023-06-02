#pragma once
#include "blocks.h"
#include <glm/glm.hpp>
typedef mycraft::blocks::BLOCK BLOCK_TP;

namespace mycraft
{
    class world {
        public:
            world(glm::ivec3 a, glm::ivec3 b);
            bool isVaild(glm::ivec3 pos);
            void setBlock(glm::ivec3 pos, BLOCK_TP block);
            BLOCK_TP getBlock(glm::ivec3 pos);
        
        private:
            BLOCK_TP ***blocks;
            glm::ivec3 start;
            glm::ivec3 end;
    };

    world::world(glm::ivec3 a, glm::ivec3 b) : start(a), end(b) {
        // alloc blocks
        blocks = new BLOCK_TP **[end.x - start.x + 1];
        for (int i = 0; i < end.x - start.x + 1; i++) {
            blocks[i] = new BLOCK_TP *[end.y - start.y + 1];
            for (int j = 0; j < end.y - start.y + 1; j++) {
                blocks[i][j] = new BLOCK_TP[end.z - start.z + 1];
            }
        }
    }

    bool world::isVaild(glm::ivec3 pos) {
        return pos.x >= start.x && pos.x <= end.x && pos.y >= start.y && pos.y <= end.y && pos.z >= start.z && pos.z <= end.z;
    }

    void world::setBlock(glm::ivec3 pos, BLOCK_TP block) {
        if (!isVaild(pos)) return;
        blocks[pos.x - start.x][pos.y - start.y][pos.z - start.z] = block;
    }

    BLOCK_TP world::getBlock(glm::ivec3 pos) {
        if (!isVaild(pos)) return BLOCK_TP::AIR;
        return blocks[pos.x - start.x][pos.y - start.y][pos.z - start.z];
    }

} // namespace mycraft
