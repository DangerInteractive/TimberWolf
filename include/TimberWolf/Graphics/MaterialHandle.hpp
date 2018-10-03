#ifndef TW_CLASS_MATERIALHANDLE
#define TW_CLASS_MATERIALHANDLE

namespace tw {
class MaterialHandle {

public:

    MaterialHandle () = default;
    virtual ~MaterialHandle () = 0;

    MaterialHandle (MaterialHandle&&) = default;
    MaterialHandle& operator = (MaterialHandle&&) = default;

    MaterialHandle (const MaterialHandle&) = delete;
    MaterialHandle& operator = (const MaterialHandle&) = delete;

    virtual bool bind () = 0;
    virtual bool unbind () = 0;

};
}

#endif
