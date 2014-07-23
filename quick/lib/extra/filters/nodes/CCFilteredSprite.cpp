/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== FilteredSprite

FilteredSprite::FilteredSprite()
: _pFilters(NULL)
{

}

FilteredSprite::~FilteredSprite()
{
    _pFilters.clear();
}

void FilteredSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    // Don't do calculate the culling if the transform was not updated
    _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
    
    if(_insideBounds)
    {
        // normal effect: order == 0
        _quadCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, transform);
        renderer->addCommand(&_quadCommand);
        
        int i = 0;
        for(auto &command : _pCommand) {
            QuadCommand &q = std::get<2>(command);
            q.init(_globalZOrder, _texture->getName(), std::get<1>(command)->getGLProgramState(), _blendFunc, &_quad, 1, transform);
            renderer->addCommand(&q);
            
            i++;
            if (i > 1){
            break;
            }
        }
    }
}

Filter* FilteredSprite::getFilter(unsigned int $index)
{
	if (_pFilters.size() == 0 || $index >= (unsigned int)(_pFilters.size()))
	{
		return NULL;
	}
	return static_cast<Filter*>(_pFilters.at($index));
}

Vector<Filter*>& FilteredSprite::getFilters()
{
	return _pFilters;
}

void FilteredSprite::setFilters(Vector<Filter*>& $pFilters)
{
	_pFilters = $pFilters;
    
    _pCommand.clear();
    ssize_t i = 0;
    for (auto &filter : _pFilters) {
        _pCommand.push_back(std::make_tuple(i, filter, QuadCommand()));
        i++;
    }
	//CCLOG("FilteredSprite setFilters:%d", _pFilters->count());
	updateFilters();
}

//================== FilteredSpriteWithOne

FilteredSpriteWithOne* FilteredSpriteWithOne::create()
{
	FilteredSpriteWithOne *pSprite = new FilteredSpriteWithOne();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

FilteredSpriteWithOne* FilteredSpriteWithOne::create(const char* $pszFileName)
{
	FilteredSpriteWithOne *pobSprite = new FilteredSpriteWithOne();
	if (pobSprite && pobSprite->initWithFile($pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

FilteredSpriteWithOne* FilteredSpriteWithOne::create(const char* $pszFileName, const Rect& $rect)
{
	FilteredSpriteWithOne *pobSprite = new FilteredSpriteWithOne();
	if (pobSprite && pobSprite->initWithFile($pszFileName, $rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


FilteredSpriteWithOne* FilteredSpriteWithOne::createWithTexture(Texture2D* $pTexture)
{
    FilteredSpriteWithOne *pobSprite = new FilteredSpriteWithOne();
    if (pobSprite && pobSprite->initWithTexture($pTexture))
    {
        pobSprite->autorelease();
        return static_cast<FilteredSpriteWithOne*>(pobSprite);
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

FilteredSpriteWithOne* FilteredSpriteWithOne::createWithTexture(Texture2D* $pTexture, const Rect& $rect)
{
    FilteredSpriteWithOne *pobSprite = new FilteredSpriteWithOne();
    if (pobSprite && pobSprite->initWithTexture($pTexture, $rect))
    {
        pobSprite->autorelease();
        return static_cast<FilteredSpriteWithOne*>(pobSprite);
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}


FilteredSpriteWithOne* FilteredSpriteWithOne::createWithSpriteFrame(SpriteFrame* $pSpriteFrame)
{
	FilteredSpriteWithOne *pobSprite = new FilteredSpriteWithOne();
	if ($pSpriteFrame && pobSprite)
	{
		if ($pSpriteFrame->isRotated())
		{
			Sprite* __sp = Sprite::createWithSpriteFrame($pSpriteFrame);
			Size __size = __sp->getContentSize();
			__sp->setAnchorPoint(Vec2(0,0));
			__sp->setPosition(Vec2(0,0));
			RenderTexture* __rTex = RenderTexture::create(__size.width, __size.height);
			__rTex->begin();
			__sp->visit();
			__rTex->end();
			Texture2D* __newTex = new Texture2D();
			__newTex->initWithImage(__rTex->newImage(true));
			__newTex->autorelease();
			pobSprite->initWithTexture(__newTex);
			//CCLOG("==== FilteredSprite::initWithTexture, rotated true texture wh(%f,%f)", __newTex->getContentSize().width, __newTex->getContentSize().height);
		}
		else
		{
			pobSprite->initWithSpriteFrame($pSpriteFrame);
		}
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

FilteredSpriteWithOne* FilteredSpriteWithOne::createWithSpriteFrameName(const char* $pszSpriteFrameName)
{
	SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName($pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", $pszSpriteFrameName);
	CCASSERT(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

Filter* FilteredSpriteWithOne::getFilter(unsigned int $index)
{
	return FilteredSprite::getFilter(0);
}

void FilteredSpriteWithOne::setFilter(Filter* $pFilter)
{
    Vector<Filter*> __pFilters;
    __pFilters.pushBack($pFilter);
	FilteredSprite::setFilters(__pFilters);
}

void FilteredSpriteWithOne::setFilters(Vector<Filter*>& $pFilters)
{
    FilteredSprite::setFilters($pFilters);
	//CCASSERT(false, "setFilters on FilteredSpriteWithOne is forbidden!");
}

void FilteredSpriteWithOne::clearFilter()
{
    _pFilters.clear();
    //CCLOG("FilteredSpriteWithOne::clearFilter");
//    setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
}

void FilteredSpriteWithOne::drawFilter()
{
	// show custom filter
	if (_pFilters.size() == 1)
	{
		static_cast<Filter*>(_pFilters.at(0))->draw();
	}
}

bool FilteredSpriteWithOne::updateFilters()
{
	//CCASSERT(_pFilters.size() == 1, "Invalid Filter!");
	do
	{
		unsigned int __count = _pCommand.size();
		CC_BREAK_IF(__count == 0);
        auto item = _pCommand.at(0);
        Filter* __filter = static_cast<Filter*>(std::get<1>(item));
		__filter->initSprite(this);
		if (__filter->getGLProgramState())
		{
            setGLProgramState(__filter->getGLProgramState());
		}
		CHECK_GL_ERROR_DEBUG();
		return true;
	} while (0);

	return false;
}
//================== FilteredSpriteWithMulti

FilteredSpriteWithMulti* FilteredSpriteWithMulti::create()
{
	FilteredSpriteWithMulti *pSprite = new FilteredSpriteWithMulti();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

FilteredSpriteWithMulti* FilteredSpriteWithMulti::create(const char* $pszFileName)
{
	Texture2D* __pTexture = Director::getInstance()->getTextureCache()->addImage($pszFileName);
	Rect __rect = Rect(0, 0, 0, 0);
	__rect.size = __pTexture->getContentSize();
	return createWithTexture(__pTexture, __rect);
}

FilteredSpriteWithMulti* FilteredSpriteWithMulti::create(const char* $pszFileName, const Rect& $rect)
{
	Texture2D* __pTexture = Director::getInstance()->getTextureCache()->addImage($pszFileName);
	return FilteredSpriteWithMulti::createWithTexture(__pTexture, $rect);
}

FilteredSpriteWithMulti* FilteredSpriteWithMulti::createWithTexture(Texture2D* $pTexture)
{
	Rect __rect = Rect(0, 0, 0, 0);
	__rect.size = $pTexture->getContentSize();
	FilteredSpriteWithMulti *pobSprite = FilteredSpriteWithMulti::createWithTexture($pTexture, __rect);
	return pobSprite;
}

FilteredSpriteWithMulti* FilteredSpriteWithMulti::createWithTexture(Texture2D* $pTexture, const Rect& $rect)
{
	FilteredSpriteWithMulti *pobSprite = FilteredSpriteWithMulti::create();
	pobSprite->setTSTexture($pTexture);
	pobSprite->setTSRect($rect);
	return pobSprite;
}

FilteredSpriteWithMulti* FilteredSpriteWithMulti::createWithSpriteFrame(SpriteFrame* $pSpriteFrame)
{
	FilteredSpriteWithMulti *pobSprite = FilteredSpriteWithMulti::create();
	pobSprite->setTSFrame($pSpriteFrame);
	return pobSprite;
}

FilteredSpriteWithMulti* FilteredSpriteWithMulti::createWithSpriteFrameName(const char* $pszSpriteFrameName)
{
	SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName($pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", $pszSpriteFrameName);
	CCASSERT(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

FilteredSpriteWithMulti::FilteredSpriteWithMulti()
: _pTexture(NULL)
, _pFrame(NULL)
, _rect(0.f, 0.f, 0.f, 0.f)
{
}

FilteredSpriteWithMulti::~FilteredSpriteWithMulti()
{
	CC_SAFE_RELEASE(_pTexture);
	CC_SAFE_RELEASE(_pFrame);
}

Texture2D* FilteredSpriteWithMulti::getTSTexture()
{
	return _pTexture;
}

void FilteredSpriteWithMulti::setTSTexture(Texture2D* $texture)
{
	CC_SAFE_RETAIN($texture);
	CC_SAFE_RELEASE(_pTexture);
	_pTexture = $texture;
}

SpriteFrame* FilteredSpriteWithMulti::getTSFrame()
{
	return _pFrame;
}

void FilteredSpriteWithMulti::setTSFrame(SpriteFrame* $pFrame)
{
	CC_SAFE_RETAIN($pFrame);
	CC_SAFE_RELEASE(_pFrame);
	_pFrame = $pFrame;
}

Rect FilteredSpriteWithMulti::getTSRect()
{
	return _rect;
}

void FilteredSpriteWithMulti::setTSRect(const Rect& $rect)
{
	_rect = $rect;
}

void FilteredSpriteWithMulti::setFilter(Filter* $pFilter)
{
	CCASSERT(false, "setFilter on FilteredSpriteWithMulti is forbidden!");
}

void FilteredSpriteWithMulti::clearFilter()
{
    //CCLOG("FilteredSpriteWithMulti::clearFilter");
    _pFilters.clear();
    if (_pTexture)
    {
        initWithTexture(_pTexture, _rect);
    }
    else if (_pFrame)
    {
        initWithSpriteFrame(_pFrame);
    }
}

bool FilteredSpriteWithMulti::updateFilters()
{
	CCASSERT(_pFilters.size()>1, "Invalid Filter!");
	do
	{
		FilteredSprite* __sp = NULL;
		Size __size;
		if (_pTexture)
		{
			__size = _pTexture->getContentSize();
		}
		else if (_pFrame)
		{
			__size = _pFrame->getRect().size;
		}
		else
		{
			break;
		}

		unsigned int __count = _pFilters.size();
		Texture2D* __newTex = NULL;
		RenderTexture* __canva = RenderTexture::create(__size.width, __size.height);
		//CCLOG("FilteredSpriteWithMulti::updateFilters %f, %f", __size.width, __size.height);
		for (size_t i = 0; i < __count; i++)
		{
			//CCLOG("FilteredSpriteWithMulti render %d", i);
			
			__canva->begin();
			Filter* __filter = static_cast<Filter*>(_pFilters.at(i));
			if (i == 0)
			{
				__sp = _pTexture ?
					FilteredSpriteWithOne::createWithTexture(_pTexture) :
					FilteredSpriteWithOne::createWithSpriteFrame(_pFrame);
			}
			else
			{
				__sp = FilteredSpriteWithOne::createWithTexture(__newTex);
			}
			__sp->setFilter(__filter);
			__sp->setAnchorPoint(Vec2(0, 0));
			//__sp->setPosition(Vec2(0, 0));
			//__sp->getTexture()->setAliasTexParameters();
			__sp->visit();
			__canva->end();
			__newTex = new Texture2D();
			__newTex->initWithImage(__canva->newImage(true));
			__newTex->autorelease();

			//CCLOG("__sp (%u, %u)", __newTex->getPixelsWide(), __newTex->getPixelsHigh());
		}
		initWithTexture(__newTex);
		CHECK_GL_ERROR_DEBUG();
		//CCLOG("FilteredSpriteWithMulti updateFilters:%d", __count);
		//CCLOG("==== FilteredSpriteWithMulti updateFilters texture %f, %f", __newTex->getContentSize().width, __newTex->getContentSize().height);
		return true;
	} while (0);

	return false;
}

void FilteredSpriteWithMulti::drawFilter(){}

NS_CC_EXT_END