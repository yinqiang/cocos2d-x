
#ifndef __CC_EXTENSION_CCEFFECTSPRITE_H_
#define __CC_EXTENSION_CCEFFECTSPRITE_H_

#include "cocos2dx_extra.h"

NS_CC_EXTRA_BEGIN

class Effect;
class EffectSprite : public Sprite
{
public:
    static EffectSprite *create(const std::string& filename);
    static EffectSprite *create(const char* filename);

    void setEffectByName(const char* name, float val1 = 0, float val2 = 0, float val3 = 0);
    void addEffectByName(const char* name, int order, float val1 = 0, float val2 = 0, float val3 = 0);
    void setEffect(Effect* effect);
    void addEffect(Effect *effect, ssize_t order);

    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
    EffectSprite();
    ~EffectSprite();
    
    Effect* createEffectByName(const char* name, float val1 = 0, float val2 = 0, float val3 = 0);

    std::vector<std::tuple<ssize_t,Effect*,QuadCommand>> _effects;
    Effect* _defaultEffect;
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_EFFECTSPRITE_H_
