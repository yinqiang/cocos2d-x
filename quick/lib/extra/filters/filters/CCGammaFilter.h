#ifndef __CCGAMMA_FILTER__
#define __CCGAMMA_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== GammaFilter

class GammaFilter : public SingleFloatParamFilter
{

public:
	static GammaFilter* create();
	static GammaFilter* create(float $param);

	GammaFilter();

	virtual void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);

};

NS_CC_EXT_END

#endif //__CCGAMMA_FILTER__
