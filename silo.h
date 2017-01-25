// A Silo


#ifndef SILO_H
#define SILO_H

#include "headers.h"
#include "buildings.h"


class Silo : public Building {
 public:

  // Constructors 

  Silo() {}

  Silo( vector pos ) : Building( pos ) {

    roundsLeft = 15;
  }

  bool canShoot() {
    return (roundsLeft > 0);
  }

  void decrMissiles() {
    roundsLeft--;
  }

  vector position() {
    return pos;
  }

  // Draw the silo

  void draw() {

    glColor3f( 1,1,1 );

    glBegin( GL_POLYGON );
    for (float theta=0; theta<M_PI+0.01; theta += M_PI/32)
      glVertex2f( pos.x + .04 * cos(theta), pos.y + .04 * sin(theta) );
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


 private:

  int roundsLeft;
};
  

#endif
