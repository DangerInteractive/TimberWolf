#ifndef H_CLASS_MODEL
#define H_CLASS_MODEL

namespace tw {
class Model {

public:

    Model ();
    ~Model () = default;

    Model (Model&&) = default;
    Model& operator = (Model&&) = default;

    Model (const Model&) = default;
    Model& operator = (const Model&) = default;

private:

};
}

#endif
