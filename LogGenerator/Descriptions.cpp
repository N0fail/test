#pragma once
#include "Classes.h"

//****************************Object******************************
object::object(std::string _name)
{
	name = _name;
};

int object::signUp(std::string &outStr)
{
	outStr += "\"" + name + "\": ";
	return 0;
};

//****************************jsonObject******************************
jsonObject::jsonObject(std::string _name, objectGroup* _content) : object(_name),  content(_content)
{
};

int jsonObject::signUp(std::string &outStr)
{
	object::signUp(outStr);
	if (content == nullptr)
		outStr += "null";
	else
		content->signUp(outStr);
	return 0;
};

//**************************stringObject*****************************
stringObject::stringObject(std::string _name, std::string _content) : object(_name)
{
	content = _content;
};

int stringObject::signUp(std::string &outStr)
{
	object::signUp(outStr);
	if (content == nullStr)
		outStr += "null";
	else 
		outStr += "\"" + content + "\"";
	return 0;
};

//**************************intObject*****************************
intObject::intObject(std::string _name, int _content) : object(_name)
{
	content = _content;
};

int intObject::signUp(std::string &outStr)
{
	object::signUp(outStr);
	if (content == nullInt)
		outStr += "null";
	else
		outStr += std::to_string(content);
	return 0;
};

//**************************boolObject*****************************

boolObject::boolObject(std::string _name, int _content) : object(_name)
{
	content = _content;
};

int boolObject::signUp(std::string& outStr)
{
	object::signUp(outStr);
	if (content == nullBool)
		outStr += "null";
	else
		if (content == 1)
			outStr += "true";
		else
			outStr += "false";
	return 0;
};

//**************************arrayOfStringsObject*****************************
arrayOfStringsObject::arrayOfStringsObject(std::string _name, std::string* _content, int _contentLength, int _level) : object(_name)
{
	content = _content;
	contentLength = _contentLength;
	level = _level;
};

int arrayOfStringsObject::signUp(std::string &outStr)
{
	object::signUp(outStr);
	outStr += "[\n";
	std::string tab = "";
	for (int i = 0; i < level; ++i)
		tab += "	";
	for (int i = 0; i < contentLength - 1; ++i)
	{
		outStr += tab + "	";
		outStr += content[i];
		outStr += ",\n";
	}
	outStr += tab + "	";
	outStr += content[contentLength - 1];
	outStr += "\n";
	outStr += tab;
	outStr += "]";
	return 0;
};

//**************************objectPointer*****************************
objectPointer::objectPointer(object* _obj)
{
	obj = _obj;
	next = nullptr;
};

//**************************objectGroup*****************************
objectGroup::objectGroup(int _level) : head(nullptr), end(nullptr)
{
	level = _level;
};

int objectGroup::addObject(object* obj)
{
	if (head == nullptr)
	{
		head = new objectPointer(obj);
		end = head;
	}
	else
	{
		end->next = new objectPointer(obj);
		end = end->next;
	}
	return 0;
};

int objectGroup::signUp(std::string &outStr)
{
	std::string tab = "";
	for (int i = 0; i < level; ++i)
		tab += "	";
	objectPointer* p = head;
	if (p == nullptr)
		outStr += "{}";
	else
	{
		outStr += "{\n";
		while (p->next != nullptr)
		{
			outStr += tab + "	";
			p->obj->signUp(outStr);
			outStr += ",\n";
			p = p->next;
		}
		outStr += tab + "	";
		p->obj->signUp(outStr);
		outStr += "\n" + tab + "}";
		return 0;
	}
};