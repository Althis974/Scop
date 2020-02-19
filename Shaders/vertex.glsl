#version 330

in vec2 in_position;
out vec2 position;


void main() {

    position = in_position;
    gl_Position = vec4(in_position.x, in_position.y, 0.0, 1.0);
}
