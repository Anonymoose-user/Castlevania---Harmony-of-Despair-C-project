// Dll/Player/PlayerInput.h - pad state handed to the player each frame
// (0x20 bytes, PlayerBase +0x2C0; no vtable). Four 13-button masks and four
// stick axes, written by PlayerBase::setInput (slot +0x1C4). Names inferred.
#pragma once

class PlayerInput {
public:
    PlayerInput();
    ~PlayerInput();                                 // empty

    void setMasks(unsigned int m0, unsigned int m1, unsigned int m2, unsigned int m3);
    void setBit0(unsigned int button);
    void setBit1(unsigned int button);
    void setBit2(unsigned int button);
    void setBit3(unsigned int button);
    void setSticks(float s0, float s1, float s2, float s3);
    bool test0(int button) const;
    bool test1(int button) const;
    bool test2(int button) const;
    bool test3(int button) const;
    unsigned int getMask0() const;
    unsigned int getMask1() const;
    float getStick0() const;
    float getStick1() const;
    float getStick2() const;
    float getStick3() const;

    enum { BUTTON_COUNT = 13 };

    unsigned int m_mask[4];                         // +0x00
    float m_stick[4];                               // +0x10
};
