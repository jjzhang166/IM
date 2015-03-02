//
//  TableBase.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-2-15.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//


#include "TableBase.h"

TableBase::TableBase()
{

}
TableBase::~TableBase()
{

}

bool TableBase::loadTableFromJsonFile()
{
	clear();
	return loadTableFromJsonFile(getJasonFileName());
}

void TableBase::clear()
{

}

bool TableBase::loadTableFromJsonFile(char* pFileName)
{
	CCLog("%s", pFileName);
	bool bRet = false;
	do 
	{	
		char * pBuffer = NULL;
		CC_BREAK_IF(pFileName == NULL);

		std::string tFullName("");
		tFullName = pFileName;

        std::string tFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(tFullName.c_str());

		unsigned long lFileLen = 0L;
		pBuffer = (char*)(CCFileUtils::sharedFileUtils()->getFileData(tFullPath.c_str(),"rb+" , &lFileLen));
		//pXorCoding(pBuffer, lFileLen);  // 解密过程

		CSJson::Reader reader;
		CSJson::Value jsValue;
		bool parseRet = reader.parse(pBuffer, jsValue,false);

		int nCount = jsValue.size();
        CCLog("tableItem is :%d", nCount);
		for (int i=0; i<nCount; i++)
		{
			addRow(jsValue[i]);
		}
		CC_SAFE_DELETE_ARRAY(pBuffer);

		bRet = true;
	} while (0);
	return bRet;
}

bool TableBase::addRow(const CSJson::Value& Vl)
{
	bool bRet = false;
	do 
	{	

		bRet = true;
	} while (0);

	return bRet;
}
