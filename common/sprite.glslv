attribute vec2 a_position;

uniform mat4 u_model_view;
uniform mat4 u_projection;
uniform vec2 u_size;

varying vec2 v_texcoord;

void main() {
  gl_Position = vec4(a_position, 0.0, 1.0) * u_model_view * u_projection;
  v_texcoord = (a_position / u_size) + vec2(0.5, 0.5);
}
