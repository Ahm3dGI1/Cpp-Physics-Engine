#include "rigidbody.h"

// Update the global centroid based on the current position and orientation
void rigidbody::UpdateGlobalCentroidFromPosition(void)
{
    globalCentroid = localCentroid * orientation + position;
}

// Update the position based on the global centroid and orientation
void rigidbody::UpdatePositionFromGlobalCentroid(void)
{
    position = globalCentroid - localCentroid * orientation;
}

// Add a collider to the rigidbody and update the mass and centroid
void rigidbody::AddCollider(Collider& collider)
{
    // Add the collider to the list
    colliders.Add(collider);

    // Reset the local centroid and mass
    localCentroid.Zero();
    mass = 0.0f;

    // Calculate the new local centroid and mass
    for (Collider& collider : colliders)
    {
        localCentroid += collider.localCentroid * collider.mass;
        mass += collider.mass;
    }

    // Calculate the inverse mass and finalize the local centroid calculation
    inverseMass = 1.0f / mass;
    localCentroid *= inverseMass;

    // Calculate the local inertia tensor using the Parallel Axis Theorem
    mat3x3 localInertiaTensor;
    localInertiaTensor.Zero();

    for(Collider& collider : colliders)
    {
        vec3d offset = collider.localCentroid - localCentroid;
        float offsetDotOffset = offset * offset;
        mat3x3 offsetCrossOffset = offset.OuterProduct(offset);
        localInertiaTensor += collider.localIntertiaTensor + collider.mass * (mat3x3::Identity() * offsetDotOffset - offsetCrossOffset);
    }
}

// Update the orientation based on the angular velocity
void rigidbody::UpdateOrientation(void){
    // Orthonomalize the orientation matrix
    Quat q = orientation.ToQuaternion();
    q.Normalize();
    orientation = q.ToMatrix();

    // Update the inverse orientation matrix
    inverseOrientation = orientation.Transposed();
}

// Convert a global point to a local point
const vec3d rigidbody::GlobalToLocalPoint(const vec3d& point) const
{
    return (point - position) * inverseOrientation;
}

// Convert a local point to a global point
const vec3d rigidbody::LocalToGlobalPoint(const vec3d& point) const
{
    return point * orientation + position;
}

// Convert a global vector to a local vector
const vec3d rigidbody::GlobalToLocalVector(const vec3d& vector) const
{
    return vector * inverseOrientation;
}

// Convert a local vector to a global vector
const vec3d rigidbody::LocalToGlobalVector(const vec3d& vector) const
{
    return vector * orientation;
}

// Apply a force at a specific point, updating the force and torque accumulators
void rigidbody::ApplyForce(const vec3d& force, const vec3d& point)
{
    forceAccum += force;
    torqueAccum += (point - globalCentroid) % force;
}