//
// Created by leo on 19-5-1.
//

#ifndef GLGRAPH_MAZEMODEL_H
#define GLGRAPH_MAZEMODEL_H

#include <cstddef>
#include <vector>
#include <mutex>
#include <map>
#include <string>
#include <tuple>
#include <GLES3/gl3.h>

namespace mazeModel {
    using namespace std;

    /**
     * 点
     */
    using Point = tuple<float, float>;

    struct {
        /**
         * 函数登记，迷宫的生成函数
         * @param gen 生成式集合
         * @return 一个点序列一个下标序列
         */
        tuple<vector<Point>, vector<unsigned short>> (*getMaze)(multimap<char, string> const &gen);
    } mazeGenerator;

    multimap<char, string> lex;

    class MazeModel {
        vector<Point> points;
        vector<unsigned short> indecies;
        mutex mutex; /// 保证互斥
    public:
        MazeModel();
        /**
         * 刷新函数
         */
        void refresh();
        /**
         * 绘制函数
         */
        void draw(GLuint vertexId);
    };

}

#endif //GLGRAPH_MAZEMODEL_H
