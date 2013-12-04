#include "MovingObject.h"
#include "Laser.h"
#include <iostream>
#include "Vec2D.h"

MovingObject::MovingObject()
{
    xVel = 0.0;
    yVel = 0.0;
    rotVel = 0.0;

    Collider.x = xPos;
    Collider.y = yPos;

    can_take_damage = true;
}

int MovingObject::get_type()
{
    return T_MOVOBJ;
}

void MovingObject::update()
{
    Object::update();

    xPos_old = xPos;
    yPos_old = yPos;

    xVel_old = xVel;
    yVel_old = yVel;
    rotVel_old = rotVel;

    //Collider.x = xPos;
    //Collider.y = yPos;

    std::vector<Object*> overlapping;

    //check if object is already colliding
    for( uint i=0; i<objects.size(); i++ )
    {
        Circle other_collider = objects[i]->get_collider();
        if( solid && objects[i]->is_solid()
                && (objects[i] != this)
                && ( objects[i]->get_team() != get_team()
                    || objects[i]->get_team() < 0 )
                && checkCollision( Collider, other_collider )
          )
        {
            overlapping.push_back(objects[i]);
            if( (Collider.x - other_collider.x) < 0 )
                xVel -= Separation_vel;
            else
                xVel += Separation_vel;

            if( (Collider.y - other_collider.y) < 0 )
                yVel -= Separation_vel;
            else
                yVel += Separation_vel;
        }
    }

    if( rotVel > 20 )
        takeDamage(1);

    //Move the object left or right
    xPos = fmod( (xPos + xVel + LEVEL_WIDTH), LEVEL_WIDTH );

    //Move the object up or down
    yPos = fmod( (yPos + yVel + LEVEL_HEIGHT), LEVEL_HEIGHT );

    // apparently fmod (float modulo) doesn't do negative numbers (I think it takes the abs val)
    // so to get around this I just shift the number line to avoid passing negatives to fmod, 
    // hence the added LEVEL_WIDTH/LEVEL_HEIGHT in the first args

    //Rotate the object clockwise or counter-clockwise
    Angle = fmod( (Angle + rotVel + 360), 360 );

    xVel -= (Speed_Decay * xVel);
    yVel -= (Speed_Decay * yVel);
    rotVel -= ((Speed_Decay/5) * rotVel);

    Collider.x = xPos;
    Collider.y = yPos;

    //Next-frame collision checks
    for( uint i=0; i<objects.size(); i++ )
    {
        Circle other_collider = objects[i]->get_collider();
        std::vector<Object*>::iterator obj;
        obj = std::find(overlapping.begin(), overlapping.end(), objects[i]);
        if( objects[i] != this && obj == overlapping.end()
                && checkCollision( Collider, other_collider ) )
            onCollide( objects[i] );
    }
}

void MovingObject::onCollide( Object* collided_with )
{
    if( solid && collided_with->is_solid()
            && ( collided_with->get_team() != get_team()
                || collided_with->get_team() < 0 ) )
    {
        float xPos_other, yPos_other, Angle_other, xVel_other, yVel_other, rotVel_other;
        collided_with->get_values(&xPos_other, &yPos_other, &Angle_other,
                &xVel_other, &yVel_other, &rotVel_other);

        //float vel_old = sqrt( xVel_old*xVel_old + yVel_old*yVel_old );
        //float vel_other = sqrt( xVel_other*xVel_other + yVel_other*yVel_other );

        float vel_old_squared = xVel_old*xVel_old + yVel_old*yVel_old;
        float vel_other_squared = xVel_other*xVel_other + yVel_other*yVel_other;
        float v1 = sqrt( vel_old_squared );
        float v2 = sqrt( vel_other_squared );
        //float m1 = get_mass();
        //float m2 = collided_with->get_mass();

        //std::cout<<get_team()<<" tA|tB "<<collided_with->get_team()<<std::endl;
        //std::cout<<m1<<" m1|m2 "<<m2<<std::endl;

        //////(m1*v1*v1 + m2*v2*v2)*loss_factor = m1*v1'*v1' + m2*v2'*v2'

        //float v1_new = ((m1-m2)/(m1+m2))*v1 + ((m2+m2)/(m1+m2))*v2;
        //float v2_new = ((m2-m1)/(m1+m2))*v2 + ((m1+m1)/(m1+m2))*v1;
        //v1_new /= LOSS_FACTOR;
        //v2_new /= LOSS_FACTOR;
        //float A = atan2( yPos_old-yPos_other, xPos_old-xPos_other );
        //float angle2_new = atan( (yPos_other-yPos_old)/(xPos_other-xPos_old) );
        //float angle1_new = 0;
        //float angle2_new = 0;

        //std::cout<<angle1_new<<" a1|a2 "<<angle2_new<<"\n"<<std::endl;

        //angle1_new -= M_PI/2;
        //angle2_new -= M_PI/2;

        /////--------------------
        // Most of the following code is stolen/adapted from here:
        // http://stackoverflow.com/questions/345838/ball-to-ball-collision-detection-and-handling
        //
        Vec2D delta;
        delta.set(xPos_old - xPos_other, yPos_old - yPos_other);
        float d = delta.get_length();
        Vec2D mtd = delta.multiply( ( (Collider.r + collided_with->get_collider().r) - d) / d );

        float im1 = 1 / get_mass(); 
        float im2 = 1 / collided_with->get_mass();

        Vec2D v;
        v.set(xVel_old - xVel_other, yVel_old - yVel_other);
        float vn = v.dot(mtd.normalize());

        //float lf = LOSS_FACTOR;
        //float res = .85;
        float res = 1;
        /*
        if( v1 < 1 )
        {
            res = 0.1;
            lf = 1;
        }
        */
        float i = (-(1.0f + res) * vn) / (im1 + im2);
        //float i = (-(1.95) * vn) / (im1 + im2);
        //float i = -vn / (im1 + im2);
        Vec2D impulse = mtd.multiply(i);

        //this.velocity = this.velocity.add(impulse.multiply(im1));
        //ball.velocity = ball.velocity.subtract(impulse.multiply(im2));
        
        xVel += (impulse.get_x()*im1);
        yVel += (impulse.get_y()*im1);

        float xVel2 = xVel_other;
        float yVel2 = yVel_other;

        xVel2 -= (impulse.get_x()*im2);
        yVel2 -= (impulse.get_y()*im2);

        //xVel /= lf;
        //yVel /= lf;
        //xVel2 /= lf;
        //yVel2 /= lf;

        collided_with->set_values( xPos_other, yPos_other, Angle_other,
                xVel2, yVel2, rotVel_other );

        //
        //
        //
        //////----------------------

        /*
        xVel = v1_new*cos(angle1_new);
        yVel = v1_new*sin(angle1_new);
        collided_with->set_values( xPos_other, yPos_other, Angle_other,
                v2_new*cos(angle2_new), v2_new*sin(angle2_new), rotVel_other );
        */

        //Undo move left or right
        xPos = xPos_old;

        //Undo move up or down
        yPos = yPos_old;

        Collider.x = xPos;
        Collider.y = yPos;
        /////

        //damage the object depending on how fast it was moving when it collided
        //int damage = abs( vel_old_squared - vel_other_squared ) * Collision_Damage_multiplier;
        int damage = abs( v1 - v2 ) * Collision_Damage_multiplier;
        //if( damage > 0 )
            //std::cout<<damage<<" collision damage"<<std::endl;
        takeDamage( damage );
        collided_with->takeDamage( damage );
        /*
    } else {
        if( collided_with->get_type() == T_EXPLOSION )
        {
            takeDamage(1);
        }
        //else if( )
        //{
        //}
        */
    }
}
