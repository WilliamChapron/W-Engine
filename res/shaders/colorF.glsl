#version 330 core
out vec4 FragColor;

in vec4 vertexColor;

uniform bool hasDiffuseTexture;  // Le bool�en pour v�rifier la pr�sence de la texture

void main() {
	FragColor = vertexColor;
}
