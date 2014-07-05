#ifndef __CCSHADER_FILTER_H__
#define __CCSHADER_FILTER_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCGL.h"
#include "filters/shaders/ccFilterShaders.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

class CCFilteredSprite;

//================== Filter

class Filter : public CCObject
{
public:
	Filter();
	~Filter();

	virtual void initSprite(CCFilteredSprite* $sprite);
	virtual void draw();
	CCGLProgram* getProgram();

	const char* shaderName;
protected:
	CCGLProgram* _pProgram;
	void initProgram();
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

class SingleFloatParamFilter : public Filter
{
public:
	SingleFloatParamFilter();

	virtual void setParameter(float $param);
protected:
	float _param;
};



NS_CC_EXT_END

#endif /* __CCSHADER_FILTER_H__ */
