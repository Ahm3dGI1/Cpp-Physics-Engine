// rigidbody.h

// Include other headers
#include "math.h"
#include "collider.h"

// Define the rigidbody structure
struct rigidbody
{
    // Basic properties
    float mass;
    float inverseMass;

    // Inertia tensors
    mat3x3 localInverseInertiaTensor;
    mat3x3 globalInverseInertiaTensor;

    // Centroids
    vec3d localCentroid;
    vec3d globalCentroid;

    // Position and orientation
    vec3d position;
    mat3x3 orientation;
    mat3x3 inverseOrientation;

    // Velocity
    vec3d velocity;
    vec3d angularVelocity;

    // Force and torque accumulators
    vec3d forceAccum;
    vec3d torqueAccum;

    // List of colliders
    ColliderList colliders;

    // Function to update global centroid from position
    void UpdateGlobalCentroidFromPosition(void);

    // Function to update position from global centroid
    void UpdatePositionFromGlobalCentroid(void);

    // Function to update orientation
    void UpdateOrientation(void);

    // Function to add a collider
    void AddCollider(Collider& collider);

    // Functions to convert between global and local points/vectors
    const vec3d GlobalToLocalPoint(const vec3d& point) const;
    const vec3d LocalToGlobalPoint(const vec3d& point) const;
    const vec3d GlobalToLocalVector(const vec3d& vector) const;
    const vec3d LocalToGlobalVector(const vec3d& vector) const;

    // Function to apply force at a point
    void ApplyForce(const vec3d& force, const vec3d& point);
};