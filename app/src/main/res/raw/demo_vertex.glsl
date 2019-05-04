#version 300 es

in vec4 vPos;
uniform mat4 spinMatrix;
out float baseColor;
void main() {
    vec4 pos = spinMatrix * vPos;
    gl_Position = pos;
    baseColor = (1.0/pow(1e-5+abs(pos.z), 2.0f));
}
