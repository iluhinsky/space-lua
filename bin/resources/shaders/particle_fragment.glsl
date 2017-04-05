#version 330

in vec2 TexCoord_;

uniform sampler2D texture;

out vec4 FragColor;

void main()
{
    vec4 diffColor = texture2D(texture, vec2(TexCoord_.x, TexCoord_.y));

	FragColor =  diffColor;
}
