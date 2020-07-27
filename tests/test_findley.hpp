#include "findley.hpp"
#include "stress.hpp"

#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>

//auto generate_load_case(std::array<double, 6> load_data, int num_points) -> std::vector<Tensor3d>;
auto generate_load_history(
    double sigma_a, double sigma_m, double tau_a, double tau_m, 
    double delta, double lambda, int num_points) -> std::vector<Tensor3d>;

TEST_CASE("Uniaxial loading") 
{
    SECTION("Uniaxial load") {
        Tensor3d t1 = from_voigt(0,0,0,0,0,0);
        Tensor3d t2 = from_voigt(100,0,0,0,0,0);
        std::vector<Tensor3d> load_history = {t1, t2};

        Findley findley;

        double max_resolved_shear = 0.0;
        for (auto i: iter::range(180)) {
            for (auto j: iter::range(180)) {
                double const alpha = i * PI/180;
                double const beta = j * PI/180;
                double const nx = std::sin(beta)*std::cos(alpha);
                double const ny = std::sin(beta)*std::sin(alpha);
                double const nz = std::cos(beta);
                Vector3d unit_normal(nx, ny, nz);
                max_resolved_shear = std::max(max_resolved_shear, findley.Damage(load_history, 0.0, unit_normal));
            }
        }

        REQUIRE(max_resolved_shear == Approx(100.0/4.0));
    }
    
    SECTION("Pure shear load") {
        Tensor3d t1 = from_voigt(0,0,0,0,0,0);
        Tensor3d t2 = from_voigt(100,0,0,0,0,0);
        std::vector<Tensor3d> load_history = {t1, t2};

        Findley findley;

        double max_resolved_shear = 0.0;
        for (auto i: iter::range(180)) {
            for (auto j: iter::range(180)) {
                double const alpha = i * PI/180;
                double const beta = j * PI/180;
                double const nx = std::sin(beta)*std::cos(alpha);
                double const ny = std::sin(beta)*std::sin(alpha);
                double const nz = std::cos(beta);
                Vector3d unit_normal(nx, ny, nz);
                max_resolved_shear = std::max(max_resolved_shear, findley.Damage(load_history, 0.0, unit_normal));
            }
        }

        REQUIRE(max_resolved_shear == Approx(100.0/4.0));
    }
}


TEST_CASE("Load Case 0 from Paper"){
    int const num_angles = 30;
    std::vector<Tensor3d> load_history = generate_load_history(138.1, 0.0, 167.1, 0.0, 0.0, 1.0, 100);
    Findley findley;

    double max_damage = 0.0;
    for (auto i: iter::range(num_angles)) {
        for (auto j: iter::range(num_angles)) {
            double const alpha = (double)i * PI/(double)num_angles;
            double const beta = (double)j * PI/(double)num_angles;
            double const nx = std::sin(beta)*std::cos(alpha);
            double const ny = std::sin(beta)*std::sin(alpha);
            double const nz = std::cos(beta);
            Vector3d unit_normal = {nx, ny, nz};
            max_damage = std::max(max_damage, findley.Damage(load_history, 0.0, unit_normal));
        }
    }

    REQUIRE(max_damage == Approx(180.8).margin(0.5));
}

TEST_CASE("Load Case 5 from Paper"){
    int const num_angles = 30;
    std::vector<Tensor3d> load_history = generate_load_history(249.7, 0.0, 124.8, 0.0, 30.0, 1.0, 100);
    Findley findley;

    double max_damage = 0.0;
    for (auto i: iter::range(num_angles)) {
        for (auto j: iter::range(num_angles)) {
            double const alpha = (double)i * PI/(double)num_angles;
            double const beta = (double)j * PI/(double)num_angles;
            double const nx = std::sin(beta)*std::cos(alpha);
            double const ny = std::sin(beta)*std::sin(alpha);
            double const nz = std::cos(beta);
            Vector3d unit_normal = {nx, ny, nz};
            max_damage = std::max(max_damage, findley.Damage(load_history, 0.0, unit_normal));
        }
    }

    REQUIRE(max_damage == Approx(170.5).margin(0.5));
}


TEST_CASE("Load Case 15 from Paper"){
    int num_angles = 30;
    std::vector<Tensor3d> load_history = generate_load_history(283.0, 0.0, 136.0, 136.0, 90, 1.0, 100);
    Findley findley;

    double max_damage = 0.0;
    for (auto i: iter::range(num_angles)) {
        for (auto j: iter::range(num_angles)) {
            double const alpha = (double)i * PI/(double)num_angles;
            double const beta = (double)j * PI/(double)num_angles;
            double const nx = std::sin(beta)*std::cos(alpha);
            double const ny = std::sin(beta)*std::sin(alpha);
            double const nz = std::cos(beta);
            Vector3d unit_normal = {nx, ny, nz};
            max_damage = std::max(max_damage, findley.Damage(load_history, 0.0, unit_normal));
        }
    }

    REQUIRE(max_damage == Approx(174.2).margin(0.5));
}


auto generate_load_history(
    double sigma_a, double sigma_m, double tau_a, double tau_m, 
    double delta, double lambda, int num_points) -> std::vector<Tensor3d>
{
    double step_size = lambda < 1 ? 1.0/lambda : 1.0;

    std::vector<Tensor3d> load_history;
    for (auto i : iter::range(num_points)) {
        double const angle = (double)i * step_size *  2.0*PI/(double)num_points;
        double const xx = sigma_m + sigma_a * std::sin(angle);
        double const xy = tau_m + tau_a * std::sin(lambda * angle + delta*PI/180);
        load_history.emplace_back(from_voigt(xx, 0, 0, 0, 0, xy));
    }

    return load_history;
}