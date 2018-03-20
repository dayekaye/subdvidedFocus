// fragment shader

#version 150

in vec2 textureCoord;
out vec4 fColor;
uniform sampler2D textureID;  //the texture unit to sample from

void main()
{
	vec4 color;
	float blurAmnt = 0.01;

	color += 1.0 * texture(textureID, textureCoord + vec2(blurAmnt * -4.0, 0.0));
	color += 2.0 * texture(textureID, textureCoord + vec2(blurAmnt * -3.0, 0.0));
	color += 3.0 * texture(textureID, textureCoord + vec2(blurAmnt * -2.0, 0.0));
	color += 4.0 * texture(textureID, textureCoord + vec2(blurAmnt * -1.0, 0.0));

	color += 5.0 * texture(textureID, textureCoord + vec2(blurAmnt, 0));

	color += 4.0 * texture(textureID, textureCoord + vec2(blurAmnt * 1.0, 0.0));
	color += 3.0 * texture(textureID, textureCoord + vec2(blurAmnt * 2.0, 0.0));
	color += 2.0 * texture(textureID, textureCoord + vec2(blurAmnt * 3.0, 0.0));
	color += 1.0 * texture(textureID, textureCoord + vec2(blurAmnt * 4.0, 0.0));

	color /= 25.0;

	fColor = color;

}