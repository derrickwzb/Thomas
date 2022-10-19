#include <vector>
#include "BehaviourFCT.hpp"

class LogicSystem
{
private:
	std::vector<BehaviourFCT*> m_behaviours;
	//std::vector<
	
public:
	void Init();

	void Update();

	void End();

	void AddBehaviour(BehaviourFCT* behaviour);




};