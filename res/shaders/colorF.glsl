#version 330 core
out vec4 FragColor;

in vec4 vertexColor;

uniform bool hasDiffuseTexture;  // Le booléen pour vérifier la présence de la texture

void main() {
	FragColor = vertexColor;
}
