#include <iostream>
//using namespace std;//using编译指令

using std::cout;//using声明机制
using std::endl;


namespace wd
{
	void display()
	{
		cout<<"wd::display()"<<endl;
		tls::display();
	}
}//end of namespace wd
namespace tls
{
	void display()
	{
		cout<<"tls::display()"<<endl;
	}
}//end of namespace tls
int main()
{
	wd::display();//:: 作用域限定符
	tls::display();
	return 0;
}
