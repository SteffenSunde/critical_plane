#include "geometry.hpp"

#include <Eigen/Geometry>
#include <cppitertools/range.hpp>

#include <array>

auto maximum_rectangular_hull(PointList2d const& points, int num_steps) -> double
{
    /*
        Calculates the maximum rectangular hull containing the given points
        
        Returns: Length of rectangle diagonal
    */
    int const num_points = points.size();
    if (num_points < 1) return 0;
    
    double max_diagonal = 0.0;
    double max_angle = 0.0;

    for (auto i: iter::range(num_steps)) {
        double const angle = i * PI/2.0/num_steps;

        Eigen::Rotation2D<double> const rot(-angle);
        rot.toRotationMatrix();
        PointList2d rotated_points;  // TODO: Move outside and reserve space to avoid resize
        //rotated_points.reserve(num_points);
        std::transform(points.begin(), points.end(), std::back_inserter(rotated_points), 
            [rot](auto const& point) { return rot*point;} );
        
        double x_max = -INF, y_max = -INF, x_min = INF, y_min = INF;
        for (auto const& point : rotated_points) {
            double const& x = point[0];
            double const& y = point[1];
            if (x > x_max) x_max = x;
            if (x < x_min) x_min = x;
            if (y > y_max) y_max = y;
            if (y < y_min) y_min = y;
        }

        // No need to sqrt before comparison
        double const diagonal_squared = std::pow(x_max - x_min, 2.0) + std::pow(y_max - y_min, 2.0);
        max_diagonal = std::max(max_diagonal, diagonal_squared);
    }

    return sqrt(max_diagonal)/2.0;
}