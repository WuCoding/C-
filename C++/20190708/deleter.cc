#include <iostream>
#include <memory>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::shared_ptr;

struct FileCloser
{
	void operator()(FILE *fp)
	{
		if(fp){//如果文件指针不为nullptr
			fclose(fp);
			cout<<">> fclose(fp)"<<endl;
		}
	}
};

void test0()
{
	unique_ptr<FILE,FileCloser> up(fopen("test.txt","aw+"));

	string msg="hello,world";
	fwrite(msg.c_str(),1,msg.size(),up.get());
}

void test1()
{
	shared_ptr<FILE> up(fopen("test.txt","aw+"),FileCloser());

	string msg="hello,world\n";
	fwrite(msg.c_str(),1,msg.size(),up.get());
}

int main(void)
{
	//test0();
	test1();
	
	return 0;
}
