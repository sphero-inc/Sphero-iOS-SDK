/*
<codex>
<abstract>Simple fragment shader.</abstract>
<version>1.0</version>
</codex>
*/

precision mediump float;

varying vec4 v_color;

void main()
{
	gl_FragColor = v_color;
}
