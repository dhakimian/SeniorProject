#include "Powerup.h"

Powerup::Powerup(float xPosition, float yPosition , float ang)
{
	xPos = xPosition;
	yPos = yPosition;
	Angle = ang;
	rotVel = 1.5;
	Collider.r = 10;
	imageindex = 0;
	TEX_INDEX = POWERUP;
}
void Powerup::pickup()
{
	while(dead == false)
	{
	rotVel +=1;
	if(rotVel == 20)
		dead = true;
	}
}
