#version 400

in vec3 vert;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 color;

void main() {
    color = vert;
    gl_Position = P * V * M * vec4(vert, 1.0);
}
