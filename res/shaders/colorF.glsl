#version 330 core
out vec4 FragColor;

in vec4 vertexColor;

uniform bool hasDiffuseTexture;  

void main() {
	FragColor = vertexColor;
}
