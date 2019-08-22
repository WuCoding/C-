#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::ostream_iterator;
using std::replace_if;

void test0()
{
	vector<int> numbers {1,2,3,4,5,6,7,8,9,10};

	//将vector容器中的元素拷贝到绑定了标准输出流的输出流容器
	copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	//显示：1 2 3 4 5 6 7 8 9 10

#if 0
	//lambda表达式
	replace_if(numbers.begin(),numbers.end(),
		[](int number){ return number>6;},
		22);
	//显示：1 2 3 4 5 6 22 22 22 22
#endif
	//二元断言
	std::less<int> lt;
	std::greater<int> gt;

	//函数适配器，函数绑定器---->在调用函数之前提前给某一个参数绑定值
	//变成一个一元断言
	//bind1st(lt,6);
	//bind2nd(lt,6);

#if 0
	replace_if(numbers.begin(),numbers.end(),bind1st(lt,6),66);
	//显示：1 2 3 4 5 6 66 66 66 66
#endif

#if 1
	replace_if(numbers.begin(),numbers.end(),bind2nd(lt,6),66);
	//显示：66 66 66 66 66 6 7 8 9 10
#endif
	
	//打印容器中的元素
	copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
}

int main(void)
{
	test0();

	return 0;
}

