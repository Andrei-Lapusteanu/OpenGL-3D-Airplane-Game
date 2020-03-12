#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal; 

// Uniforms for light properties
uniform vec3 light_pos;
uniform vec3 eye_pos;
uniform float material_ka;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform vec3 object_color;
uniform float alpha;

layout(location = 0) out vec4 out_color;

void main()
{
    // Vectors
    vec3 L = normalize(light_pos - world_position);
    vec3 V = normalize(eye_pos - world_position);
    vec3 H = normalize(L + V);
	vec3 R = reflect(world_normal, L);

    // Diffuse light
    float diffuse_light = material_kd * max(dot(world_normal, L), 0);

    // Specular light
    int gets_light = 0;
	if(dot(world_normal, L) > 0.0)
		 gets_light = 1;

	float specular_light = material_ks * gets_light * pow(max(dot(world_normal, H), 0), material_shininess);

    out_color = vec4(object_color * (material_ka + diffuse_light + specular_light), alpha);
}