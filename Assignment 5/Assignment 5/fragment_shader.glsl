#version 400

in vec2 frag_tex_coord;
in vec3 position_eye, normal_eye;
in mat4 view_mat;

uniform sampler2D tex;

uniform vec3 light_position_world;
uniform vec3 light_position_gem1;
uniform vec3 light_position_gem2;

uniform mat3 light_properties_world;
uniform mat3 light_properties_gem;

const vec3 Ks = vec3(1.0, 1.0, 1.0);
const vec3 Kd = vec3(2.0, 2.0, 2.0);
const vec3 Ka = vec3(3.0, 3.0, 3.0);
const float specular_exponent = 100.0;

const vec4 fog_color = vec4(0.05, 0.1, 0.1, 1.0);
const float fog_density = 0.065;

out vec4 fragment_colour;

vec3 create_light(vec3 position, mat3 properties, float light_reach) {
    vec3 Ls = properties[0];
    vec3 Ld = properties[1];
    vec3 La = properties[2];
    
    vec3 light_position_eye = vec3(view_mat * vec4(position, 1.0));
    vec3 direction_to_light_eye = normalize(light_position_eye - position_eye);
    
    float distance_from_light_to_position = length(light_position_eye - position_eye);
    float light_intensity = min(max(1.0/pow(distance_from_light_to_position/light_reach,2.0),0.0),1.0);

    vec3 Ia = La * Ka * light_intensity;

    float dot_prod = dot(direction_to_light_eye, normal_eye);
    dot_prod = max(dot_prod, 0.0);
    vec3 Id = Ld * Kd * dot_prod;
    
    vec3 reflection_eye = reflect(-direction_to_light_eye, normal_eye);
    vec3 surface_to_viewer_eye = normalize(-position_eye);
    float dot_prod_specular = dot(reflection_eye, surface_to_viewer_eye);
    dot_prod_specular = max(dot_prod_specular, 0.0);
    float specular_factor = pow(dot_prod_specular, specular_exponent);
    vec3 Is = Ls * Ks * specular_factor;
    
    return Is + Id + Ia;
}

void main () {    
    vec3 light_world = create_light(light_position_world, light_properties_world, 200.0);
    vec3 light_gem1 = create_light(light_position_gem1, light_properties_gem, 30.0);
    vec3 light_gem2 = create_light(light_position_gem2, light_properties_gem, 30.0);
    
    vec3 light = light_world + light_gem1 + light_gem2;
    
    vec2 flipped_tex_coord = vec2(frag_tex_coord.x, 1.0 - frag_tex_coord.y);
    vec4 texture_light = vec4(light, 1.0) * texture(tex, flipped_tex_coord);
    
    float dist = length(-position_eye);
    
    float fog_factor = 1.0 / exp((dist * fog_density) * (dist * fog_density));
    fog_factor = clamp(fog_factor, 0.0, 1.0);
    fragment_colour = mix(fog_color, texture_light, fog_factor);
}
