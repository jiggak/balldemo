attribute vec2 a_position;
uniform mat3 u_mvp_matrix;
void main() {
  gl_Position = vec4((vec3(a_position, 0.0) * u_mvp_matrix), 1.0);
}
