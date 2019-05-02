//
// Created by leo on 19-5-1.
//

#include <mazeModel.h>

namespace mazeModel {
    MazeModel::MazeModel() = default {
        tie(points,indecies) = mazeGenerator.getMaze(lex);
    }

    void MazeModel::refresh() {
        mutex.lock();
        tie(points,indecies) = mazeGenerator.getMaze(lex);
        mutex.unlock();
    }

    void MazeModel::draw(GLuint vertexId) {
        mutex.lock();

        glVertexAttribPointer(vertexId,3,GL_FLOAT,GL_FALSE,0,points.data());
        glDrawElements(GL_LINES,GLsizei(indecies.size()),GL_UNSIGNED_SHORT,indecies.data());

        mutex.unlock();
    }
}
