
#ifndef __CCHUE_FILTER__
#define __CCHUE_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== HueFilter

class HueFilter : public SingleFloatParamFilter
{

public:
	static HueFilter* create();
	static HueFilter* create(float $param);

	HueFilter();

	void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCHUE_FILTER__
