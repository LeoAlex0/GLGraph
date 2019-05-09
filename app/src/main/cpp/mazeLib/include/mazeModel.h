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

    extern struct MazeFunc{
        /**
         * 函数登记，迷宫的生成函数
         * @param arc 一次旋转的角度，角度制
         * @param gen 生成式集合
         * @return 一个点序列一个下标序列
         */
        tuple<vector<Point>, vector<unsigned short>> (*getMaze)(int arc,vector<string> const &gen);

        /**
         * 初始化函数，构造时调用。仅构造时调用
         */
        void (*init)();
    } mazeGenerator;

    extern vector<string> lex;

    extern class MazeModel {
        vector<Point> points;
        vector<unsigned short> indecies;
        mutex mutex,refreshing; /// 保证互斥
    public:
        MazeModel();
        /**
         * 刷新函数
         */
        void refresh();
        /**
         * 绘制函数
         */
        void draw(GLuint positionHandler);
    } mazeObject;

}

#endif //GLGRAPH_MAZEMODEL_H
