#include <iostream>
#include <string>
#include "tinyxml.h"
using namespace std;

class Test
{
public:
	Test(){};
	~Test(){};

	static void hello(){ cout<< "test"<<endl;}

};

class Test2: public Test
{
	Test2(){};
	~Test2(){};
	static void hello(){ cout<< "test2"<<endl;}

};
static int randit()
{
	static int testme;
	throw new std::exception();
}

static int gettestit()
{
}
static Test* test;


void testrec(TiXmlElement *element, std::string &value)
{
	TiXmlElement *tmp = element;
	std::string str;
	while(tmp)
	{
		str = tmp->Value();
		if( tmp->FirstChildElement() == 0 )
		{
			const char* pText = tmp->GetText();
			if( pText )
			{
				std::string text = pText;

				cout << value + "/" + str << " " << text << endl;
			}
		}
		else
		{
			cout << str << endl;
			testrec(tmp->FirstChildElement(), value + std::string("/") + str);
		}
		tmp = tmp->NextSiblingElement();
	}	
}


void main()
{
	//test=test;
	TiXmlDocument doc;
	doc.LoadFile("testxml.xml");
	//{
		TiXmlHandle docHandle( &doc );


		TiXmlElement *element = docHandle.FirstChildElement().Element();
		testrec(element,std::string(""));
	//	int i = 0;
 //		while (element)
	//	{
	//		int j = 0;
	//		element = docHandle.FirstChild("units").FirstChild("unit").Child(j).Element();
	//		while(element)
	//		{
	//			//cout<<element->Value()<<endl;
	//			cout<<element->Value()<<endl;
	//			cout<<element->GetText()<<endl;
	//			element = docHandle.FirstChild("units").Child("unit",i).Child(++j).Element();
	//		}
	//		element = docHandle.FirstChild("units").Child("unit",++i).Element();
	//	}

	//}
	getchar();


}