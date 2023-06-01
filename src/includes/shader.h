#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>

namespace mycraft {
    std::string readFile(const char *filePath) {
        // read a file and return the context
        std::ifstream infile(filePath);
        std::string line, context="";
        while (std::getline(infile, line)) {
            context += line + '\n';
        }
        return context+'\0';
    }

    GLuint loadShader(const char *vertex_path, const char *fragment_path) {
        
        // Read Source
        std::string vShader = readFile(vertex_path);
        std::string fShader = readFile(fragment_path);
        const char *vShaderSrc = vShader.c_str();
        const char *fShaderSrc = fShader.c_str();
        int success;
        char log[512];

        // Load Vertex Shader
        unsigned int vShaderProg = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vShaderProg, 1, &vShaderSrc, NULL);
        glCompileShader(vShaderProg);
        glGetShaderiv(vShaderProg, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vShaderProg, 500, NULL, log);
            std::cout << "Error (loading vertex shader):\n" << log << std::endl;
        }

        // Load Fragment Shader
        unsigned int fShaderProg = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fShaderProg, 1, &fShaderSrc, NULL);
        glCompileShader(fShaderProg);
        glGetShaderiv(fShaderProg, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fShaderProg, 500, NULL, log);
            std::cout << "Error (loading fragment shader):\n" << log << std::endl;
        }
        
        // Linking Program
        GLuint prog = glCreateProgram();
        glAttachShader(prog, vShaderProg);
        glAttachShader(prog, fShaderProg);
        glLinkProgram(prog);
        glGetProgramiv(prog, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(prog, 500, NULL, log);
            std::cout << "Error (Linking Program):\n" << log << std::endl;
        }
        return prog;
    }
    
    // shader class
    class Shader {
        public:
            GLuint program;
            Shader (const char *vertex_path, const char *fragment_path);
            void useProgram();
            GLint GetUniLocation(const char *name);
    };

    Shader::Shader(const char *vertex_path, const char *fragment_path) {
        this->program = loadShader(vertex_path, fragment_path);
    }
    void Shader::useProgram() {
        glUseProgram(this->program);
    }
    GLint Shader::GetUniLocation(const char *name) {
        return glGetUniformLocation(this->program, name);
    }
}