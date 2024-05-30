#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform int flip;

void main()
{
    TexCoords = vertex.zw;

    if (flip == 0)
    {
    TexCoords.x = -TexCoords.x;
    }
    else
    {
    TexCoords.x = TexCoords.x;
    }

    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}