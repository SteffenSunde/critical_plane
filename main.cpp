#include "data_structures.hpp"
#include "findley.hpp"
#include "stress.hpp"
#include "tri_hemisphere.hpp"
#include "file_handling.hpp"

#include <Eigen/Core>
#include <iostream>

int main() {
    TriHemisphere hs;
    Findley fn;
    hs.Refine();
    hs.Refine();

    TensorList3d load_history {from_voigt(0, -242, 0, 0, 0, 0), from_voigt(0, 242, 0, 0, 0, 0)};
    int max_iterations = 20;
    int new_nodes = hs.m_nodes.size();
    int iteration = 1;
    double subset_size = 0.1;
    while(new_nodes > 0) {
        std::vector<double> damages;
        damages.reserve(new_nodes);
        for (int i=hs.m_visited_nodes; i < hs.m_nodes.size(); ++i) {
            Vector3d const& n = hs.m_nodes[i].coords;
            damages.push_back(fn.Damage(load_history, 0.0, n));
        }

        hs.AddValues(damages);
        if(iteration < max_iterations) {
            new_nodes = hs.RefineNodes(subset_size);  // TODO: This only refines in a small stupid area around the first found max!
            iteration++;
            subset_size /= 2;
        } else {
            std::cout << "Warning: Maximum number of iterations reached! Stopping...\n";
            break;
        }
    }

    write_to_file(hs, "C:/Users/steff/source/repos/test/build/Debug/test.vtk");
}