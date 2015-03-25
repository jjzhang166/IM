#ifndef _CHAT_VIEW_CELL_H_
#define _CHAT_VIEW_CELL_H_

#include <iostream>
#include "CrossApp.h"
#include "CrossAppExt.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChatViewCell:public CATableViewCell
{
public:
	ChatViewCell();
	virtual ~ChatViewCell();
	static ChatViewCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);

public:
	void initWithCell();
	void setMsgTime(string& mTime);
	void showImgMsg(string& url, const char* dpos);
	void showTextMsg(string& msg, const char* dpos);	
	void requestResult(CCHttpClient* client, CCHttpResponse* response);

protected:
	virtual void normalTableViewCell();
	virtual void highlightedTableViewCell();
	virtual void selectedTableViewCell();
	virtual void disabledTableViewCell();

private:
	int fontSize;

};

#endif