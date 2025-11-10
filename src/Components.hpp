#pragma once

#include"Animation.hpp"
#include"Vec2.hpp"

class Component {
    public:
    bool exists = false;
};

class CTransform : public Component {
    public:
    Vec2f pos       = {0.0,0.0};
    Vec2f prevPos   = {0.0,0.0};
    Vec2f scale     = {1.0,1.0};
    Vec2f velocity  = {5.0,5.0};
    float angle     = 0;

    CTransform()    = default;
    CTransform( const Vec2f& p) : pos(p) {} 
    CTransform( const Vec2f& p, const Vec2f& v, const Vec2f& sc, float a) : pos(p), prevPos(p), velocity(v), scale(sc), angle(a) {} 
};

class CLifespan : public Component {
    public:

    int lifespan = 0;
    int remaining = 0;
    CLifespan() = default;
    CLifespan(int totalLifespan) : lifespan(totalLifespan), remaining(totalLifespan) {}
};

class CInput : public Component {
    public:
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;
    bool canShoot = true;
    bool canJump = true;

    CInput() = default;
};

class CBoundingBox : public Component {
    public:
    Vec2f size;
    Vec2f halfSize;
    CBoundingBox() = default;
    CBoundingBox(const Vec2f& s) : size(s), halfSize(s.x/2,s.y/2) {}
};

class CAnimation : public Component {
    public: 
    Animation animation;
    bool repeat = false;
    CAnimation() = default;
    CAnimation(const Animation& animation, bool r) : animation(animation), repeat(r) {}
};

class CGravity : public Component {
    public:
    float gravity = 0;
    CGravity() = default;
    CGravity(float g) : gravity(g) {}  
};

class CState : public Component {
    public:
    std::string state = "jumping";
    CState() = default;
    CState(const std::string& s) : state(s) {}
};

static_assert(std::is_default_constructible_v<CTransform>);
static_assert(std::is_default_constructible_v<CLifespan>);
static_assert(std::is_default_constructible_v<CInput>);
static_assert(std::is_default_constructible_v<CBoundingBox>);
static_assert(std::is_default_constructible_v<CAnimation>);
static_assert(std::is_default_constructible_v<CGravity>);
static_assert(std::is_default_constructible_v<CState>);

static_assert(std::is_default_constructible_v<Vec2f>);
static_assert(std::is_default_constructible_v<Animation>);
