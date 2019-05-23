//
// Created by leo on 19-5-9.
//

#include <vector>
#include <tuple>
#include <utility>
#include <random>
#include <string>
#include "mazeModel.h"

using namespace std;
using mazeModel::Point;


constexpr float eps = 1e-2;
static float pi;

static default_random_engine e(u_long(time(nullptr)));

static void init() {
    pi = acosf(-1);
}

static float dis(Point const &x, Point const &y) {
    auto[x1, y1] = x;
    auto[x2, y2] = y;
    return hypot(x1 - x2, y1 - y2);
}

/**
 * 最近点查找
 * @param vec 点集
 * @param p 已知点
 * @return 最近点下标与其距离
 */
static tuple<size_t, float>
nearestPoint(Point const *vec, size_t len, Point const &p) {
    //TODO: 可以改成拿K-d树做
    tuple<size_t, float> ret = make_tuple(0ul, dis(vec[0], p));
    for (unsigned i = 1; i < len; ++i)
        if (float nd = dis(vec[i], p);nd < std::get<1>(ret))
            ret = make_tuple(i, nd);

    return ret;
}

/**
 * 通过生成字串生成地图
 * @param fStep 每次前进的步长
 * @param rStep 每次旋转的弧度
 * @param s 生成的字符串
 * @return 生成的地图
 */
static tuple<vector<Point>, vector<unsigned short>>
getGraph(float fStep, float rStep, string const &s) {
    Point pos = make_tuple(-1.f, 0.f);
    float f = 0;

    vector<Point> points = {pos};
    vector<unsigned short> indices = {0};

    auto insertPoint = [&]() {
        if (auto[ni, nd] = nearestPoint(points.data(), points.size(), pos);nd < eps)
            indices.push_back(ni);
        else {
            indices.push_back(points.size());
            points.push_back(pos);
        }
    };

    for (auto c:s) {
        switch (c) {
            case '+' :
                f += rStep;
                insertPoint();
                break;
            case '-':
                f -= rStep;
                insertPoint();
                break;
            default:
                pos = pos + make_tuple(fStep * cosf(f), fStep * sinf(f));
        }
    }

    return make_tuple(points, indices);
}

static tuple<vector<Point>, vector<unsigned short>>
getMaze(int arc, vector<string> const &gen) {
    const float rStep = pi * arc / 180;
    uniform_int_distribution<size_t> u(0ul, gen.size());
    float fStep = 2;
    string s = "F";

    for (; fStep > eps; fStep /= 3) {
        string newS;
        for (auto c:s) {
            if (c == 'F') {
                size_t rd = u(e);
                if (rd == 0) newS += "FFF";
                else newS += gen[rd - 1];
            } else newS += c;
        }

        s = std::move(newS);
    }
    return getGraph(fStep, rStep, s);
}

namespace mazeModel {
    struct MazeFunc LEO_GENERATOR{
            .getMaze = getMaze,
            .init = init,
    };
}