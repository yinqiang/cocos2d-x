#include "CCTestFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN


//================== TestFilter

TestFilter* TestFilter::create()
{
	TestFilter* __filter = new TestFilter();
	__filter->autorelease();
	return __filter;
}

TestFilter* TestFilter::create(float $resolation)
{
	TestFilter* __filter = TestFilter::create();
	__filter->setParameter($resolation);
	return __filter;
}

TestFilter::TestFilter()
{
	this->shaderName = kCCFilterShader_test;
}

CCGLProgram* TestFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("TestFilter::loadShader, program: %p", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_test_vert,
		ccFilterShader_test_frag);
	return __p;
}

void TestFilter::setParameter(float $resolation)
{
	//The initProgram() will perform in initSprite()
}

void TestFilter::initSprite(CCFilteredSprite* $sprite)
{
	CCSize __size = $sprite->getContentSize();
	/*_textureWidth = __size.width;
	_textureHeight = __size.height;*/
	_textureWidth = 480;
	_textureHeight = 320;
	initProgram();
}

void TestFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("TestFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
}

void TestFilter::setUniforms(CCGLProgram* $cgp)
{
	CCTexture2D* __maskTex = CCTextureCache::sharedTextureCache()->addImage("mask10.png");
	__maskTex->setAntiAliasTexParameters();

	CCTexture2D* __tex1 = CCTextureCache::sharedTextureCache()->addImage("dirt.png");
	__tex1->setAntiAliasTexParameters();


	int u_mask = $cgp->getUniformLocationForName("u_mask");
	int u_texture1 = $cgp->getUniformLocationForName("u_texture1");
	int u_cctexture = $cgp->getUniformLocationForName("CC_Texture0");

	CCLOG("TestFilter::setUniforms u_mask:%d, u_texture1:%d, CC_Texture0:%d", u_mask, u_texture1, u_cctexture);
	$cgp->setUniformLocationWith1i(u_mask, 2);
	$cgp->setUniformLocationWith1i(u_texture1, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, __maskTex->getName());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, __tex1->getName());
	glActiveTexture(GL_TEXTURE0);

	CCLOG("TestFilter::setUniforms _textureWidth:%.5f,_textureHeight:%.5f",
		_textureWidth, _textureHeight);
}

NS_CC_EXT_END
