#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class SafeFile
{
	public:
		//构造函数
		SafeFile(FILE *fp)
		: _fp(fp)
		{}

		//写文件函数
		void write(const string &msg)
		{
			fwrite(msg.c_str(),1,msg.size(),_fp);
		}

		//析构函数
		~SafeFile()
		{
			if(_fp){
				//关闭文件
				fclose(_fp);
				cout<<"fclose(fp)"<<endl;
			}
		}
	private:
		//数据成员
		FILE *_fp;
};

int main(void)
{
	SafeFile sf(fopen("test.txt","aw+"));
	string msg="hello,world\n";
	sf.write(msg);

	return 0;
}
