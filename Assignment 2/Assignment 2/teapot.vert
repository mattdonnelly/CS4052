#version 400

layout(location=0) in vec3 vp; // points
layout(location=1) in vec3 vn; // normals (will just use as colours)

uniform mat4 M; // model matrix

out vec3 n;

void main () {
	n = (M * vec4(vn, 0.0)).xyz;
	gl_Position = M * vec4(vp, 1.0) ;
}
