//
// Created by leo on 19-5-1.
//

#include <mazeModel.h>

namespace mazeModel {
    MazeModel::MazeModel::MazeModel() {
        tie(points,indecies) = mazeGenerator.getMaze(lex);
    }
}
