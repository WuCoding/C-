#include "tinyxml2.h" //""从当前目录开始搜索

#include <iostream>   //从系统路径开始搜索
#include <regex>
using std::cout;
using std::endl;
using namespace tinyxml2;

void test0()
{
	XMLDocument doc;
	doc.LoadFile("coolshell.xml");
	if(doc.ErrorID()){
		cout<<"doc load error!"<<endl;
		return;
	}
	XMLElement * itemElement;
	itemElement=doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
	do{
		XMLElement * titleElement=itemElement->FirstChildElement("title");
		XMLElement * linkElement=itemElement->FirstChildElement("link");
		XMLElement * contentElement=itemElement->FirstChildElement("content:encoded");

		const char * title=titleElement->GetText();
		const char * link=linkElement->GetText();
		const char * content=contentElement->GetText();

		cout<<"title:"<<title<<endl;
		cout<<"link:"<<link<<endl;
		cout<<"content:"<<content<<endl;
		
	}while(itemElement=itemElement->NextSiblingElement("item"));
}

int main(void)
{
	test0();

	return 0;
}
	
