struct PSOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uvs : UVS;
};

PSOutput main(PSOutput input)
{
    PSOutput output;
    output.pos = float4(0, 0, 0, 0);
    output.color = float4(0, 0, 0, 1);
    output.uvs = float2(0, 0);

    return output;
}