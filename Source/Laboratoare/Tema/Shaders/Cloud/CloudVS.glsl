#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in mat4 v_instance_matrix;
//layout(location = 7) in vec3 v_color;


// Uniform properties
uniform mat4 View;
uniform mat4 Projection;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;

void main()
{
	// TODO: compute world space vertex position and normal
    vec3 world_pos = (v_instance_matrix * vec4(v_position, 1)).xyz;
	vec3 world_norm = normalize(mat3(v_instance_matrix) * v_normal);

	// TODO: send world position and world normal to Fragment Shader
	world_position = world_pos;
	world_normal = world_norm;

	gl_Position = Projection * View * v_instance_matrix * vec4(v_position, 1.0);
}
