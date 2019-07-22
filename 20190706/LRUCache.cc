#include <iostream>
#include <list>
#include <unordered_map>
//unordered_map底层实现是哈希桶，空间换时间，查找元素的时间复杂度为O(1)
using std::cout;
using std::endl;
using std::list;
using std::unordered_map;

class LRUCache
{
	//嵌套类
	struct CacheNode //struct默认权限为public
	{
		//嵌套类的构造函数
		CacheNode(int k,int v)
		: key(k)
		, value(v)
		{}

		//数据成员
		int key;
		int value;
	};
	public:
		//构造函数
		LRUCache(int capacity)
		: _capacity(capacity)
		{}

		//放入元素
		void put(int key,int value)
		{
			//获得关键字在unordered_map中的迭代器
			//it->first为关键字，it->second为关键字在链表中的迭代器
			auto it=_keys.find(key);//这是个O(1)操作
			if(it==_keys.end()){
				//要放入的元素在容器中不存在
				if(_nodes.size()==_capacity){
					//自定义容器中已满，淘汰掉链表最后的元素
					//即最久没被访问的元素
					int deleteKey=_nodes.back().key;
					//从链表中删除，链表中的元素为自定义的嵌套类对象
					//（键值对）
					_nodes.pop_back();
					//从unordered_map中删除
					_keys.erase(deleteKey);
				}
				//此时可以放入元素
				//创建对象
				CacheNode node(key,value);
				//将元素以头插法插入队列头
				_nodes.push_front(node);
				//将元素的地址和关键字绑定放入到unordered_map中
				_keys.insert(make_pair(key,_nodes.begin()));
				//或者用另一种方法将元素放入unordered_map中
				//_keys[key]=_nodes.begin();
			}else{
				//关键字已经存在，则表示进行更新值的操作
				//将值进行改变
				it->second->value=value;
				//因为进行了更新，所以将该节点从链表中拿出放到链表头
				//it->first为key，it->second为链表的迭代器
				_nodes.splice(_nodes.begin(),_nodes,it->second);
				//将unordered_map中的元素值（记录链表迭代器的值）更新
				_keys[key]=_nodes.begin();
			}
		}

		//获得元素的值
		int get(int key)
		{
			//获得关键字在unordered_map中的迭代器
			//it->first为关键字，it->second为关键字在链表中的迭代器
			auto it=_keys.find(key);
			if(it==_keys.end()){
				//key关键字不存在
				return -1;
			}else{
				//key关键字存在
				//获得该关键字的值
				int ret=it->second->value;
				//将该节点放到链表开头
				_nodes.splice(_nodes.begin(),_nodes,it->second);
				//改变unordered_map中元素的值
				_keys[key]=_nodes.begin();
				//返回查找的值
				return ret;
			}
		}
	private:
		//数据成员
		int _capacity;//最多存储的元素数量
		list<CacheNode> _nodes;//存储嵌套类对象（键值对）的链表容器
		//存储关键字在链表中的位置，unordered_map容器中key值可以重复，
		//查询效率高，底层用哈希桶来实现
		unordered_map<int,list<CacheNode>::iterator> _keys;
};

int main(void)
{
	//创建LRUCache类对象，初始化该对象容量
	LRUCache cache(2);

	//放入一个元素
	cache.put(1,1);
	cout<<"get(1)="<<cache.get(1)<<endl;
	//显示：get(1)=1
	

	//再放入一个元素
	cache.put(2,2);
	cout<<"get(2)="<<cache.get(2)<<endl;
	//显示：get(2)=2

	//再放入一个元素
	cache.put(3,3);

	cout<<"get(1)="<<cache.get(1)<<endl;
	//显示：get(1)=-1

	cout<<"get(2)="<<cache.get(2)<<endl;
	//显示：get(2)=2

	cout<<"get(3)="<<cache.get(3)<<endl;
	//显示：get(3)=3

	//再放入一个元素
	cache.put(4,4);
	cout<<"get(3)="<<cache.get(3)<<endl;
	//显示：get(3)=3

	cout<<"get(2)="<<cache.get(2)<<endl;
	//显示：get(2)=-1

	return 0;
}



