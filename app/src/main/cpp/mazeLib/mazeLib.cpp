//
// Created by leo on 19-4-25.
//

#include <jni.h>
#include <chrono>
#include <cmath>
#include <vector>
#include "esUtil.h"

#define MAZE_RENDERER(a) Java_org_zleoalex_glgraph_gl_renderer_MazeRenderer_##a

extern "C" {

GLuint program,colorHandler,positionHanderler,spinMatHandler;

GLfloat points [] = {
        -.5f,1,0,
        .3,-.6f,0,
        -.4f,.7,0
};

std::vector<GLfloat> matrix;

constexpr size_t elemOfCoord = 3;
constexpr size_t vertexStride = elemOfCoord * sizeof(GLfloat);
constexpr size_t numOfPoints = sizeof(points)/ sizeof(points[0]);
constexpr GLushort drawIndices [] = {0,1,2,0,3,4};
constexpr GLfloat color[] = {1,0,0,1};
constexpr GLfloat omega = 1e-3;

JNIEXPORT jboolean JNICALL
MAZE_RENDERER(init) (JNIEnv *env, jobject, jstring vtxSrc, jstring vtxFrag) {
    program = createProgram(env,vtxSrc,vtxFrag);

    if (!program) {
        ALOGE("程序创建失败");
        return JNI_FALSE;
    }

    matrix = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };

    colorHandler = static_cast<GLuint>(glGetUniformLocation(program, "vColor"));
    positionHanderler = static_cast<GLuint>(glGetAttribLocation(program, "vPos"));
    spinMatHandler = static_cast<GLuint>(glGetUniformLocation(program, "spinMatrix"));

    glClearColor(0, 0, 0, 0);
    return JNI_TRUE;
}


JNIEXPORT void JNICALL
MAZE_RENDERER(resize) (JNIEnv *, jobject, jint width, jint height) {
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT);
}

JNIEXPORT void JNICALL
MAZE_RENDERER(step) (JNIEnv *, jobject) {
    static const auto zero = std::chrono::system_clock::now();
    auto cur = std::chrono::system_clock::now();
    std::chrono::duration<double,std::milli> mili = cur - zero;
    const double theta = (mili * omega).count();
    const auto c = GLfloat(cos(theta)),s = GLfloat(sin(theta));
    matrix = {
            c,0,s,0,
            0,1,0,0,
            s,0,c,0,
            0,0,0,1
    };

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    glLineWidth(10);

    glUniform4fv(colorHandler,1,color);
    glUniformMatrix4fv(spinMatHandler,1,GL_FALSE,matrix.data());

    glEnableVertexAttribArray(positionHanderler);

    glVertexAttribPointer(positionHanderler,elemOfCoord,GL_FLOAT,GL_FALSE,vertexStride,points);
    glDrawElements(GL_LINES,6,GL_UNSIGNED_SHORT,drawIndices);
}

JNIEXPORT void JNICALL
MAZE_RENDERER(fresh) (JNIEnv *, jobject) {

}
}