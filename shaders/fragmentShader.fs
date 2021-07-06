#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D ourTexture;
uniform vec3 ourColor;



void main(){
FragColor = texture(ourTexture, texCoord) * vec4(ourColor,1.0);
}