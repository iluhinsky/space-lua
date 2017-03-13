#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

uniform mat4 gWVP;  
uniform mat4 gWV;
uniform mat3 gWN;

uniform vec3	  lightPos;
uniform vec3	  eyePos;

uniform float	  scale;

out vec2 TexCoord_;

out vec3 l;
out vec3 v;
out vec3 n;

void main()
{
    TexCoord_ = TexCoord;	
	gl_Position = gWVP * vec4(scale*Position, 1.0);

	vec3 p = vec3 (gWV * vec4(scale*Position, 1.0));

	l = normalize (vec3 (vec3(gWV * vec4(lightPos, 1.0))     - p));
	v = normalize (- p) + eyePos * 0.0000001;
	n = normalize (vec3(gWV * vec4(Normal, 0.0) ) );
}
