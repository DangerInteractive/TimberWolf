#ifndef H_CLASS_KEYMOD
#define H_CLASS_KEYMOD

namespace tw {
class KeyMod {

public:

    static inline constexpr unsigned int MOD_SHIFT   = 0b0001;
    static inline constexpr unsigned int MOD_CONTROL = 0b0010;
    static inline constexpr unsigned int MOD_ALT     = 0b0100;
    static inline constexpr unsigned int MOD_SUPER   = 0b1000;

    explicit KeyMod (int);
    KeyMod (bool, bool, bool, bool);
    ~KeyMod () = default;

    KeyMod (KeyMod&&) = default;
    KeyMod& operator = (KeyMod&&) = default;

    KeyMod (const KeyMod&) = default;
    KeyMod& operator = (const KeyMod&) = default;

    int getFlags () const;
    bool getShift () const;
    bool getControl () const;
    bool getAlt () const;
    bool getSuper () const;

    void setFlags (int);
    void setShift (bool);
    void setControl (bool);
    void setAlt (bool);
    void setSuper (bool);

    bool operator == (const KeyMod&);
    bool operator != (const KeyMod&);

private:

    unsigned int m_flags;

};
}

#endif
