#include "../../../include/TimberWolf/Graphics/Mesh.hpp"

tw::Mesh::Mesh (tw::Vertex vertices...) {

    m_vertices.emplace_back(vertices);

}

bool tw::Mesh::isPersistent () const {

    return m_persist;

}

bool tw::Mesh::hasHandle () const {

    return m_handle != nullptr;

}

bool tw::Mesh::hasOriginalData () const {

    return isPersistent() || !hasHandle();

}

void tw::Mesh::makePersistent () {

    if (m_handle != nullptr) {
        throw std::runtime_error("Cannot make mesh persistent after handle was obtained");
    }

    m_persist = true;

}

void tw::Mesh::makeEphemeral () {

    m_persist = false;

    eraseOriginalData();

}

tw::MeshHandle* tw::Mesh::getHandle () const {

    return m_handle.get();

}

void tw::Mesh::setHandle (std::unique_ptr<MeshHandle>&& handle) {

    m_handle = std::move(handle);

    if (!m_persist) {
        eraseOriginalData();
    }

}

void tw::Mesh::setHandle (MeshHandle* handle) {

    setHandle(std::unique_ptr<MeshHandle>(handle));

}

unsigned int tw::Mesh::getVertexCount () const {

    return m_vertices.size();

}

const std::vector<tw::Vertex>& tw::Mesh::getVertices () const {

    return m_vertices;

}

const tw::Vertex& tw::Mesh::getVertex (unsigned int index) const {

    return m_vertices.at(index);

}

bool tw::Mesh::indexBufferEnabled () const {

    return m_indexBufferEnabled;

}

unsigned int tw::Mesh::getIndexCount () const {

    return m_indices.size();

}

const std::vector<uint32_t>& tw::Mesh::getIndices () const {

    return m_indices;

}

uint32_t tw::Mesh::getIndex (unsigned int index) const {

    return m_indices.at(index);

}

bool tw::Mesh::normalBufferEnabled () const {

    return m_normalBufferEnabled;

}

unsigned int tw::Mesh::getNormalCount () const {

    return m_normals.size();

}

const std::vector<tw::Normal>& tw::Mesh::getNormals () const {

    return m_normals;

}

const tw::Normal& tw::Mesh::getNormal (unsigned int index) const {

    return m_normals.at(index);

}

bool tw::Mesh::textureBufferEnabled () const {

    return m_textureBufferEnabled;

}

unsigned int tw::Mesh::getTexturePointCount () const {

    return m_texturePoints.size();

}

const std::vector<tw::TexturePoint>& tw::Mesh::getTexturePoints () const {

    return m_texturePoints;

}

const tw::TexturePoint& tw::Mesh::getTexturePoint (unsigned int index) const {

    return m_texturePoints.at(index);

}

bool tw::Mesh::skeletalBufferEnabled () const {

    return m_skeletalBufferEnabled;

}

unsigned int tw::Mesh::getJointBindingCount () const {

    return m_jointBindings.size();

}

unsigned int tw::Mesh::getJointWeightCount () const {

    return m_jointWeights.size();

}

const std::vector<tw::Vector3Integer>& tw::Mesh::getJointBindings () const {

    return m_jointBindings;

}

const std::vector<tw::Vector3>& tw::Mesh::getJointWeights () const {

    return m_jointWeights;

}

const tw::Vector3Integer& tw::Mesh::getJointBinding (unsigned int index) const {

    return m_jointBindings.at(index);

}

const tw::Vector3& tw::Mesh::getJointWeight (unsigned int index) const {

    return m_jointWeights.at(index);

}

void tw::Mesh::addVertices (const Vertex& vertices...) {

    m_vertices.emplace_back(vertices);

}

void tw::Mesh::addIndices (uint32_t indices...) {

    m_indices.emplace_back(indices);
    m_indexBufferEnabled = true;

}

void tw::Mesh::addNormals (const Normal& normals...) {

    m_normals.emplace_back(normals);
    m_normalBufferEnabled = true;

}

void tw::Mesh::addTexturePoints (const TexturePoint& texturePoints...) {

    m_texturePoints.emplace_back(texturePoints);
    m_textureBufferEnabled = true;

}

void tw::Mesh::addJointBindings (const Vector3Integer& jointBindings...) {

    m_jointBindings.emplace_back(jointBindings);
    m_skeletalBufferEnabled = true;

}

void tw::Mesh::addJointWeights (const Vector3& jointWeights...) {

    m_jointWeights.emplace_back(jointWeights);
    m_skeletalBufferEnabled = true;

}

void tw::Mesh::setVertex (unsigned int index, const Vertex& vertex) {

    m_vertices.at(index) = vertex;

}

void tw::Mesh::setIndex (unsigned int indexOfIndex, uint32_t index) {

    m_indices.at(indexOfIndex) = index;

}

void tw::Mesh::setTexturePoint (unsigned int index, const TexturePoint& texturePoint) {

    m_texturePoints.at(index) = texturePoint;

}

void tw::Mesh::setJointBinding (unsigned int index, const Vector3Integer& jointBinding) {

    m_jointBindings.at(index) = jointBinding;

}

void tw::Mesh::setJointWeight (unsigned int index, const Vector3& jointWeight) {

    m_jointWeights.at(index) = jointWeight;

}

void tw::Mesh::clearVertices () {

    m_vertices.clear();

}

void tw::Mesh::clearIndices () {

    m_indexBufferEnabled = false;
    m_indices.clear();

}

void tw::Mesh::clearNormals () {

    m_normalBufferEnabled = false;
    m_normals.clear();

}

void tw::Mesh::clearTexturePoints () {

    m_textureBufferEnabled = false;
    m_texturePoints.clear();

}

void tw::Mesh::clearJointBindings () {

    m_skeletalBufferEnabled = false;
    m_jointBindings.clear();

}

void tw::Mesh::clearJointWeights () {

    m_skeletalBufferEnabled = false;
    m_jointWeights.clear();

}

void tw::Mesh::enableIndexBuffer () {

    m_indexBufferEnabled = true;

}

void tw::Mesh::disableIndexBuffer () {

    m_indexBufferEnabled = false;

}

void tw::Mesh::enableNormalBuffer () {

    m_normalBufferEnabled = true;

}

void tw::Mesh::disableNormalBuffer () {

    m_normalBufferEnabled = false;

}

void tw::Mesh::enableTextureBuffer () {

    m_textureBufferEnabled = true;

}

void tw::Mesh::disableTextureBuffer () {

    m_textureBufferEnabled = false;

}

void tw::Mesh::enableSkeletalBuffer () {

    m_skeletalBufferEnabled = true;

}

void tw::Mesh::disableSkeletalBuffer () {

    m_skeletalBufferEnabled = false;

}

uint16_t tw::Mesh::getTracksToBuffer () {

    if (m_handle != nullptr && !m_persist) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    unsigned int set = FLAG_VERTEX;
    set |= indexBufferEnabled() ? FLAG_INDEX : 0;
    set |= normalBufferEnabled () ? FLAG_NORMAL : 0;
    set |= textureBufferEnabled() ? FLAG_TEXTURE : 0;
    set |= skeletalBufferEnabled() ? FLAG_JOINT_BINDING | FLAG_JOINT_WEIGHT : 0;
    return set;

}

void* tw::Mesh::getDataPointer (uint8_t attrib) {

    if (m_handle != nullptr && !m_persist) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    switch (attrib) {

        case ATTRIB_VERTEX:
            return &m_vertices.front();

        case ATTRIB_INDEX:
            return &m_indices.front();

        case ATTRIB_NORMAL:
            return &m_normals.front();

        case ATTRIB_TEXTURE:
            return &m_texturePoints.front();

        case ATTRIB_JOINT_BINDING:
            return &m_jointBindings.front();

        case ATTRIB_JOINT_WEIGHT:
            return &m_jointWeights.front();

        default:
            return nullptr;

    }

}

size_t tw::Mesh::getDataBytes (uint8_t attrib) {

    if (m_handle != nullptr && !m_persist) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    switch (attrib) {

        case ATTRIB_VERTEX:
            return getVertexCount() * sizeof(Vertex);

        case ATTRIB_INDEX:
            return getIndexCount() * sizeof(uint32_t);

        case ATTRIB_NORMAL:
            return getNormalCount() * sizeof(Normal);

        case ATTRIB_TEXTURE:
            return getTexturePointCount() * sizeof(TexturePoint);

        case ATTRIB_JOINT_BINDING:
            return getJointBindingCount() * sizeof(Vector3Integer);

        case ATTRIB_JOINT_WEIGHT:
            return getJointWeightCount() * sizeof(Vector3);

        default:
            return 0;

    }

}

unsigned int tw::Mesh::getSegmentCount (uint8_t attrib) {

    if (m_handle != nullptr && !m_persist) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    switch (attrib) {

        case ATTRIB_VERTEX:
            return getVertexCount();

        case ATTRIB_INDEX:
            return getIndexCount();

        case ATTRIB_NORMAL:
            return getNormalCount();

        case ATTRIB_TEXTURE:
            return getTexturePointCount();

        case ATTRIB_JOINT_BINDING:
            return getJointBindingCount();

        case ATTRIB_JOINT_WEIGHT:
            return getJointWeightCount();

        default:
            return 0;

    }

}

int32_t tw::Mesh::getSegmentSize (uint8_t attrib) {

    if (!hasOriginalData()) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    switch (attrib) {

        case ATTRIB_VERTEX:
            return 3; // x, y, and z

        case ATTRIB_INDEX:
            return 1; // index

        case ATTRIB_NORMAL:
            return 3; // x, y, and z

        case ATTRIB_TEXTURE:
            return 2; // u and v

        case ATTRIB_JOINT_BINDING:
            return 3; // first, second, and third

        case ATTRIB_JOINT_WEIGHT:
            return 3; // first, second, and third

        default:
            return 0; // who knows

    }

}

tw::GraphicsBufferable::DataType tw::Mesh::getDataType (uint8_t attrib) {

    if (!hasOriginalData()) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    switch (attrib) {

        case ATTRIB_INDEX:
            return DataType::UINT;

        case ATTRIB_JOINT_BINDING:
            return DataType::INT;

        default:
            return DataType::FLOAT;

    }

}

size_t tw::Mesh::getDataTypeBytes (uint8_t attrib) {

    if (!hasOriginalData()) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    switch (attrib) {

        case ATTRIB_INDEX:
            return sizeof(uint32_t);

        case ATTRIB_JOINT_BINDING:
            return sizeof(int32_t);

        default:
            return sizeof(float);

    }

}

bool tw::Mesh::isNormalized (uint8_t attrib) {

    if (!hasOriginalData()) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    switch (attrib) {

        case ATTRIB_NORMAL:
            return true; // you better actually normalize those normals

        default:
            return false;

    }

}

size_t tw::Mesh::getStride (uint8_t attrib) {

    if (!hasOriginalData()) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    return 0;

}

size_t tw::Mesh::getOffset (uint8_t attrib) {

    if (!hasOriginalData()) {
        throw std::runtime_error("Cannot get bufferable data after handle is set when not persistent.");
    }

    return 0;

}

void tw::Mesh::eraseOriginalData () {

    std::vector<Vertex>().swap(m_vertices);
    std::vector<uint32_t>().swap(m_indices);
    std::vector<Normal>().swap(m_normals);
    std::vector<TexturePoint>().swap(m_texturePoints);
    std::vector<Vector3Integer>().swap(m_jointBindings);
    std::vector<Vector3>().swap(m_jointWeights);

}
