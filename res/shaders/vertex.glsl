#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoords;

uniform mat4 u_World;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 vertexColor;

void main() {
    gl_Position = u_Projection * u_View * u_World * vec4(aPos, 1.0);
    vertexColor = aColor;

}
