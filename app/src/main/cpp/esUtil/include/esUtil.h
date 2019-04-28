//
// Created by leo on 19-3-10.
//

#ifndef GLDEMO_ESUTIL_H
#define GLDEMO_ESUTIL_H

#include <android/log.h>
#include <jni.h>
#include <GLES3/gl3.h>

#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, "esUtil", __VA_ARGS__)

/**
 * 通过顶点着色器和面元找色器代码构造GL程序
 * @param vtxSrc 顶点着色器代码
 * @param fragSrc 片元着色器代码
 * @return 创建的GL程序的编号
 */
GLuint createProgram(const char* vtxSrc, const char* fragSrc);

/**
 * 通过顶点着色器和面元找色器代码构造GL程序
 * @param vtxSrc 顶点着色器代码
 * @param fragSrc 片元着色器代码
 * @return 创建的GL程序的编号
 */
GLuint createProgram(JNIEnv * env,jstring vtxSrc, jstring fragSrc);

#endif //GLDEMO_ESUTIL_H
