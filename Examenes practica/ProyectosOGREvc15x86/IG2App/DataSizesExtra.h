#ifndef DataSizesExtra_h
#define DataSizesExtra_h

#include "IG2Object.h"

class DataSizesExtra
{
public:
    static const Vector3 AIRPLANE_BODY_SIZE;
    static const Vector3 AIRPLANE_WING_SIZE;
    static const Vector3 AIRPLANE_RUDDER_SIZE;
    static const Vector3 ENGINE_BASE_SIZE;
    static const Vector3 ROCKET_SIZE;

    static const int AIRPLANE_NUM_ROCKETS;
    static const float AIRPLANE_SPEED;
    static const float AIRPLANE_ROTATION;

    // dic 2025
    static const int NUM_SPHERES_PER_RING;
    static const Vector3 SPHERE_SIZE;
    static const float OUTER_RING_RADIUS;
    static const float INNER_RING_RADIUS;
    static const float RING_SPEED;
    static const float SPHERE_SPEED;
    static const Vector3 SINBAD_INITIAL_POSITION;
    static const float SINBAD_WALK_LENGTH;
    static const float SINBAD_TIME_WALKING;
    static const float SINBAD_TIME_ROTATING;
    static const Vector3 KEEP_SCALE;

    // extra
    static const float SINBAD_SPEED;
    static const int NUM_SPHERE;
};
#endif /* DataSizesExtra_h */