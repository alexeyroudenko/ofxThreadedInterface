attribute vec4 position;
attribute vec2 texcoord;				// set automatically by OF 

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
varying vec2 texcoord0;

void main() {
	gl_Position = projectionMatrix * modelViewMatrix * position;;
	texcoord0 = texcoord;
}
