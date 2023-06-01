#version 330 core
in vec2 TexCoord;
uniform sampler2D Texture;
uniform float block;
out vec4 color;

void main() {
    color = texture(Texture, vec2(0.0f, block/100.0f)+TexCoord);
}