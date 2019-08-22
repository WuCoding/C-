#include <iostream>
#include <map>
#include <string>
using std::cout;
using std::endl;
using std::multimap;
using std::string;
using std::pair;

template <class Container>
void display(const Container &c)
{
	for(auto &elem:c)
	{
		cout<<elem.first<<"--->"<<elem.second<<endl;
	}
}

void test0()
{
	//创建multimap容器
	multimap<string,string> cities{
		pair<string,string>("010","北京"),
		pair<string,string>("021","上海"),
		std::make_pair("0755","深圳"),
		std::make_pair("022","天津"),
		std::make_pair("0755","广州")
	};
	//打印multimap容器中元素信息
	display(cities);
	//按照升序排列，可有关键词重复元素
	//显示：010--->北京
	//      021--->上海
	//      022--->天津
	//      0755--->深圳
	//      0755--->广州

	//multimap不支持下标访问运算符，因为一个关键词可对应多个元素
	//cout<<cities["010"]<<endl;
	
	//查找元素 find count
	size_t cnt=cities.count("0755");
	if(cnt){//cnt不为0
		cout<<"查找成功！"<<endl;
	}else{//cnt为0
		cout<<"查找失败！"<<endl;
	}
	cout<<"cnt="<<cnt<<endl;
	//显示：查找成功！
	//     cnt=2

#if 0
	//下面这种方式不适用于multimap容器，因为multimap容器中一个关键
	//字可对应多个元素，所以插入结果一定成功
	pair<multimap<string,string>::iterator,bool> ret=
		cities.insert(std::make_pair("027","成都"));
	if(ret.second){//插入成功
		cout<<"插入成功！"<<endl;
		cout<<ret.first->first<<"--->"<<ret.first->second<<endl;
	}else{//插入失败
		cout<<"插入失败！"<<endl;
		cout<<ret.first->first<<"--->"<<ret.first->second<<endl;
	}
#endif

#if 1
	auto ret=cities.insert(std::make_pair("027","成都"));	
	cout<<ret->first<<"--->"<<ret->second<<endl;
	//显示：027--->成都
#endif
}

void test1()
{
	//按照string类型的降序排列
	multimap<string,string,std::greater<string>> cities{
		pair<string,string>("010","北京"),
		pair<string,string>("021","上海"),
		std::make_pair("0755","深圳"),
		std::make_pair("022","天津"),
		std::make_pair("0755","广州")
	};
	//打印容器中的元素信息
	display(cities);
	//显示：0755--->深圳
	//      0755--->广州
	//      022--->天津
	//      021--->上海
	//      010--->北京

	//multimap不支持下标访问运算符
	//cout<<cities["010"]<<endl;
	
	//查找元素 find count
	size_t cnt=cities.count("01090");
	if(cnt){//如果cnt不为0
		cout<<"查找成功！"<<endl;
	}else{//cnt为0
		cout<<"查找失败！"<<endl;
	}
	cout<<"cnt="<<cnt<<endl;
	//显示：查找失败！
	//     cnt=0

	auto ret=cities.insert(std::make_pair("027","成都"));
	cout<<ret->first<<"--->"<<ret->second<<endl;
	//因为multimap容器中允许元素的关键词重复，所以插入必成功
	//显示：027--->成都
	
}

int main(void)
{
	//test0();
	test1();

	return 0;
}
