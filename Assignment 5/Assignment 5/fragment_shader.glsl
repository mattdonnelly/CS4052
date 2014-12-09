#version 400

in vec2 frag_tex_coord;
in vec3 position_eye, normal_eye;
in mat4 view_mat;

uniform sampler2D tex;

struct LightSource {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float attenuation;
};

const int max_lights = 8;
uniform int num_lights;
uniform LightSource light_sources[max_lights];

const vec3 Ks = vec3(1.0, 1.0, 1.0);
const vec3 Kd = vec3(2.0, 2.0, 2.0);
const vec3 Ka = vec3(1.5, 1.5, 1.5);
const float specular_exponent = 100.0;

const vec4 fog_color = vec4(0.05, 0.1, 0.1, 1.0);
const float fog_density = 0.05;

out vec4 fragment_colour;

vec3 create_light(LightSource light) {
    vec3 light_position_eye = vec3(view_mat * vec4(light.position, 1.0));
    vec3 direction_to_light_eye = normalize(light_position_eye - position_eye);
    float dist = length(light_position_eye - position_eye);
    
    float intensity = min(max(1.0 / pow(dist / light.attenuation, 2.0), 0.0), 1.0);
    
    vec3 Ia = light.ambient * intensity;
    
    float dot_prod = max(dot(direction_to_light_eye, normal_eye), 0.0);

    vec3 Id = light.diffuse * dot_prod * intensity;
    //Id = clamp(Id, 0.0, 1.0);
    
    vec3 Is = light.specular * specular_exponent * intensity;
    //Is = clamp(Is, 0.0, 1.0);

    return Ia + Id + Is;
}

void main () {
    vec3 light;
    for (int i = 0; i < num_lights; i++) {
        light += create_light(light_sources[i]);
    }

    vec4 texture_light = vec4(light, 1.0) * texture(tex, frag_tex_coord);
    
    float dist = length(-position_eye);
    
    float fog_factor = 1.0 / exp((dist * fog_density) * (dist * fog_density));
    fog_factor = clamp(fog_factor, 0.0, 1.0);
    fragment_colour = mix(fog_color, texture_light, fog_factor);
}
