attribute vec2 a_position;

uniform mat4 u_projection;
uniform mat4 u_translation;

uniform vec2  u_char_size;
uniform float u_char_offset;
uniform float u_char_scale;

varying vec2 v_texcoord;

void main() {
  gl_Position = vec4(a_position, 0.0, 1.0) * u_translation * u_projection;
  vec2 texcoord = (a_position / u_char_size) + vec2(0.5, 0.5);
  mat2 scale = mat2(u_char_scale, 0.0, 0.0, 1.0);
  v_texcoord = (texcoord * scale) + vec2(u_char_offset * u_char_scale, 0.0);
}
