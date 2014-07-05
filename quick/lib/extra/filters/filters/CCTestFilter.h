
#ifndef __CCTEST_FILTER__
#define __CCTEST_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== TestFilter

class TestFilter : public Filter
{

public:
	static TestFilter* create();
	static TestFilter* create(float $resolation);

	TestFilter();

	void setParameter(float $resolation);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _textureWidth;
	float _textureHeight;
};

NS_CC_EXT_END

#endif //__CCTEST_FILTER__
