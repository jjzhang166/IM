//
//  TableLanguage.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-2-15.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __TABLE_LANGUAGE_H__
#define __TABLE_LANGUAGE_H__
#include "TableBase.h"

typedef std::map<int, std::string> MAP_TableLanguage;


class TableLanguage : public TableBase
{
public:
	TableLanguage();
	virtual ~TableLanguage();
    
    static TableLanguage* getInstance();

    void destroy();
public:
	virtual void clear();
	std::string getTableItemByID(int ID);

protected:
	virtual char* getJasonFileName();
	virtual bool addRow(const CSJson::Value& Vl);

protected:
    MAP_TableLanguage m_mTableData;
};
#endif //__TABLE_LANGUAGE_H__