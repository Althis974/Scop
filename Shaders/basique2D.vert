// Version du GLSL

#version 410 core


// Entree Shader

in vec2 in_Vertex;


// Fonction main

void main()
{
    // Position finale du vertex

    gl_Position = vec4(in_Vertex, 0.0, 1.0);
}