#ifndef TRI_HEMISPHERE_HPP
#define TRI_HEMISPHERE_HPP
#include <vector>

#include "data_structures.hpp"

struct TriCell 
{
    int a, b, c;
    int parent;
    bool refined = false;
};

struct TriNode 
{
    Vector3d coords;
    bool visited = false;
};

/*

TODO: Implement a simpler TriHemisphere that only needs
two coordinates to define a point. The third point is related to the 
first two by 1 - x^2 - y^2

Use quadtree to lookup nodes.
Also make constexpr

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
    
    TriHemisphere(); 

    int Refine();  // Globally refine all cells
    //int RefineNodes(double const threshold);  
    int RefineNodes(double const ratio);  // Refine critical cells
    void AddValues(std::vector<double> const& damages);

private:
    void RefineCell(int const id);
    int FindNode(Vector3d const& coordinates, size_t const cell_id);
    bool EvaluateCell(size_t const id, double const threshold) const;
    int FindNode();
    std::vector<int> CriticalNodes();
};

#endif  // TRI_HEMISPHERE_HPP