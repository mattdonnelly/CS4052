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
    
    float dist = length(light_position_eye - position_eye);

    vec3 L = normalize(light_position_eye - position_eye);
    vec3 E = normalize(-position_eye);
    vec3 R = normalize(-reflect(L, normal_eye));

    float intensity = min(max(1.0 / pow(dist / light.attenuation, 2.0), 0.0), 1.0);
    
    vec3 Ia = light.ambient * intensity;

    vec3 Id = light.diffuse * max(dot(normal_eye, L), 0.0) * intensity;
    Id = clamp(Id, 0.0, 1.0);
    
    vec3 Is = light.specular * pow(max(dot(R, E), 0.0), 0.3 * light.shininess);
    Is = clamp(Is, 0.0, 1.0);

    return Ia + Id + Is;
}

void main () {
    vec3 light;
    for (int i = 0; i < num_lights; i++) {
        light += create_light(light_sources[i]);
    }
    
    float dist = length(-position_eye);
    float fog_factor = 1.0 / exp((dist * fog_density) * (dist * fog_density));
    fog_factor = clamp(fog_factor, 0.0, 1.0);
    
    fragment_colour = mix(fog_color, vec4(light, 1.0) * texture(tex, frag_tex_coord), fog_factor);
}
