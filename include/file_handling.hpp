#ifndef FILE_HANDLING_HPP
#define FILE_HANDLING_HPP

#include "data_structures.hpp"
#include "tri_hemisphere.hpp"

#include <string>


/// Exports the hemisphere with damage values as VTK legacy format
void write_to_file(PointList2d const&, std::string const&);

/// Exports the hemisphere with damage values as VTK legacy format
void write_to_file(TriHemisphere const& hemisphere, std::string const& file);

#endif // FILE_HANDLING_HPP