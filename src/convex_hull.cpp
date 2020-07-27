#include "convex_hull.hpp"

#include <cppitertools/range.hpp>
#include <Eigen/Core>

#include <algorithm>
#include <functional>
#include <vector>

auto orientation(Vector2d const& a, Vector2d const& b, Vector2d const& c) -> std::optional<Turn>
{
    double const crossprod = (b[0]-a[0])*(c[1]-b[1])-(b[1]-a[1])*(c[0]-b[0]);
    if (crossprod < 0.0) {
        return Turn::CW;
    } else if (crossprod > 0.0) {
        return Turn::CCW;
    }
    return std::nullopt;
}

auto lexicographical_sort(PointList2d points) -> PointList2d 
{
    auto lexicographical_order = [](Vector2d const& a, Vector2d const& b) -> bool {
        if (a[0] < b[0]) return true;
        else if (a[0] > b[0]) return false;
        return (a[1] < b[1]);
    };

    std::sort(points.begin(), points.end(), lexicographical_order);
    return points;
}

auto convex_hull(PointList2d points) -> PointList2d 
{
    int N = points.size();
    if (N < 2) return points;

    points = lexicographical_sort(points);

    std::vector<Vector2d> upper;
    upper.reserve(N/2);
    upper.push_back(points[0]);
    upper.push_back(points[1]);
    for (auto i: iter::range(2, N)) {
        size_t pos = 0;
        while (upper.size() - pos >= 2) {
            size_t length = upper.size();
            auto turn = orientation(upper[length-pos-2], upper[length-pos-1], points[i]);
            if (turn && turn.value() == Turn::CW) {
                pos++;
            } else {
                upper.erase(upper.end()-pos-1);
            }
        }
        upper.emplace_back(points[i]);
    }

    std::vector<Vector2d> lower;
    lower.reserve(N/2);
    lower.push_back(points[N-1]);
    lower.push_back(points[N-2]);
    for (auto i: iter::range(N-3, 0, -1)) {
        size_t pos = 0;
        while (lower.size() - pos >= 2) {
            size_t length = lower.size();
            auto turn = orientation(lower[length-pos-2], lower[length-pos-1], points[i]);
            if(turn && turn.value() == Turn::CW) {
                pos++;
            } else {
                lower.erase(lower.end()-pos-1);
            }
        }
        lower.emplace_back(points[i]);
    }

    if (lower.size() > 1) upper.insert(upper.end(), lower.begin()+1, lower.end());

    return upper;
}