#include "test.h"

//====================================《城市视图类》======================================
class CityView
{
	public:
		CityView(City * city) 
		: _city(city) 
		{}
		
		//城市更换旗子时
		void showFlag() const;
	private:
		City * _city;
};
