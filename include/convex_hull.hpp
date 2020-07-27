#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include "data_structures.hpp"

#include <Eigen/Core>
#include <vector>
#include <optional>

auto orientation(Vector2d const& a, Vector2d const& b, Vector2d const& c) -> std::optional<Turn>;
auto lexicographical_sort(PointList2d) -> PointList2d;
auto convex_hull(PointList2d points) -> PointList2d;

#endif // CONVEX_HULL_HPP