#include "catch.hpp"
#include "convex_hull.hpp"

TEST_CASE("Orientation") {
    SECTION("Colinear points does not have an orientation") {
        Vector2d p1{0, 0};
        Vector2d p2{1, 0};
        Vector2d p3{2, 0};
        auto orient = orientation(p1, p2, p3);
        REQUIRE(!orient.has_value());
    }
    
    SECTION("Right turn (Clockwise)") {
        Vector2d p1{0, 0};
        Vector2d p2{0, 1};
        Vector2d p3{1, 1};
        auto orient = orientation(p1, p2, p3);
        REQUIRE(orient.value() == Turn::CW);
    }
    
    SECTION("Left turn (Counter-clockwise)") {
        Vector2d p1{0, 0};
        Vector2d p2{1, 0};
        Vector2d p3{1, 1};
        auto orient = orientation(p1, p2, p3);
        REQUIRE(orient.value() == Turn::CCW);
    }
    
}