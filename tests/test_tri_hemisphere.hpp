#include "tri_hemisphere.hpp"

#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>

TEST_CASE("Test uniaxial") 
{
    TriHemisphere hs;

    SECTION("Unit hemisphere") {
        REQUIRE(hs.m_cells.size() == 4);
        REQUIRE(hs.m_nodes.size() == 5);
    }

    SECTION("One level global refinement") {
        hs.Refine();
        REQUIRE(hs.m_cells.size() == 20);
        REQUIRE(hs.m_refined_cells == 4);
        REQUIRE(hs.m_nodes.size() == 13);
    }

    SECTION("One level adaptive refinement") {
        hs.Refine();
        hs.AddValues({1,0,0,0,0,0,0,0,0,0,0,0,0});
        int refined_nodes = hs.RefineNodes(0.05);
        REQUIRE(hs.m_max_value == 1.0);
        REQUIRE(hs.m_max_node == 0);
    }
}
