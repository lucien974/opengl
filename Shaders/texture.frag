// Version du GLSL

#version 150 core


// Entr�e

in vec2 coordTexture;


// Uniform

uniform sampler2D textureSampler;


// Sortie

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel

    out_Color = texture(textureSampler, coordTexture);
}
