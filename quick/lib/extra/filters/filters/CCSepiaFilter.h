
#ifndef __CCSEPIA_FILTER__
#define __CCSEPIA_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== SepiaFilter

class SepiaFilter : public Filter
{

public:
	static SepiaFilter* create();
	static SepiaFilter* create(float $resolation);

	SepiaFilter();

	void setParameter();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

NS_CC_EXT_END

#endif //__CCSEPIA_FILTER__
