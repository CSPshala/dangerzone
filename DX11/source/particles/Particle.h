///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Particle.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle particle data
///////////////////////////////////////////////////////////////////////////
#ifndef _PARTICLE_H
#define _PARTICLE_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "Emitter.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class Particle : public Emitter
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Particle();
	~Particle();

	/********** Public Utility Functions ************/

	/********** Public Accessors ************/	
	void Update(float deltaTime);

	/********** Public Mutators  ************/		

private:
	/********** Private Members ************/	

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif