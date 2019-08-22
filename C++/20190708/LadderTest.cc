#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution
{
	public:
		//该函数作用为返回从头单词到尾单词的路径长度
		int ladderLength(const string &begWord,
				const string &endWord,
				const vector<string> &wordList)
		{
			//先查看字典中有没有结尾单词
			int cnt=count(wordList.begin(),wordList.end(),endWord);
			if(cnt==0)
			{
				//字典中没有结尾单词，直接失败，返回路径长度为0
				return 0;
			}

			//先将字典中的元素拷贝到unordered_set容器words，底层实现哈希桶
			unordered_set<string> words(wordList.begin(),wordList.end());
			//用来存放被访问过的元素
			unordered_set<string> visited;
			//用来存首单词和尾单词之间路径，记录一个单词和他上一个单词
			unordered_map<string,string> paths;

			queue<string> currentQue; //当前一层的元素队列
			queue<string> nextQue; //下一层的节点队列

			//此时为第一层
			int len=1;
			currentQue.push(begWord);//先将头单词放到第一层
			visited.insert(begWord);//将begWord放入已访问容器中
			while(!currentQue.empty())
			{
				while(!currentQue.empty())
				{
					//获得当前队列头元素并出栈
					string word=currentQue.front();
					currentQue.pop();
					//求取下一层节点
					vector<string> nextStatus;//存储下一层元素的容器
					//求当前队列出队的头节点的子节点
					getNextStatus(word,words,visited,nextStatus);
					//将nextStatus容器中的下一层元素，放入下一层元素
					//队列nextQue中
					for(auto &status:nextStatus)
					{
						//将下一层元素放入下一层队列
						nextQue.push(status);
						//将该元素和其父元素放到unordered_map容器中
						paths[status]=word;
						//查看该元素是不是尾单词
						if(status==endWord)
						{
							//是尾单词，则查找结束，打印路径
							printPaths(status,paths);
							//返回路径长度
							return len+1;
						}
						//将元素压入已使用容器
						visited.insert(status);
					}
				}
				//将路径长度+1
				++len;
				//将nextQue中的元素移动到currentQue中，
				//nextQue变为空，currentQue中的元素为之前子代的元素
				swap(currentQue,nextQue);

			}
			return 0;
		}

		//该函数作用为传入一个字符串，将满足该字符串子代的字符串压入result容器中
		void getNextStatus(const string &word,
				const unordered_set<string> &words,
				const unordered_set<string> &visited,
				vector<string> &result)
		{
			for(auto & candicate:words)
			{
				if(isValid(word,candicate))
				{
					//进入此处表示这两个字符串只有一位不同，可以成为父子关系

					//查看该目标元素是否已经被用过了
					int cnt=visited.count(candicate);
					if(cnt==0)
					{
						//表示该目标元素没有被用过，可以作为子代

						//将目标元素压到子代容器中
						result.push_back(candicate);
					}
				}
			}

		}

		//判断两个字符串是否只有一位不同
		bool isValid(const string &word,const string &candicate)
		{
			//用来记录两个对比字符串的不同的位的数量
			int cnt=0;
			for(size_t idx=0;idx!=word.size();++idx)
			{
				//每一位开始遍历
				if(word[idx]!=candicate[idx])
				{
					++cnt;
				}
			}
			//只有一位不同时返回true，其他情况返回false
			return cnt==1;
		}

		//打印头单词到尾单词的路径
		void printPaths(const string &end,
				const unordered_map<string,string> &paths)
		{
			//it->first当前单词，it->second当前单词的父单词
			auto it=paths.find(end);
			if(it==paths.end()){
				//没有以end为关键字的元素，即end为最后一个要找的元素

				//打印end并返回
				cout<<end<<endl;
				return;
			}else{
				//查找到了以end为关键字的元素

				//打印end并递归调用printPaths
				cout<<end<<"<-";
				printPaths(it->second,paths);
			}
		}
};

int main(void)
{
	vector<string> wordList={"hot","dot","dog","lot","log","cog"};
	string begWord="hit";
	string endWord="cog";

	cout<<Solution().ladderLength(begWord,endWord,wordList)<<endl;

	return 0;
}





