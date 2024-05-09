#include "rigidbody.h"

// Function to integrate rigid bodies over a time step
void IntegrateRigidBodies(std::vector<rigidbody>& rigidBodies, vec3d globalCentroid, vec3d velocity, vec3d angularVelocity, mat3x3 orientation, float dt){
    for (auto& body : rigidBodies){
        body.velocity += body.forceAccum * body.inverseMass * dt;

        body.angularVelocity += body.globalInverseInertiaTensor * body.torqueAccum * dt;

        body.forceAccum.Zero();
        body.torqueAccum.Zero();

        globalCentroid = velocity * dt;

        const vec3d axis = angularVelocity.Normalized();
        const float angle = angularVelocity.Magnitude() * dt;
        orientation = mat3x3::FromAxisAngle(axis, angle);

        body.UpdateOrientation();
        body.UpdatePositionFromGlobalCentroid();
    }
}