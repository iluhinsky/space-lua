#version 330

in vec2 TexCoord_;

uniform sampler2D texture;
uniform float estimatedTime;
uniform float lifeTime;

out vec4 FragColor;

void main()
{
    	float ration = estimatedTime/lifeTime;
	vec4 alpha = texture2D(texture, vec2(TexCoord_.x, TexCoord_.y));
	FragColor =  vec4(alpha.rgb+vec3(1.0, 1.0, 0.0)*(1-ration), alpha.a * ration);
}
