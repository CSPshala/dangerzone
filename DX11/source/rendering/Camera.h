///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Camera.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Camera...duh
///////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <d3dx10math.h>

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class Camera
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Camera();
	~Camera();

	/********** Public Utility Functions ************/
	void Render();

	/********** Public Accessors ************/
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void GetViewMatrix(D3DXMATRIX&);	

	/********** Public Mutators  ************/	
	void SetPosition(float x, float y, float z);
	void SetPosition(const D3DXVECTOR3& in);
	void SetRotation(float x, float y, float z);
	void SetRotation(const D3DXVECTOR3& in);
	void SetMoveDelta(const D3DXVECTOR3& in) { m_moveDelta = in; }

private:
	/********** Private Members ************/
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXVECTOR3 m_moveDelta;
	D3DXMATRIX m_viewMatrix;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif