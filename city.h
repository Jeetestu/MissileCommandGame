// A city


#ifndef CITY_H
#define CITY_H


#include "buildings.h"


class City : public Building {
 public:

  // Constructors 

  City() {}

  City( vector pos ) : Building( pos ) {}

  // Draw the city

  void draw() {

    glColor3f( 1,1,1 );

    glBegin( GL_POLYGON );
    glVertex2f( pos.x + .04, pos.y );
    glVertex2f( pos.x + .04, pos.y + .03 );
    glVertex2f( pos.x - .04, pos.y + .03 );
    glVertex2f( pos.x - .04, pos.y );
    glEnd();
  }

  bool isHit( vector missilePos, float radius ){
      // check if explosions centre lies within city
      if((pos.x + .04) >= missilePos.x &&
         (pos.x - .04) <= missilePos.x &&
	 	   0.03 >= missilePos.y -radius)
         return true;
      if((pos.x + .04) >= missilePos.x + radius &&
         (pos.x - .04) <= missilePos.x + radius &&
	 	   0.03 >= missilePos.y -radius)
         return true;
      if((pos.x + .04) >= missilePos.x - radius &&
         (pos.x - .04) <= missilePos.x - radius &&
	 	   0.03 >= missilePos.y -radius)
         return true;

      return false;
  } 
};
  


#endif
