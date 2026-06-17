#ifndef DataSizes_h
#define DataSizes_h

#include "IG2Object.h"
#include <OgreParticleSystem.h>

class DataSizes
{
    public:
        static const int NUM_SPHERES_PER_RING;
        static const Ogre::Vector3 SPHERE_SIZE;
        static const float OUTER_RING_RADIUS;
        static const float INNER_RING_RADIUS;
        static const float RING_SPEED;
        static const float SPHERE_SPEED;    
        static const Ogre::Vector3 SINBAD_INITIAL_POSITION;
        static const float SINBAD_WALK_LENGTH;
        static const float SINBAD_TIME_WALKING;
        static const float SINBAD_TIME_ROTATING;
        static const Ogre::Vector3 KEEP_SCALE;
};
#endif
