
#ifndef __CC_EXTENSION_CCEFFECTSPRITE_H_
#define __CC_EXTENSION_CCEFFECTSPRITE_H_

#include "cocos2dx_extra.h"

class Effect;
class EffectSprite : public Sprite
{
public:
    static EffectSprite *create(const std::string& filename);

    void setEffectByName(const char* name);
    void addEffectByName(const char* name, int order);

    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
    EffectSprite();
    ~EffectSprite();
    
    Effect* createEffectByName(const char* name);
    void setEffect(Effect* effect);
    void addEffect(Effect *effect, ssize_t order);

    std::vector<std::tuple<ssize_t,Effect*,QuadCommand>> _effects;
    Effect* _defaultEffect;
};

#endif // __CC_EXTENSION_EFFECTSPRITE_H_
