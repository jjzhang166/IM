//
//  AddHeadForgrand.h
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#include "CrossApp.h"
#include "IMDATA.h"
USING_NS_CC;
//头像处理，箭头处理
class AddHeadForgrand:public CAObject
{
public:
	AddHeadForgrand();
	virtual ~AddHeadForgrand();
	static AddHeadForgrand* getInstance();
	void addHeadForgrand(CAImageView* pImageView);
	//void tablecellAddRightArrow(CATableViewCell* pcell, const CCSize& cellsize);
	//CABarButtonItem* leftBackBtn();	
};
