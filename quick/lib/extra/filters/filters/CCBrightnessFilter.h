#ifndef __CCBRIGHTNESS_FILTER__
#define __CCBRIGHTNESS_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN
//================== BrightnessFilter

class BrightnessFilter : public SingleFloatParamFilter
{

public:
	static BrightnessFilter* create();
	static BrightnessFilter* create(float $brightness);

	BrightnessFilter();

	virtual void setParameter(float $brightness);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCBRIGHTNESS_FILTER__