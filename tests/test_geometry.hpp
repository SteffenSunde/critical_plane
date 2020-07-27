#include "geometry.hpp"

#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>


TEST_CASE("Maximum rectangular hull") 
{
    SECTION("Simple square box (Coarse)") {
        PointList2d input = {{0,0}, {1,0}, {1,1}, {0,1}};
        double answer = maximum_rectangular_hull(input, 20);
        double correct = 1.0;
        REQUIRE(answer == Approx(correct).margin(1e-2));
    }

    SECTION("Simple square box (Fine)") {
        PointList2d input = {{0,0}, {1,0}, {1,1}, {0,1}};
        double answer = maximum_rectangular_hull(input, 300);
        double correct = 1.0;
        REQUIRE(answer == Approx(correct).margin(1e-5));
    }
}

TEST_CASE("Maximum rectangular hull of line") {
    SECTION("First quadrant") {
        PointList2d input = {{0,0}, {1,1}};
        double answer = maximum_rectangular_hull(input, 200);
        double correct = std::sqrt(2.0)/2;
        REQUIRE(answer == Approx(correct).margin(1e-5));        
    }

    SECTION("First and third quadrant") {
        PointList2d input = {{0,0}, {1,1}, {-1,-1}};
        double answer = maximum_rectangular_hull(input, 200);
        double correct = std::sqrt(2.0);
        REQUIRE(answer == Approx(correct).margin(1e-5));          
    }
}

TEST_CASE("Maximum rectangular hull of circle") {
    PointList2d input;
    for (auto i: iter::range(30)) {
        double const alpha = i/30.0 * 2*PI;
        Vector2d const point{100*std::cos(alpha), 100*std::sin(alpha)};
        input.emplace_back(point);
    }
    double answer = maximum_rectangular_hull(input, 200);
    REQUIRE(answer == Approx(100*sqrt(2)).margin(0.5));
}