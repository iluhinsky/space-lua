#version 330

in vec2 TexCoord_;

uniform sampler2D texture;
uniform float estimatedTime;
uniform float lifeTime;
uniform vec3  blendColor;

out vec4 FragColor;

void main()
{
    	float ration = estimatedTime/lifeTime;
	vec4 alpha = texture2D(texture, vec2(TexCoord_.x, TexCoord_.y));
	FragColor =  vec4(blendColor, alpha.a * ration);
}
