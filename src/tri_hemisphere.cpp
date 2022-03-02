#include "tri_hemisphere.hpp"

#include <cppitertools/range.hpp>

#include <numeric>


/// Generate a unit hemisphere (pyramid)
TriHemisphere::TriHemisphere() :
    m_nodes({{{0, 1, 0}}, {{0, 0, -1}}, {{-1, 0, 0}}, {{0, 0, 1}}, {{1, 0, 0}}}),
    m_cells({{0, 1, 4, -1}, {0, 1, 2, -1}, {0, 2, 3, -1}, {0, 3, 4, -1}}),
    m_num_cells(4), m_num_nodes(5), m_refined_cells(0), m_visited_nodes(0), m_max_value(0.0)

{

}


/// Refines all triangles in the hemsiphere into four new ones 
int TriHemisphere::Refine() 
{
    int num_cells = this->m_cells.size();
    for (auto i: iter::range(num_cells)) {
        if (!m_cells[i].refined)
            this->RefineCell(i);
    }
    return this->m_cells.size() - num_cells;
}


/// Refines a specific cell into four new ones
void TriHemisphere::RefineCell(int const id)
{
    int const a = m_cells[id].a;
    int const b = m_cells[id].b;
    int const c = m_cells[id].c;

    Vector3d const mp1 = ((m_nodes[a].coords + m_nodes[b].coords) * 0.5).normalized();
    Vector3d const mp2 = ((m_nodes[b].coords + m_nodes[c].coords) * 0.5).normalized();
    Vector3d const mp3 = ((m_nodes[c].coords + m_nodes[a].coords) * 0.5).normalized();

    int d = this->FindNode(mp1, id);  // TODO: Use QuadTree lookup
    int e = this->FindNode(mp2, id);
    int f = this->FindNode(mp3, id);

    m_cells.push_back({m_cells[id].a, d, f, id});
    m_cells.push_back({m_cells[id].b, d, e, id});
    m_cells.push_back({d, e, f, id});
    m_cells.push_back({m_cells[id].c, e, f, id});

    m_cells[id].refined = true;
    m_refined_cells++;
}

/// Insert a new node if it is not already in the Hemisphere.
/// TODO: Use Quadtree structure for O(log n) lookup
/// TODO: Should rather be called InsertNode!
int TriHemisphere::FindNode(Vector3d const &v, size_t const cell_id) { 
    auto it = std::find_if(m_nodes.begin(),
                           m_nodes.end(), [&v](auto const &el) {
                               return el.coords.isApprox(v);
                           });

    if(it != m_nodes.end()) {
        return std::distance(m_nodes.begin(), it);
    } else {
        m_nodes.push_back({v, false});
        return m_nodes.size() - 1;
    }
}


/// Refines a certain ratio of all cells based on their value
/// TODO: Implement smarter selection!
int TriHemisphere::RefineNodes(double const subset_ratio)
{
    int const num_nodes = m_nodes.size();
    int const num_subset = (int)(subset_ratio * num_nodes);
    if (subset_ratio < 0.0001) return 0;
    int const num_cells = m_cells.size();

    // Find indices of a critical subset of nodes
    std::vector<int> const indices = this->CriticalNodes();

    // Refine cells connected to the critical nodes
    for (int i=0; i < num_subset; ++i) {
        int const index = indices[i];
        for (int j=0; j < num_cells; ++j) {
            if (!m_cells[j].refined) {
                if (m_cells[j].a == index || m_cells[j].b == index || m_cells[j].c == index)
                this->RefineCell(j);
            }
        }
    }
    return m_nodes.size() - num_nodes;
}


/// Add a series of new values computed since last time Hemisphere was refined.
void TriHemisphere::AddValues(std::vector<double> const& values) 
{
    if(values.size() != m_nodes.size() - m_visited_nodes) {
        printf("Warning: Unknown number of values encountered when adding to a TriHemisphere\n");
    } else {
        for(int i=0; i < values.size(); i++) {
            if(values[i] > m_max_value) {
                m_max_value = values[i];
                m_max_node = i;
            }

            m_values.push_back(values[i]);
            m_nodes[m_visited_nodes].visited = true;
            m_visited_nodes++;
        }
    } 
}


/// Find the id numbers of all critical nodes
/// TODO: Inefficient
std::vector<int> TriHemisphere::CriticalNodes()
{
    std::vector<int> idx(m_values.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), 
    [&](int i1, int i2) { return m_values[i1] > m_values[i2]; });
    return idx; 
}