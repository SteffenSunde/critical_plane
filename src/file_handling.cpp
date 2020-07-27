#include "file_handling.hpp"

#include <fstream>
#include <iostream>

void print_to_file(PointList2d const& points, std::string const& file_path)
{
    std::ofstream file_stream;
    file_stream.open(file_path);
    file_stream << "x,y\n";
    for (auto const& p: points)
    {
        file_stream << p[0] << "," << p[1] << "\n";
    }
    file_stream.close();
    return;
}


void write_to_file(TriHemisphere const& hemisphere, std::string const& file_path)
{
    // Plots the given set of unit normals as a set of points and triangular cells in VTK Legacy format.
    int const num_points = hemisphere.m_nodes.size();  //m_nodes.size();
    int const discarded_cells = (int)std::count_if(hemisphere.m_cells.begin(), hemisphere.m_cells.end(), [] (auto const& c) {return c.refined; });
    int const num_cells = hemisphere.m_cells.size() - discarded_cells;

    std::cout << "Writing " << num_points << " of points with "
              << num_cells << " cells to file (" << hemisphere.m_refined_cells << " cells were refined)\n";
    std::ofstream file_stream;
    file_stream.open(file_path);

    // Write VTK Legacy header stuff
    file_stream << "# vtk DataFile Version 4.0\nAngle set\nASCII\nDATASET UNSTRUCTURED_GRID\n\n";

    // Write Points
    file_stream << "POINTS " << num_points << " double\n";
    for (TriNode const& p : hemisphere.m_nodes) {
        file_stream << p.coords[0] << " " << p.coords[1] << " " << p.coords[2] << "\n";
    }

    // if (hs.m_nodes.size() > 0) {
    //     std::cout << "Warning: Unvisited nodes in hemisphere!\n";
    //     for (Node const& p : hs.m_nodes) {
    //         file_stream << p.coords(0) << " " << p.coords(1) << " " << p.coords(2) << "\n";
    //     }
    // }

    // Write cells
    file_stream << "\nCELLS " << num_cells << " " << num_cells * 4 << "\n"; // 4 is number of integers per line
    for (TriCell const& c : hemisphere.m_cells) {
        if (!c.refined)
            file_stream << "3 " << c.a << " " << c.b << " " << c.c << "\n";
    }

    file_stream << "\nCELL_TYPES " << num_cells << "\n";
    for (auto const& c: hemisphere.m_cells) {
        if (!c.refined)
            file_stream << "5\n";
    }

    // Looks like shit. Maybe make into cell data?
    if(hemisphere.m_values.size() == num_points) 
    {
        file_stream << "\nPOINT_DATA " << num_points << " SCALARS eq_shear double 1\nLOOKUP_TABLE default\n";
        for(double const& v: hemisphere.m_values) {
            file_stream << v << "\n";
        }        
    }

    // size_t const num_unvisited_nodes = hemisphere.m_nodes.size() - hemisphere.m_values.size();
    // if(num_unvisited_nodes > 0) {
    //     std::cout << "Warning: " << num_unvisited_nodes << " Unvisited nodes in hemisphere\n";
    //     for(int i=0; i < num_unvisited_nodes; i++) {
    //         file_stream << "0\n";
    //     }
    // }

    // // Cell data
    // file_stream << "\nCELL_DATA " << num_cells << " SCALARS eq_shear double 1\nLOOKUP_TABLE default\n";
    // for(auto const& cell: as.cells)
    // {
    //     const double damage = (damages[cell.a].damage + damages[cell.b].damage + damages[cell.c].damage)/3;
    //     file_stream << damage << "\n";
    // }

    file_stream.close();

    return;;
}