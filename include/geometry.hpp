#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "data_structures.hpp"

/// Calculates the maximum rectangular hull containing the given points. At least 10 steps is recommended for accuracy.
auto maximum_rectangular_hull(PointList2d const& points, int refinement_level) -> double;

#endif // GEOMETRY_HPP