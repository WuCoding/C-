#include <iostream>
using namespace std;//using编译指令
namespace wd
{
	void display()
	{
		cout<<"wd::display()"<<endl;
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
