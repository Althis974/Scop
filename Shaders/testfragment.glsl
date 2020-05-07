#version 410 core

flat in vec4		fragment_color_f;
in vec4				fragment_color_s;
in vec2				txt_coor;

uniform bool		smod;
uniform bool		apply;
uniform bool		gmod;
uniform sampler2D	txt;

out vec4			col;

void	main()
{
	float	grey;

	if (smod)
		col = fragment_color_s;
	else
		col = fragment_color_f;
	if (apply)
		col = texture(txt, txt_coor);
    if (gmod)
    {
        grey = (0.2125 * col.x + 0.7154 * col.y + 0.0721 * col.z) / 3.0f;
        col = vec4(grey, grey, grey, 1.0f);
    }
    grey = (0.2125 * col.x + 0.7154 * col.y + 0.0721 * col.z) / 3.0f;
    col = vec4(grey, grey, grey, 1.0f);
}
