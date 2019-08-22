#include <iostream>
#include <map>
#include <string>
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;

//打印容器中元素的函数模板
template <class Container>
void display(const Container &c)
{
	for(auto &elem:c) //elem是pair类型
	{
		cout<<elem.first<<"--->"<<elem.second<<endl;
	}
}

void test0()
{
	//map默认情况下按关键字升序方式进行排列
	//不能放关键字相同的元素
	
	//创建一个map容器
	map<string,string> cities{
		//第一种初始化元素方法
		pair<string,string>("010","北京"),
		pair<string,string>("021","上海"),
		//第二种初始化元素方法
		std::make_pair("0755","深圳"),
		std::make_pair("022","天津"),
		std::make_pair("0755","广州")
	};
	//打印map容器中的元素信息
	cout<<"------------------------------------------->"<<endl;
	display(cities);
	//重复关键字的元素没有添加
	//显示：010--->北京
	//      021--->上海
	//      022--->天津
	//      0755--->深圳
	

	//map支持下标访问运算符，时间复杂度为0(logN)
	cout<<"-------------------------------------------->"<<endl;
	cout<<cities["010"]<<endl;
	//显示：北京

	//如果关键字存在，还可以对value进行修改
	cities["010"]="南京";
	cout<<"-------------------------------------------->"<<endl;
	cout<<cities["010"]<<endl;
	//显示：南京
	//打印容器中的元素信息
	cout<<"-------------------------------------------->"<<endl;
	display(cities);
	//显示：010--->南京
	//      021--->上海
	//      022--->天津
	//      0755---->深圳

	//如果对应的关键字不存在，则会直接添加一个新元素
	cities["023"]="重庆";
	cout<<"-------------------------------------------->"<<endl;
	display(cities);
	//显示：010--->南京
	//      021--->上海
	//      022--->天津
	//      023--->重庆
	//      0755--->深圳

	//查找元素 find count
	size_t cnt=cities.count("01090");
	if(cnt){//cnt不为0，即存在要找的元素
		cout<<"查找成功！"<<endl;
	}else{//cnt为0，不存在要找的元素
		cout<<"查找失败！"<<endl;
	}//显示：查找失败！

	cities["027"]="武汉";
#if 0
	//通过pair来判断插入新元素成功与否
	pair<map<string,string>::iterator,bool> ret=cities.insert(std::make_pair("027","成都"));
#endif

#if 1
	//通过auto来自动推断类型
	auto ret=cities.insert(std::make_pair("027","成都"));
#endif

	//判断插入成功与否
	if(ret.second){//插入成功
		cout<<"添加元素成功！"<<endl;
		cout<<ret.first->first<<"----->"<<ret.first->second<<endl;
	}else{//插入失败
		cout<<"添加元素失败！"<<endl;
		cout<<ret.first->first<<"----->"<<ret.first->second<<endl;
	}
	//关键字相同的元素添加失败
	//显示：添加元素失败！
	//      027----->武汉
}

void test1()
{
	//以其他排序方式创建map容器
	map<string,string,std::greater<string>> cities{
		pair<string,string>("010","北京"),
		pair<string,string>("021","上海"),
		std::make_pair("0755","深圳"),
		std::make_pair("022","天津"),
		std::make_pair("0755","广州")
	};
	//打印map容器中的元素信息
	cout<<"---------------------------------------------->"<<endl;
	display(cities);
	//按照关键字降序排列，重复关键字的不再添加
	//显示：0755--->深圳
	//      022--->天津
	//      021--->上海
	//      010--->北京

	//map支持下标访问运算符，时间复杂度为0(logN)
	cout<<"----------------------------------------------->"<<endl;
	cout<<cities["010"]<<endl;
	//显示：北京

	//如果关键字存在，还可以对value进行修改
	cities["010"]="南京";
	cout<<"----------------------------------------------->"<<endl;
	cout<<cities["010"]<<endl;
	//显示：南京
	
	//打印容器中的元素信息
	cout<<"------------------------------------------------>"<<endl;
	display(cities);
	//显示：0755--->深圳
	//      022--->天津
	//      021--->上海
	//      010--->南京

	//如果对应的关键字不存在，则会直接以该关键字创建一个元素
	cout<<"--------------------------------------------------->"<<endl;
	cout<<cities["027"]<<endl;
	//显示：      （什么也不显示）
	//打印容器中的信息
	cout<<"---------------------------------------------------->"<<endl;
	display(cities);
	//显示：0755--->深圳
	//      027--->
	//      022--->天津
	//      021--->上海
	//      010--->南京

	//如果对应的关键字不存在，则会直接添加一个新元素
	cities["023"]="重庆";
	cout<<"----------------------------------------------------->"<<endl;
	display(cities);
	//显示：0755--->深圳
	//      027--->
	//      023--->重庆
	//      022--->天津
	//      021--->上海
	//      010--->南京

	//查找元素  find  count
	size_t cnt=cities.count("01090");
	if(cnt){//如果cnt不为0
		cout<<"查找成功！"<<endl;
	}else{//cnt为0
		cout<<"查找失败！"<<endl;
	}//显示：查找失败！

	cities["027"]="武汉";

#if 0
	//第一种插入成功与否检测方式
	pair<map<string,string>::iterator,bool> ret=
		cities.insert(std::make_pair("027","成都"));
#endif

#if 1
	//第二种插入成功与否检测方式
	auto ret=cities.insert(std::make_pair("027","成都"));
#endif

	if(ret.second){//插入成功
		cout<<"添加元素成功！"<<endl;
		cout<<ret.first->first<<"---->"<<ret.first->second<<endl;
	}else{//插入失败
		cout<<"添加元素失败！"<<endl;
		cout<<ret.first->first<<"---->"<<ret.first->second<<endl;
	}
	//关键字重复则添加失败
	//显示：添加元素失败！
	//      027----->武汉
}

int main(void)
{
	//test0();
	test1();

	return 0;
}
		



