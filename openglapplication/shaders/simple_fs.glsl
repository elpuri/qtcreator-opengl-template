uniform sampler2D uTexture;
varying vec2 vTexCoord0;

void main(void)
{
    gl_FragColor = texture2D(uTexture, vTexCoord0.st);
}

