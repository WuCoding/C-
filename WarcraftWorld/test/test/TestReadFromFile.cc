#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#include <string>
#include <map>
using std::cout;
using std::endl;
using std::cin;
using std::copy;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::list;
using std::queue;
using std::map;
using std::istream_iterator;
using std::ostream_iterator;
enum Color{
	RED,
	BLUE,
	NOTSET
};
enum WarriorType{
	DRAGON_TYPE,
	NINJA_TYPE,
	ICEMAN_TYPE,
	LION_TYPE,
	WOLF_TYPE
};
//通过某种颜色，得到字符串
inline string toString(Color color)
{
	return (color==RED)?string("red"):string("blue");
}
//通过武士类型，得到字符串
inline string toString(WarriorType type)
{
	switch(type) {
		case DRAGON_TYPE:
			return "dragon";
		case NINJA_TYPE:
			return "ninja";
		case ICEMAN_TYPE:
			return "iceman";
		case LION_TYPE:
			return "lion";
		case WOLF_TYPE:
			return "wolf";
		default:
			return string();
	}
}

//通过字符串，得到武士类型
inline WarriorType toWarriorType(const string &str)
{
	if("dragon"==str)
		return DRAGON_TYPE;
	if("ninja"==str)
		return NINJA_TYPE;
	if("iceman"==str)
		return ICEMAN_TYPE;
	if("lion"==str)
		return LION_TYPE;
	if("wolf"==str)
		return WOLF_TYPE;	
}


struct InitData
{
	size_t _initElements;           //初始生命元
	size_t _cityCount;              //城市数量
	size_t _minutes;                //游戏进行时间
	//武士的初始生命值
	map<WarriorType, size_t> _initLifes;
	//武士的初始攻击力
	map<WarriorType, size_t> _initAttacks;
};

vector<InitData> _groups;
vector<WarriorType> _initWarriorOrder;
template<class T>
void readFromStream(T &is)
{
	string warrior;
	for(int i=0;i<5;++i)
	{
		is>>warrior;
		_initWarriorOrder.push_back(toWarriorType(warrior));
	}
	
	cout<<"_initWarriorOrder中的元素"<<endl;
	for(int i=0;i<5;++i)
	{
		cout<<toString(_initWarriorOrder[i])<<" ";
	}
	cout<<endl;


	istream_iterator<int> isi(is);
	vector<int> originalData;
	copy(isi,istream_iterator<int>(),std::back_inserter(originalData));

	cout<<"originalData中的元素"<<endl;
	for(int i=0;i<originalData.size();++i)
	{
		cout<<originalData[i]<<" ";
	}
	cout<<endl;
	//创建InitData并压入栈
	for(int i=0;i<originalData[0];++i)
	{
		InitData it;
		int j=i*13+1;
		//初始化生命元
		it._initElements=originalData[j++];
		//初始化城市数量
		it._cityCount=originalData[j++];
		//初始化游戏时间
		it._minutes=originalData[j++];
		//初始化武士的初始生命值
		it._initLifes[_initWarriorOrder[0]]=originalData[j++];
		it._initLifes[_initWarriorOrder[1]]=originalData[j++];
		it._initLifes[_initWarriorOrder[2]]=originalData[j++];
		it._initLifes[_initWarriorOrder[3]]=originalData[j++];
		it._initLifes[_initWarriorOrder[4]]=originalData[j++];
		//初始化武士的攻击力
		it._initAttacks[_initWarriorOrder[0]]=originalData[j++];
		it._initAttacks[_initWarriorOrder[1]]=originalData[j++];
		it._initAttacks[_initWarriorOrder[2]]=originalData[j++];
		it._initAttacks[_initWarriorOrder[3]]=originalData[j++];
		it._initAttacks[_initWarriorOrder[4]]=originalData[j++];
		_groups.push_back(it);
	}
}




int test4()
{
	//ifstream ifs("config.txt");
	//readFromStream(ifs);
	
	readFromStream(cin);






#if 0
	vector<InitData> _groups;

	vector<WarriorType> _initWarriorOrder;
	string warrior;
	for(int i=0;i<5;++i)
	{
		ifs>>warrior;
		_initWarriorOrder.push_back(toWarriorType(warrior));
	}

	cout<<"_initWarriorOrder中的元素"<<endl;
	for(int i=0;i<5;++i)
	{
		cout<<toString(_initWarriorOrder[i])<<" ";
	}
	cout<<endl;


	istream_iterator<int> isi(ifs);
	vector<int> originalData;
	copy(isi,istream_iterator<int>(),std::back_inserter(originalData));

	cout<<"originalData中的元素"<<endl;
	for(int i=0;i<originalData.size();++i)
	{
		cout<<originalData[i]<<" ";
	}
	cout<<endl;
	//创建InitData并压入栈
	for(int i=0;i<originalData[0];++i)
	{
		InitData it;
		int j=i*13+1;
		//初始化生命元
		it._initElements=originalData[j++];
		//初始化城市数量
		it._cityCount=originalData[j++];
		//初始化游戏时间
		it._minutes=originalData[j++];
		//初始化武士的初始生命值
		it._initLifes[_initWarriorOrder[0]]=originalData[j++];
		it._initLifes[_initWarriorOrder[1]]=originalData[j++];
		it._initLifes[_initWarriorOrder[2]]=originalData[j++];
		it._initLifes[_initWarriorOrder[3]]=originalData[j++];
		it._initLifes[_initWarriorOrder[4]]=originalData[j++];
		//初始化武士的攻击力
		it._initAttacks[_initWarriorOrder[0]]=originalData[j++];
		it._initAttacks[_initWarriorOrder[1]]=originalData[j++];
		it._initAttacks[_initWarriorOrder[2]]=originalData[j++];
		it._initAttacks[_initWarriorOrder[3]]=originalData[j++];
		it._initAttacks[_initWarriorOrder[4]]=originalData[j++];
		_groups.push_back(it);
	}
#endif

	//创建InitData成功
	cout<<"创建InitData完毕"<<endl;
	
	cout<<"_initWarriorOrder中的元素"<<endl;
	for(int i=0;i<5;++i)
	{
		cout<<toString(_initWarriorOrder[i])<<" ";
	}
	cout<<endl;

	cout<<">>>_groups[0]数据为:"<<endl;


	cout<<"initElements="<<_groups[0]._initElements<<endl;
	cout<<"cityCount="<<_groups[0]._cityCount<<endl;
	cout<<"minutes="<<_groups[0]._minutes<<endl;

		//初始化武士的初始生命值
	 cout<<_groups[0]._initLifes[DRAGON_TYPE]<<" "
		<<_groups[0]._initLifes[NINJA_TYPE]<<" "
		<<_groups[0]._initLifes[ICEMAN_TYPE]<<" "
		<<_groups[0]._initLifes[LION_TYPE]<<" "
		<<_groups[0]._initLifes[WOLF_TYPE]<<" "
		<<endl;
	
	cout<<">>>_groups[1]数据为:"<<endl;


	cout<<"initElements="<<_groups[1]._initElements<<endl;
	cout<<"cityCount="<<_groups[1]._cityCount<<endl;
	cout<<"minutes="<<_groups[1]._minutes<<endl;

		//初始化武士的初始生命值
	 cout<<_groups[1]._initLifes[DRAGON_TYPE]<<" "
		<<_groups[1]._initLifes[NINJA_TYPE]<<" "
		<<_groups[1]._initLifes[ICEMAN_TYPE]<<" "
		<<_groups[1]._initLifes[LION_TYPE]<<" "
		<<_groups[1]._initLifes[WOLF_TYPE]<<" "
		<<endl;
	cout<<_groups.size()<<endl;	

}

int main(void)
{
	//test0();
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}













