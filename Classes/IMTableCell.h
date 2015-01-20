//
//  IMTableCell.h
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __IMTABLECELL_H__
#define __IMTABLECELL_H__

typedef enum{
	Group = 0,
	Friend,
	Strange
}IMCellType;

#include "CrossApp.h"
#include <vector>
USING_NS_CC;
using namespace std;

class IMTableCell : public CATableViewCell
{
public:
	IMTableCell();
	virtual ~IMTableCell();
	static IMTableCell* create(IMCellType celltype);
public:
	void initCell();
	void initCellWithGroup();
	void initCellWithFriend();
	void initCellWithStrange();
protected:
	void baseView();
private:
	CAImageView *m_pHead;
	CAImageView *m_pGroup;
	CALabel *m_pName;
	CALabel *m_pContent;
	IMCellType m_pcelltype;
};


#endif