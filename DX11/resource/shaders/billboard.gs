cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
	float4 camPos;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

[maxvertexcount(5)]
void GS_Billboard( point PixelInputType input[1], inout TriangleStream<PixelInputType> TriStream)
{
	float4 normal = input[0].position - camPos;
	normal = normalize(normal);

    // World/View/Projection matrix
	matrix WVPMat = { {1,0,0,0},  
					  {0,1,0,0},  
					  {0,0,1,0},  
					  {0,0,0,1}  };  
					  
	WVPMat = mul(WVPMat, worldMatrix);
	WVPMat = mul(WVPMat, viewMatrix);
	WVPMat = mul(WVPMat, projectionMatrix);
	
	// Just one point for now
	PixelInputType psOutput;
	
	/*
	// plane normal
	float3 planeNormal = float3(input[0].position.xyz) - float3(camPos.xyz);
	planeNormal.y = 0.0f;
	planeNormal = normalize(planeNormal);
	
	// Get up and right vectors
	float3 upVec = {0.0f, 1.0f, 0.0f};
	float3 rightVector = normalize(cross(planeNormal, upVec));	
	// slice our right vector down to half width (1 right now hardcoded)
	rightVector = rightVector * 1.0f;
	// Add some height into the upvec (2 right now hardcoded)
	upVec = float3(0.0f, 2.0f, 0.0f);

	
	
	psOutput.color = input[0].color;
	psOutput.position = input[0].position + float4(rightVector,1.0f); // bottom right vertex
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput);
	
	psOutput.color = input[0].color;
	psOutput.position = input[0].position - float4(rightVector,1.0f); // bottom left vertex
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput);
	
	psOutput.color = input[0].color;
	psOutput.position = input[0].position + float4(rightVector,1.0f) + float4(upVec,1.0f); // top right vertex
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput);
	
	
	psOutput.color = input[0].color;
	psOutput.position = input[0].position - float4(rightVector,1.0f) + float4(upVec,1.0f); // top left vertex
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput); 
	*/
	
	// Build quad	
	// Bottom right
	psOutput.color = input[0].color;
	psOutput.position.x = input[0].position.x + 1.0f;
	psOutput.position.y = input[0].position.y - 1.0f;
	psOutput.position.z = input[0].position.z;
	psOutput.position.w = input[0].position.w;
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput);
	
	// Bottom left
	psOutput.color = input[0].color;
	psOutput.position.x = input[0].position.x - 1.0f;
	psOutput.position.y = input[0].position.y - 1.0f;
	psOutput.position.z = input[0].position.z;
	psOutput.position.w = input[0].position.w;
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput);
	
	// Top Right
	psOutput.color = input[0].color;
	psOutput.position.x = input[0].position.x + 1.0f;
	psOutput.position.y = input[0].position.y + 1.0f;
	psOutput.position.z = input[0].position.z;
	psOutput.position.w = input[0].position.w;
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput);
	
	/*
	// Top left
	psOutput.color = input[0].color;
	psOutput.position.x = input[0].position.x - 1.0f;
	psOutput.position.y = input[0].position.y + 1.0f;
	psOutput.position.z = input[0].position.z;
	psOutput.position.w = input[0].position.w;
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput);
	
		// Bottom left
	psOutput.color = input[0].color;
	psOutput.position.x = input[0].position.x - 1.0f;
	psOutput.position.y = input[0].position.y - 1.0f;
	psOutput.position.z = input[0].position.z;
	psOutput.position.w = input[0].position.w;
	psOutput.position = mul(psOutput.position,WVPMat);
	TriStream.Append(psOutput);
	*/
	
}