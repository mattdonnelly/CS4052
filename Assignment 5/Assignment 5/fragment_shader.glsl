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
    float shininess;
};

const int max_lights = 8;
uniform int num_lights;
uniform LightSource light_sources[max_lights];

const vec4 fog_color = vec4(0.05, 0.1, 0.1, 1.0);
const float fog_density = 0.06;

out vec4 fragment_colour;

vec3 create_light(LightSource light) {
    vec3 light_position_eye = vec3(view_mat * vec4(light.position, 1.0));
    vec3 direction_to_light_eye = normalize(light_position_eye - position_eye);
    float dist = length(light_position_eye - position_eye);

    float intensity = min(max(1.0 / pow(dist / light.attenuation, 2.0), 0.0), 1.0);
    
    vec3 Ia = light.ambient * intensity;
    
    float dot_prod = max(dot(direction_to_light_eye, normal_eye), 0.0);

    vec3 Id = light.diffuse * dot_prod * intensity;
    
    vec3 reflection_eye = reflect(-direction_to_light_eye, normal_eye);
    vec3 surface_to_viewer_eye = normalize(-position_eye);
    float dot_prod_specular = dot(reflection_eye, surface_to_viewer_eye);
    dot_prod_specular = max(dot_prod_specular, 0.0);
    float specular_factor = pow(dot_prod_specular, light.shininess);

    vec3 Is = light.specular * specular_factor * intensity;

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
