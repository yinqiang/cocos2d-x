#ifndef __CCSATURATION_FILTER__
#define __CCSATURATION_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== SaturationFilter

class SaturationFilter : public SingleFloatParamFilter
{

public:
	static SaturationFilter* create();
	static SaturationFilter* create(float $param);

	SaturationFilter();

	virtual void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};


NS_CC_EXT_END

#endif //__CCSATURATION_FILTER__
