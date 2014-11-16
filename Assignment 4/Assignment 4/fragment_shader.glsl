#version 400

in vec3 position_eye, normal_eye;

uniform mat4 view_mat;

vec3 light_position_world  = vec3 (0.0, 0.0, 2.0);
vec3 Ls = vec3 (1.0, 1.0, 1.0);
vec3 Ld = vec3 (0.7, 0.7, 0.7);
vec3 La = vec3 (0.2, 0.2, 0.2);

vec3 Ks = vec3 (1.0, 1.0, 1.0);
vec3 Kd = vec3 (1.0, 0.5, 0.0);
vec3 Ka = vec3 (1.0, 1.0, 1.0);
float specular_exponent = 100.0;

out vec4 fragment_colour;

void main () {
    vec3 Ia = La * Ka;
    
    vec3 light_position_eye = vec3 (view_mat * vec4 (light_position_world, 1.0));
    vec3 distance_to_light_eye = light_position_eye - position_eye;
    vec3 direction_to_light_eye = normalize(distance_to_light_eye);
    float dot_prod = dot(direction_to_light_eye, normal_eye);
    dot_prod = max(dot_prod, 0.0);
    vec3 Id = Ld * Kd * dot_prod;
    
    vec3 surface_to_viewer_eye = normalize(-position_eye);
    
    vec3 half_way_eye = normalize(surface_to_viewer_eye + direction_to_light_eye);
    float dot_prod_specular = max(dot (half_way_eye, normal_eye), 0.0);
    float specular_factor = pow(dot_prod_specular, specular_exponent);
    
    vec3 Is = Ls * Ks * specular_factor;
    
    fragment_colour = vec4 (Is + Id + Ia, 1.0);
}