#include "stress.hpp"

#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>

TEST_CASE("Test calc_shear") 
{
    Tensor3d stress = from_voigt(2, 2, 1, -2, 3, 1);
    Vector3d plane_normal{1,2,-2};
    plane_normal.normalize();

    SECTION("Only shear") {

        Vector3d answer = calc_shear(stress, plane_normal);
        REQUIRE(answer[0] == Approx(-40.0/27.0));
        REQUIRE(answer[1] == Approx(37.0/27.0));
        REQUIRE(answer[2] == Approx(17.0/27.0));
    }
    
    SECTION("Normal and shear") {
        auto const [normal, shear] = normal_and_shear(stress, plane_normal);
        
        REQUIRE(normal == Approx(22.0/9.0));
        REQUIRE(shear[0] == Approx(-40.0/27.0));
        REQUIRE(shear[1] == Approx(37.0/27.0));
        REQUIRE(shear[2] == Approx(17.0/27.0));
    }
}

TEST_CASE("Parallel projection") {
    SECTION("Vector parallell to the plane of projection") {
        Vector3d vec{1,2,0};
        Vector3d ex{1,0,0};
        Vector3d ey{0,1,0};
        Vector3d ez{0,0,1};
        Csys csys;
        csys << ex, ey, ez;

        auto answer = shear_projection(vec, csys);
        REQUIRE(answer[0] == Approx(1.0));
        REQUIRE(answer[1] == Approx(2.0));
    }
    
    SECTION("Vector perpendicular to the plane of projection") {
        Vector3d vec{1,0,0};
        Vector3d ex{0,0,0};
        Vector3d ey{1,0,0};
        Vector3d ez{0,1,0};
        Csys csys;
        csys << ex, ey, ez;

        auto answer = shear_projection(vec, csys);
        REQUIRE(answer[0] == Approx(0.0));
        REQUIRE(answer[1] == Approx(0.0));
    }

    SECTION("Shear projection") {
        Vector3d vec{1,0,0};

        Vector3d ex{0,0,0};
        Vector3d ey{1,0,0};
        Vector3d ez{0,1,0};
        Csys csys;
        csys << ex, ey, ez;

        auto answer = shear_projection(vec, csys);
        REQUIRE(answer[0] == Approx(0.0));
        REQUIRE(answer[1] == Approx(0.0));
    }
    
}

TEST_CASE("In-plane csys") {
    Vector3d plane_normal{1,0,0};
    auto answer = in_plane_csys(plane_normal);
    Csys correct;
    correct << 0, 0, 1,
               1, 0, 0,
               0, 1, 0;

    for (auto i : iter::range(3)) {
        for (auto j : iter::range(3)) {
            REQUIRE(answer(i, j) == Approx(correct(i,j)).margin(0.5));
        }
    }
}