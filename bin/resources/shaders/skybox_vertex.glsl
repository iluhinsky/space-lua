#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;

uniform mat4 gWVP;


uniform float	  scale;

out vec2 TexCoord_;

void main()
{
    TexCoord_ = TexCoord;	
	gl_Position = gWVP * vec4(scale*Position, 1.0);
}
