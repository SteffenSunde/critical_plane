#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include "data_structures.hpp"

#include <Eigen/Core>
#include <vector>
#include <optional>

/// Three points in the plane are either co-linear or form a left or right turn.
auto orientation(Vector2d const& a, Vector2d const& b, Vector2d const& c) -> std::optional<Turn>;

/// Sort two-dimensional points (x,y) lexicographically, i.e. by x then y coordinates.
auto lexicographical_sort(PointList2d) -> PointList2d;

/// Computes the unique (two-dimensional) convex hull by the given list of points.
auto convex_hull(PointList2d points) -> PointList2d;

#endif // CONVEX_HULL_HPP