#include "test.h"

//=======================================《武士类型》===============================================

// std::enable_shared_from_this能让一个对象
// （假设其名为t，且已被一个std::shared_ptr对象pt管理）
// 安全地生成其他额外的std::shared_ptr实例（假设名为pt1,pt2, ...） 
// ，它们与pt共享对象t的所有权。
// 若一个类T继承std::enable_shared_from_this<T>，
// 则会为该类T提供成员函数：shared_from_this。
// 当T类型对象t被一个为名为pt的std::shared_ptr<T>类对象管理时，
// 调用T::shared_from_this成员函数，将会返回一个新的std::shared_ptr<T>对象，
// 它与pt共享t的所有权。

//武士类型
class Warrior
: public std::enable_shared_from_this<Warrior>
{
	public:
		//构造函数
		Warrior(
		Color color,        	//颜色
		const string & name,	//名字
		size_t id,          	//id
		size_t hp,	        //血量
		size_t forces,		//攻击力
		WarriorType type)	//武士类型
		: _color(color)
		, _name(name)
		, _id(id)
		, _hp(hp)
		, _forces(forces)
		, _type(type)
		{}

		//析构函数（设为虚函数）
		virtual ~Warrior()
		{ }
		//行军函数，不需要判断是否死亡或到达对方司令部
		virtual void march()
		{
			if(RED==_color){//该武士为红方武士
				++_cityId;
			}else{//该武士为蓝方武士
				--_cityId;				
			}
		}

		//主动攻击函数，参数为被攻击武士
		virtual void attack(WarriorPtr warrior)
		{
			size_t hpBegin=warrior->getHp();
			size_t hp=warrior->getHp()-_forces;
			if(hp<0)
			{
				hp=0;
				if(LION_TYPE==warrior->getType())
				{
					//将lion武士的初始生命值转移
					_hp+=hpBegin;
				}
			}
			warrior->setHp(hp);
		}
		//反击函数，参数为被攻击武士
		virtual void defense(WarriorPtr warrior)
		{
			size_t hpBegin=warrior->getHp();
			size_t hp=warrior->getHp()-_forces/2;
			if(hp<0)
			{
				hp=0;
				if(LION_TYPE==warrior->getType())
				{
					//将lion武士的初始生命值转移
					_hp+=hpBegin;
				}
			}
			warrior->setHp(hp);
		}
		//成为胜利者
		void beWinner()
		{
			_headquarters->addWinner(this);
		}
		//被奖励，生命值+8
		void beRewarded()
		{
			_hp+=8;
		}
		//为司令部获取生命元
		void sentElementsToHeadquarters(size_t elements)
		{
			_headquarters->increaseElements(elements);
		}
		//改变武士单位的血量
		void setHp(size_t hp) 
		{ 
			_hp = hp; 
		}
		//改变当前所在城市id
		void setCity(size_t id) 
		{ 
			_cityId = id;
	       	}
		//改变所处的阵营
		void setHeadquarters(Headquarters * headquarters)
		{ 
			_headquarters = headquarters;
	       	}
		//获得武士的颜色
		Color getColor() const 
		{ 
			return _color;
	       	}
		//获得武士的姓名
		string getName() 
		{ 
			return _name; 
		}
		//获得武士id
		size_t getId() const 
		{ 
			return _id;
	       	}
		//获得武士的血量
		size_t getHp() const 
		{ 
			return _hp; 
		}
		//获得武士当前所处城市id
		size_t getCityId() const 
		{ 
			return _cityId; 
		}
		//？？？？？？？？？
		//size_t getElements() const 
		//{ 
		//	return _hp; 
		//}

		//获得从某个城市获取的的生命元
		size_t getEarnElements() const 
		{ 
			return _earnElements; 
		}
		//获得武士的攻击力
		size_t getForces() const 
		{ 
			return _forces; 
		}
		//获得武士的类型
		WarriorType getType() const 
		{ 
			return _type; 
		}
	protected:
		Color _color;			//颜色
		string _name;			//姓名 例：dragon、ninja
		size_t _id;			//编号
		size_t _hp;			//生命值
		size_t _forces;			//攻击力
		size_t _cityId;			//位于某个城市
		size_t _earnElements;		//从某个城市中获取的生命元
		WarriorType _type;		//武士类型 例：DRAGON_TYPE、NINJA_TYPE
		Headquarters * _headquarters;	//所处的司令部
};

//Dragon武士类型
class Dragon
: public Warrior  //以public方式继承基类Warrior
{
	public:
		//构造函数，士气=降生后司令部剩余生命元/dragon生命元
		Dragon(Color color,size_t id,size_t hp,size_t forces,float morale)
		: Warrior(color,"dragon",id,hp,forces,DRAGON_TYPE)  //初始化基类部分
		, _morale(morale)					//初始化士气
		{}
		
		//获得Dragon武士士气值
		virtual
		float getMorale() const 
		{ 
			return _morale; 
		}
	private:
		//数据成员
		float _morale;//士气值
};

//Ninja武士类型
class Ninja
: public Warrior  //以public方式继承基类Warrior
{
	public:
		//构造函数
		Ninja(Color color,size_t id,size_t hp,size_t forces)
		: Warrior(color,"ninja", id, hp, forces, NINJA_TYPE)
		{}
		//ninja 挨打了也从不反击敌人，需覆盖
		virtual 
		void defense(WarriorPtr warrior) override
		{}
};

//Iceman武士类型
class Iceman
: public Warrior
{
	public:
		//构造函数
		Iceman(Color color,size_t id,size_t hp,size_t forces)
		: Warrior(color,"iceman",id,hp,forces,ICEMAN_TYPE)
		, _steps(0)  //前进的步数初始化为0
		{}
		
		//iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。但是
		//若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。
		//需覆盖
		virtual void march() override
		{
			++_steps;
			//城市id改变
			if(RED==_color){
				//该武士为红方武士
				++_cityId;
			}else{
				//该武士为蓝方武士
				--_cityId;
			}
			if(0==_step%2){
				//已经走了偶数步
				if(_hp<=9){
					_hp=1;
					_forces+=20;
				}else{
					_hp-=9;
					_forces+=20;
				}
			}
		}
	private:
		//数据成员
		size_t _steps;//前进的步数
};
		
//Lion武士类型
class Lion
: public Warrior
{
	public:
		//构造函数
		Lion(Color color,size_t id,size_t hp,size_t forces,size_t loyalty)
		: Warrior(color, "lion", id, hp, forces, LION_TYPE)
		, _loyalty(loyalty)      //初始化忠诚度
		{}

		//获得Lion武士的忠诚度
		virtual
		size_t getLoyalty() const override 
		{ 
			return _loyalty; 
		}
	private:
		//数据成员
		size_t _loyalty; //忠诚度
};


class Wolf
: public Warrior
{
	public:
		Wolf(Color color, size_t id, size_t hp, size_t forces)
		: Warrior(color, "wolf", id, hp, forces, WOLF_TYPE)
		, _killTimes(0)      //初始化主动攻击杀死敌人次数
		{}
		
		//在一个wolf 通过主动攻击杀死敌人的次数达到偶数的时刻（次数从1开始算），在战斗完
		//成后，该wolf生命值和攻击力都增加1倍。如果其杀死的敌人是lion,则攻击力和生命
		//值先加倍，然后才吸取lion的生命值。获取总部的生命元奖励，发生在加倍之后。只有在
		//主动攻击杀死敌人时才能有加倍的事情，反击杀死敌人则不不会发生加倍。
		
		//需覆盖，传递的参数为被攻击的武士
		virtual 
		void attack(WarriorPtr warrior) override
		{
			size_t hpBegin=warrior->getHp();
			size_t hp=warrior->getHp()-_forces;
			if(hp<0)
			{
				++_killTimes;
				hp=0;
				if(0==_killTimes%2){//主动击杀次数到达偶数次
					_hp=_hp*2;
					_forces=_forces*2;
				}
				if(LION_TYPE==warrior->getType())
			}
			warrior->setHp(hp);
		}
	private:
		//数据成员
		int _killTimes;//击杀次数
};


