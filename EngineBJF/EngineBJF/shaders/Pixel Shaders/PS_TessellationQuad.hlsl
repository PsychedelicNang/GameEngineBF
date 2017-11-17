struct DS_OUTPUT
{
    float4 vPosition : SV_POSITION;
    float4 color : COLOR;
};

float4 main(DS_OUTPUT pixelInput) : SV_TARGET
{
    return float4(0.0f, 1.0f, 1.0f, 1.0f);
}