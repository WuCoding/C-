#include "test.h"
//========================================《城市类型》=========================================
//城市类型
class City
{
	public:
		//构造函数
		City(size_t id, size_t elements = 0)
		: _flag(Color::NOTSET)    	//初始化此时的旗帜为未设置
		, _id(id)                 	//城市id
		, _elements(elements)		//存有的生命元数
		, _redWinCount(0)		//红方连赢次数
		, _blueWinCount(0)		//蓝方连赢次数
		{}

		//城市生产生命元函数
		void produceElements()
		{
			_elements+=10;
		}
		//某武士进入该城市
		void attach(WarriorPtr)
		{

		//某武士离开该城市
		void detach(WarriorPtr);
		//开始战斗
		void startBattle()
		{
			//获得红方武士指针和蓝方武士指针
			WarriorPtr redWarrior,blueWarrior;
			redWarrior=_redWarriors.back();
			blueWarrior=_blueWarriors.back();
			battle(redWarrior,blueWarrior);
			if(0==blueWarrior->getHp())
			{
				//红方胜利
				++_redWinCount;
				_blueWinCount=0;
				redWarrior->beWinner();
				takenBy(redWarrior);
			}else if(0==redWarrior->getHp()){
				//蓝方胜利
				++_blueWinCount;
				_redWinCount=0;
				blueWarrior->beWinner();
				takenBy(blueWarrior);
			}
			isChangingFlag();
		}				
		}
		//生命元被某武士取走
		void takenBy(WarriorPtr warrior)
		{
			warrior->sentElementsToHeadquarters(_elements);
			_elements=0;
		}
		
		//获得该城市id
		size_t getId() const 
		{ 
			return _id; 
		}
		//获得该城市旗帜颜色
		Color getFlag() const 
		{ 
			return _flag; 
		}
		
		//获得当前位于该城市的武士总数
		size_t getWarriorAmount() const
		{ 
			return _redWarriors.size() + _blueWarriors.size(); 
		}
		//获得该城市中红方武士
		vector<WarriorPtr> & getRedWarriors() 
		{ 
			return _redWarriors; 
		}
		//获得该城市中蓝方武士
		vector<WarriorPtr> & getBlueWarriors() 
		{ 
			return _blueWarriors;
		}
	private:
		//2名武士的具体战斗状况
		void battle(WarriorPtr redWarrior, WarriorPtr blueWarrior)
		{
			if(((NOTSET==_flag)&&(1==_id%2))||(RED==_flag))
			{
				//红方武士主动攻击
				redWarrior->attack(blueWarrior);
				if(blueWarrior->getHp()!=0)
				{
					//蓝方武士进行反击
					blueWarrior->defense(redWarrior);
				}
			}else{
				//蓝方武士主动攻击
				blueWarrior->attack(redWarrior);
				if(redWarrior->getHp()!=0)
				{
					//红方武士进行反击
					redWarrior->defense(blueWarrior);
				}
			}
		}
		//判断是否更换旗子
		void isChangingFlag()
		{
			if(2==_redWinCount){//红方连赢2次
				_flag=RED;
				_redWinCount=0;
			}else if(2==_blueWinCount){//蓝方连赢2次
				_flag=BLUE;
				_blueWinCount=0;
			}
		}
	private:
		Color _flag;			//城市旗子的颜色
		size_t _id;			//城市编号
		size_t _elements;		//城市当前存有的生命元
		size_t _redWinCount;		//红魔军连续胜利次数
		size_t _blueWinCount;		//蓝魔军连续胜利次数
		vector<WarriorPtr> _redWarriors;//存储当前该城的红方武士
		vector<WarriorPtr> _blueWarriors;//存储当前该城的蓝方武士
};



