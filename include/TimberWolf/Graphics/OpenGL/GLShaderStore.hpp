#ifndef TW_CLASS_GLSHADERSTORE
#define TW_CLASS_GLSHADERSTORE

/**
 * @file
 *
 * Header file for the tw::GLShaderStore class.
 */

#include <unordered_map>
#include <string>
#include <memory>
#include "GLShaderProgram.hpp"
#include "GLShader.hpp"
#include "GLVertexShader.hpp"
#include "GLFragmentShader.hpp"
#include "GLGeometryShader.hpp"
#include "GLTesselationEvaluationShader.hpp"
#include "GLTesselationControlShader.hpp"
#include "GLComputeShader.hpp"

namespace tw {
class GLShaderStore {

public:

    GLShaderStore () = delete; // static only
    ~GLShaderStore () = delete;

    GLShaderStore (GLShaderStore&&) = delete;
    GLShaderStore& operator = (GLShaderStore&&) = delete;

    GLShaderStore (const GLShaderStore&) = delete;
    GLShaderStore& operator = (const GLShaderStore&) = delete;

    static bool vertexShaderExists (const std::string&);
    static std::shared_ptr<GLVertexShader> getVertexShader (const std::string&);
    static bool fragmentShaderExists (const std::string&);
    static std::shared_ptr<GLFragmentShader> getFragmentShader (const std::string&);
    static bool geometryShaderExists (const std::string&);
    static std::shared_ptr<GLGeometryShader> getGeometryShader (const std::string&);
    static bool tesselationEvaluationShaderExists (const std::string&);
    static std::shared_ptr<GLTesselationEvaluationShader> getTesselationEvaluationShader (const std::string&);
    static bool tesselationControlShaderExists (const std::string&);
    static std::shared_ptr<GLTesselationControlShader> getTesselationControlShader (const std::string&);
    static bool computeShaderExists (const std::string&);
    static std::shared_ptr<GLComputeShader> getComputeShader (const std::string&);
    static bool shaderProgramExists (const std::string&);
    static std::shared_ptr<GLShaderProgram> getShaderProgram (const std::string&);

    template <typename ...T>
    static std::shared_ptr<GLVertexShader> makeVertexShader (const std::string& key, T&&... args) {

        if (vertexShaderExists(key)) {
            logVertexShaderAlreadyExists(key);
            return nullptr;
        }

        auto vertexShader = std::make_shared<GLVertexShader>(std::forward<T>(args)...);

        if (registerVertexShader(key, vertexShader)) {
            return vertexShader;
        } else {
            return nullptr;
        }

    }
    static bool registerVertexShader (const std::string&, const std::shared_ptr<GLVertexShader>&);
    static bool registerVertexShader (const std::string&, GLVertexShader*);
    static void deleteVertexShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<GLFragmentShader> makeFragmentShader (const std::string& key, T&&... args) {

        if (fragmentShaderExists(key)) {
            logFragmentShaderAlreadyExists(key);
            return nullptr;
        }

        auto fragmentShader = std::make_shared<GLFragmentShader>(std::forward<T>(args)...);

        if (registerFragmentShader(key, fragmentShader)) {
            return fragmentShader;
        } else {
            return nullptr;
        }

    }
    static bool registerFragmentShader (const std::string&, const std::shared_ptr<GLFragmentShader>&);
    static bool registerFragmentShader (const std::string&, GLFragmentShader*);
    static void deleteFragmentShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<GLGeometryShader> makeGeometryShader (const std::string& key, T&&... args) {

        if (geometryShaderExists(key)) {
            logGeometryShaderAlreadyExists(key);
            return nullptr;
        }

        auto geometryShader = std::make_shared<GLGeometryShader>(std::forward<T>(args)...);

        if (registerGeometryShader(key, geometryShader)) {
            return geometryShader;
        } else {
            return nullptr;
        }

    }
    static bool registerGeometryShader (const std::string&, const std::shared_ptr<GLGeometryShader>&);
    static bool registerGeometryShader (const std::string&, GLGeometryShader*);
    static void deleteGeometryShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<GLTesselationEvaluationShader> makeTesselationEvaluationShader (const std::string& key, T&&... args) {

        if (tesselationEvaluationShaderExists(key)) {
            logTesselationEvaluationShaderAlreadyExists(key);
            return nullptr;
        }

        auto tesselationEvaluationShader = std::make_shared<GLTesselationEvaluationShader>(std::forward<T>(args)...);

        if (registerTesselationEvaluationShader(key, tesselationEvaluationShader)) {
            return tesselationEvaluationShader;
        } else {
            return nullptr;
        }

    }
    static bool registerTesselationEvaluationShader (const std::string&, const std::shared_ptr<GLTesselationEvaluationShader>&);
    static bool registerTesselationEvaluationShader (const std::string&, GLTesselationEvaluationShader*);
    static void deleteTesselationEvaluationShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<GLTesselationControlShader> makeTesselationControlShader (const std::string& key, T&&... args) {

        if (tesselationControlShaderExists(key)) {
            logTesselationControlShaderAlreadyExists(key);
            return nullptr;
        }

        auto tesselationControlShader = std::make_shared<GLTesselationControlShader>(std::forward<T>(args)...);

        if (registerTesselationControlShader(key, tesselationControlShader)) {
            return tesselationControlShader;
        } else {
            return nullptr;
        }

    }
    static bool registerTesselationControlShader (const std::string&, const std::shared_ptr<GLTesselationControlShader>&);
    static bool registerTesselationControlShader (const std::string&, GLTesselationControlShader*);
    static void deleteTesselationControlShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<GLComputeShader> makeComputeShader (const std::string& key, T&... args) {

        if (computeShaderExists(key)) {
            logComputeShaderAlreadyExists(key);
            return nullptr;
        }

        auto computeShader = std::make_shared<GLComputeShader>(std::forward<T>(args)...);

        if (registerComputeShader(key, computeShader)) {
            return computeShader;
        } else {
            return nullptr;
        }

    }
    static bool registerComputeShader (const std::string&, const std::shared_ptr<GLComputeShader>&);
    static bool registerComputeShader (const std::string&, GLComputeShader*);
    static void deleteComputeShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<GLShaderProgram> makeShaderProgram (const std::string& key, T&&... args) {

        if (shaderProgramExists(key)) {
            logShaderProgramAlreadyExists(key);
            return nullptr;
        }

        auto shaderProgram = std::make_shared<GLShaderProgram>(std::forward<T>(args)...);

        if (registerShaderProgram(key, shaderProgram)) {
            return shaderProgram;
        } else {
            return nullptr;
        }

    }
    static bool registerShaderProgram (const std::string&, const std::shared_ptr<GLShaderProgram>&);
    static bool registerShaderProgram (const std::string&, GLShaderProgram*);
    static void deleteShaderProgram (const std::string&);

private:

    static void logVertexShaderAlreadyExists (const std::string&);
    static void logFragmentShaderAlreadyExists (const std::string&);
    static void logGeometryShaderAlreadyExists (const std::string&);
    static void logTesselationEvaluationShaderAlreadyExists (const std::string&);
    static void logTesselationControlShaderAlreadyExists (const std::string&);
    static void logComputeShaderAlreadyExists (const std::string&);
    static void logShaderProgramAlreadyExists (const std::string&);

    static std::unordered_map<std::string, std::shared_ptr<GLVertexShader>> m_vertexShaders;
    static std::unordered_map<std::string, std::shared_ptr<GLFragmentShader>> m_fragmentShaders;
    static std::unordered_map<std::string, std::shared_ptr<GLGeometryShader>> m_geometryShaders;
    static std::unordered_map<std::string, std::shared_ptr<GLTesselationEvaluationShader>> m_tesselationEvaluationShaders;
    static std::unordered_map<std::string, std::shared_ptr<GLTesselationControlShader>> m_tesselationControlShaders;
    static std::unordered_map<std::string, std::shared_ptr<GLComputeShader>> m_computeShaders;

    static std::unordered_map<std::string, std::shared_ptr<GLShaderProgram>> m_shaderPrograms;

};
}

#endif
