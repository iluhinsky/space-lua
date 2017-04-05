#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

uniform mat4 gWVPs;  
uniform mat4 gWVs;
uniform mat3 gWNs; 

uniform vec3	  lightPoss;
uniform vec3	  eyePoss;

uniform float	  scales;

out vec2 TexCoord_;

out vec3 l;
out vec3 v;
out vec3 n;

void main()
{
    TexCoord_ = TexCoord;	
	gl_Position = gWVPs * vec4(scales*Position, 1.0);

	vec3 p = vec3 (gWVs * vec4(scales*Position, 1.0));

	l = normalize (vec3 (vec3(gWVs * vec4(lightPoss, 1.0))     - p));
	v = normalize (- p) + eyePoss * 0.0000001;
	n = normalize (vec3(gWVs * vec4(Normal, 0.0) ) );
}
