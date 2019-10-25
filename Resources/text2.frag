#ifdef GL_ES
varying lowp vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif

uniform sampler2D u_Texture;

void main(void)
{
    gl_FragColor = texture2D(CC_Texture0, v_texCoord) * texture2D(u_Texture, v_texCoord);
}