#include <iostream>
using std::cout;
using std::endl;

class Point
{
	public:
		//加上默认构造函数
		Point()=default;
#if 0
		Point()
		: _ix(0)
		, _iy(0)
		{
			cout<<"Point()"<<endl;
		}
#endif
		explicit//禁止隐式（转换）调用 如：Point p1=5;这里就进行了隐式类型转换，将int型转为Point型，其实是隐式调用了Point类的构造函数
		Point(int ix,int iy=0)
		: _ix(ix)
		, _iy(iy)
		{
			cout<<"Point(int,int)"<<endl;
		}

		void setX(int ix)
		{
			_ix=ix;
		}

#if 0
		void print()//非const版本的函数，this指针类型为 Point* const this
		{
			//非const版本的成员函数是可以修改成员的，但是不能修改this指针的指向，因为this是常量指针
			//this=0x45a56c85b8dd; 这是错误的
			_ix=100; //这是可以执行成功的
			cout<<"void print()"<<endl;
			cout<<"("<<this->_ix<<","<<this->_iy<<")"<<endl;
		}
#endif

#if 1
		//以后只要某一个函数不会对数据成员进行修改，都要将其设置为const成员函数
		void print() const  //this指针的类型为 const Point* const this
		{
			//_ix=100; 这是错误语句，不能通过const成员函数修改对象的数据成员
			cout<<"void print() const"<<endl;
			cout<<"("<<this->_ix<<","<<this->_iy<<")"<<endl;
		}
#endif
		~Point()
		{
			cout<<"~Point()"<<endl;
		}
	private:
		//另一种初始化方式
		int _ix=0;
		int _iy=0;
};

void func1(const Point &rhs)
{
	//作为一个const对象，只能调用const成员函数
	rhs.print();//该print()函数是const版本
}

int main(void)
{
	//Point pt1(1,2);//非const对象调用的是非const成员函数
	//pt1.print();   //非const对象也可以调用const成员函数
	
	//const Point pt2(3,4);//const对象只能调用const成员函数
	//pt2.print();
	
	//func1(pt1);
	
	//创建类对象的数组
	Point points[5]={
		Point(1,2),//只初始化前两个元素，后面的元素使用默认构造函数
		Point(3,4)
	};

	points[0].print();
	points[2].print();

	//Point pt1=5;//隐式转换（将int型转换为Point类型）：先产生临时对象，再进行赋值，临时对象使用Point(5)这个构造函数来产生，再进行赋值操作。
	//pt1.print();

	return 0;
}











