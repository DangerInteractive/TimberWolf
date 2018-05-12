#include "../include/ShaderStore.hpp"

/**
 * @class tw::ShaderStore
 *
 * Static map-based object cache keeping track of handles to shader objects and
 * shader programs via a std::string key.
 */

/**
 * Check if a vertex shader handle with the given key exists.
 *
 * @param key vertex shader key to check
 * @return true if vertex shader key exists, false if not
 */
bool tw::ShaderStore::vertexShaderExists (const std::string& key) {

    if (m_vertexShaders.find(key) == m_vertexShaders.end()) {
        return false;
    } else {
        return true;
    }

}

/**
 * Get a std::shared_ptr to the vertex shader handle with the given key. Returns
 * nullptr if the vertex shader key does not exist.
 *
 * @param key vertex shader key
 * @return shared pointer to vertex shader handle, nullptr if none
 */
std::shared_ptr<tw::VertexShader> tw::ShaderStore::getVertexShader (const std::string& key) {

    if (!vertexShaderExists(key)) {
        return nullptr;
    }

    return m_vertexShaders[key];

}

/**
 * Check if a fragment shader handle with the given key exists.
 *
 * @param key fragment shader key to check
 * @return true if fragment shader key exists, false if not
 */
bool tw::ShaderStore::fragmentShaderExists (const std::string& key) {

    if (m_fragmentShaders.find(key) == m_fragmentShaders.end()) {
        return false;
    } else {
        return true;
    }

}

/**
 * Get a std::shared_ptr to the fragment shader handle with the given key.
 * Returns nullptr if the fragment shader key does not exist.
 *
 * @param key fragment shader key
 * @return shared pointer to fragment shader handle, nullptr if none
 */
std::shared_ptr<tw::FragmentShader> tw::ShaderStore::getFragmentShader (const std::string& key) {

    if (!fragmentShaderExists(key)) {
        return nullptr;
    }

    return m_fragmentShaders[key];

}

/**
 * Check if a geometry shader handle with the given key exists.
 *
 * @param key geometry shader key to check
 * @return true if geometry shader key exists, false if not
 */
bool tw::ShaderStore::geometryShaderExists (const std::string& key) {

    if (m_geometryShaders.find(key) == m_geometryShaders.end()) {
        return false;
    } else {
        return true;
    }

}

/**
 * Get a std::shared_ptr to the geometry shader handle with the given key.
 * Returns nullptr if the geometry shader key does not exist.
 *
 * @param key geometry shader key
 * @return shared pointer to geometry shader, nullptr if none
 */
std::shared_ptr<tw::GeometryShader> tw::ShaderStore::getGeometryShader (const std::string& key) {

    if (!geometryShaderExists(key)) {
        return nullptr;
    }

    return m_geometryShaders[key];

}

/**
 * Check if a tesselation evaluation shader handle with the given key exists.
 *
 * @param key tesselation evaluation shader key to check
 * @return true if tesselation evaluation shader key exists, false if not
 */
bool tw::ShaderStore::tesselationEvaluationShaderExists (const std::string& key) {

    if (m_tesselationEvaluationShaders.find(key) == m_tesselationEvaluationShaders.end()) {
        return false;
    } else {
        return true;
    }

}

/**
 * Get a std::shared_ptr to the tesselation evaluation shader handle with the
 * given key. Returns nullptr if the tesselation evaluation shader key does not
 * exist.
 *
 * @param key tesselation evaluation shader key
 * @return shared pointer to tesselation evaluation shader, nullptr if none
 */
std::shared_ptr<tw::TesselationEvaluationShader> tw::ShaderStore::getTesselationEvaluationShader (const std::string& key) {

    if (!tesselationEvaluationShaderExists(key)) {
        return nullptr;
    }

    return m_tesselationEvaluationShaders[key];

}

/**
 * Check if a tesselation control shader handle with the given key exists.
 *
 * @param key tesselation control shader key to check
 * @return true if tesselation control shader key exists, false if not
 */
bool tw::ShaderStore::tesselationControlShaderExists (const std::string& key) {

    if (m_tesselationControlShaders.find(key) == m_tesselationControlShaders.end()) {
        return false;
    } else {
        return true;
    }

}

/**
 * Get a std::shared_ptr to the tesselation control shader handle with the given
 * key. Returns nullptr if the tesselation control shader key does not exist.
 *
 * @param key tesselation evaluation shader key
 * @return shared pointer to tesselation control shader, nullptr if none
 */
std::shared_ptr<tw::TesselationControlShader> tw::ShaderStore::getTesselationControlShader (const std::string& key) {

    if (!tesselationControlShaderExists(key)) {
        return nullptr;
    }

    return m_tesselationControlShaders[key];

}

/**
 * Check if a compute shader handle with the given key exists.
 *
 * @param key compute shader key to check
 * @return true if compute shader key exists, false if not
 */
bool tw::ShaderStore::computeShaderExists (const std::string& key) {

    if (m_computeShaders.find(key) == m_computeShaders.end()) {
        return false;
    } else {
        return true;
    }

}

/**
 * Get a std::shared_ptr to the compute shader handle with the given key.
 * Returns nullptr if the compute shader key does not exist.
 *
 * @param key compute shader key
 * @return shared pointer to compute shader, nullptr if none
 */
std::shared_ptr<tw::ComputeShader> tw::ShaderStore::getComputeShader (const std::string& key) {

    if (!computeShaderExists(key)) {
        return nullptr;
    }

    return m_computeShaders[key];

}

/**
 * Check if a shader program handle with the given key exists.
 *
 * @param key shader program key to checl
 * @return true if shader program key exists, false if not
 */
bool tw::ShaderStore::shaderProgramExists (const std::string& key) {

    if (m_shaderPrograms.find(key) == m_shaderPrograms.end()) {
        return false;
    } else {
        return true;
    }

}

/**
 * Get a std::shared_ptr to the shader program handle with the given key.
 * Returns nullptr if the shader program key does not exist.
 *
 * @param key shader program key
 * @return shared pointer to shader program, nullptr if none
 */
std::shared_ptr<tw::ShaderProgram> tw::ShaderStore::getShaderProgram (const std::string& key) {

    if (!shaderProgramExists(key)) {
        return nullptr;
    }

    return m_shaderPrograms[key];

}

bool tw::ShaderStore::registerVertexShader (const std::string& key, const std::shared_ptr<VertexShader>& vertexShader) {

    if (vertexShaderExists(key)) {
        logVertexShaderAlreadyExists(key);
        return false;
    }

    m_vertexShaders.emplace(key, vertexShader);
    return true;

}

bool tw::ShaderStore::registerVertexShader (const std::string& key, VertexShader* vertexShader) {

    return registerVertexShader(key, std::shared_ptr<VertexShader>(vertexShader));

}

void tw::ShaderStore::deleteVertexShader (const std::string& key) {

    if (!vertexShaderExists(key)) {
        return;
    }

    m_vertexShaders[key].reset();
    m_vertexShaders.erase(key);

}

bool tw::ShaderStore::registerFragmentShader (const std::string& key, const std::shared_ptr<FragmentShader>& fragmentShader) {

    if (fragmentShaderExists(key)) {
        logFragmentShaderAlreadyExists(key);
        return false;
    }

    m_fragmentShaders.emplace(key, fragmentShader);
    return true;

}

bool tw::ShaderStore::registerFragmentShader (const std::string& key, FragmentShader* fragmentShader) {

    return registerFragmentShader(key, std::shared_ptr<FragmentShader>(fragmentShader));

}

void tw::ShaderStore::deleteFragmentShader (const std::string& key) {

    if (!fragmentShaderExists(key)) {
        return;
    }

    m_fragmentShaders[key].reset();
    m_fragmentShaders.erase(key);

}

bool tw::ShaderStore::registerGeometryShader (const std::string& key, const std::shared_ptr<GeometryShader>& geometryShader) {

    if (geometryShaderExists(key)) {
        logGeometryShaderAlreadyExists(key);
        return false;
    }

    m_geometryShaders.emplace(key, geometryShader);
    return true;

}

bool tw::ShaderStore::registerGeometryShader (const std::string& key, GeometryShader* geometryShader) {

    return registerGeometryShader(key, std::shared_ptr<GeometryShader>(geometryShader));

}

void tw::ShaderStore::deleteGeometryShader (const std::string& key) {

    if (!geometryShaderExists(key)) {
        return;
    }

    m_geometryShaders[key].reset();
    m_geometryShaders.erase(key);

}

bool tw::ShaderStore::registerTesselationEvaluationShader (const std::string& key, const std::shared_ptr<TesselationEvaluationShader>& tesselationEvaluationShader) {

    if (tesselationEvaluationShaderExists(key)) {
        logTesselationEvaluationShaderAlreadyExists(key);
        return false;
    }

    m_tesselationEvaluationShaders.emplace(key, tesselationEvaluationShader);
    return true;

}

bool tw::ShaderStore::registerTesselationEvaluationShader (const std::string& key, TesselationEvaluationShader* tesselationEvaluationShader) {

    return registerTesselationEvaluationShader(key, std::shared_ptr<TesselationEvaluationShader>(tesselationEvaluationShader));

}

void tw::ShaderStore::deleteTesselationEvaluationShader (const std::string& key) {

    if (!tesselationEvaluationShaderExists(key)) {
        return;
    }

    m_tesselationEvaluationShaders[key].reset();
    m_tesselationEvaluationShaders.erase(key);

}

bool tw::ShaderStore::registerTesselationControlShader (const std::string& key, const std::shared_ptr<TesselationControlShader>& tesselationControlShader) {

    if (tesselationControlShaderExists(key)) {
        logTesselationControlShaderAlreadyExists(key);
        return false;
    }

    m_tesselationControlShaders.emplace(key, tesselationControlShader);
    return true;

}

bool tw::ShaderStore::registerTesselationControlShader (const std::string& key, TesselationControlShader* tesselationControlShader) {

    return registerTesselationControlShader(key, std::shared_ptr<TesselationControlShader>(tesselationControlShader));

}

void tw::ShaderStore::deleteTesselationControlShader (const std::string& key) {

    if (!tesselationControlShaderExists(key)) {
        return;
    }

    m_tesselationControlShaders[key].reset();
    m_tesselationControlShaders.erase(key);

}

bool tw::ShaderStore::registerComputeShader (const std::string& key, const std::shared_ptr<ComputeShader>& computeShader) {

    if (computeShaderExists(key)) {
        logComputeShaderAlreadyExists(key);
        return false;
    }

    m_computeShaders.emplace(key, computeShader);
    return true;

}

bool tw::ShaderStore::registerComputeShader (const std::string& key, ComputeShader* computeShader) {

    return registerComputeShader(key, std::shared_ptr<ComputeShader>(computeShader));

}

void tw::ShaderStore::deleteComputeShader (const std::string& key) {

    if (!computeShaderExists(key)) {
        return;
    }

    m_computeShaders[key].reset();
    m_computeShaders.erase(key);

}

std::shared_ptr<tw::ShaderProgram> tw::ShaderStore::makeShaderProgramByKeys (
    const std::string& key,
    const std::string& vertexShaderKey,
    const std::string& fragmentShaderKey,
    const std::string& geometryShaderKey,
    const std::string& tesselationEvaluationShaderKey,
    const std::string& tesselationControlShaderKey,
    const std::string& computeShaderKey
) {

    return makeShaderProgram(
        key,
        (vertexShaderKey.size() > 0 ? getVertexShader(vertexShaderKey) : nullptr),
        (fragmentShaderKey.size() > 0 ? getFragmentShader(fragmentShaderKey) : nullptr),
        (geometryShaderKey.size() > 0 ? getGeometryShader(geometryShaderKey) : nullptr),
        (tesselationEvaluationShaderKey.size() > 0 ? getTesselationEvaluationShader(tesselationEvaluationShaderKey) : nullptr),
        (tesselationControlShaderKey.size() > 0 ? getTesselationControlShader(tesselationControlShaderKey) : nullptr),
        (computeShaderKey.size() > 0 ? getComputeShader(computeShaderKey) : nullptr)
    );

}

bool tw::ShaderStore::registerShaderProgram (const std::string& key, const std::shared_ptr<ShaderProgram>& shaderProgram) {

    if (shaderProgramExists(key)) {
        logShaderProgramAlreadyExists(key);
        return false;
    }

    m_shaderPrograms.emplace(key, shaderProgram);
    return true;

}

bool tw::ShaderStore::registerShaderProgram (const std::string& key, ShaderProgram* shaderProgram) {

    return registerShaderProgram(key, std::shared_ptr<ShaderProgram>(shaderProgram));

}

void tw::ShaderStore::deleteShaderProgram (const std::string& key) {

    if (!shaderProgramExists(key)) {
        return;
    }

    m_shaderPrograms[key].reset();
    m_shaderPrograms.erase(key);

}

void tw::ShaderStore::logVertexShaderAlreadyExists (const std::string& key) {

    Log::warning("shaderstore", "Vertex shader with \"", key, "\" key already exists.");

}

void tw::ShaderStore::logFragmentShaderAlreadyExists (const std::string& key) {

    Log::warning("shaderstore", "Fragment shader with \"", key, "\" key already exists.");

}

void tw::ShaderStore::logGeometryShaderAlreadyExists (const std::string& key) {

    Log::warning("shaderstore", "Geometry shader with \"", key, "\" key already exists.");

}

void tw::ShaderStore::logTesselationEvaluationShaderAlreadyExists (const std::string& key) {

    Log::warning("shaderstore", "Tesselation evaluation shader with \"", key, "\" key already exists.");

}

void tw::ShaderStore::logTesselationControlShaderAlreadyExists (const std::string& key) {

    Log::warning("shaderstore", "Tesselation control shader with \"", key, "\" key already exists.");

}

void tw::ShaderStore::logComputeShaderAlreadyExists (const std::string& key) {

    Log::warning("shaderstore", "Compute shader with \"", key, "\" key already exists.");

}

void tw::ShaderStore::logShaderProgramAlreadyExists (const std::string& key) {

    Log::warning("shaderstore", "Shader program with \"", key, "\" key already exists.");

}

std::unordered_map<std::string, std::shared_ptr<tw::VertexShader>> tw::ShaderStore::m_vertexShaders;
std::unordered_map<std::string, std::shared_ptr<tw::FragmentShader>> tw::ShaderStore::m_fragmentShaders;
std::unordered_map<std::string, std::shared_ptr<tw::GeometryShader>> tw::ShaderStore::m_geometryShaders;
std::unordered_map<std::string, std::shared_ptr<tw::TesselationEvaluationShader>> tw::ShaderStore::m_tesselationEvaluationShaders;
std::unordered_map<std::string, std::shared_ptr<tw::TesselationControlShader>> tw::ShaderStore::m_tesselationControlShaders;
std::unordered_map<std::string, std::shared_ptr<tw::ComputeShader>> tw::ShaderStore::m_computeShaders;

std::unordered_map<std::string, std::shared_ptr<tw::ShaderProgram>> tw::ShaderStore::m_shaderPrograms;
