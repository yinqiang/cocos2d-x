
#ifndef __CC_EXTENSION_CCEFFECT_H_
#define __CC_EXTENSION_CCEFFECT_H_

#include "cocos2dx_extra.h"
#include "EffectSprite.h"

NS_CC_EXTRA_BEGIN

class Effect : public Ref
{
public:
    GLProgramState* getGLProgramState() const { return _glprogramstate; }
    virtual void setTarget(EffectSprite *sprite){}

protected:
    bool initGLProgramState(const std::string &fragmentFilename);
    bool initGLProgramStateWithByte(const GLchar* frag);
    Effect();
    virtual ~Effect();
    GLProgramState *_glprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string _fragSource;
    EventListenerCustom* _backgroundListener;
#endif
};


class EffectBlur : public Effect
{
public:
	CREATE_FUNC(EffectBlur);

    void setBlurRadius(float radius);
    void setBlurSampleNum(float num);

protected:
    bool init(float blurRadius = 10.0f, float sampleNum = 5.0f);
    virtual void setTarget(EffectSprite *sprite) override;
    
    float _blurRadius;
    float _blurSampleNum;
};

// Outline
class EffectOutline : public Effect
{
public:
	CREATE_FUNC(EffectOutline);

protected:
    bool init();
};

// Noise
class EffectNoise : public Effect
{
public:
    CREATE_FUNC(EffectNoise);

protected:
    bool init();

    virtual void setTarget(EffectSprite* sprite) override;
};

// Edge Detect
class EffectEdgeDetect : public Effect
{
public:
    CREATE_FUNC(EffectEdgeDetect);

protected:
    bool init();

    virtual void setTarget(EffectSprite* sprite) override;
};

// Grey
class EffectGreyScale : public Effect
{
public:
    CREATE_FUNC(EffectGreyScale);

protected:
    bool init();
};

// Sepia
class EffectSepia : public Effect
{
public:
    CREATE_FUNC(EffectSepia);

protected:
    bool init();
};

// bloom
class EffectBloom : public Effect
{
public:
    CREATE_FUNC(EffectBloom);

protected:
    bool init();
};

// cel shading
class EffectCelShading : public Effect
{
public:
    CREATE_FUNC(EffectCelShading);

protected:
    bool init();

    virtual void setTarget(EffectSprite* sprite) override;
};

// Lens Flare
class EffectLensFlare : public Effect
{
public:
    CREATE_FUNC(EffectLensFlare);

protected:
    bool init();

    virtual void setTarget(EffectSprite* sprite) override;
};


//

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_EFFECT_H_

