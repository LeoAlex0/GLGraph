//
// Created by zalex on 2019/5/3.
//

#include "mazeModel.h"
#include <vector>

namespace mazeModel {

    tuple<vector<Point>, vector<unsigned short>>
    getMaze(const multimap<char, string> &) {
        vector<Point> points = {
                {-.5, .5},
                {-.5,-.5},
                { .5,-.5},
                { .5, .5}
        };
        vector<GLushort> drawIndices = {0, 1, 2, 3, 0, 2};

        return make_tuple(points, drawIndices);
    }

    multimap<char, string> lex = {
            {'F', "RFRRRRFR"},
    };

    MazeFunc mazeGenerator = {
            .getMaze = getMaze,
    };

    MazeModel mazeObject;
}