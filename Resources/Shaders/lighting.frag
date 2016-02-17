// uniform sampler2D texture;
// uniform vec2 posLight;
// uniform float maxx;
// uniform float minn;


// float intensity(in vec4 color)
// {
//     //return 0.2126 * color.x + 0.7152 * color.y + 0.722 * color.z;
//     return 0.333 * color.x + 0.333 * color.y + 0.333 * color.z;
// }

// void main()
// {
//     vec2 pix = gl_FragCoord.st;
//     float distance = sqrt((posLight.x - pix.x)*(posLight.x - pix.x)+(posLight.y-pix.y)*(posLight.y-pix.y));
//     float delta = max(1.0-((distance - minn) / (maxx - minn)),0.1);
    
//     // sobel broken
//     // float x = 1.0;
//     // float y = 1.0;
//     // vec2 sign = vec2(1.0);
//     // vec4 horizEdge = vec4( 0.0 );
//     // horizEdge -= intensity( texture2D( texture, vec2( gl_TexCoord[0].x - x, gl_TexCoord[0].y - y ) ) ) * 1.0 * sign.x;
//     // horizEdge -= intensity( texture2D( texture, vec2( gl_TexCoord[0].x - x, gl_TexCoord[0].y     ) ) ) * 2.0 * sign.x;
//     // horizEdge -= intensity( texture2D( texture, vec2( gl_TexCoord[0].x - x, gl_TexCoord[0].y + y ) ) ) * 1.0 * sign.x;
//     // horizEdge += intensity( texture2D( texture, vec2( gl_TexCoord[0].x + x, gl_TexCoord[0].y - y ) ) ) * 1.0 * sign.x;
//     // horizEdge += intensity( texture2D( texture, vec2( gl_TexCoord[0].x + x, gl_TexCoord[0].y     ) ) ) * 2.0 * sign.x;
//     // horizEdge += intensity( texture2D( texture, vec2( gl_TexCoord[0].x + x, gl_TexCoord[0].y + y ) ) ) * 1.0 * sign.x;
//     // vec4 vertEdge = vec4( 0.0 );
//     // vertEdge -= intensity( texture2D( texture, vec2( gl_TexCoord[0].x - x, gl_TexCoord[0].y - y ) ) ) * 1.0 * sign.y;
//     // vertEdge -= intensity( texture2D( texture, vec2( gl_TexCoord[0].x    , gl_TexCoord[0].y - y ) ) ) * 2.0 * sign.y;
//     // vertEdge -= intensity( texture2D( texture, vec2( gl_TexCoord[0].x + x, gl_TexCoord[0].y - y ) ) ) * 1.0 * sign.y;
//     // vertEdge += intensity( texture2D( texture, vec2( gl_TexCoord[0].x - x, gl_TexCoord[0].y + y ) ) ) * 1.0 * sign.y;
//     // vertEdge += intensity( texture2D( texture, vec2( gl_TexCoord[0].x    , gl_TexCoord[0].y + y ) ) ) * 2.0 * sign.y;
//     // vertEdge += intensity( texture2D( texture, vec2( gl_TexCoord[0].x + x, gl_TexCoord[0].y + y ) ) ) * 1.0 * sign.y;
//     // // vec3 edge = sqrt((horizEdge.rgb * horizEdge.rgb) + (vertEdge.rgb * vertEdge.rgb));
//     // vec4 edge = vec4(sqrt(horizEdge.rgb * horizEdge.rgb), texture2D( texture, gl_TexCoord[0].xy ).a );
    
    
//     vec4 textureColor = //vec4( edge, texture2D( texture, gl_TexCoord[0].xy ).a );
//         texture2D(texture, vec2( gl_TexCoord[0].xy)) ;

//     vec4 color = textureColor * gl_Color;

//     if (distance > maxx) gl_FragColor = color * vec4(0.1,0.1,0.1,1) * intensity(color);//*vec4(0.9,0.9,0.9,1) ;
//     else if (distance < minn) gl_FragColor = color;
//     else gl_FragColor = color * vec4(delta,delta,delta,1.0) * intensity(color);//*vec4(1.0-delta,1.0-delta,1.0-delta,1); 

//     // gl_FragColor = color;

//     //if (delta < posDelta) gl_FragColor = vec4(posDelta,posDelta,posDelta,1);

// }

uniform sampler2D texture;
uniform vec2 posLight;
uniform float maxx;
uniform float minn;


void main()
{
    vec2 pix = gl_FragCoord.st;
    float distance = sqrt((posLight.x - pix.x)*(posLight.x - pix.x)+(posLight.y-pix.y)*(posLight.y-pix.y));
    float delta = max(1.0-((distance - minn) / (maxx - minn)),0.1);
    if (distance > maxx) gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * vec4(0.1,0.1,0.1,1) * gl_Color;
    else if (distance < minn) gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;
    else gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * vec4(delta,delta,delta,1.0);
    //if (delta < posDelta) gl_FragColor = vec4(posDelta,posDelta,posDelta,1);

}