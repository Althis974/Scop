#version 410 core

flat in vec4		fragment_color_f;
in vec4				fragment_color_s;
in vec2				txt_coor;

uniform bool		smod;
uniform bool		apply;
uniform sampler2D	txt;

out vec4			col;

void	main()
{
	if (smod)
		col = fragment_color_s;
	else
		col = fragment_color_f;
	if (apply)
		col = texture(txt, txt_coor);
}
