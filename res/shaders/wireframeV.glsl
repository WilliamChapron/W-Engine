#version 330 core
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec4 aColor;

uniform mat4 u_World;      
uniform mat4 u_View;       
uniform mat4 u_Projection; 

out vec4 fragColor;

void main() {
    gl_Position = u_Projection * u_View * u_World * vec4(aPos, 1.0);

    fragColor = aColor;
}
