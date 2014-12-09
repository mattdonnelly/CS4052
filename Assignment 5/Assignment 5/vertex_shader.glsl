#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_tex_coord;
layout (location = 2) in vec3 vertex_normal;

uniform mat4 projection, view, model;

out mat4 view_mat;
out vec2 frag_tex_coord;
out vec3 position_eye, normal_eye;

void main () {
    view_mat = view;
    frag_tex_coord = vertex_tex_coord;
    position_eye = vec3 (view * model * vec4 (vertex_position, 1.0));
    normal_eye = vec3 (view * model * vec4 (vertex_normal, 0.0));
    gl_Position = projection * vec4 (position_eye, 1.0);
}
