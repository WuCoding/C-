#include <iostream> //标准输入输出流
#include <sstream>  //字符串输入输出流
#include <string>
#include <fstream> //文件输入输出流
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
//显示字符串流的状态
void printStreamStatus(stringstream &fs)
{
	cout<<"fs's badbit="<<fs.bad()<<endl
		<<"fs's failbit="<<fs.fail()<<endl
		<<"fs's eofbit="<<fs.eof()<<endl
		<<"fs's goodbit="<<fs.good()<<endl<<endl;
}

void test0()
{
	int number1=1;
	float number2=2.22;

	//字符串流
	stringstream ss;
	//字符串输出流
	ss<<"number1="<<number1<<" number2= "<<number2;//将各种类型数据拼接组合成字符串输出流中的内容
	//将字符串流中的内容以字符串的形式输出
	cout<<ss.str()<<endl<<endl;//字符串流功能有些像sprintf()

	string key;
	int value;

	//将字符串流中的内容输出，直到到达字符串流的末尾
	while(!ss.eof()){
		ss>>key>>value;//将字符串流中的数据分别放到string类型变量和int类型变量
		cout<<key<<"------>"<<value<<endl;
	}
}

//利用字符串流将int类型转string类型
string int2str(int number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}

//定义一个结构体，作为容器的元素类型
struct Element
{
	//构造函数
	Element(const string &k,const string &v)
	: key(k),value(v)
	{}
	string key;
	string value;
}
//将文件中的内容以key value对的形式存入到容器中
void readConfiguration(const string &filename)
{
	//将文件打开
	ifstream ifs(filename);
	//判断文件流的状态
	if(!ifs.good()){
		cout<<">> ifstream open"<<filename<<"error!"<<endl;
		return;
	}

	//创建容器，元素类型为自己创建的Element结构体
	vector<Element> config;//config配置

	string key,value;
	string line;//用来存一行的数据
	while(getline(ifs,line)){  //循环获取文件的行信息
		istringstream iss(line); //将行信息放到字符串流中
		while(!iss.eof()){  //直到读取到字符串流的末尾
			//将字符串流中的信息依次放入到对应变量中
			iss>>key>>value;
			//创建一个Element结构体对象
			Element element(key,value);
			//将该对象压入容器中
			config.push_back(element);
		}
	}
	//循环遍历容器中的元素
	for(auto & element:config)
	{
		cout<<element.key<<"------->"<<element.value<<endl;
	}
}

void test1()
{
	string filename="my.conf";
	readConfiguration(filename);
}

int main(void)
{
	test0();
	test1();
	
	return 0;
}




