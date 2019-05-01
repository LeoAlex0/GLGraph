//
// Created by leo on 19-5-1.
//

#ifndef GLGRAPH_MAZEMODEL_H
#define GLGRAPH_MAZEMODEL_H

#include <cstddef>
#include <vector>
#include <map>
#include <string>
#include <tuple>

namespace mazeModel {
    using namespace std;

    /**
     * 点
     */
    using Point = tuple<float,float>;

    struct {
        /**
         * 函数登记，迷宫的生成函数
         * @param gen 生成式集合
         * @return 一个点序列一个下标序列
         */
        tuple<vector<Point>,vector<short>> (*getMaze) (multimap<char,string> const& gen);
    } mazeGenerator;
    multimap<char,string> lex;

    class MazeModel {
        vector<Point> points;
        vector<short> indecies;
    public:
        MazeModel();
    };

}

#endif //GLGRAPH_MAZEMODEL_H
