
#include "Effect.h"
#include "shaders/FilterShaders.h"

USING_NS_CC_EXTRA;

bool Effect::initGLProgramState(const std::string &fragmentFilename)
{
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _fragSource = fragSource;
#endif
    
    _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    _glprogramstate->retain();

    return _glprogramstate != nullptr;
}

bool Effect::initGLProgramStateWithByte(const GLchar* frag)
{
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, frag);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _fragSource = fragSource;
#endif
    
    _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    _glprogramstate->retain();
    
    return _glprogramstate != nullptr;
}

Effect::Effect()
: _glprogramstate(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _backgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                      [this](EventCustom*)
                                                      {
                                                          auto glProgram = _glprogramstate->getGLProgram();
                                                          glProgram->reset();
                                                          glProgram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, _fragSource.c_str());
                                                          glProgram->link();
                                                          glProgram->updateUniforms();
                                                      }
                                                      );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backgroundListener, -1);
#endif
}

Effect::~Effect()
{
    CC_SAFE_RELEASE_NULL(_glprogramstate);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
}

// Blur
void EffectBlur::setTarget(EffectSprite *sprite)
{
    Size size = sprite->getTexture()->getContentSizeInPixels();
    _glprogramstate->setUniformVec2("resolution", size);
    _glprogramstate->setUniformFloat("blurRadius", _blurRadius);
    _glprogramstate->setUniformFloat("sampleNum", _blurSampleNum);
}

bool EffectBlur::init(float blurRadius, float sampleNum)
{
    //initGLProgramState("Shaders/example_Blur.fsh");
    initGLProgramStateWithByte(FilterShader_blur_frag);
    _blurRadius = blurRadius;
    _blurSampleNum = sampleNum;
    
    return true;
}

void EffectBlur::setBlurRadius(float radius)
{
    _blurRadius = radius;
}

void EffectBlur::setBlurSampleNum(float num)
{
    _blurSampleNum = num;
}


// Outline
bool EffectOutline::init()
{
    //initGLProgramState("Shaders/example_outline.fsh");
    initGLProgramStateWithByte(FilterShader_outline_frag);

    Vec3 color(1.0f, 0.2f, 0.3f);
    GLfloat radius = 0.01f;
    GLfloat threshold = 1.75;

    _glprogramstate->setUniformVec3("u_outlineColor", color);
    _glprogramstate->setUniformFloat("u_radius", radius);
    _glprogramstate->setUniformFloat("u_threshold", threshold);
    return true;
}


// Noise
bool EffectNoise::init() {
    //initGLProgramState("Shaders/example_Noisy.fsh");
    initGLProgramStateWithByte(FilterShader_noisy_frag);
    return true;
}

void EffectNoise::setTarget(EffectSprite* sprite)
{
    auto s = sprite->getTexture()->getContentSizeInPixels();
    getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
}

// Edge Detect
bool EffectEdgeDetect::init() {
    //initGLProgramState("Shaders/example_edgeDetection.fsh");
    initGLProgramStateWithByte(FilterShader_edgedetection_frag);
    return true;
}

void EffectEdgeDetect::setTarget(EffectSprite* sprite)
{
    auto s = sprite->getTexture()->getContentSizeInPixels();
    getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
}

// Grey
bool EffectGreyScale::init() {
    //initGLProgramState("Shaders/example_greyScale.fsh");
    initGLProgramStateWithByte(FilterShader_greyscale_frag);
    return true;
}

// Sepia
bool EffectSepia::init() {
    //initGLProgramState("Shaders/example_sepia.fsh");
    initGLProgramStateWithByte(FilterShader_sepia_frag);
    return true;
}

// bloom
bool EffectBloom::init() {
    //initGLProgramState("Shaders/example_bloom.fsh");
    initGLProgramStateWithByte(FilterShader_bloom_frag);
    return true;
}

// cel shading
bool EffectCelShading::init() {
    //initGLProgramState("Shaders/example_celShading.fsh");
    initGLProgramStateWithByte(FilterShader_celshading_frag);
    return true;
}

void EffectCelShading::setTarget(EffectSprite* sprite)
{
    auto s = sprite->getTexture()->getContentSizeInPixels();
    getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
}

// Lens Flare
bool EffectLensFlare::init() {
    //initGLProgramState("Shaders/example_lensFlare.fsh");
    initGLProgramStateWithByte(FilterShader_lensflare_frag);
    return true;
}

void EffectLensFlare::setTarget(EffectSprite* sprite)
{
    auto s = sprite->getTexture()->getContentSizeInPixels();
    getGLProgramState()->setUniformVec2("textureResolution", Vec2(s.width, s.height));

    s = Director::getInstance()->getWinSize();
    getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));

}

