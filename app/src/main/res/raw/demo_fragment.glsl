#version 300 es

precision mediump float;

uniform vec4 vColor;
out vec4 fragColor;
in float baseColor;
void main() {
    fragColor = normalize(vColor+vec4(0, baseColor, 0, 0));
}
