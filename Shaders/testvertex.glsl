#version 410 core

in vec3 		pos;

uniform mat4	mvp;
uniform int		color;

flat out vec4	fragment_color_f;
out vec4		fragment_color_s;
out	vec2		txt_coor;

void	main()
{
	gl_Position = mvp * vec4(pos, 1.0f);
	if (color == 0)
        fragment_color_s = vec4((pos.x * 0.2125) / 3.0f, (pos.x * 0.3154) / 3.0f, (pos.x * 0.4821) / 3.0f , 1.0f);
    if (color == 1)
		fragment_color_s = vec4(pos * 0.4f + 0.4f, 1.0f);
	fragment_color_f = fragment_color_s;
    txt_coor = vec2(pos.x * 2, pos.y * 2);
}
