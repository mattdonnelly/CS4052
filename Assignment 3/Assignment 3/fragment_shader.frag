#version 400

uniform sampler2D tex;

in vec2 frag_tex_coord;

out vec4 frag_colour;

void main() {
    frag_colour = texture(tex, frag_tex_coord);
}
