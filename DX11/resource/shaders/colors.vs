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
struct ColorVertexInputType
{
    float3 position : POSITION;
    float3 color : COLOR;
};

struct ColorPixelInputType
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
ColorPixelInputType ColorVertexShader(ColorVertexInputType input)
{
    ColorPixelInputType output;    

	float4 pos = float4(input.position,1.0f);

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(pos, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Store the color for the pixel shader.
    output.color = input.color;
    
    return output;
}