//
// Created by leo on 19-3-10.
//

#include <GLES3/gl3.h>
#include <cstdlib>
#include <jni.h>

#include "esUtil.h"

/**
 * 在日志中记录错误情况
 * @param funcName 出现在日志中的函数名称
 * @callgraph
 * @return 是否存在错误
 */
bool checkGlError(const char* funcName) {
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        ALOGE("GL error after %s(): 0x%08x\n", funcName, err);
        return true;
    }
    return false;
}

/**
 * 按照源代码创建一个相应类型的着色器
 * @author zLeoAlex
 * @param shaderType 着色器类型(顶点or片元)
 * @param src 相应的代码
 * @return 成功则为着色器编号，失败则为0
 */
GLuint createShader(GLenum shaderType, const char* src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        checkGlError("glCreateShader");
        return 0;
    }
    glShaderSource(shader, 1, &src, nullptr);

    GLint compiled = GL_FALSE;

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); /// 获取编译结果

    if (compiled) return shader; ///编译成功

    /// 编译失败，获取错误信息
    GLint infoLogLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 0) {
        auto *infoLog = (GLchar *) malloc(static_cast<size_t>(infoLogLen));
        if (infoLog) {
            glGetShaderInfoLog(shader, infoLogLen, nullptr, infoLog);
            ALOGE("Could not compile %s shader:\n%s\n",
                  shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
                  infoLog);

            free(infoLog);
        }
    }

    glDeleteShader(shader);
    return 0;
}

/**
 * 通过顶点着色器和片元着色器源码构造渲染程序
 * @param vtxSrc 顶点着色器源码
 * @param fragSrc 片元着色器源码
 * @return 程序编号，失败为0
 */
GLuint createProgram(const char* vtxSrc, const char* fragSrc) {
    GLuint vtxShader = 0,
            fragShader = 0,
            program = 0;
    GLint linked = GL_FALSE;

    if (vtxShader = createShader(GL_VERTEX_SHADER, vtxSrc);vtxShader) {
        if (fragShader = createShader(GL_FRAGMENT_SHADER, fragSrc);fragShader) {
            if (program = glCreateProgram(); !program) checkGlError("glCreateProgram");
            else {
                glAttachShader(program, vtxShader);
                glAttachShader(program, fragShader);

                glLinkProgram(program);
                glGetProgramiv(program, GL_LINK_STATUS, &linked);
                if (!linked) {
                    ALOGE("Could not link program");
                    GLint infoLogLen = 0;
                    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
                    if (infoLogLen) {
                        auto *infoLog = (GLchar *) malloc(static_cast<size_t>(infoLogLen));
                        if (infoLog) {
                            glGetProgramInfoLog(program, infoLogLen, nullptr, infoLog);
                            ALOGE("Could not link program:\n%s\n", infoLog);
                            free(infoLog);
                        }
                    }
                    glDeleteProgram(program);
                    program = 0;
                }
            }
        }
    }
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);
    return program;
}

/**
 * 通过顶点着色器和片元着色器源码构造渲染程序
 * @param env JNI环境
 * @param vtxSrc 顶点着色器源码
 * @param fragSrc 片元着色器源码
 * @return 程序编号，失败为0
 */
GLuint createProgram(JNIEnv * env,jstring vtxSrc, jstring fragSrc) {
    const char
        *vtx = env->GetStringUTFChars(vtxSrc, nullptr),
        *frag = env->GetStringUTFChars(fragSrc, nullptr);
    const GLuint ret = createProgram(vtx,frag);
    env->ReleaseStringUTFChars(vtxSrc,vtx);
    env->ReleaseStringUTFChars(fragSrc,frag);
    return ret;
}