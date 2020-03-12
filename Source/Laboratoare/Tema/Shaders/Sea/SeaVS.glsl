#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float theta;
uniform float msTime;
uniform float extRand;

// Output values to fragment shader
flat out vec3 world_position;
flat out vec3 world_normal;

vec3 applyDistort(vec3 vertex)
{
	// Sine wave: y(t) = A * sin(w * t + phi);
	// Omega:     W = 2 * pi / T;
	// Period:	  T = 1 / f;
	float A = 0.015f;
	float pi = 3.14159f;
	float f = 4.0f;
	float T = 1 / f;
	float omega = 2 * pi / T;

	float xDistort = A * sin(omega * (theta + pi) * v_position.x * -1);
	float yDistort = A * sin(omega * (theta + pi) * v_position.y * -1);
	float zDistort = A * sin(omega * (theta + pi) * v_position.z * -1);

	return vertex + vec3(xDistort, yDistort, zDistort);
}

void main()
{
	// Compute world space vertex position and normal
    vec3 world_pos = (Model * vec4(v_position, 1)).xyz;
	vec3 world_norm = normalize(mat3(Model) * v_normal);

	// Send world position and world normal to Fragment Shader
	world_position = world_pos;
	world_normal = world_norm;

	// Apply distortion to sphere
	vec3 pos = v_position;
	pos = applyDistort(pos);

	gl_Position = Projection * View * Model * vec4(pos, 1.0);
}
