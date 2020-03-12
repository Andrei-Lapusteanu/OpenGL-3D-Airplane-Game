#version 430 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

// Input from Vertex Shader
in VS_OUT {
	vec3 world_position;
	vec3 world_normal;
} gs_in[];

// Input from OpenGL
uniform mat4 View;
uniform mat4 Projection;

uniform float explode_timer;
uniform bool has_exploded;

// Output to Fragment Shader
out vec3 world_position;
out vec3 world_normal;

// Get triangle face normal
vec3 GetPrimitiveNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

// Explode face
vec4 explode(vec4 position, vec3 normal)
{
	if(has_exploded)
	{
		// Primitive travel direction
		float magnitude = 3.0f;
		vec3 direction = normal * cos(explode_timer) * magnitude;

		return position + vec4(direction, 0.0);
	}
	else
		return position;
}

void main()
{
	vec3 normal = GetPrimitiveNormal();
	vec4 expl_pos[3];
	vec3 p_aux[3];
	vec3 CG;

	// Send data to fragment shader
	world_position = gs_in[0].world_position;
	world_normal= gs_in[0].world_normal;

	for(int i = 0; i < 3; i++)
	{
		expl_pos[i] = explode(gl_in[i].gl_Position, normal);
		CG += expl_pos[i].xyz;
	}

	CG /= 3;

	for(int i = 0; i < 3; i++)
	{
		if(has_exploded)
			p_aux[i] = CG + (expl_pos[i].xyz - CG) * explode_timer * 3;
		else
			p_aux[i] = CG + (expl_pos[i].xyz - CG) * explode_timer;
		gl_Position = Projection * View * vec4(p_aux[i], 1.0);
		EmitVertex();
	}	

	EndPrimitive();
}