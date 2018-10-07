#pragma once
#include <iostream>
#include <string>
#include <fstream>

const std::string nullStr = "!@$^&$$@#&*$ch23;47./3,.21";//означает, что вместо строки должно быть написано null
const int nullInt = -3459876;//означает, что вместо числа должно быть написано null, нужно сделать по-другому но пока так
const int nullBool = -1;//означает, что вместо логической константы должно быть написано null, нужно сделать по-другому но пока так
const std::string someStr = "some string"; //встявляется в stringOjbect поля, которые не важны для анализа
const int someInt = 7252686;//вставляется в intObject поля, которые не важны для анализа
const int minAnswers = 1;//минимальное число вопросов в тесте
const int maxAnswers = 10;//максимальное число вопросов в тесте
const int minChoices = 2;//минимальное число вариантов в вопросе с неск. вариантами
const int maxChoices = 5;//максимальное число вариантов в вопросе с неск. вариантами
const int maxAttempts = 3;//максимальное генерируемое число попыток
const int maxGrade = 10;//должно быть разным для разных тестов, но пока так
const int maxYear = 2018;//максимальный год, который может быть сгенерирован
const int minYear = 2014;//минимальный год, который может быть сгенерирован

class objectGroup;
class objectPointer;

class object
{
public:
	object(std::string _name);
	virtual int signUp(std::string &outStr);//добавляет своё содержимое в результирующую строку
	std::string name;
};

class jsonObject : public object
{
public:
	jsonObject(std::string _name, objectGroup* _content);
	virtual int signUp(std::string &outStr);
	objectGroup* content;//для удобства добавления перенесён в паблик
};

class arrayOfStringsObject : public object
{
public:
	arrayOfStringsObject(std::string _name, std::string* _content, int _contentLegnth, int _level = 0);
	virtual int signUp(std::string &outStr);
private:
	int level;//то же, что у objectGroup
	int contentLength;
	std::string* content;
};

class stringObject : public object
{
public:
	stringObject(std::string _name, std::string _content);
	virtual int signUp(std::string &outStr);
private:
	std::string content;
};

class intObject : public object
{
public:
	intObject(std::string _name, int _content);
	virtual int signUp(std::string &outStr);
private:
	int content;
};

class boolObject : public object
{
public:
	boolObject(std::string _name, int _content);
	virtual int signUp(std::string &outStr);
	int content;
};

class objectPointer
{
public:
	object* obj;
	objectPointer* next;
	objectPointer(object* _obj);
};

class objectGroup
{
public:
	objectGroup(int _level = 0);
	objectPointer* head;
	objectPointer* end;
	int addObject(object*);
	//int deleteObject(object*);
	int signUp(std::string &outStr);
private:
	int level;//показывает уровень вложенности группы(для правильного выравнивания)
};
