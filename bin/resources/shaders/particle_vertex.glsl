#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

uniform mat4 gWVP;  
uniform mat4 gWV;

uniform vec3	  eyePos;

uniform float	  scale;

out vec2 TexCoord_;

void main()
{
    TexCoord_ = TexCoord;

	mat3 rot = mat3(gWV[0][0], gWV[1][0], gWV[2][0], gWV[0][1], gWV[1][1], gWV[2][1], gWV[0][2], gWV[1][2], gWV[2][2]);

	mat3 RotateToCamera = mat3(	 1.0,  0.0,  0.0, 
					 0.0,  0.0,  -1.0, 
					 0.0,  1.0,  0.0);

	gl_Position =   gWVP * vec4(scale*rot*(Position*RotateToCamera), 1.0);	
}
