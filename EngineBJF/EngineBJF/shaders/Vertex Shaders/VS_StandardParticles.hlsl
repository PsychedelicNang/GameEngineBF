struct Vertex {
	float3 InitialPosW : POSITION; 
	float3 InitialVelW : VELOCITY; 
	float2 SizeW       : SIZE;
	float Age			: AGE; 
	uint Type          : TYPE;
};


float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}