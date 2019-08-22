#include "Subject.h"
#include "Observer.h"

#include <algorithm>

//响铃函数
void Ring::alarm()
{
	if(!_isRing){//如果_isRing为false
		_isRing=true;
		notify();
		_isRing=false;
	}
}

//将观察者加入list容器
void Ring::attach(Observer *ob)
{
	//先查找原容器中有无该元素
	auto it=std::find(_oblist.begin(),_oblist.end(),ob);
	if(it==_oblist.end()){//如果原容器中无该元素
		//将该元素放入容器中
		_oblist.push_back(ob);
	}
}

//将观察者从原容器中删除
void Ring::detach(Observer *ob)
{
	auto it=std::find(_oblist.begin(),_oblist.end(),ob);
	if(it!=_oblist.end()){//原容器中有该元素
		//将该元素从容器中删除
		_oblist.erase(it);
	}
}

//将容器中的观察者们依次唤醒
void Ring::notify()
{
	for(auto &ob:_oblist){
		ob->update();
	}
}



