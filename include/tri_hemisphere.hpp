#ifndef TRI_HEMISPHERE_HPP
#define TRI_HEMISPHERE_HPP
#include <vector>

#include "data_structures.hpp"


/// A triangular cell
struct TriCell 
{
    int a, b, c;
    int parent;
    bool refined = false;
};


/// Coordinate data for a node in a hemisphere
struct TriNode 
{
    Vector3d coords;
    bool visited = false;
};


/*
A data structure to keep track of material plane orientations.
Data is stored as a two-dimensional mesh of triangles, s.t. each triangle
may be refined based on a refinement scheme.

Warning: Not very efficient yet.

TODO: 
- Use quadtree to store point data for O(logn) lookup
- Different (less brute-force) strategies for refinement
- Implement a static constexpr version for compile-time search space calculation. 
*/
struct TriHemisphere 
{
    std::vector<TriCell> m_cells;
    std::vector<TriNode> m_nodes;
    std::vector<double> m_values;
    int m_num_cells;
    int m_num_nodes;
    int m_refined_cells;
    int m_visited_nodes;
    double m_max_value;
    int m_max_node;
    
    /// Generate a unit hemisphere (pyramid)
    TriHemisphere(); 

    /// Refines a certain ratio of all cells based on their value
    int RefineNodes(double const ratio); 

    /// Refines all triangles in the hemsiphere into four new ones 
    int Refine();

    /// Add a series of new values computed since last time Hemisphere was refined
    void AddValues(std::vector<double> const& damages);

private:

    /// Refines a specific cell into four new ones
    void RefineCell(int const id);

    /// Insert a new node if it is not already in the Hemisphere
    int FindNode(Vector3d const& coordinates, size_t const cell_id);

    //bool EvaluateCell(size_t const id, double const threshold) const;

    /// Insert a new node if it is not already in the Hemisphere.
    int FindNode();
    
    /// Store ids for the critical node selection
    std::vector<int> CriticalNodes();
};

#endif  // TRI_HEMISPHERE_HPP