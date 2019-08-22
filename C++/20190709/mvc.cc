#include <iostream>
#include <string>
#include <map>
#include <memory>
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::shared_ptr;

class Student
{
public:
	//构造函数
	Student(size_t id=0,const string &name=string())
	: _id(id)
	, _name(name)
	{
		cout<<"Student(size_t,string)"<<endl;
	}

	//获得学号
	size_t getId() const
	{
		return _id;
	}
	//获得姓名
	string getName() const
	{
		return _name;
	}

	//析构函数
	~Student()
	{
		cout<<"~Student()"<<endl;
	}
private:
	//数据成员
	size_t _id;
	string _name;
};

//展示类
class View  //数据成员为一个Student类型的指针
{
public:
	//构造函数
	View(Student *stu=nullptr)
	: _stu(stu)
	{
		cout<<"View(Student *)"<<endl;
	}

	void setStudent(Student *stu)
	{
		_stu=stu;
	}

	//虚函数，显示函数
	virtual void show() const
	{
		cout<<"id:"<<_stu->getId()<<endl
			<<"name:"<<_stu->getName()<<endl;
	}
protected:
	//数据成员
	Student * _stu;
};

class SubView
: public View
{
public:
	void show() const override//强制覆盖
	{
		cout<<"{ id:"<< _stu->getId()
			<<",name:"<<_stu->getName()
			<<"}"<<endl;
	}
};

//控制类
class Controller//数据成员为id和student对象对应的map容器
{
public:
	//构造函数
	Controller()
	{
		cout<<"Controller()"<<endl;
	}

	//将id和对应student对象放入map容器中
	void attach(const Student & stu) //左值引用
	{
		_students[stu.getId()]=stu;
	}

	void attach(Student && stu)  //右值引用
	{
		_students[stu.getId()]=std::move(stu);
	}

	//将传入的id对应的键值对从map容器中删除
	void detach(size_t id)
	{
		auto it=_students.find(id);
		if(it!=_students.end()){//说明map容器中含有该id的键值对
			//删除该键值对
			_students.erase(id);
		}
	}

	//将map容器中的student对象的信息都打印出来
	void show(View * view) //基类的指针指向派生类的对象，触发虚函数机制
	{
		for(auto & element : _students){
			//将student对象注册进展示对象中
			view->setStudent(&element.second);
			//进行展示
			view->show();
		}
	}

private:
	map<size_t,Student> _students;
};

int main(void)
{
	Controller controller;
	
	//将id和student对象的键值对放入到map容器中
	controller.attach(Student(100,"Jackie"));
	controller.attach(Student(101,"John"));
	controller.attach(Student(102,"Marry"));

	shared_ptr<View> view(new View());//基类指针指向基类对象
	shared_ptr<View> view2(new SubView());//基类指针指向派生类对象

	//使用基类view对象来展现
	controller.show(view.get());
	//使用派生类SubView对象来展现
	controller.show(view2.get());

	return 0;
}
	


