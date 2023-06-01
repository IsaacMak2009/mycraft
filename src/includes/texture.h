#pragma once

#include <GL/glew.h>
#include <cstdio>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace mycraft {
    class Texture {
        public:
            GLuint texture;
            Texture (const char *texture_path, GLuint TexParm, GLuint Texfilt);
            void bindTexture();
    };

    GLuint loadTexture(const char *path, GLuint TexParm = GL_REPEAT, GLuint Texfilt = GL_LINEAR) {

        // check extension
        char *ext;
        GLuint imFormat = GL_RGB;
        ext = strrchr(strdup(path), '.');
        if (strcmp(ext, ".png") == 0) {
            //printf("%s", ext);
            imFormat = GL_RGBA;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TexParm);	// Set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TexParm);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texfilt);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Texfilt);
        int width, height, nChannel;
        unsigned char *image = stbi_load(path, &width, &height, &nChannel, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, imFormat, width, height, 0, imFormat, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        printf("Load image: \n\twidth=%d, \n\theight=%d, \n\tnChannel=%d, \n\tfile=%s\n\n", width, height, nChannel, path);
        stbi_image_free(image); // free memory
        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }

    Texture::Texture (const char *texture_path, GLuint TexParm = GL_REPEAT, GLuint Texfilt = GL_LINEAR) {
        this->texture = loadTexture(texture_path, TexParm, Texfilt);
    }

    void Texture::bindTexture() {
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }
}