#version 330 core
in vec2 TexCoords;
in vec4 ParticleColor;
out vec4 color;

uniform sampler2D texture;

void main()
{
    color = (texture(texture, TexCoords) * ParticleColor);
}  