#ifdef GL_ES
precision highp float;
#endif

uniform vec2 u_resolution;
uniform float u_time;
uniform float s_linesSize;

uniform float s_breatheAlpha;
uniform float s_breatheValue;

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    float aspect = u_resolution.x / u_resolution.y;
    vec2 position = 0.5 - uv;           
    if (aspect > 1.) aspect = 2.0 / aspect;

    vec2 uvd = 1.6 * vec2(position.x, position.y / aspect);
    uvd.x += .1 * cos(10. * uvd.y + 0.08 * u_time);
    uvd.y += .1 * sin(10. * uvd.x + 0.08 * u_time);


    float r = 10.0 * sqrt(dot(uvd, uvd));
    float value = (1.0 * sin(40.0 * r * s_linesSize - 4.0 * u_time));
    float col = smoothstep(0.5 - 0.2, 0.5, value);
    vec3 color = vec3(col, col, col);
    gl_FragColor = vec4(color, 1.0 * s_breatheAlpha);
}