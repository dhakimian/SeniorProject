#include "Laser.h"

Laser::Laser()
{

    //xPos = 0;
    //yPos = 0;

    Collider.r = 2;

    TEX_INDEX = LASER1;
    explode_sound = Mix_LoadWAV( "media/sounds/Hit.wav");
    weapon_level = 1;
    time_powerup = 1;
}

void Laser::set_values(float x, float y, float ang, float xv, float yv, int time)
{
    xPos = x;
    yPos = y;
    Angle = ang;
    xVel = xv;
    yVel = yv;
    time_left = time;
    dead = false;
    if (weapon_level == 1)
        TEX_INDEX = LASER1;
    else if (weapon_level == 2)
        TEX_INDEX = LASER2;
    else if (weapon_level == 3)
        TEX_INDEX = LASER3;
    else
    {
        TEX_INDEX = LASER4;
    }
    img_index = -1;
    boom = false;
    channelint = 1;
}

void Laser::explode()
{
    xVel /= 1.11;
    yVel /= 1.11;
    if(img_index < 0)
        TEX_INDEX = EXP_0;
    else if(img_index < 1){
        TEX_INDEX = EXP_1;
        Mix_PlayChannel( channelint, explode_sound, 0 );
        }
    else if(img_index < 2)
        TEX_INDEX = EXP_2;
    else if(img_index < 3)
        TEX_INDEX = EXP_3;
    else if(img_index < 4)
        TEX_INDEX = EXP_4;
    else if(img_index < 5)
        TEX_INDEX = EXP_5;
    else if(img_index < 6)
        TEX_INDEX = EXP_6;
    else if(img_index < 7)
        TEX_INDEX = EXP_7;
    else if(img_index < 8)
        TEX_INDEX = EXP_8;
    else if(img_index < 9)
        TEX_INDEX = EXP_9;
    else if(img_index < 10)
        TEX_INDEX = EXP_10;
    else if(img_index < 11)
        TEX_INDEX = EXP_11;
    else if(img_index < 12)
        TEX_INDEX = EXP_12;
    else if(img_index < 13)
        TEX_INDEX = EXP_13;
    else if(img_index < 14)
        TEX_INDEX = EXP_14;
    else if(img_index < 15)
        TEX_INDEX = EXP_15;
    else if(img_index < 16)
        TEX_INDEX = EXP_16;
    else if(img_index < 17)
        TEX_INDEX = EXP_17;
    else if(img_index < 18)
        TEX_INDEX = EXP_18;
    else if(img_index < 18)
        TEX_INDEX = EXP_19;
    else if(img_index < 20)
        TEX_INDEX = EXP_20;
    else if(img_index < 21)
        TEX_INDEX = EXP_21;
    else if(img_index < 22)
        TEX_INDEX = EXP_22;
    else if(img_index < 23)
        TEX_INDEX = EXP_23;
    else if(img_index < 24)
        TEX_INDEX = EXP_24;
    else if(img_index < 25)
        TEX_INDEX = EXP_25;
    else if(img_index < 26)
        TEX_INDEX = EXP_26;
    else if(img_index < 27)
        TEX_INDEX = EXP_27;   
    else if(img_index < 28)
        TEX_INDEX = EXP_28;
    else if(img_index < 29)
        TEX_INDEX = EXP_29;
    else if(img_index < 30)
        TEX_INDEX = EXP_30;
    else if(img_index < 31)
        TEX_INDEX = EXP_31;
    else if(img_index < 32)
        TEX_INDEX = EXP_32;
    else if(img_index < 33)
        TEX_INDEX = EXP_33;
}


void Laser::update()
{
    time_left--;
    if( time_left <= 0 )
        dead = true;
    else
        MovingObject::update();
}

void Laser::upgrade()
{
    weapon_level++;
    //also change collider dimention depending on how the images change
}
