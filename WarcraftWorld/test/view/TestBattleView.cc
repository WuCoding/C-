#include "test.h"
//===========================================《战斗视图类》======================================
class BattleView
{
	public:
		BattleView(WarriorPtr warrior1, WarriorPtr warrior2)
		: _warrior1(warrior1)
		, _warrior2(warrior2)
		{}
		
		//武士主动攻击时
		void showBattle() const;
		//武士反击时
		void showDefense() const;
	
	private:
		WarriorPtr _warrior1;
		WarriorPtr _warrior2;
};
