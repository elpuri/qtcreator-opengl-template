#version 410

uniform sampler2D uTexture;
in vec2 vTexCoord0;
layout(location = 0, index = 0) out vec4 fragColor;

void main(void)
{
    fragColor = texture(uTexture, vTexCoord0.st);
}


