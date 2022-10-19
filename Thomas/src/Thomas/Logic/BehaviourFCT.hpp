#include "../Scene/Entity.h"

typedef void(*InitBehaviour)(unsigned int*);
typedef void(*UpdateBehaviour)(unsigned int*);
typedef void(*EndBehaviour)(unsigned int*);

class BehaviourFCT
{
private:

	InitBehaviour m_InitBehaviour;
	UpdateBehaviour m_UpdateBehaviour;
	EndBehaviour m_EndBehaviour;

public:
	BehaviourFCT(const InitBehaviour& Init, const UpdateBehaviour & Update, const EndBehaviour & End);
	//m_InitBehaviour(Init);

};