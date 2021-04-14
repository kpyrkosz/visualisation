#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;

out vec2 texcoords;

uniform mat3 transform;
uniform mat4 ortho;

void main()
{
	gl_Position = ortho * vec4(transform * position, 1.0f);
	texcoords = uvs;
}