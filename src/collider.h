// collider.h

#include <vector>
#include "math.h"

// Define the Collider structure
struct Collider
{
    float mass;  // Mass of the collider
    mat3x3 localIntertiaTensor;  // Local inertia tensor of the collider
    vec3d localCentroid;  // Local centroid of the collider
};

// Define the ColliderList structure
struct ColliderList
{
    std::vector<Collider> colliders;  // Vector to store multiple colliders

    // Begin and end functions for iterator access
    auto begin() { return colliders.begin(); }
    auto end() { return colliders.end(); }
    auto begin() const { return colliders.begin(); }
    auto end() const { return colliders.end(); }

    // Function to add a collider to the list
    void Add(const Collider& collider)
    {
        colliders.push_back(collider);
    }

    // Function to get the count of colliders in the list
    int Count() const
    {
        return colliders.size();
    }

    // Overload the [] operator to access colliders by index
    Collider& operator[](int index)
    {
        return colliders[index];
    }

    // Overload the [] operator to access colliders by index (const version)
    const Collider& operator[](int index) const
    {
        return colliders[index];
    }
};