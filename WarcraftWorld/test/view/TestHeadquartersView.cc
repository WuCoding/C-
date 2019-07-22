#include "test.h"
//=================================《司令部视图类》=======================================
class HeadquartersView
{
	public:
		HeadquartersView(Headquarters * headquarters)
		: _headquarters(headquarters)
		{}
		
		//司令部报告情况时
		void showLeftElements() const;
		
		//司令部被占领时
		void showBeTaken() const;
	private:
		Headquarters * _headquarters;
};
