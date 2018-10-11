#ifndef TW_CLASS_GLMESHHANDLE
#define TW_CLASS_GLMESHHANDLE

#include <GL/glew.h>

#include "../Mesh.hpp"
#include "../MeshHandle.hpp"

#include "GLVertexArray.hpp"

namespace tw {
class GLMeshHandle : public MeshHandle {

public:

    GLMeshHandle () = default;
    explicit GLMeshHandle (GLVertexArray&&);
    explicit GLMeshHandle (Mesh&);
    ~GLMeshHandle () = default;

    GLMeshHandle (GLMeshHandle&&) = default;
    GLMeshHandle& operator = (GLMeshHandle&&) = default;

    GLMeshHandle (const GLMeshHandle&) = default;
    GLMeshHandle& operator = (const GLMeshHandle&) = default;

    const GLVertexArray& getVao () const;

    bool bind () override;
    bool unbind () override;

    static bool clearBound ();

private:

    GLVertexArray m_vao {};

};
}

#endif
