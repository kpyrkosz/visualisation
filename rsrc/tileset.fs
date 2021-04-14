#version 330

in vec2 texcoords;

uniform sampler2D sampler;

out vec4 FragColor;

void main()
{  
  FragColor = texture(sampler, texcoords).rgba;
}
