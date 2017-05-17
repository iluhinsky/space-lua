#version 330

in vec2 TexCoord_;

in vec3 l;
in vec3 v;
in vec3 n;

uniform sampler2D texture;
uniform vec3 color;

out vec4 FragColor;

void main()
{
    vec4 diffColor = texture2D(texture, vec2(TexCoord_.x, TexCoord_.y));

	const vec4  specColor = vec4(0.4, 0.4, 0.2, 1.0);
	const float specPower = 100.0;

	vec3 n2 = normalize (n);
	vec3 l2 = normalize (l); 
	vec3 v2 = normalize (v);

	vec3 r  = reflect (-n2, v2);

	vec4 diff = (diffColor+vec4(color, 1)) * (0.5f + 0.5f * max ( dot (n2, l2), 0.0));
	vec4 spec = specColor * pow ( max ( dot (l2, r), 0.0), specPower );

	FragColor =  diff + spec;
}
