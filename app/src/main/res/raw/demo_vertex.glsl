#version 300 es

layout(location = 0) in vec4 vPos;
uniform mat4 spinMatrix;
void main() {
    gl_Position = spinMatrix * vPos;
}
