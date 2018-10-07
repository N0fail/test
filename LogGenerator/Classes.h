#pragma once
#include <iostream>
#include <string>
#include <fstream>

const std::string nullStr = "!@$^&$$@#&*$ch23;47./3,.21";//��������, ��� ������ ������ ������ ���� �������� null
const int nullInt = -3459876;//��������, ��� ������ ����� ������ ���� �������� null, ����� ������� ��-������� �� ���� ���
const int nullBool = -1;//��������, ��� ������ ���������� ��������� ������ ���� �������� null, ����� ������� ��-������� �� ���� ���
const std::string someStr = "some string"; //����������� � stringOjbect ����, ������� �� ����� ��� �������
const int someInt = 7252686;//����������� � intObject ����, ������� �� ����� ��� �������
const int minAnswers = 1;//����������� ����� �������� � �����
const int maxAnswers = 10;//������������ ����� �������� � �����
const int minChoices = 2;//����������� ����� ��������� � ������� � ����. ����������
const int maxChoices = 5;//������������ ����� ��������� � ������� � ����. ����������
const int maxAttempts = 3;//������������ ������������ ����� �������
const int maxGrade = 10;//������ ���� ������ ��� ������ ������, �� ���� ���
const int maxYear = 2018;//������������ ���, ������� ����� ���� ������������
const int minYear = 2014;//����������� ���, ������� ����� ���� ������������

class objectGroup;
class objectPointer;

class object
{
public:
	object(std::string _name);
	virtual int signUp(std::string &outStr);//��������� ��� ���������� � �������������� ������
	std::string name;
};

class jsonObject : public object
{
public:
	jsonObject(std::string _name, objectGroup* _content);
	virtual int signUp(std::string &outStr);
	objectGroup* content;//��� �������� ���������� �������� � ������
};

class arrayOfStringsObject : public object
{
public:
	arrayOfStringsObject(std::string _name, std::string* _content, int _contentLegnth, int _level = 0);
	virtual int signUp(std::string &outStr);
private:
	int level;//�� ��, ��� � objectGroup
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
	int level;//���������� ������� ����������� ������(��� ����������� ������������)
};
