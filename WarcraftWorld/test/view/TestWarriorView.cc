#include "test.h"

//================================《武士视图类》==========================
//武士视图类
class WarriorView
{
	public:
		WarriorView(WarriorPtr warrior)
		: _warrior(warrior)
		{}
		
		void showBorn() const;//武士出生时

		void showMarch() const;//武士行军时

		void showEarnElements() const;//武士取走城市生命元时

		void showReachDestination() const;//武士到达敌方司令部时

	protected:

		void showName() const;

		void showToCity() const;

		void showInCity() const;

		void showDeath() const;

		void showElementsAndForces() const;

	protected:

		WarriorPtr _warrior;
};
//dragon欢呼视图类
class DragonView
: public WarriorView
{
	public:
		DragonView(WarriorPtr warrior)
		: WarriorView(warrior)
		{}
		
		//dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，就会欢呼。
		void showYell() const;
};
