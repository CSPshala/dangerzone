// http://www.rastertek.com/dx11tut04.html
/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
	float4 camPos;
};

//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;
	
	matrix WVPMat = { {1,0,0,0},  
					  {0,1,0,0},  
					  {0,0,1,0},  
					  {0,0,0,1}  };  
					  
	WVPMat = mul(WVPMat, worldMatrix);
	WVPMat = mul(WVPMat, viewMatrix);
	WVPMat = mul(WVPMat, projectionMatrix);

    // Calculate the position of the vertex against the world, view, and projection matrices.
    //output.position = mul(input.position, worldMatrix);
    //output.position = mul(output.position, viewMatrix);
    //output.position = mul(output.position, projectionMatrix);
	//output.position = mul(worldMatrix,input.position);
    //output.position = mul(viewMatrix,output.position);
    //output.position = mul(projectionMatrix,output.position);
	
	output.position = mul(input.position, WVPMat);
    
    // Store the input color for the pixel shader to use.
    output.color = input.color;
    
    return output;
}