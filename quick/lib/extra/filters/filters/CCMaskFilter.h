#ifndef __CCMASK_FILTER__
#define __CCMASK_FILTER__

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== MaskFilter

class MaskFilter : public Filter
{

public:
	static MaskFilter* create();
	static MaskFilter* create(CCString* $maskImage);
	static MaskFilter* createWithSpriteFrameName(CCString* $maskImage);

	MaskFilter();

	void setParameter(CCString* $param);
	virtual void initSprite(CCFilteredSprite* $sprite);
	inline void setIsSpriteFrame(bool $isSpriteFrame){ _isSpriteFrame = $isSpriteFrame; };
protected:
	void initProgram();
	CCString* _param;
	bool _isSpriteFrame;

};

NS_CC_EXT_END

#endif //__CCMASK_FILTER__