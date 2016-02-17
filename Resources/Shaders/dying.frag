uniform sampler2D texture;
uniform bool expand;
uniform float time;
uniform float maxTime;


void main()
{
    float delta;
    if (expand) delta = (time/maxTime);
    else delta = 1.0-(time/maxTime);

    gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color * vec4(1.0,1.0,1.0,delta);
    
}