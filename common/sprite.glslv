attribute vec2 a_position;

uniform mat3 u_model_view;
uniform mat3 u_projection;
uniform vec2 u_size;

varying vec2 v_texcoord;

void main() {
  vec3 position = vec3(a_position, 0.0) * u_model_view * u_projection;
  gl_Position = vec4(position, 1.0);
  v_texcoord = (a_position / u_size) + vec2(0.5, 0.5);
}
