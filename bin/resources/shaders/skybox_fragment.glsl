#version 330

in vec2 TexCoord_;


uniform sampler2D texture;
uniform vec3 color;
uniform float time;

out vec4 FragColor;

void main()
{
    vec4 diffColor = texture2D(texture, vec2(TexCoord_.x, TexCoord_.y));

	vec4 diff = diffColor+vec4(color, 1);
	diff.a =  (diff.x + diff.y+diff.z)*(diff.x + diff.y+diff.z)/9.0;
	diff.x = 1.0 - (1.0 - diff.x + sin(time/2.0)/11.0)*(1.0 - diff.x);
	diff.y = 1.0 - (1.0 - diff.y + sin(time/2.0)/11.0)*(1.0 - diff.y);
	diff.z = 1.0 - (1.0 - diff.z + sin(time/2.0)/11.0)*(1.0 - diff.z);


	FragColor =  diff;
}
