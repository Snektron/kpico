attribute highp vec4 aVertices;
attribute highp vec2 aTexCoords;

varying vec2 vTexCoords;

void main()
{
        vTexCoords = aTexCoords;
        gl_Position = vec4(aVertices.xy, 0, 1);
}
