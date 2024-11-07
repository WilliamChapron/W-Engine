#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoords;    

uniform sampler2D texture1;  // La texture diffuse
uniform bool hasDiffuseTexture;  // Le bool�en pour v�rifier la pr�sence de la texture

void main() {
    if (hasDiffuseTexture) {
        FragColor = texture(texture1, TexCoords);
    } else {
        FragColor = vertexColor;
        FragColor = vec4(1.0, 1.0,0.0,1.0);
        
    }
}