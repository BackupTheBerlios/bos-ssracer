#ifndef CFRONTENDMESSAGE_H
#define CFRONTENDMESSAGE_H

#include "task.h"

class CFrontendMessage : public ITaskMessage {
public:
	CFrontendMessage(int key);
	~CFrontendMessage();

	int Key() {return m_iKey;}
protected:
	int m_iKey;

private:

};

#endif