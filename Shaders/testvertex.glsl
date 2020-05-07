#version 410 core

in vec3 		pos;

uniform mat4	mvp;
uniform int		color;

flat out vec4	fragment_color_f;
out vec4		fragment_color_s;
out	vec2		txt_coor;

void	main()
{
    float	grey;

	gl_Position = mvp * vec4(pos, 1.0f);
	if (color == 0)
    {
        grey = (pos.y * 0.2125 + pos.z * 0.7154 + pos.y * 0.0721) / 3.0f;
        fragment_color_s = vec4(grey, grey, grey, 1.0f);
    }
    if (color == 1)
		fragment_color_s = vec4(pos * 0.4f + 0.4f, 1.0f);
	fragment_color_f = fragment_color_s;
    txt_coor = vec2(pos.x * 2, pos.y * 2);
}
