
#ifndef FINDLEY_HPP
#define FINDLEY_HPP

#include "data_structures.hpp"

/*
Struct to represent the Findley critical plane fatigue damage criterion.

TODO:
- Parametrize on e.g. number of maximum rectangular hull orientations
- Choose resolved shear stress amplitude method
- Implement multihreaded version
*/
struct Findley
{
    /// Calculates the fatigue damage in the candidate plane
    auto Damage(TensorList3d const& stress_history, double findley_k, Vector3d const& plane_normal) -> double;

    /// Adaptively searches through the candidate material planes using hemisphere discretisation
    auto AdaptiveDamage(TensorList3d, const& stress_history, double findley_k) -> TriHemisphere;
};

#endif // FINDLEY_HPP