///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Emitter.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Manage particle behavior
///////////////////////////////////////////////////////////////////////////
#ifndef _EMITTER_H
#define _EMITTER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <vector>
using std::vector;

#include "../rendering/ForwardRenderer.h"
#include "../rendering/ParticleContext.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class Particle;

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class Emitter
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Emitter();
	~Emitter();
	/********** Public Utility Functions ************/
	bool Initialize();
	void Shutdown();
	virtual void Update(float deltaTime);
	virtual void Render();

	/********** Public Accessors ************/
	vector<Particle*>& GetParticles() { return m_Particles; }
	const D3DXVECTOR3&	GetPosition() { return m_position; }
	const D3DXVECTOR3&  GetVelocity() { return m_velocity; }
	bool  GetIsAlive() { return m_isAlive; }

	/********** Public Mutators  ************/	
	void AddParticle(Particle* in);
	void SetPosition(const D3DXVECTOR3& in) { m_position = in; }
	void SetPosition(float x, float y, float z);
	void SetVelocity(const D3DXVECTOR3& in) { m_velocity = in; }
	void SetVelocity(float x, float y, float z);
	void SetIsAlive(bool in) { m_isAlive = in; }

	/*********** Public datatypes ***********/


private:
	/********** Private Members ************/
	// Particles
	vector<Particle*>	m_Particles;
	// Movement values
	D3DXVECTOR3		m_velocity;
	D3DXVECTOR3		m_position;
	// Life values
	bool			m_isAlive;
	// Render context
	ParticleContext m_RenderContext;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	
};
#endif