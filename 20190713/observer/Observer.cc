#include "Observer.h"
#include "Subject.h"

#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

void Baby::update()
{
	::srand(::clock());
	int number=::rand()%100;
	if(number<70){
		cout<<">> Baby"<<_name
			<<"is sleeping sweetly!"<<endl;
	}else{
		cout<<">>Baby"<<_name
			<<"is awake, and start cring loudly!"<<endl;
	}
}

void Nurse::update()
{
	::srand(::clock());
	int number=::rand()%100;
	if(number<70){
		cout<<">>Nurse"<<_name
			<<"is awake, and start opening the door!"<<endl;
	}else{
		cout<<">>Nurse"<<_name
			<<"sleeps sweetly!"<<endl;
	}
}

void Guest::knock(Ring &ring)
{
	cout<<">>Guest"<<_name
		<<"is knocking at the door !"<<endl;
	ring.alarm();
}
