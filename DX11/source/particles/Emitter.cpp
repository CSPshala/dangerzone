///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Emitter.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Manage particle behavior
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "Emitter.h"
#include "Particle.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
Emitter::Emitter()
{
	m_velocity = D3DXVECTOR3(0,0,0);
	m_position = D3DXVECTOR3(0,0,0);
	m_isAlive = false;	
}

Emitter::~Emitter()
{	
	for(unsigned int i = 0; i < m_Particles.size(); ++i) {
		if(m_Particles[i]) {
			delete m_Particles[i];
		} }	
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool Emitter::Initialize()
{
	bool result;


	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = m_RenderContext.Initialize();
	if(!result)
	{
		return false;
	}

	return true;
}

void Emitter::Shutdown()
{
	// Release the vertex and index buffers.
	m_RenderContext.Shutdown();

	return;
}

void Emitter::Update(float deltaTime)
{
	// Update myself
	SetPosition(GetPosition() + GetVelocity());

	// Update particles
	for(unsigned int i = 0; i < m_Particles.size(); ++i) {
		m_Particles[i]->Update(deltaTime);
	}
}

void Emitter::Render()
{
	m_RenderContext.RenderBuffers();
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////


////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
void Emitter::AddParticle(Particle* in)
{
	m_Particles.push_back(in);
}

void Emitter::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Emitter::SetVelocity(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////