#ifndef CCOLLISIONMESSAGE_H
#define CCOLLISIONMESSAGE_H

#include "task.h"

class CCollisionMessage : public ITaskMessage {
public:
	CCollisionMessage();
	~CCollisionMessage();

	int x;
	// Get/Set functions for the structures below:

protected:
	// Will put info on collision here:
	// *Entity collided with
	// *net resultant velocity
	// *net resultant angular velocity
private:

};

#endif

