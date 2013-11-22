#ifndef _POWERUP_H
#define _POWERUP_H

#include "MovingObject.h"

class Powerup : public MovingObject
{
	public:
		Powerup(float xPosition = 0.0, float yPosition = 0.0, float ang = 0.0);
		void pickup();

		int imageindex = 0;
	protected:
		
	
};

#endif