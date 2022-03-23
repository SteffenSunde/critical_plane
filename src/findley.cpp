#include "findley.hpp"
#include "stress.hpp"
#include "convex_hull.hpp"

#include <cppitertools/range.hpp>
#include "findley.hpp"
#include "geometry.hpp"
#include "tri_hemisphere.hpp"

#include <array>

/*
Calculates the fatigue damage in the candidate plane

Findley damage parameter $f$ is given by
$$f = \tau_a + k\sigma_{max}$$

where
- $\tau_a$ is the resolved shear stress by maximum rectangular hull
- $k$ is a material parameter
- $\sigma_{max}$ is the largest normal stress in the plane 
*/
auto Findley::Damage(TensorList3d const& stress_history, double findley_k, Vector3d const& plane_normal) -> double
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


/*
Adaptively search for the critical plane for the given load history.
Uses a TriHemisphere to discretize the search space as a mesh of triangles.
Returns the entire hemisphere for visualization. If only critical plane orientation
and maximum damge is needed, TODO.
*/
auto Findley::AdaptiveDamage(TensorList3d const& load_history, double findley_k, size_t max_iterations) -> TriHemisphere {
    TriHemisphere hs;
    hs.Refine();
    hs.Refine();

    int new_nodes = hs.m_nodes.size();
    int iteration = 1;
    double subset_size = 0.1;
    while(new_nodes > 0) {
        std::vector<double> damages;
        damages.reserve(new_nodes);
        for (int i=hs.m_visited_nodes; i < hs.m_nodes.size(); ++i) {
            Vector3d const& n = hs.m_nodes[i].coords;
            damages.push_back(this->Damage(load_history, 0.0, n));
        }

        hs.AddValues(damages);
        if(iteration < max_iterations) {
            new_nodes = hs.RefineNodes(subset_size);  // TODO: This only refines in a small stupid area around the first found max!
            iteration++;
            subset_size /= 2;
        } else {
            printf("Warning: Maximum number of iterations reached! Stopping...\n");
            break;
        }
    }

    return hs;
}