#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include <Eigen/Core>
#include <vector>
#include <optional>
#include <limits>
#include <cassert>
#include <numbers>

// Constants
static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");
constexpr double const INF = std::numeric_limits<double>::max();
constexpr double const NEG_INF = -1 * INF;
constexpr double const PI = std::numbers::pi;

// Vectors
using Vector2d = Eigen::Vector2d;
using PointList2d = std::vector<Vector2d>;
using Vector3d = Eigen::Vector3d;
using PointList3d = std::vector<Vector3d>;

// Tensors
using Tensor3d = Eigen::Matrix3d;
using TensorList3d = std::vector<Tensor3d>;

// A Basis (Csys) is a matrix with three linearly independent basis vectors as columns
using Csys = Eigen::Matrix<double, 3, 3, Eigen::ColMajor>;


// // Coordinate-systems
// struct Csys2d {  // Make into tuple?
//     Vector3d ex;
//     Vector3d ey;
// };

// struct Csys3d {
//     Vector3d ex;
//     Vector3d ey;
//     Vector3d ez;
// };

enum class Turn {
    CW,
    CCW,
};

#endif // DATA_STRUCTURES_HPP