#include <iostream>
using std::cout;
using std::endl;
//const成员函数和非const成员函数
class Point
{
	public:
	//构造函数
		Point()
		: _ix(0)
		, _iy(0)
		{
			cout<<"Point()"<<endl;
		}

		Point(int ix,int iy)
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
		void print()//这里没有加const表示this类型为Point *const this
		{
			//非const版本的成员函数是可以修改成员的
			this->_ix=100;
			cout<<"void print()"<<endl;
			cout<<"("<<this->_ix<<","<<this->_iy<<")"<<endl;
		}
#endif

		
		
		
		//以后只要某一个函数不会对数据成员进行修改，都要将其设置为const成员函数
		
#if 1
		void print() const//此时this指针类型为 const Point* const this
		{
			//该函数不能对对象的数据成员进行修改
			//this->_ix=100; 这就是一条错误语句
			cout<<"void print() const"<<endl;
			cout<<"("<<this->_ix<<","<<this->_iy<<")"<<endl;
		}
#endif

	//析构函数
		~Point()//注：析构函数没有参数，所以析构函数只有一个，没有重构
		{
			cout<<"~Point()"<<endl;
		}

	private:
		int _ix;
		int _iy;
};

void func1(const Point &rhs)//rhs是一个const引用，所以通过rhs只能调用const函数成员
{
	rhs.print();
}

int main(void)
{
	Point pt1(1,2);//非const对象调用的是非const成员函数
	cout<<"pt1=";//但如果没有非const对象，也可以调用const对象
	pt1.print();


	const Point pt2(3,4);//const对象只能调用const成员函数
	pt2.print();

	func1(pt1);

	//创建一个类的对象的数组
	Point points[5]={
		Point(1,2),
		Point(3,4)
	};//只对前两个成员进行初始化

	points[0].print();
	points[1].print();

	return 0;

}











