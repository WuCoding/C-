#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>

#include <limits>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <functional>
#include <iterator>
#include <set>

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
using std::copy;
using std::list;
using std::queue;
using std::map;
using std::istream_iterator;
using std::ostream_iterator;
class Warrior;
using WarriorPtr =Warrior *;
enum Color{
	RED,
	BLUE,
	NOTSET
};
enum WarriorType{
	DRAGON_TYPE,
	NINJA_TYPE,
	ICEMAN_TYPE,
	LION_TYPE,
	WOLF_TYPE
};
//通过某种颜色，得到字符串
inline string toString(Color color)
{
	return (color==RED)?string("red"):string("blue");
}
//通过武士类型，得到字符串
inline string toString(WarriorType type)
{
	switch(type) {
		case DRAGON_TYPE: 
			return "dragon";
		case NINJA_TYPE: 
			return "ninja";
		case ICEMAN_TYPE: 
			return "iceman";
		case LION_TYPE: 
			return "lion";
		case WOLF_TYPE: 
			return "wolf";
		default:
			return string();
	}
}

//通过字符串，得到武士类型
inline WarriorType toWarriorType(const string &str)
{
		if("dragon"==str)
			return DRAGON_TYPE;
		if("ninja"==str)
			return NINJA_TYPE;
		if("iceman"==str)
			return ICEMAN_TYPE;
		if("lion"==str)
			return LION_TYPE;
		if("wolf"==str)
			return WOLF_TYPE;	
}


