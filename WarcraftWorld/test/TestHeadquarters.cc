#include "test.h"


//=====================================《司令部类型》===========================================
//司令部类型
class Headquarters
{
	public:
		//构造函数，初始化司令部颜色和生命元
		Headquarters(Color color, size_t elements)
		: _color(color)
		, _elements(elements)
		, _earnElements(0)
		, _nextWarriorIndex(0)//index指针
		{
			//初始化unordered_map容器
			_warriorTypeAmounts.insert(std::make_pair(DRAGON_TYPE,0));
			_warriorTypeAmounts.insert(std::make_pair(NINJA_TYPE,0));
			_warriorTypeAmounts.insert(std::make_pair(ICEMAN_TYPE,0));
			_warriorTypeAmounts.insert(std::make_pair(LION_TYPE,0));
			_warriorTypeAmounts.insert(std::make_pair(WOLF_TYPE,0));		
		}

		//析构函数（虚函数）
		virtual 
		~Headquarters() 
		{}

		//创建武士过程
		void createWarriorProcess()
		{
			//获得接下来要创建的武士的类型
			WarriorType warriorType;
			warriorType=_warriorCreatingOrder[_nextWarriorIndex];
			//调用该类型武士的创建函数
			WarriorPtr warriorPtr;
			warriorPtr=createOneWarrior(warriorType);
			//设置武士的_cityId
			warriorPtr->setCity(_id);
			//将武士类型下标移动
			nextWarriorType();
			//将该武士加入_warriors
			_warriors.push_back(warriorPtr);
			//将_warriorTypeAmounts的同类型武士数+1
			++_warriorTypeAmounts[warriorType];
		}
		//创建一个武士
		WarriorPtr createOneWarrior(WarriorType warriorType)
		{
			//获得武士id、hp、forces
			size_t id=_warriors.size()+1;
			size_t hp=GameConfig::getInstance()->warriorInitalLife(warriorType);
			size_t forces=GameConfig::getInstance()->warriorInitalAttack(warriorType);
			
			switch (warriorType){
				case DRAGON_TYPE:
					return createDragon(id,hp,forces);
					break;
				case NINJA_TYPE:
					return createNinja(id,hp,forces);
					break;
				case ICEMAN_TYPE:
					return createIceman(id,hp,forces);
					break;
				case LION_TYPE:
					return createLion(id,hp,forces);
					break;
				case WOLF_TYPE:
					return createWolf(id,hp,forces);
			}
		}
		
		//添加胜利者将胜利者加入到胜利者优先级队列中
		void addWinner(WarriorPtr warrior)
		{
			_winners.push(warrior);
		}		
		//奖励胜利者，按照优先级队列奖励武士
		void reward()
		{
			//当奖励队列不为空，且司令部生命元>=8，执行奖励
			while((!_winners.empty())&&(_elements>=8))
			{
				_winners.top()->beRewarded();
				_winners.pop();
				_elements-=8;
			}
			//将优先级队列清空
			while(!_winners.empty())
			{
				_winners.pop();
			}
		}	

		//统计1次战斗结束后从城市获取的生命元，战斗结束后先奖励武士，
		//然后才收回武士战斗胜利获得生命元
		//
		//司令部有两个时间点获得生命元，一个在30分时，一个城市只有一个武士
		//一个在40分时，发生战斗并获得胜利，但此时先奖励武士后获得战胜的生命元
		//_earnElements表示的就是一次战斗结束后获得的生命元
		void increaseElements(size_t elements) 
		{ 
			_earnElements +=elements;
		}

		//设置所剩生命元的数量
		void setElements(size_t elements) 
		{ 
			_elements = elements; 
		}

		//设置武士生产顺序
		template <typename Iterator>
		void setWarriorCreatingOrder(Iterator beg,Iterator end)
		{ 
			for(; beg != end; ++beg) 
			{
				//底层实现vector容器
				_warriorCreatingOrder.push_back(*beg);
			}
		}

		//获得司令部id
		size_t getId() const 
		{ 
			return _id; 
		}
		//改变司令部id
		void setId(size_t id) 
		{ 
			_id = id; 
		}
		//获得司令部颜色
		Color getColor() const 
		{ 
			return _color; 
		}
		//获得当前司令部所剩生命元
		size_t getElements() const 
		{ 
			return _elements; 
		}
		//获得司令部生产的所有武士
		vector<WarriorPtr> & getWarriors() 
		{ 
			return _warriors; 
		}
	private:
		//生产各种武士函数，基类指针指向派生类对象
		WarriorPtr createIceman(size_t id, size_t hp, size_t forces)
		{
			//先将司令部生命元减少，再创建堆对象
			_elements-=hp;
			return new Iceman(_color,id,hp,forces);
		}
		WarriorPtr createLion(size_t id, size_t hp, size_t forces)
		{
			_elements-=hp;
			return new Lion(_color,id,hp,forces,_elements);
		}
		WarriorPtr createWolf(size_t id, size_t hp, size_t forces)
		{
			_elements-=hp;
			return new Wolf(_color,id,hp,forces);
		}
		WarriorPtr createNinja(size_t id, size_t hp, size_t forces)
		{
			_elements-=hp;
			return new Ninja(_color,id,hp,forces);
		}
		WarriorPtr createDragon(size_t id, size_t hp, size_t forces);
		{
			_elements-=hp;
			float morale=_elements/hp;
			return new Dragon(_color,id,hp,forces,morale);
		}

		//改变_nextWarriorIndex的值
		void nextWarriorType()
		{
			if(4==_warriorCreatingOrder){
				//已经到生产顺序的末尾，重新回到开头
				_warriorCreatingOrder=0;
			}else{
				++_warriorCreatingOrder;
			}
		}
		//获得下次待生产武士类型
		WarriorType getNextWarriorType()
		{ 
			return _warriorCreatingOrder[_nextWarriorIndex]; 
		}
	protected:
		Color _color;//红或者蓝
		size_t _id;//编号, 0代表红色司令部, N+1 代表蓝色司令部
		size_t _elements;//当前司令部所剩的生命元

		//司令部总是先奖励武士，然后再收回打了胜仗的城市的生命元
		//因司令部生命元不足而领不到奖励的武士，司令部也不会在取得战利品生命元后
		//为其补发奖励
		size_t _earnElements;//一次战斗时刻结束后，所有武士获取的生命元
		size_t _nextWarriorIndex;//下次待生产的武士下标

		//武士生产的顺序
		vector<WarriorType> _warriorCreatingOrder;

		//一次战斗时间结束后，胜利的所有武士
		//优先级队列，优先级由WarriorComparator函数决定
		priority_queue<WarriorPtr,vector<WarriorPtr>,WarriorComparator> _winners;

		//生产的所有武士
		vector<WarriorPtr> _warriors;

		//各种类型武士的数量，unordered_map底层哈希桶实现
		unordered_map<WarriorType, size_t> _warriorTypeAmounts;
		
};

//优先级队列比较函数类
struct WarriorComparator
{
	bool operator()(const WarriorPtr lhs,const WarriorPtr rhs) const
	{
		//<是大顶堆，左边<右边被从堆顶上换下来
		//比较两个武士距离己方司令部的距离
		if(RED==lhs->getColor()){//两武士是红方
			return lhs->getCityId()<rhs->getCityId;
		}else{//两武士是蓝方
			return lhs->getCityId()>rhs->getCityId;
		}
	}
};

//红司令部类型
class RedHeadquarters
: public Headquarters //以public方式继承基类Headquarters
{
	public:
		//构造函数，传入初始生命元
		RedHeadquarters(size_t elements)
		: Headquarters(RED, elements)
		{}
};

//蓝司令部类型
class BlueHeadquarters
: public Headquarters //以public方式继承基类Headquarters
{
	public:
		//构造函数，传入初始生命元
		BlueHeadquarters(size_t elements)
		: Headquarters(BLUE, elements)
		{}
};



