#include "stress.hpp"

#include <Eigen/Core>
#include <Eigen/Dense>

#include <vector>
#include <iostream>

/// Calculates the shear stress vector given Cauchy tensor
auto calc_shear(Tensor3d const& stress, Vector3d const& plane_normal) -> Vector3d
{
    Vector3d const traction = stress*plane_normal;
    return traction - (plane_normal.transpose()*traction)*plane_normal;
}


/// Helper function to generate a 3x3 stress matrix from Voigt components
auto from_voigt(double xx, double yy, double zz, double yz, double xz, double xy) -> Tensor3d 
{
    Tensor3d stress_matrix;
    stress_matrix << xx, xy, xz, xy, yy, yz, xz, yz, zz;
    return stress_matrix;
}


/// Calculates the normal stress (scalar) and shear stress for the given plane
auto normal_and_shear(Tensor3d const& stress, Vector3d const& plane_normal) -> std::tuple<double, Vector3d>
{
    double const normal_stress = plane_normal.transpose()*stress*plane_normal;
    Vector3d const shear_stress = stress*plane_normal - normal_stress * plane_normal;
    return {normal_stress, shear_stress};
}


/// Generates a coordinate system for the given plane.
/// Unit directions is chosen by cyclic permutation s.t. z-axis is in the plane normal direction.
auto in_plane_csys(Vector3d const& plane_normal) -> Csys
{
    Vector3d const plane_unit_normal = plane_normal.normalized();

    double nx = std::abs(plane_unit_normal[0]);
    double ny = std::abs(plane_unit_normal[1]);
    double nz = std::abs(plane_unit_normal[2]);

    // Determine orientation of in-plane x-axis
    // X-axis chosen by cyclic permutation of the largest component of plane normal
    Vector3d ex;
    if (nx > ny && nx > nz) {
        ex = {0, 1, 0};
    } else if (ny > nx && ny > nz) {
        ex = {0, 0, 1};
    } else {
        ex = {1, 0, 0};
    }

    // Find its orientation relative to standard basis
    ex = (ex - (ex.transpose()*plane_unit_normal)*plane_unit_normal).normalized();

    // Determine orientation of in-plane y-axis
    Vector3d ey = plane_unit_normal.cross(ex);
    Csys basis;
    basis << ex, ey, plane_normal;
    return basis;
}


/// Calculates the shear stress (2d vector) history in the plane by parallel projection
auto shear_path(TensorList3d const& stress_history, Vector3d const& plane_normal) -> PointList2d
{
    Csys const basis = in_plane_csys(plane_normal);

    // TODO: Check use of Vector2d = vec3d.head<2>();
    PointList2d result;
    result.reserve(stress_history.size());
    for (auto const& T: stress_history) {
        Vector3d const shear = calc_shear(T, plane_normal);
        double const x = shear.dot(basis.col(0));  // TODO Check optimisation
        double const y = shear.dot(basis.col(1));
        result.emplace_back(Vector2d{x, y});
    }

    return result;
}


/// Obtain the 2-dimensional vector in the plane by shear vector projection
/// Csys is the local coordinate system where the first two directions define the projection plane.
/// Hence, third coordinate direction is the plane unit normal
auto shear_projection(Vector3d const& shear, Csys const& local_csys) ->  Vector2d
{
    return {shear.dot(local_csys.col(0)), shear.dot(local_csys.col(1))};  // TODO: Maybe faster to just do the full matrix operation and cap result?
}