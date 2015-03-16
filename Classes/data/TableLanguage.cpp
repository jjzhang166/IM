//
//  TableLanguage.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-2-15.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "TableLanguage.h"

static TableLanguage* m_pTableLanguage = NULL;

TableLanguage::TableLanguage()
{

}

TableLanguage::~TableLanguage()
{
    clear();
    CC_SAFE_DELETE(m_pTableLanguage);
}

TableLanguage* TableLanguage::getInstance()
{
    if(!m_pTableLanguage)
    {
        m_pTableLanguage = new TableLanguage();
    }
    return m_pTableLanguage;
}

void TableLanguage::destroy()
{
    if(m_pTableLanguage)
    {
        delete m_pTableLanguage;
        m_pTableLanguage = NULL;
    }
}

void TableLanguage::clear()
{
	m_mTableData.clear();
}

std::string TableLanguage::getTableItemByID(int ID)
{
    MAP_TableLanguage::iterator itrItem = m_mTableData.find(ID);
    if(itrItem != m_mTableData.end())
    {
        return itrItem->second;
    }
    return "";
}

char* TableLanguage::getJasonFileName()
{
	return "IMJson/LanguagesFontNew_CN.json";
}

bool TableLanguage::addRow( const CSJson::Value& Vl )
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!TableBase::addRow(Vl));
        int id = Vl["ID"].asInt();
        std::string str = Vl["Value"].asString();
        //CCLog("id is:%d, language is:%s", id, str.c_str());
        m_mTableData.insert(MAP_TableLanguage::value_type(id, str));
        bRet = true;
	}while(0);

	return bRet;
}
