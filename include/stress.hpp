#ifndef STRESS_HPP
#define STRESS_HPP

#include "data_structures.hpp"

#include <Eigen/Core>
#include <vector>
#include <optional>

auto from_voigt(double xx, double yy, double zz, double yz, double xz, double xy) -> Tensor3d;
auto calc_shear(Tensor3d const& stress, Vector3d const& plane_normal) -> Vector3d;
auto normal_and_shear(Tensor3d const& stress, Vector3d const& plane_normal) -> std::tuple<double, Vector3d>;
auto shear_path(PointList3d const& stress_history, Vector3d const& plane_normal) -> PointList2d;
auto in_plane_csys(Vector3d const& plane_normal) -> Csys;
auto shear_projection(Vector3d const& shear, Csys const& local_csys) -> Vector2d;

#endif // STRESS_HPPW