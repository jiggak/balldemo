attribute vec2 a_position;
uniform mat3 u_mvp_matrix;
varying vec2 v_texcoord;

void main() {
  gl_Position = vec4((vec3(a_position, 0.0) * u_mvp_matrix), 1.0);
  v_texcoord = a_position * vec2(0.5) + vec2(0.5);
}
