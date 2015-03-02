//
//  TableBase.h
//  IM
//
//  Created by qiaoxin265@126.com on 15-2-15.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __TABLE_BASE_H__
#define __TABLE_BASE_H__
#include <string>
#include <CrossAppExt.h>

class TableBase 
{
public:
	TableBase();
	virtual ~TableBase();

public:
	bool loadTableFromJsonFile();
	virtual void clear();

protected:
	bool loadTableFromJsonFile(char* pFileName);

	virtual char* getJasonFileName() = 0;
	virtual bool addRow(const CSJson::Value& Vl);
};

#endif // __TABLE_BASE_H__
