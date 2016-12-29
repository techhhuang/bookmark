#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
class Object
{
public:
	Object(){

	}
	~Object(){

	}
	
};
class EventArgs
{
public:
	EventArgs(){

	}
	~EventArgs(){

	}
	
};

class EventHandler:public Object
{
public:
	EventHandler(){

	}
	void raise(Object &sender,EventArgs &e){
		cout<<"event raise"<<endl;
		this->callbackList[0](sender,e);
	}
	void on(void (*callback)(Object &sender,EventArgs &e)){
		callbackList[0]=callback;
	}
	void operator+=(void (*callback)(Object &sender,EventArgs &e)){
		callbackList[0]=callback;
	}
private:
	void (*callbackList[9])(Object &sender,EventArgs &e);
};

class Person:public Object
{
public:
	Person(string name){
		this->name=name;
	}
	void sayHello(){
		cout<< "typeinfo done:"<<typeid(done).name()<<endl;
		cout<< "typeinfo this:"<<typeid(*this).name()<<endl;
		EventArgs e;
		done.raise(*this,e);

	}
	EventHandler done;
	string name;
private:
	
	
	
};

void callback(Object &sender,EventArgs &e){
	// Person p=static_cast<Person&>(sender);
	Person p=(Person&)sender;
	cout<<"hello :"<<p.name<<endl;
}

int main(){
	Person p("Jack");
	//p.done.on(callback);
	p.done+=callback;
	p.sayHello();
}

