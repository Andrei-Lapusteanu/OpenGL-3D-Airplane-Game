#version 430 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
	vec3 world_position;
	vec3 world_normal;
} gs_in[];

out vec3 world_position;
out vec3 world_normal;

vec3 GetPrimitiveNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
	float time = 0.0f;
	float magnitude = 0.0f;
	vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
	return position + vec4(direction, 0.0);
}

void main()
{
	// Send data to fragment shader
	world_position = gs_in[0].world_position;
	world_normal= gs_in[0].world_normal;

	vec3 normal = GetPrimitiveNormal();

	for(int i = 0; i < 3; i++)
	{
		gl_Position = explode(gl_in[i].gl_Position, normal);
		EmitVertex();
	}

	EndPrimitive();
}