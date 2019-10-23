attribute vec4 a_position;

#ifdef GL_ES
varying lowp vec4 v_position;
#else
varying vec4 v_position;
#endif

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_position = a_position;
}