#include "findley.hpp"
#include "stress.hpp"
#include "convex_hull.hpp"

#include <cppitertools/range.hpp>
#include "findley.hpp"
#include "geometry.hpp"

#include <array>

double Findley::Damage(TensorList3d const& stress_history, double findley_k, Vector3d const& plane_normal)
{

    int const num_points = stress_history.size();
    if (num_points < 1) return 0.0;

    double max_normal_stress = -INF;
    PointList2d shear_history;
    shear_history.reserve(num_points);

    // Choose a local in-plane basis
    Csys csys = in_plane_csys(plane_normal);

    for (auto i: iter::range(num_points)) {
        Tensor3d const& stress = stress_history[i];

        auto const [normal_stress, shear_stress] = normal_and_shear(stress, plane_normal);
        Vector2d plane_shear = shear_projection(shear_stress, csys);
        shear_history.emplace_back(plane_shear);
        max_normal_stress = std::max(max_normal_stress, normal_stress);
    }

    PointList2d const points = convex_hull(shear_history);
    double const resolved_shear_stress_amplitude = maximum_rectangular_hull(points, 10);

    return resolved_shear_stress_amplitude + findley_k * max_normal_stress;
}