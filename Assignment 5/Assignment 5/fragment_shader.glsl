#version 400

in vec2 frag_tex_coord;
in vec3 position_eye, normal_eye;
in mat4 view_mat;

uniform sampler2D tex;

const vec3 light_position_world  = vec3(5.0, 5.0, 5.0);

const vec3 Ls = vec3(0.7, 0.9, 0.9);
const vec3 Ld = vec3(0.4, 0.7, 0.7);
const vec3 La = vec3(0.1, 0.2, 0.2);

const vec3 Ks = vec3(0.8, 1.0, 1.0);
const vec3 Kd = vec3(0.0, 0.5, 1.0);
const vec3 Ka = vec3(2.0, 2.0, 2.0);
const float specular_exponent = 100.0;

const vec4 fog_color = vec4(0.05, 0.1, 0.1, 1.0);
const float fog_density = 0.025;

out vec4 fragment_colour;

void main () {
    vec3 Ia = La * Ka;

    vec3 light_position_eye = vec3(view_mat * vec4(light_position_world, 1.0));
    vec3 distance_to_light_eye = light_position_eye - position_eye;
    vec3 direction_to_light_eye = normalize(distance_to_light_eye);
    float dot_prod = dot(direction_to_light_eye, normal_eye);
    dot_prod = max(dot_prod, 0.0);
    vec3 Id = Ld * Kd * dot_prod;

    vec3 reflection_eye = reflect(-direction_to_light_eye, normal_eye);
    vec3 surface_to_viewer_eye = normalize(-position_eye);
    float dot_prod_specular = dot(reflection_eye, surface_to_viewer_eye);
    dot_prod_specular = max(dot_prod_specular, 0.0);
    float specular_factor = pow(dot_prod_specular, specular_exponent);
    vec3 Is = Ls * Ks * specular_factor;

    vec2 flipped_tex_coord = vec2(frag_tex_coord.x, 1.0 - frag_tex_coord.y);
    vec4 light_colour = vec4(Is + Id + Ia, 1.0) * texture(tex, flipped_tex_coord);
    
    vec4 view_space = view_mat * vec4(position_eye, 1.0);
    float dist = length(view_space);
    
    float fog_factor = 1.0 / exp((dist * fog_density) * (dist * fog_density));
    fog_factor = clamp(fog_factor, 0.0, 1.0);
    fragment_colour = mix(fog_color, light_colour, fog_factor);
}
