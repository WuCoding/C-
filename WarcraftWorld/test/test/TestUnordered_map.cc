#include "test.h"

class Test
{
	public:
		Test()
		{
			_amounts.insert(std::make_pair(DRAGON_TYPE,0));
			_amounts.insert(std::make_pair(NINJA_TYPE,0));
			_amounts.insert(std::make_pair(ICEMAN_TYPE,0));
			_amounts.insert(std::make_pair(LION_TYPE,0));
			_amounts.insert(std::make_pair(WOLF_TYPE,0));
		}


		void addAmounts(WarriorType warriorType)
		{
			++_amounts[warriorType];
		}

		void display() const
		{
			cout<<_amounts.find(DRAGON_TYPE)->second<<endl;
			cout<<_amounts.find(NINJA_TYPE)->second<<endl;
			cout<<_amounts.find(ICEMAN_TYPE)->second<<endl;
			cout<<_amounts.find(LION_TYPE)->second<<endl;
			cout<<_amounts.find(WOLF_TYPE)->second<<endl;
#if 0
			cout<<"dragon cnt="<<_amounts[DRAGON_TYPE]<<endl;
			cout<<"ninja cnt="<<_amounts[NINJA_TYPE]<<endl;
			cout<<"iceman cnt="<<_amounts[ICEMAN_TYPE]<<endl;
			cout<<"lion cnt="<<_amounts[LION_TYPE]<<endl;
			cout<<"wolf cnt="<<_amounts[WOLF_TYPE]<<endl;
#endif
		}
	private:
		unordered_map<WarriorType,size_t> _amounts;
};

int test0()
{
	Test test;
	test.display();
	
	test.addAmounts(DRAGON_TYPE);
	test.addAmounts(NINJA_TYPE);
	test.addAmounts(ICEMAN_TYPE);
	test.addAmounts(LION_TYPE);
	test.addAmounts(WOLF_TYPE);

	test.display();
	return 0;
}

int main(void)
{
	test0();
}
