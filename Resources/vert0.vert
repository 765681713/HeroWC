attribute vec4 a_position;
attribute vec4 a_color;

#ifdef GL_ES
varying lowp vec4 v_color;
#else
varying vec4 v_color;
#endif

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_color = a_color;
}