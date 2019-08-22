#include <iostream>
#include <memory>
#include <algorithm>
using std::cout;
using std::endl;
using std::allocator;

//类模板
template <class Type>
class Vector
{
	public:
		//给一个名称起一个别名，类似预处理语句
		using iterator=Type *;
		using const_iterator=const Type *;

		//无参构造函数
		Vector()
		: _start(nullptr)
		, _finish(nullptr)
		, _end_of_storage(nullptr)
		{}

		//析构函数
		~Vector()
		{
			if(size()>0){//容器不为空
				//从尾部依次销毁元素
				while(_start!=_finish)
				{
					_alloc.destroy(--_finish);
					//stl源码allocator类中destroy成员函数实现	
					//void destroy(pointer __p) { __p->~_Tp(); }
					//将一个类指针传入，然后用该指针调用该类的
					//析构函数
				}
				_alloc.deallocate(_start,capacity());
				//deallocate成员函数源码：
				//void deallocate(pointer __p, size_type __n)
				//{ _Alloc::deallocate(__p, __n * sizeof(_Tp)); }
				//这里的_Alloc::deallocate有两个版本：
				//1.一级配置器：
				//	>malloc和free的封装直接执行free
				//2.二级配置器：
				//	>16个自由空闲链表加内存池，如果内存回收的大小小于128，
				//	>则将该空间放到空闲链表中
			}
		}

		//返回容器中元素个数
		size_t size() const
		{
			return _finish-_start;
		}
		//返回容器的容量
		size_t capacity() const
		{
			return _end_of_storage-_start;
		}
		//压栈操作
		void push_back(const Type &value);
		//出栈操作
		void pop_back();

		//返回首元素
		const_iterator begin() const
		{
			return _start;
		}
		//返回尾元素
		const_iterator end() const
		{
			return _finish;
		}

		//下标运算符重载函数
		Type & operator[](size_t idx)
		{
			return _start[idx];
		}
	private:
		//私有成员函数
		void reallocate();
	private:
		//数据成员
		//allocator类的对象，静态数据成员
		static allocator<Type> _alloc;
		//管理空间的三个指针
		Type * _start;//指向堆内存容器头位置
		Type * _finish;//指向容器最后一个元素
		Type * _end_of_storage;//指向堆内存容器尾位置
};

//静态数据成员在类外初始化
template <class Type>
allocator<Type> Vector<Type>::_alloc;//默认初始化

//--------------------------------Vector类成员函数的实现---------------------------------
//压栈操作函数实现
template <class Type>
void Vector<Type>::push_back(const Type & value)
{
	if(size()==capacity()){//容器空间已满
		//调用类中的私有成员函数
		reallocate();
	}
	//此时有空间放数据了
	_alloc.construct(_finish++,value);
	//stl源码中construct源码：
	//void construct(pointer __p, const _Tp& __val) { new(__p) _Tp(__val); }
}

//出栈操作函数实现
template <class Type>
void Vector<Type>::pop_back()
{
	if(size()!=0){//容器不为空
		_alloc.destroy(--_finish);
		//destroy的源码实现：
		//void destroy(pointer __p) { __p->~_Tp(); }
	}
}

//私有成员函数reallocate()实现
template <class Type>
void Vector<Type>::reallocate()
{
	size_t capa=capacity();
	size_t newCapa=2*capa>0?2*capa:1;

	Type *p=_alloc.allocate(newCapa);//为类型化空间
	//allocate有两种开辟空间的方式：
	//1.一级配置器：
	//	>开辟空间大于128，调用malloc开辟堆空间
	//2.二级配置器：
	//	>开辟空间小于128，从自由空闲链表中拿空闲
	//	>的空间块
	
	if(_start){//_start不为nullptr
		//只有在最初创建Vector对象时_start才为nullptr
		//只有在reallocate()中才有改变_start操作，说明
		//经过扩充空间不是最初创建的空容器，而是经过
		//reallocate()之后的容器，说明容器中存在元素

		//执行将原有旧内存中的元素复制到新开辟的新内存
		//空间中
		std::uninitialized_copy(_start,_finish,p);
		//暂时没看懂uninitialized_copy源码。。。。

		while(_start!=_finish)
		{
			_alloc.destroy(--_finish);
			//stl源码allocator类中destroy成员函数实现	
			//void destroy(pointer __p) { __p->~_Tp(); }
			//将一个类指针传入，然后用该指针调用该类的
			//析构函数
		}

		//回收原来的旧空间
		_alloc.deallocate(_start,capa);
		//deallocate成员函数源码：
		//void deallocate(pointer __p, size_type __n)
		//{ _Alloc::deallocate(__p, __n * sizeof(_Tp)); }
		//这里的_Alloc::deallocate有两个版本：
		//1.一级配置器：
		//	>malloc和free的封装直接执行free
		//2.二级配置器：
		//	>16个自由空闲链表加内存池，如果内存回收的大小小于128，
		//	>则将该空间放到空闲链表中
	}
	//重新给_start赋值
	_start=p;
	//重新给_finish赋值
	_finish=_start+capa;
	//重新给_end_of_storage赋值
	_end_of_storage=_start+newCapa;
}

//------------------------------------------普通函数模板----------------------------------------
//打印容器中元素的函数模板
template <class Container>
void display(const Container &c)
{
	typename Container::const_iterator it=c.begin();
	//在Container::const_iterator前加上typename告诉编译器const_iterator
	//是一个类型，不然会报错
	while(it!=c.end()){
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

//获得容器当前的元素数量和容量的函数模板
template <class Container>
void printCapacity(const Container &c)
{
	cout<<"c'size="<<c.size()<<endl;
	cout<<"c'capacity="<<c.capacity()<<endl;
}

//对Vector进行内置类型测试
int test0()
{
	Vector<int> numbers;
	numbers.push_back(1);
	printCapacity(numbers);
	//显示：c'size=1
	//      c'capacity=1
	numbers.push_back(1);
	printCapacity(numbers);
	//显示：c'size=2
	//      c'capacity=2
	numbers.push_back(1);
	printCapacity(numbers);
	//显示：c'size=3
	//      c'capacity=4
	numbers.push_back(1);
	printCapacity(numbers);
	//显示：c'size=4
	//      c'capacity=4
	numbers.push_back(1);
	printCapacity(numbers);
	//显示：c'size=5
	//      c'capacity=8
	numbers.push_back(1);
	printCapacity(numbers);
	//显示：c'size=6
	//      c'capacity=8

	display(numbers);
	//显示：1 1 1 1 1 1
	return 0;
}

//自定义类型
class Point
{
	public:
		//构造函数
		Point(int ix=0,int iy=0)
		: _ix(ix)
		, _iy(iy)
		{
			cout<<"Point(int,int)"<<endl;
		}
		//复制构造函数
		Point(const Point & rhs)
		: _ix(rhs._ix)
		, _iy(rhs._iy)
		{
			cout<<"Point(const Point & rhs)"<<endl;
		}

		//打印函数
		void print() const
		{
			cout<<"("<<_ix<<","<<_iy<<")"<<endl;
		}
		
		//改变数据成员_ix的值
		void setX(int ix)
		{
			_ix=ix;
		}

		//改变数据成员_iy的值
		void setY(int iy)
		{
			_iy=iy;
		}

		//析构函数
		~Point()
		{
			cout<<"~Point()"<<endl;
		}

		//友元函数声明
		friend std::ostream & operator<<(std::ostream &os,const Point &rhs);

	private:
		//数据成员
		int _ix;
		int _iy;
};

//输出运算符重载函数实现
std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

//测试以自定义类型对象做元素
void test1()
{
	Vector<Point> points;
	points.push_back(1);
	printCapacity(points);
	//显示：Point(int,int) 临时匿名对象创建
	//      Point(const Point &rhs) 复制构造到容器开辟的空间中
	//      ~Point() 临时匿名对象销毁
	//      c'size=1
	//      c'capacity=1

	points.push_back(1);
	printCapacity(points);
	//显示：Point(int,int)
	//      Point(const Point &rhs) 这里发生了新空间的开辟，原有旧元素的拷贝
	//      ~Point()
	//      Point(const Point &rhs)
	//      ~Point()
	//      c'size=2
	//      c'capacity=2

	points.push_back(1);
	printCapacity(points);
	//显示：Point(int,int)
	//	Point(const Point &rhs) 再次发生新空间的开辟和旧元素的拷贝
	//	Point(const Point &rhs)
	//	~Point()
	//	~Point()
	//	Point(const Point &rhs)
	//	~Point()
	//	c'size=3
	//	c'capacity=4
	
	points.push_back(1);
	printCapacity(points);
	//显示：Point(int,int) 这里没有再发生新空间的开辟
	//	Point(const Point &rhs)
	//	~Point()
	//	c'size=4
	//	c'capacity=4
	points.push_back(1);
	printCapacity(points);
	//显示：Point(int,int)
	//	Point(const Point &rhs) 发生新空间的开辟和旧元素的拷贝
	//	Point(const Point &rhs)
	//	Point(const Point &rhs)
	//	Point(const Point &rhs)
	//	~Point()
	//	~Point()
	//	~Point()
	//	~Point()
	//	Point(const Point &rhs)
	//	~Point()
	//	c'size=5
	//	c'capacity=8
	points.push_back(1);
	printCapacity(points);
	//显示：Point(int,int)
	//	Point(const Point &rhs)
	//	~Point()
	//	c'size=6
	//	c'capacity=8
	display(points);
	//显示：(1,0)(1,0)(1,0)(1,0)(1,0)(1,0)

	//测试重载的下标运算符
	for(size_t idx=0;idx!=points.size();++idx)
	{
		cout<<points[idx]<<" ";
	}
	cout<<endl;
	//显示：(1,0)(1,0)(1,0)(1,0)(1,0)(1,0)
	
	//将容器开辟的空间上的对象销毁
	//显示：~Point()
	//	~Point()
	//	~Point()
	//	~Point()
	//	~Point()
	//	~Point()
}

int main(void)
{
	//test0();
	test1();

	return 0;
}









