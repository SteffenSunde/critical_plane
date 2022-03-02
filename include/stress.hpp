#ifndef STRESS_HPP
#define STRESS_HPP

#include "data_structures.hpp"

#include <Eigen/Core>
#include <vector>
#include <optional>

/// Helper function to generate a 3x3 stress matrix from Voigt components
auto from_voigt(double xx, double yy, double zz, double yz, double xz, double xy) -> Tensor3d;

/// Calculates the shear stress vector given Cauchy tensor
auto calc_shear(Tensor3d const& stress, Vector3d const& plane_normal) -> Vector3d;

/// Calculates the normal stress (scalar) and shear stress for the given plane
auto normal_and_shear(Tensor3d const& stress, Vector3d const& plane_normal) -> std::tuple<double, Vector3d>;

/// Calculates the shear stress (2d vector) history in the plane by parallel projection
auto shear_path(PointList3d const& stress_history, Vector3d const& plane_normal) -> PointList2d;

/// Generates a coordinate system for the given plane
auto in_plane_csys(Vector3d const& plane_normal) -> Csys;

/// Obtain the 2-dimensional vector in the plane by shear vector projection
auto shear_projection(Vector3d const& shear, Csys const& local_csys) -> Vector2d;

#endif // STRESS_HPP