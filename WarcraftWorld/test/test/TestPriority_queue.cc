#include "test.h"

class Point
{
	public:
		Point(int x,int y)
		: _x(x)
		, _y(y)
		{}

		int add() const
		{
			return _x+_y;
		}
		friend std::ostream & operator<<(std::ostream&,const Point&);
	private:
		int _x;
		int _y;
};

std::ostream & operator<<(std::ostream &os,const Point & rhs)
{
	os<<"("<<rhs._x<<","<<rhs._y<<")";
	return os;
}

struct ComparePoint
{
	bool operator() (const Point &lhs,const Point &rhs) const
	{
		return lhs.add()<rhs.add();
	}
};

int test0()
{
	Point p1(1,2);
	Point p2(2,3);
	Point p3(3,4);
	Point p4(4,5);
	Point p5(5,6);

	priority_queue<Point,vector<Point>,ComparePoint> test;
	test.push(p1);
	cout<<test.top()<<endl;
	test.push(p3);
	cout<<test.top()<<endl;
	test.push(p2);
	cout<<test.top()<<endl;
	test.push(p5);
	cout<<test.top()<<endl;
	test.push(p4);
	cout<<test.top()<<endl;

	cout<<"按优先级输出优先级队列中的元素："<<endl;
	while(!test.empty())
	{
		cout<<test.top()<<endl;
		test.pop();
	}

}

int main(void)
{
	test0();
}


	/*
	tmp1 a(1);
	tmp1 b(2);
	tmp1 c(3);
	priority_queue<tmp1> d;
	d.push(b);
	d.push(c);
	d.push(a);
	while (!d.empty()) 
	{
		cout << d.top().x << '\n';
		d.pop();
	}
	cout << endl;
	 
	priority_queue<tmp1, vector<tmp1>, tmp2> f;
	f.push(b);
	f.push(c);
	f.push(a);
	while (!f.empty()) 
	{
		cout << f.top().x << '\n';
		f.pop();
	}
	*/
