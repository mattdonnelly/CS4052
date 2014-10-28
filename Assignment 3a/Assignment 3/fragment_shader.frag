#version 400

uniform sampler2D tex;

in vec2 frag_tex_coord;

out vec4 frag_colour;

void main() {
    vec2 flipped_tex_coord = vec2(frag_tex_coord.x, 1.0 - frag_tex_coord.y);
    frag_colour = texture(tex, flipped_tex_coord);
}
