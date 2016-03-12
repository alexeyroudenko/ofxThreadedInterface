uniform vec2 resolution;
uniform float time;
uniform sampler2DRect texture0;
uniform sampler2DRect texture1;

uniform float parameter0;
uniform float parameter1;
uniform float parameter2;
uniform float parameter3;
uniform float parameter4;
uniform float parameter5;
uniform float parameter6;

void main() {
    vec2 pos = gl_TexCoord[0].st;
    vec2 position = gl_TexCoord[0].st -.5  + parameter0 * 0.5 * sin(parameter1 * time / 100.0 + pos.y / 200.0) * cos(parameter2 * time / 100.0 + cos(pos.x / 100.0));
    vec2 center = resolution.xy / 2.0;
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec3 color = texture2DRect(texture0, position).rgb;
    vec3 cameraColor = texture2DRect(texture1, position).rgb;
    vec2 displaced = position + parameter4 * .01 * (position - center);
    vec4 colorFade = texture2DRect(texture0, displaced);
    vec3 result = 1.0 * color.rgb * (cameraColor.r * parameter5 * 0.01) + parameter3 * .05 * (color.rgb - 1.2 * colorFade.rgb);
    gl_FragColor = vec4(result.r + 0.1 * cameraColor.r, result.r, result.r, 1.0);
    //gl_FragColor = vec4(cameraColor.r, cameraColor.r, cameraColor.r, 1.0);
}