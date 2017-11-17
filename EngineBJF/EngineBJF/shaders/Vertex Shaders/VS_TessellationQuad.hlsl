struct VertexInput
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 position : POSITION;
    float4 color : COLOR;
};

VertexOutput main(VertexInput input)
{
    VertexOutput vOut;
    vOut.position = input.position;
    vOut.color = input.color;

    return vOut;
}