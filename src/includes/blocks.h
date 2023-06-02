#pragma once

namespace mycraft::blocks {
    enum BLOCK {
        AIR,
        GRASS,
        DIRT,
        STONE,
        COBBLESTONE,
        PLANKS,
        SAPLING,
        BEDROCK,
        WATER,
        LAVA,
        SAND,
        GRAVEL,
        GOLD_ORE,
        IRON_ORE,
        COAL_ORE,
        LOG,
        LEAVES,
        SPONGE,
        GLASS,
        LAPIS_ORE,
        LAPIS_BLOCK,
        DISPENSER,
        SANDSTONE,
        NOTE_BLOCK,
        POWERED_RAIL,
        DETECTOR_RAIL,
        STICKY_PISTON,
        COBWEB,
        TALL_GRASS,
        DEAD_BUSH,
        PISTON,
        PISTON_HEAD,
        WOOL,
        DANDELION,
        POPPY,
        BLUE_ORCHID,
        ALLIUM,
        AZURE_BLUET,
        RED_TULIP,
        ORANGE_TULIP,
        WHITE_TULIP,
        PINK_TULIP,
        OXEYE_DAISY,
        RED_MUSHROOM,
        BROWN_MUSHROOM,
        GOLD_BLOCK,
        IRON_BLOCK,
        BRICKS,
        TNT,
        BOOKSHELF,
        MOSSY_COBBLESTONE,
        IMP_49,
        IMP_48,
        IMP_47,
        IMP_46,
        IMP_45,
        IMP_44,
        IMP_43,
        IMP_42,
        IMP_41,
        IMP_40,
        IMP_39,
        IMP_38,
        IMP_37,
        IMP_36,
        IMP_35,
        IMP_34,
        IMP_33,
        IMP_32,
        IMP_31,
        IMP_30,
        IMP_29,
        IMP_28,
        IMP_27,
        IMP_26,
        IMP_25,
        IMP_24,
        IMP_23,
        IMP_22,
        IMP_21,
        IMP_20,
        IMP_19,
        IMP_18,
        IMP_17,
        IMP_16,
        IMP_15,
        IMP_14,
        IMP_13,
        IMP_12,
        IMP_11,
        IMP_10,
        IMP_09,
        IMP_08,
        IMP_07,
        IMP_06,
        IMP_05,
        IMP_04,
        IMP_03,
        IMP_02,
        IMP_01,    
    };

    float vertices_pos[] = {
        -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,-0.5f, -0.5f, -0.5f,-0.5f, -0.5f,  0.5f,0.5f, -0.5f,  0.5f, 0.5f,  0.5f,  0.5f, 0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,-0.5f, -0.5f,  0.5f,-0.5f,  0.5f,  0.5f,-0.5f,  0.5f, -0.5f,-0.5f, -0.5f, -0.5f,-0.5f, -0.5f, -0.5f,-0.5f, -0.5f,  0.5f,-0.5f,  0.5f,  0.5f,0.5f,  0.5f,  0.5f, 0.5f,  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f,  0.5f, 0.5f,  0.5f,  0.5f, -0.5f, -0.5f, -0.5f,0.5f, -0.5f, -0.5f, 0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,-0.5f, -0.5f, -0.5f,-0.5f,  0.5f, -0.5f,0.5f,  0.5f, -0.5f, 0.5f,  0.5f,  0.5f, 0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,-0.5f,  0.5f, -0.5f,
    };

    float texture_uv[][2] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f
    };

    float tex_x_scale = 1.0f/6.0f;
    float tex_y_scale = 1.0f/100.0f;

    void generate_cube(float vertices[], BLOCK block) {
        for (int i=0; i<6*6; i++) {
            // pos_x, pos_y, pos_z, tex_x, tex_y
            vertices[i*5+0] = vertices_pos[i*3+0];
            vertices[i*5+1] = vertices_pos[i*3+1];
            vertices[i*5+2] = vertices_pos[i*3+2];
            // check which side
            // back, front, left, right, bottom, top
            int j = i%6;
            switch (i/6) {
                case 0: // back
                    vertices[i*5+3] = texture_uv[j][0]*tex_x_scale+3*tex_x_scale;
                    vertices[i*5+4] = texture_uv[j][1]*tex_y_scale+(int)block*tex_y_scale;
                    break;
                case 1: // front
                    vertices[i*5+3] = texture_uv[j][0]*tex_x_scale+4*tex_x_scale;
                    vertices[i*5+4] = texture_uv[j][1]*tex_y_scale+(int)block*tex_y_scale;
                    break;
                case 2: // left
                    vertices[i*5+3] = texture_uv[j][0]*tex_x_scale+1*tex_x_scale;
                    vertices[i*5+4] = texture_uv[j][1]*tex_y_scale+(int)block*tex_y_scale;
                    break;
                case 3: // right
                    vertices[i*5+3] = texture_uv[j][0]*tex_x_scale+2*tex_x_scale;
                    vertices[i*5+4] = texture_uv[j][1]*tex_y_scale+(int)block*tex_y_scale;
                    break;
                case 4: // bottom
                    vertices[i*5+3] = texture_uv[j][0]*tex_x_scale+5*tex_x_scale;
                    vertices[i*5+4] = texture_uv[j][1]*tex_y_scale+(int)block*tex_y_scale;
                    break;
                case 5: // top
                    vertices[i*5+3] = texture_uv[j][0]*tex_x_scale+0*tex_x_scale;
                    vertices[i*5+4] = texture_uv[j][1]*tex_y_scale+(int)block*tex_y_scale;
                    break;
            }
        }
    }
} // namespace mycraft