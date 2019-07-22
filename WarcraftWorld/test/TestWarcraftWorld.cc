#include "test.h"

//==========================================《控制类型》=============================================
class WarcraftWorld 
{ 
	public: 
		//构造函数
		explicit 
		WarcraftWorld() 
		: _redHeadquarters(nullptr) 
		, _blueHeadquarters(nullptr) 
		{ 
			//初始化游戏函数
			init(); 
		} 

		void start();//游戏开始 
		{ 
			while(1) 
			{
				//第0分，双方司令部生产兵
				createWarrior(); 
				//第10分，双方兵往前移动，同时判断是否游戏结束
				if(gameOverAfterWarriorMarch()) 
				{ 
					break; 
				} 
				//第20分，城市生产10个生命元
				cityProduceElements();
			        //第30分，城市只有1个武士，则该武士从城市中取走生命元	
				takeCityElements(); 
				//第40分，有2个武士的城市进行战斗
				battle(); 
				//第50分，司令部汇报当前生命元数量
				headquartersReportElements(); 
			} 
		}

		//设置红方司令部产兵顺序
		template <typename Iterator> 
		void setRedWarriorCreatingOrder(Iterator beg, Iterator end);
		//设置蓝方司令部产兵顺序
		template <typename Iterator> 
		void setBlueWarriorCreatingOrder(Iterator beg, Iterator end);
		//析构函数
		~WarcraftWorld() 
		{ 
			//将红方Headquarters类型的堆对象释放
			if(_redHeadquarters) delete _redHeadquarters; 
			//将蓝方Headquarters类型的堆对象释放
			if(_blueHeadquarters) delete _blueHeadquarters; 
		} 
	private:
	        //初始化函数，创建两个司令部对象（堆对象），创建城市容器	
		void init()
		{
			//为红蓝司令部开辟空间
			_redHeadquarters=new RedHeadquarters(
					GameConfig::getInstance()->
					headquartersInitialElements()
					);
			_blueHeadquarters=new BlueHeadquarters(
					GameConfig::getInstance()->
					headquartersInitialElements()
					);
			//设置红蓝司令部产兵顺序
			setRedWarriorCreatingOrder(
			GameConfig::getInstance()->getRedWarriorCreatingOrder().begin(),
			GameConfig::getInstance()->getRedWarriorCreatingOrder().end());
			setBlueWarriorCreatingOrder(
			GameConfig::getInstance()->getBlueWarriorCreatingOrder().begin(),
			GameConfig::getInstance()->getBlueWarriorCreatingOrder().end());
			//设置红蓝司令部编号
			size_t cityCount=GameConfig::getInstance()->cityCount();
			_redHeadquarters->setId(0);
			_blueHeadquarters->setId(cityCount+1);
			//创建城市对象，0为红司令部，size-1为蓝司令部
			for(int i=0;i<cityCount+2;++i)
			{
				_cities.push_back(City(i));
			}
		}
		//-------------------------事件------------------------------ 
		//第0分：创建武士
		void createWarrior()
		{
			//判断两司令部能否生产武士
			if(canCreateWarrior(_redHeadquarters)){//红司令部能产生武士
				//调用红司令部创建武士的成员函数
				_redHeadquarters->createWarriorProcess();
			}
			if(canCreateWarrior(_blueHeadquarters)){//蓝司令部能产生武士
				//调用蓝司令部创建武士的成员函数
				_blueHeadquarters->createWarriorProcess();
			}
		}								
		//第10分：武士行军，游戏结束返回true，游戏未结束返回false
		bool gameOverAfterWarriorMarch()
		{
			//红方武士行军
			warriorMarch(_redHeadquarters);
			//蓝方武士行军
			warriorMarch(_blueHeadquarters);
			if(checkRedHeadquartersBeTaken()){
				//红方失败，游戏结束
				return true;
			}
			if(checkBlueHeadquartersBeTaken()){
				//蓝方失败，游戏结束
				return true;
			}
			return false;
		}
		//第20分：城市生产生命元
		void cityProduceElements()
		{
			for(int i=1;i<_cities.size()-1;++i){
				//遍历每个城市进行生命元生产
				_cities[i].createElemtent();
			}
		}

		//第30分：武士取走城市中的生命元
		void takeCityElements()
		{
			WarriorPtr warriorPtr;
			//判断城市中总的武士数
			for(int i=1;i<_cities.size()-1;++i)
			{
				if(1==_cities[i].getWarriorAmount()){
					//城市中只有一个武士，调用给出生命元函数
					if(1==_cities[i].getRedWarriors().size())
					{
						//只有一个红方武士
						warriorPtr=_cities[i].getRedWarriors().back();
					}else{
						//只有一个蓝方武士
						warriorPtr=_cities[i].getBlueWarriors().back();
					}
					//城市中的生命元被该武士取走
					_cities[i].takenBy(warriorPtr);
				}
			}
		}
		//第40分：战斗
		void battle()
		{
			for(int i=1;i<_cities.size()-1;++i)
			{
				if(2==_cities[i].getWarriorAmount()){
					//城市有两个武士，调用干架函数
					_cities[i].battle();
				}
			}
		}
		//第50分：司令部报告情况
		void headquartersReportElements()
		{
			//红方司令部报告剩余生命元数
			size_t redElements=_redHeadquarters->getElements();
			//蓝方司令部报告剩余生命元数
			size_t blueElements=_blueHeadquarters->getElements();
		}
		
		//某个司令部能否开始创建武士
		bool canCreateWarrior(Headquarters *headquarters)
		{
			//判断司令部的生命元是否够生产下一个武士
			//headquarters->getElements(); 司令部现有的生命元
			//GameConfig::getInstance()->warriorInitalLife(WarriorType)
			//生产某类武士需要的生命元
			//司令部下一个生产的武士类型
			//headquarters->getNextWarriorType();
			size_t headElement=headquarters->getElements();
			size_t warriorElement=GameConfig::getInstance()->warriorInitalLife
				(headquarters->getNextWarriorType());
			return headElement > warriorElement;
		}
		//某个司令部的武士行军
		void warriorMarch(Headquarters * headquarters)
		{
			if(RED==headquarters->getColor){
				//--------------红方司令部---------------

				//将每个活着的，没到对面司令部的武士向前移动一步
				//headquarters->getWarriors()  获得该司令部的所有武士指针
				//WarriorPtr->getHp()  获得该武士的血量
				//WarriorPtr->getCityId()  获得该武士的当前的城市id
				for(auto &warriorPtr:headquarters->getWarriors())
				{
					//如果该武士活着且没到达对方司令部
					if((warriorPtr->getHp()!=0)&&
					(warriorPtr->getCityId()!=_cities.size()-1))
					{
						//获得武士当前所在的城市id
						size_t cityId=warriorPtr->getCityId();
						//改变武士的数据
						warriorPtr->march();
						//改变城市的数据，是不是把
						if(cityId!=0)//不在本方司令部
						{
							_cities[cityId].detach(warriorPtr);
						}
						_cities[cityId+1].attach(warriorPtr);
					}
				}
			}else{
				//---------------蓝方司令部---------------------

				for(auto &warriorPtr:headquarters->getWarriors())
				{
					if((warriorPtr->getHp()!=0)&&
					(warriorPtr->getCityId()!=0))
					{
						size_t cityId=warriorPtr->getCityId();
						warriorPtr->march();
						if(cityId!=_cities.size()-1)//不在本方司令部
						{
							_cities[cityId].detach(warriorPtr);
						}
						_cities[cityId-1].attach(warriorPtr);
					}
				}
			}

						
		}
		//判断红司令部是否被占领
		bool checkRedHeadquartersBeTaken()
		{
			//判断红方司令部中的蓝方武士数量
			if(_cities.front().getBlueWarriorCount()>1){
				//游戏结束，红方失败
				return true;
			}
			return false;
		}
		//判断蓝司令部是否被占领
		bool checkBlueHeadquartersBeTaken()
		{
			//判断蓝方司令部中的红方武士数量
			if(_cities.back().getRedWarriorCount()>1){
				//游戏结束，蓝方失败
				return true;
			}
			return false;
		}
	private: 
		//数据成员
		Headquarters * _redHeadquarters;//红色司令部 
		Headquarters * _blueHeadquarters;//蓝色司令部 
		//所有的城市,其中0号代表红色司令部，size-1代表蓝色司令部 
		vector<City> _cities;
};

//设置红方司令部产兵顺序
template <typename Iterator> 
void WarcraftWorld::setRedWarriorCreatingOrder(Iterator beg,Iterator end) 
{ 
	//调用司令部类的成员函数setWarriorCreatingOrder()
	//设置vector容器类型数据成员_warriorCreatingOrder()
	_redHeadquarters->setWarriorCreatingOrder(beg, end); 
} 
//设置蓝方司令部产兵顺序
template <typename Iterator> 
void WarcraftWorld::setBlueWarriorCreatingOrder(Iterator beg,Iterator end) 
{ 	
	//调用司令部类的成员函数setWarriorCreatingOrder()
	//设置vector容器类型数据成员_warriorCreatingOrder()
	_blueHeadquarters->setWarriorCreatingOrder(beg, end); 
} 



