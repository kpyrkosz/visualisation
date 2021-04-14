#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;

out vec2 texcoords;

uniform mat3 transform;
uniform mat4 ortho;
uniform float tile_index;
uniform float tileset_row_count;

void main()
{
	/*
	najpierw ktory rzad - UNSIGNED index/rowcount
	potem to / rowcount FLOAT i mamy z tego wspolrzedna U lewo

	potem kolumna UNSIGNED index % rowcount
	potem to / rowcount float i jest V gory
	*/

	gl_Position = ortho * vec4(transform * position, 1.0f);

	//znowu interpolacja T_T U_U O___O
	float tile_uv_step = 1.0f / tileset_row_count;
	float tile_upper_corner_v = floor(tile_index / tileset_row_count) /(tileset_row_count);
	float tile_upper_corner_u = mod(tile_index, tileset_row_count) / tileset_row_count;
	float tile_bottom_corner_u = tile_upper_corner_u + tile_uv_step;
	float tile_bottom_corner_v = tile_upper_corner_v + tile_uv_step;
	texcoords.x = mix(tile_upper_corner_u, tile_bottom_corner_u, uvs.x);
	texcoords.y = mix(tile_upper_corner_v, tile_bottom_corner_v, uvs.y);
}