
#ifndef __IMChat__Controller__
#define __IMChat__Controller__

#include <iostream>
#include "CrossApp.h"
#include "CrossAppExt.h"
#include "HXSDKController.h"
USING_NS_CC;
USING_NS_CC_EXT;


class IMChatController : public CAViewController, public CATableViewDelegate, public CATableViewDataSource
{

public:

	IMChatController(std::string ID);

	virtual ~IMChatController();

	static IMChatController* create(std::string _id);

protected:

	void viewDidLoad();

	void viewDidUnload();

public:
	virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);

	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
	// 	virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
	// 	virtual CAView* tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
	virtual unsigned int numberOfSections(CATableView *table);
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
	virtual unsigned int tableViewHeightForFooterInSection(CATableView* table, unsigned int section);


private:
	CADipSize size;
	CATableView* p_TableView;
	const char* id;
	char* time;
	string timeLast;
	std::vector<HXSDKMessage*> message;
};


#endif /* defined(__HelloCpp__ViewController__) */
