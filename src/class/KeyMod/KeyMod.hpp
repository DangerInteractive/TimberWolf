#ifndef H_CLASS_KEYMOD
#define H_CLASS_KEYMOD

class KeyMod {

public:

    static const int MOD_SHIFT   = 0x00000001;
    static const int MOD_CONTROL = 0x00000002;
    static const int MOD_ALT     = 0x00000004;
    static const int MOD_SUPER   = 0x00000008;

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

    bool operator == (const KeyMod);
    bool operator != (const KeyMod);

private:

    int m_flags;

};

#endif
