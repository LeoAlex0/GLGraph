//
// Created by leo on 19-5-1.
//

#include <mazeModel.h>

namespace mazeModel {
    MazeModel::MazeModel() {
        mazeGenerator.init();
        tie(points,indecies) = std::move(mazeGenerator.getMaze(60,lex));
    }

    void MazeModel::refresh() {
        if (!refreshing.try_lock())
            return;
        auto ans = mazeGenerator.getMaze(60,lex);

        mutex.lock();
        tie(points,indecies) = std::move(ans);
        mutex.unlock();

        refreshing.unlock();
    }

    void MazeModel::draw(GLuint positionHandler) {
        mutex.lock();

        glVertexAttribPointer(positionHandler,2,GL_FLOAT,GL_FALSE,0,points.data());
        glDrawElements(GL_LINE_STRIP,GLsizei(indecies.size()),GL_UNSIGNED_SHORT,indecies.data());

        mutex.unlock();
    }
}
