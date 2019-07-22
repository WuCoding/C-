
#include "test.h"
//============================《传入数据类型》================================
//数据类型（单例类型）
class GameConfig
{
	public:
		//创建单例对象
		static GameConfig * getInstance()
		{
			if(nullptr==_pInstance){//单例对象未创建
				_pInstance=new GameConfig();
			}
			return _pInstance;
		}

		//销毁单例对象
		static void destroy()
		{
			if(_pInstance!=nullptr){//单例对象存在
				delete _pInstance;
				_pInstance=nullptr;
			}
		}
		//从控制台终端获取测试数据
		void readFromConsole()
		{
			readFromStream(cin);
		}
		//从配置文件中获取测试数据
		void readFromFile(const string & filename)
		{
			ifstream ifs(filename);
			readFromStream(ifs);
		}
		//测试下一组数据
		void nextGroupId() 
		{ 
			++_currentGroupId; 
		}
		//获得测试数据组数
		size_t groups() const
	       	{ 
			return _groups.size(); 
		}
		//获得当前组数
		size_t currentGroupId() const 
		{ 
			return _currentGroupId;
	       	}

		//获得当前测试组的初始化城市个数
		size_t cityCount() const
		{
			return _groups[_currentGroupId]._cityCount;
		}
		//获得当前组初始化司令部初始生命元
		size_t headquartersInitialElements() const
		{
			return _groups[_currentGroupId]._initElements;
		}
		//获得当前组某类武士的初始化生命值
		size_t warriorInitalLife(WarriorType key) const 
		{
			auto map=_groups[_currentGroupId]._initLifes;
			auto it=map.find(key);
			if(it!=map.end()){
				return it->second;
			}else{
				return 0;
			}
			//return _groups[_currentGroupId]._initLifes[key];
		}
		//获得当前组某类武士的初始化攻击力
		size_t warriorInitalAttack(WarriorType key) const
		{
			auto map = _groups[_currentGroupId]._initAttacks;
			auto it = map.find(key);
			if(it != map.end()) {
				return it->second;
			} else{
				return 0;
			}
			//return _groups[_currentGroupId]._initAttacks[key];
		}
		//返回红方产兵顺序
		vector<WarriorType> & getRedWarriorCreatingOrder()
		{
			return _redWarriorCreatingOrder;
		}
		//返回蓝方产兵顺序
		vector<WarriorType> & getBlueWarriorCreatingOrder()
		{
			return _blueWarriorCreatingOrder;
		}
	private:
		//私有化构造函数
		GameConfig() 
		: _currentGroupId(0)
		{
		       	cout << "GameConfig()" <<endl; 
		}
		//私有化析构函数
		~GameConfig()
		{ 
			cout << "~GameConfig()" << endl; 
		}
		//从输入流中读取数据
		template<class T>
		void readFromStream(T &is)
		{
			//初始化生命值和攻击力初始顺序
			string warrior;
			for(int i=0;i<5;++i)
			{
				is>>warrior;
				_initWarriorOrder.push_back(toWarriorType(warrior));
			}
			//初始化红方产兵顺序
			for(int i=0;i<5;++i)
			{
				is>>warrior;
				_redWarriorCreatingOrder.push_back(toWarriorType(warrior));
			}
			//初始化蓝方产兵顺序
			for(int i=0;i<5;++i)
			{
				is>>warrior;
				_blueWarriorCreatingOrder.push_back(toWarriorType(warrior));
			}




			//初始化数字
			//测试数据组数
			//初始生命元  城市数   游戏进行时长
			//生命值
			//攻击力
			istream_iterator<int> isi(is);
			vector<int> originalData;
			copy(isi,istream_iterator<int>(),std::back_inserter(originalData));
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
				//将元素压栈
				_groups.push_back(it);
			}
				
				
		}
		//一组测试数据的结构
		struct InitData
		{
			size_t _initElements; 		//初始生命元
			size_t _cityCount;    		//城市数量
			size_t _minutes;		//游戏进行时间
			//武士的初始生命值
			map<WarriorType, size_t> _initLifes;
			//武士的初始攻击力
			map<WarriorType, size_t> _initAttacks;
		};
	private:
		//指向堆空间的单例对象的地址
		static GameConfig * _pInstance;
		//N组数据，每组初始化数据为一个InitData类的对象
		vector<InitData> _groups;
		//当前正在测试的一组数据组数
		size_t _currentGroupId;
		//输入时武士的生命值和攻击力顺序
		vector<WarriorType> _initWarriorOrder;
		//红方生产士兵顺序
		vector<WarriorType> _redWarriorCreatingOrder;
		//蓝方生产士兵顺序
		vector<WarriorType> _blueWarriorCreatingOrder;

};
//静态成员类外初始化
GameConfig * GameConfig::_pInstance=nullptr;

int main(void)
{
	GameConfig* GC=GameConfig::getInstance();
	//GC->readFromFile("config.txt");
	GC->readFromConsole();
	cout<<"产兵顺序"<<endl;
	for(auto & element: GC->getRedWarriorCreatingOrder())
	{
		cout<<toString(element)<<" ";
	}
	cout<<endl;
	for(auto & element:GC->getBlueWarriorCreatingOrder())
	{
		cout<<toString(element)<<" ";
	}
	cout<<endl;




	cout<<"测试组数："<<endl;
	cout<<">>>"<<GC->groups()<<endl;

	cout<<"当前组号："<<endl;
	cout<<">>>"<<GC->currentGroupId()<<endl;
	cout<<"当前初始化城市数："<<endl;
	cout<<">>>"<<GC->cityCount()<<endl;
	cout<<"当前初始化司令部生命元数："<<endl;
	cout<<">>>"<<GC->headquartersInitialElements()<<endl;
	cout<<"当前dragon的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(DRAGON_TYPE)<<endl;
	cout<<"当前ninja的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(NINJA_TYPE)<<endl;
	cout<<"当前iceman的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(ICEMAN_TYPE)<<endl;
	cout<<"当前lion的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(LION_TYPE)<<endl;
	cout<<"当前wolf的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(WOLF_TYPE)<<endl;

	//转到测试下一组
	GC->nextGroupId();

	cout<<"当前组号："<<endl;
	cout<<">>>"<<GC->currentGroupId()<<endl;
	cout<<"当前初始化城市数："<<endl;
	cout<<">>>"<<GC->cityCount()<<endl;
	cout<<"当前初始化司令部生命元数："<<endl;
	cout<<">>>"<<GC->headquartersInitialElements()<<endl;
	cout<<"当前dragon的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(DRAGON_TYPE)<<endl;
	cout<<"当前ninja的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(NINJA_TYPE)<<endl;
	cout<<"当前iceman的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(ICEMAN_TYPE)<<endl;
	cout<<"当前lion的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(LION_TYPE)<<endl;
	cout<<"当前wolf的生命值："<<endl;
	cout<<">>>"<<GC->warriorInitalLife(WOLF_TYPE)<<endl;

}

