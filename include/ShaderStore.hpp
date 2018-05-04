#ifndef H_TW_SHADERSTORE
#define H_TW_SHADERSTORE

#include <unordered_map>
#include <string>
#include <memory>
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "VertexShader.hpp"
#include "FragmentShader.hpp"
#include "GeometryShader.hpp"
#include "TesselationEvaluationShader.hpp"
#include "TesselationControlShader.hpp"
#include "ComputeShader.hpp"

namespace tw {
class ShaderStore {

public:

    ShaderStore () = delete; // static only
    ~ShaderStore () = delete;

    ShaderStore (ShaderStore&&) = delete;
    ShaderStore& operator = (ShaderStore&&) = delete;

    ShaderStore (const ShaderStore&) = delete;
    ShaderStore& operator = (const ShaderStore&) = delete;

    static bool vertexShaderExists (const std::string&);
    static std::shared_ptr<VertexShader> getVertexShader (const std::string&);
    static bool fragmentShaderExists (const std::string&);
    static std::shared_ptr<FragmentShader> getFragmentShader (const std::string&);
    static bool geometryShaderExists (const std::string&);
    static std::shared_ptr<GeometryShader> getGeometryShader (const std::string&);
    static bool tesselationEvaluationShaderExists (const std::string&);
    static std::shared_ptr<TesselationEvaluationShader> getTesselationEvaluationShader (const std::string&);
    static bool tesselationControlShaderExists (const std::string&);
    static std::shared_ptr<TesselationControlShader> getTesselationControlShader (const std::string&);
    static bool computeShaderExists (const std::string&);
    static std::shared_ptr<ComputeShader> getComputeShader (const std::string&);
    static bool shaderProgramExists (const std::string&);
    static std::shared_ptr<ShaderProgram> getShaderProgram (const std::string&);

    template <typename ...T>
    static std::shared_ptr<VertexShader> makeVertexShader (const std::string& key, T&&... args) {

        if (vertexShaderExists(key)) {
            return nullptr;
        }

        auto vertexShader = std::make_shared<VertexShader>(std::forward<T>(args)...);

        if (registerVertexShader(key, vertexShader)) {
            return vertexShader;
        } else {
            return nullptr;
        }

    }
    static bool registerVertexShader (const std::string&, const std::shared_ptr<VertexShader>&);
    static bool registerVertexShader (const std::string&, VertexShader*);
    static void deleteVertexShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<FragmentShader> makeFragmentShader (const std::string& key, T&&... args) {

        if (fragmentShaderExists(key)) {
            return nullptr;
        }

        auto fragmentShader = std::make_shared<FragmentShader>(std::forward<T>(args)...);

        if (registerFragmentShader(key, fragmentShader)) {
            return fragmentShader;
        } else {
            return nullptr;
        }

    }
    static bool registerFragmentShader (const std::string&, const std::shared_ptr<FragmentShader>&);
    static bool registerFragmentShader (const std::string&, FragmentShader*);
    static void deleteFragmentShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<GeometryShader> makeGeometryShader (const std::string& key, T&&... args) {

        if (geometryShaderExists(key)) {
            return nullptr;
        }

        auto geometryShader = std::make_shared<GeometryShader>(std::forward<T>(args)...);

        if (registerGeometryShader(key, geometryShader)) {
            return geometryShader;
        } else {
            return nullptr;
        }

    }
    static bool registerGeometryShader (const std::string&, const std::shared_ptr<GeometryShader>&);
    static bool registerGeometryShader (const std::string&, GeometryShader*);
    static void deleteGeometryShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<TesselationEvaluationShader> makeTesselationEvaluationShader (const std::string& key, T&&... args) {

        if (tesselationEvaluationShaderExists(key)) {
            return nullptr;
        }

        auto tesselationEvaluationShader = std::make_shared<TesselationEvaluationShader>(std::forward<T>(args)...);

        if (registerTesselationEvaluationShader(key, tesselationEvaluationShader)) {
            return tesselationEvaluationShader;
        } else {
            return nullptr;
        }

    }
    static bool registerTesselationEvaluationShader (const std::string&, const std::shared_ptr<TesselationEvaluationShader>&);
    static bool registerTesselationEvaluationShader (const std::string&, TesselationEvaluationShader*);
    static void deleteTesselationEvaluationShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<TesselationControlShader> makeTesselationControlShader (const std::string& key, T&&... args) {

        if (tesselationControlShaderExists(key)) {
            return nullptr;
        }

        auto tesselationControlShader = std::make_shared<TesselationControlShader>(std::forward<T>(args)...);

        if (registerTesselationControlShader(key, tesselationControlShader)) {
            return tesselationControlShader;
        } else {
            return nullptr;
        }

    }
    static bool registerTesselationControlShader (const std::string&, const std::shared_ptr<TesselationControlShader>&);
    static bool registerTesselationControlShader (const std::string&, TesselationControlShader*);
    static void deleteTesselationControlShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<ComputeShader> makeComputeShader (const std::string& key, T&... args) {

        if (computeShaderExists(key)) {
            return nullptr;
        }

        auto computeShader = std::make_shared<ComputeShader>(std::forward<T>(args)...);

        if (registerComputeShader(key, computeShader)) {
            return computeShader;
        } else {
            return nullptr;
        }

    }
    static bool registerComputeShader (const std::string&, const std::shared_ptr<ComputeShader>&);
    static bool registerComputeShader (const std::string&, ComputeShader*);
    static void deleteComputeShader (const std::string&);

    template <typename ...T>
    static std::shared_ptr<ShaderProgram> makeShaderProgram (const std::string& key, T&&... args) {

        if (shaderProgramExists(key)) {
            return nullptr;
        }

        auto shaderProgram = std::make_shared<ShaderProgram>(std::forward<T>(args)...);

        if (registerShaderProgram(key, shaderProgram)) {
            return shaderProgram;
        } else {
            return nullptr;
        }

    }
    static std::shared_ptr<ShaderProgram> makeShaderProgramByKeys (
        const std::string&,
        const std::string& = "",
        const std::string& = "",
        const std::string& = "",
        const std::string& = "",
        const std::string& = "",
        const std::string& = ""
    );
    static bool registerShaderProgram (const std::string&, const std::shared_ptr<ShaderProgram>&);
    static bool registerShaderProgram (const std::string&, ShaderProgram*);
    static void deleteShaderProgram (const std::string&);

private:

    static std::unordered_map<std::string, std::shared_ptr<VertexShader>> m_vertexShaders;
    static std::unordered_map<std::string, std::shared_ptr<FragmentShader>> m_fragmentShaders;
    static std::unordered_map<std::string, std::shared_ptr<GeometryShader>> m_geometryShaders;
    static std::unordered_map<std::string, std::shared_ptr<TesselationEvaluationShader>> m_tesselationEvaluationShaders;
    static std::unordered_map<std::string, std::shared_ptr<TesselationControlShader>> m_tesselationControlShaders;
    static std::unordered_map<std::string, std::shared_ptr<ComputeShader>> m_computeShaders;

    static std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaderPrograms;

};
}

#endif
