#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect texureImage;
uniform sampler2DRect maskTex;

void main (void) {
    vec2 pos = gl_TexCoord[0].st;
    vec2 maksPos;
    maksPos.x = pos.x;
    maksPos.y = pos.y;
    
    vec3 src = texture2DRect(texureImage, pos).rgb;
    float mask = texture2DRect(maskTex, maksPos).a;
//    if (drawMask == 1) {
//        mask = 1.0;
//        gl_FragColor = vec4(texture2DRect(maskTex, maksPos), mask);
//    }
    
    gl_FragColor = vec4(src, mask);
}