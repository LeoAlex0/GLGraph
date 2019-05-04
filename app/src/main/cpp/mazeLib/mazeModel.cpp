//
// Created by leo on 19-5-1.
//

#include <mazeModel.h>

namespace mazeModel {
    MazeModel::MazeModel() {
        mazeGenerator.init();
        tie(points,indecies) = mazeGenerator.getMaze(lex);
    }

    void MazeModel::refresh() {
        auto ans = mazeGenerator.getMaze(lex);

        mutex.lock();
        tie(points,indecies) = std::move(ans);
        mutex.unlock();
    }

    void MazeModel::draw(GLuint positionHandler) {
        mutex.lock();

        glVertexAttribPointer(positionHandler,2,GL_FLOAT,GL_FALSE,0,points.data());
        glDrawElements(GL_LINE_LOOP,GLsizei(indecies.size()),GL_UNSIGNED_SHORT,indecies.data());

        mutex.unlock();
    }
}
