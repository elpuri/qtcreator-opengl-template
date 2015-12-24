attribute vec3 aVertex;
attribute vec2 aTexCoord0;
uniform mat4 uMvpMatrix;
varying vec2 vTexCoord0;

void main(void)
{
    vTexCoord0 = aTexCoord0;
    vec4 v = vec4(aVertex, 1.0);
    gl_Position = uMvpMatrix * v;
}

