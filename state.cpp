// state.cpp


#include "headers.h"

#include "state.h"


// Draw each of the objects in the world


void State::draw() 

{
  int i;

  for (i=0; i<silos.size(); i++)
    silos[i].draw();

  for (i=0; i<cities.size(); i++)
    cities[i].draw();

  for (i=0; i<missilesIn.size(); i++)
    missilesIn[i].draw();

  for (i=0; i<missilesOut.size(); i++)
    missilesOut[i].draw();

  for (i=0; i<explosions.size(); i++)
    explosions[i].draw();
}


// Update the state of the world after some time interval, deltaT
//
// CHANGE ALL OF THIS FUNCTION


void State::updateState( float deltaT )

{
  int i;

  // Update the time

  currentTime += deltaT;

  // Generate some new missiles.  The rate of missle generation
  // should increase with time.
  float prob = (currentTime / 60.0) / 10.0; // probablity to increase by 10% every min
  // I feel like this should be higher but i suck playing this game
  if (randIn01() < 0.05 +  prob) {	
    float vx = randIn01() / 50.0;  
    float vy = randIn01() / 50.0;
    float dir = randIn01();
    if (dir < 0.25){
	vx = -vx;
	vy = -vy;
    }
    else if(dir >= 0.25 && dir < 0.5){
	vx = -vx;
    }
    else if(dir >= 0.5 && dir < 0.75)
	vy = -vy;

    missilesIn.add( Missile( vector( randIn01(), worldTop, 0), // source
			     vector(vx, vy, 0 ),   // velocity
			     0,                      // destination y
			     vector( 1,1,0 ) ) );    // colour
  }

  // Look for terminating missiles

  for (i=0; i<missilesIn.size(); i++)
    if (missilesIn[i].hasReachedDestination()) {
      // CHANGE THIS: ADD AN EXPLOSION
      explosions.add(Circle(missilesIn[i].position(), 0.01, 0.02, vector(0.94,0.2,0.2)));
      missilesIn.remove(i);
      i--;
    }

  for (i=0; i<missilesOut.size(); i++)
    if (missilesOut[i].hasReachedDestination()) {
      // CHANGE THIS: ADD AN EXPLOSION
      explosions.add(Circle(missilesOut[i].position(), 0.01, 0.04, vector(0.0, 1.0, 0.0)));
      //std::cout << missilesOut[i].position() << std::endl;
      missilesOut.remove(i);
      i--;
    }

  // Look for terminating explosions

  for (i=0; i<explosions.size(); i++)
    if (explosions[i].radius() >= explosions[i].maxRadius()) {
      // CHANGE THIS: CHECK FOR DESTROYED CITY OR SILO
      //check cities
      for(int j = 0; j < cities.size(); j++){
	if(cities[j].isHit(explosions[i].getPosition(), explosions[i].radius())){
	  cities.remove(j);
	  j--;
        }
      }
      // check silos
      for(int j = 0; j < silos.size(); j++){
        if(silos[j].isHit(explosions[i].getPosition(), explosions[i].radius())){
          silos.remove(j);
          j--;
        }
      }

      explosions.remove(i);
      i--;
    }

  // Look for incoming missiles that hit an explosion and are
  // destroyed

  // ADD CODE HERE
  vector missilePos;
  vector explosionPos;
  float  explosionRad;

  for(i = 0 ; i < missilesIn.size(); i++){
     missilePos = missilesIn[i].position();
     for(int j = 0; j < explosions.size(); j++){
	explosionPos = explosions[j].getPosition();
	explosionRad = explosions[j].radius();
	if(explosionPos.x + explosionRad >= missilePos.x &&
	   explosionPos.x - explosionRad <= missilePos.x &&
	   explosionPos.y + explosionRad >= missilePos.y &&
           explosionPos.y - explosionRad <= missilePos.y){
	   missilesIn.remove(i);
	   i--;
	}
     }
  }

  // Update all the moving objects

  for (i=0; i<missilesIn.size(); i++)
    missilesIn[i].move( deltaT );

  for (i=0; i<missilesOut.size(); i++)
    missilesOut[i].move( deltaT );

  for (i=0; i<explosions.size(); i++)
    explosions[i].expand( deltaT );
}


// Fire a missile

void State::fireMissile( int siloIndex, float x, float y )

{
  const float speed = 0.3;
  if(siloIndex >= silos.numElements)
	return;

  if (silos[siloIndex].canShoot()) {

    silos[siloIndex].decrMissiles();

    // CHANGE THIS
    vector pos = silos[siloIndex].position();
    vector velo = (vector(x,y,0) - pos).normalize();
    missilesOut.add( Missile( silos[siloIndex].position(),   // source
			 speed * velo, //vector(randIn01(), randIn01(), 0), // velocity
			      y,                             // destination y
			      vector( 0,1,1 ) ) );           // colour
  }
}



// Create the initial state of the world


void State::setupWorld()

{
  // Keep track of the time

  currentTime = 0;

  timeOfIncomingFlight = 6;	// 6 seconds for incoming missile to arrive

  // Seed the random number generator

#ifdef _WIN32
  srand( 12345 );
#else
  struct timeb t;
  ftime( &t );
  srand( t.time );
#endif

  // Silos are added in order left, middle, right so that they have
  // indices 0, 1, and 2 (respectively) in the "silos" array.

  silos.add(  Silo( vector( 0.1, 0, 0 ) ) );
  silos.add(  Silo( vector( 0.5, 0, 0 ) ) );
  silos.add(  Silo( vector( 0.9, 0, 0 ) ) );

  // Cities on the left

  cities.add( City( vector( 0.2, 0, 0 ) ) );
  cities.add( City( vector( 0.3, 0, 0 ) ) );
  cities.add( City( vector( 0.4, 0, 0 ) ) );

  // Cities on the right

  cities.add( City( vector( 0.6, 0, 0 ) ) );
  cities.add( City( vector( 0.7, 0, 0 ) ) );
  cities.add( City( vector( 0.8, 0, 0 ) ) );
}
