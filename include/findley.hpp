
#ifndef FINDLEY_HPP
#define FINDLEY_HPP

#include "data_structures.hpp"

struct Findley
{
    double Damage(TensorList3d const& stress_history, double findley_k, Vector3d const& plane_normal);
};

#endif // FINDLEY_HPP