#version 410 core

in vec3 		pos;

flat out vec4	frag_flat;
out vec4		frag_smooth;
out	vec2		txt_coor;

uniform mat4	mvp;
uniform bool	color;

void			main()
{
    float 		grey;

	gl_Position = mvp * vec4(pos, 1.0f);
    if (color)
        frag_smooth = vec4(pos * 0.97f + 0.4f, 1.0f);
	else
    {
        frag_smooth = vec4(pos * 0.4f + 0.4f, 1.0f);
        grey = (0.2125 * frag_smooth.x + 0.7154 * frag_smooth.y + 0.0721 * frag_smooth.z) / 3.0f;
        frag_smooth = vec4(grey, grey, grey, 1.0f);
    }
    frag_flat = frag_smooth;
    txt_coor = vec2(pos.x * 2, pos.y * 2);
}
