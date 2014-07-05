#ifndef __CCEXPOSURE_FILTER__
#define __CCEXPOSURE_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== ExposureFilter

class ExposureFilter : public SingleFloatParamFilter
{

public:
	static ExposureFilter* create();
	static ExposureFilter* create(float $param);

	ExposureFilter();

	virtual void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCEXPOSURE_FILTER__