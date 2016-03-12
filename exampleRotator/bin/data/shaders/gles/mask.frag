uniform sampler2D texureImage;
uniform sampler2D maskTex;
varying vec2 texcoord0;

void main (void) {
    vec2 pos = texcoord0;
    vec2 maksPos;
    maksPos.x = pos.x;
    maksPos.y = pos.y;
    
    vec3 src = texture2D(texureImage, pos).rgb;
    float mask = texture2D(maskTex, maksPos).a;
    gl_FragColor = vec4(src, mask);
}