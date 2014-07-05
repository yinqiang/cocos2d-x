#include "CCHazeFilter.h"

NS_CC_EXT_BEGIN

//================== HazeFilter

HazeFilter* HazeFilter::create()
{
	HazeFilter* __filter = new HazeFilter();
	__filter->autorelease();
	return __filter;
}

HazeFilter* HazeFilter::create(float $hazeDistance, float $slope)
{
	HazeFilter* __filter = HazeFilter::create();
	__filter->setParameter($hazeDistance, $slope);
	return __filter;
}

HazeFilter::HazeFilter()
: _hazeDistance(0.f)
, _slope(0.f)
{
	this->shaderName = kCCFilterShader_haze;
}

CCGLProgram* HazeFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	//CCLOG("HazeFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_haze_frag);
	return __p;
}

void HazeFilter::setParameter(float $hazeDistance, float $slope)
{
	_hazeDistance = MIN(0.5f, MAX($hazeDistance, -0.5f));
	_slope = MIN(0.5f, MAX($slope, -0.5f));
	initProgram();
}

void HazeFilter::setAttributes(CCGLProgram* $cgp)
{
	//CCLOG("HazeFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void HazeFilter::setUniforms(CCGLProgram* $cgp)
{
	int __hazeDistance = $cgp->getUniformLocationForName("u_hazeDistance");
	int __slope = $cgp->getUniformLocationForName("u_slope");
	//CCLOG("HazeFilter::setUniforms %d, %d", __hazeDistance, __slope);
	$cgp->setUniformLocationWith1f(__hazeDistance, _hazeDistance);
	$cgp->setUniformLocationWith1f(__slope, _slope);
	//CCLOG("HazeFilter::setUniforms _hazeDistance:%.5f, _slope:%.5f", _hazeDistance, _slope);
}
NS_CC_EXT_END
