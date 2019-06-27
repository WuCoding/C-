#include <iostream>//标准输入输出流
#include <fstream>//文件流
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

//全局变量
vector<string> file;

void test1()
{
	//ifstream要求文件必须存在，ifstream输入文件流，将数据从文件中读取出来
	ifstream ifs("io2.cc");
	if(!ifs.good()){//如果该文件流状态异常
		cout<<"ifstream open file error!"<<endl;
		return;
	}

	//先为vector容器开辟一个100的空间
	file.reserve(100);
	string line;//用来接从文件中读取的数据
	//getline(ifstream,string)从流中获取一行的数据存入string型变量中
	while(std::getline(ifs,line)){
		file.push_back(line);//将数据压入容器中
	}

#if 0
	//auto 自动推导元素的类型
	for(auto & line:file)//遍历file容器中的元素
	{
		cout<<line<<endl;
	}
#endif
	//将文件流进行关闭
	ifs.close();
}

void test2()
{
	string filename="test.txt";
	//与文件输入流要求文件必须存在不同，
	//文件输出流不要求文件存在
	//当文件不存在时，直接创建文件；
	//当文件存在时，直接清空文件中的内容
	ofstream ofs(filename);//文件输出流将数据输出到文件中
	if(!ofs.good()){//如果流状态位异常
		cout<<">> ofstream open error!"<<endl;
		return;
	}

	//依次遍历容器中的元素，并输出到文件输出流中
	for(auto & line:file)
	{
		ofs<<line<<"\n";
	}
	
	//关闭文件输出流
	ofs.close();
}
void test3()
{
	string filename="test.txt";
	//std::ios::app模式可以在文件的末尾追加新的内容
	ofstream ofs(filename,std::ios::app);//以追加的方式打开filename的文件
	if(!ofs.good()){//如果流的状态位异常
		cout<<">> ofstream open error!"<<endl;
		return;
	}

	//查看当前文件流的指针位置
	cout<<"pos:"<<ofs.tellp()<<endl;
	
	string line="that's a new line\n";
	ofs<<line;

	//关闭文件流
	ofs.close();
}
//打印文件流的状态信息
void printStreamStatus(fstream & fs)
{
	cout<<"fs's badbit="<<fs.bad()<<endl
		<<"fs's failbit="<<fs.fail()<<endl
		<<"fs's eofbit="<<fs.eof()<<endl
		<<"fs's goodbit="<<fs.good()<<endl;
}

void test4()
{
	string filename="readme.txt";
	//文件输入输出流，既可读又可写
	fstream fs(filename);
	if(!fs.good()){//若流的状态异常
		cout<<"fstream open error!"<<endl;
		return;
	}

	int number=-1;
	//从标准输入读入10个数，写入到文件流中
	for(size_t idx=0;idx!=10;++idx)
	{
		cin>>number;
		fs<<number<<" ";
	}
	//输出文件流当前指针的位置
	cout<<">> pos:"<<fs.tellg()<<endl;
	//将文件流指针设置到文件开头
	fs.seekg(std::ios::beg);

	//输出文件流的状态
	printStreamStatus(fs);

	//将10个数从文件中读出，打印到标准输出上
	for(size_t idx=0;idx!=10;++idx)
	{
		fs>>number;
		cout<<number<<" ";
	}
	cout<<endl;

	fs.close();
}

void test5()
{
	string filename="vector.cc";
	ifstream ifs;//文件输入流，将数据从文件中输出
	//文件输入流的打开方式
	ifs.open(filename,std::ios::in|std::ios::ate);//std::ios::ate打开文件将指针偏移到文件末尾
	if(!ifs.good()){//如果文件流状态异常
		cout<<">> ifstream open file error!"<<endl;
		return;
	}

	//显示文件输入流的指针位置
	cout<<"pos:"<<ifs.tellg()<<endl;
	//存储文件的大小
	size_t len=ifs.tellg();
	//创建一个与文件大小相同的字符数组
	char buff[len+1]={0};
	//将文件指针偏移到文件的开头
	ifs.seekg(std::ios::beg);
	//将一篇文章的内容一次性读出
	ifs.read(buff,len);

	cout<<"buff:"<<endl<<buff<<endl;
	//关闭文件流
	ifs.close();
}
int main(void)
{
	test1();
	test2();
	test3();
	test4();
	test5();
	return 0;
}











































































