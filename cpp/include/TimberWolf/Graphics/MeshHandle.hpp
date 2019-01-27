#ifndef TW_CLASS_MESHHANDLE
#define TW_CLASS_MESHHANDLE

namespace tw {
class MeshHandle {

public:

    MeshHandle () = default;
    virtual ~MeshHandle () = default;

    MeshHandle (MeshHandle&&) = default;
    MeshHandle& operator = (MeshHandle&&) = default;

    MeshHandle (const MeshHandle&) = delete;
    MeshHandle& operator = (const MeshHandle&) = delete;

    virtual bool bind () = 0;
    virtual bool unbind () = 0;

};
}

#endif
