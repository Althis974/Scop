#version 410 core

flat in vec4		frag_flat;
in vec4				frag_smooth;
in vec2				txt_coor;

out vec4			col;

uniform bool		inter;
uniform bool		apply;
uniform sampler2D	txt;

void				main()
{
	if (inter)
		col = frag_smooth;
	else
		col = frag_flat;
	if (apply)
		col = texture(txt, txt_coor);
}
