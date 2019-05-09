//
// Created by leo on 19-5-9.
//

#include <vector>
#include <tuple>
#include <random>
#include <string>
#include "mazeModel.h"

using namespace std;

namespace mazeModel {
    constexpr float eps = 1e-3;
    const float pi = acosf(-1);

    default_random_engine *e;

    void init() {
        e = new default_random_engine(unsigned long(time(nullptr)));
    }

    /**
     * 最近点查找算法
     * @param vec 点集
     * @param p 已知点
     * @return 最近点
     */
    Point
    nearestPoint (vector<Point> const & vec,Point const& p) {
        if (vec.empty()) return Point(-1.f,0.f);

    }

    /**
     * 通过生成字串生成地图
     * @param fStep 每次前进的步长
     * @param rStep 每次旋转的弧度
     * @param s 生成的字符串
     * @return 生成的地图
     */
    tuple<vector<Point>,vector<unsigned short>>
    getGraph (float fStep,float rStep,string const& s) {
        Point pos(-1.f,0.f);
        float f = 0;

        vector<Point> points = {pos};
        vector<unsigned short> indices = {0};


    }

    tuple<vector<Point>,vector<unsigned short>>
    getMaze (int arc, vector<string> const &gen){
        const float rad = pi*arc/180;


    }
}