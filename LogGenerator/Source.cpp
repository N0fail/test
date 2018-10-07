#pragma once
#include "Classes.h"

object* agentGenerator()
{
	stringObject* agent = new stringObject("agent", someStr);
	return agent;
};

object* course_idGenerator()
{
	const int coursesNum = 4;
	const std::string course_ids[coursesNum] = { "edx/AN101/2014_T1", "edx/AN111/2014_T2", "edx/AN301/2014_T3", "edx/AN102/2014_T4" };
	stringObject* course_id = new stringObject("course_id", course_ids[rand()%coursesNum]);
	return course_id;
};

object* display_nameGenerator()
{
	stringObject* display_name = new stringObject("display_name", someStr);
	return display_name;
};

object* moduleGenerator()
{
	objectGroup* moduleGroup = new objectGroup(2);
	jsonObject* module = new jsonObject("module", moduleGroup);
	module->content->addObject(display_nameGenerator());
	return module;
};

object* org_idGenerator()
{
	stringObject* org_id = new stringObject("org_id", someStr);
	return org_id;
};

object* user_idGenerator()
{
	intObject* user_id = new intObject("user_id", someInt);
	return user_id;
};

object* contextGenerator()
{
	objectGroup* contextGroup = new objectGroup(1);//через указатель, чтобы объект не удалился при выходе из функции
	jsonObject* context = new jsonObject("context", contextGroup);
	context->content->addObject(course_idGenerator());
	context->content->addObject(moduleGenerator());
	context->content->addObject(org_idGenerator());
	context->content->addObject(user_idGenerator());
	return context;
};

object* intAnswerGenerator()
{
	std::string ansName = "answer_";
	ansName += rand();
	ansName += "_";
	ansName += rand();
	intObject* intAnswer = new intObject(ansName, someInt);
	return intAnswer;
};

object* stringAnswerGenerator()
{
	std::string ansName = "answer_";
	for (int i = 0; i < 15 + rand()%10; ++i)
		ansName += (char)("A" + rand() % 26);
	stringObject* stringAnswer = new stringObject(ansName, someStr);
	return stringAnswer;
};

object* arrayAnswerGenerator(int level = 0)
{
	int choiceCount = minChoices + rand() % (maxChoices - minChoices);
	std::string* arrayOfStrings = new std::string[choiceCount];
	for (int i = 0; i < choiceCount; ++i)
		arrayOfStrings[i] = "choise_" + std::to_string(i);
	std::string ansName = "answer_";

	for (int i = 0; i < 15 + rand() % 10; ++i)
		ansName += (char)("A" + rand() % 26);

	arrayOfStringsObject* arrayAnswer = new arrayOfStringsObject(ansName, arrayOfStrings, choiceCount, level);
	return arrayAnswer;
};

jsonObject* answersGenerator()
{
	objectGroup* answersGroup = new objectGroup(2);
	jsonObject* answers = new jsonObject("answer", answersGroup);
	int n = minAnswers + (rand() % (maxAnswers - minAnswers));
	for (int i = 0; i < n; ++i)
	{
		int type = rand() % 3;
		switch (type)
		{
			case 0:
				answers->content->addObject(intAnswerGenerator());
				break;
			case 1:
				answers->content->addObject(stringAnswerGenerator());
				break;
			default:
				answers->content->addObject(arrayAnswerGenerator(3));
		}
	}
	return answers;
};

object* attemptsGenerator()
{
	intObject* attempts = new intObject("attempts", 1 + rand() % maxAttempts);
	return attempts;
};

object* correctnessGenerator()
{
	std::string content = "";
	if (rand() % 2 == 0)
		content = "correct";
	else
		content = "incorrect";
	stringObject* correctness = new stringObject("correctness", content);
	return correctness;
};

object* hintGenerator()
{
	stringObject* hint = new stringObject("hint", "");
	return hint;
};

object* hintmodeGenerator()
{
	const std::string possibleHintMods[4] = { "", nullStr, "always", "on_request" };
	stringObject* hintmode = new stringObject("hintmode", possibleHintMods[rand() % 4]);;
	return hintmode;
};

object* msgGenerator()
{
	stringObject* msg = new stringObject("msg", "");
	return msg;
};

object* npointsGenerator()
{
	intObject* npoints = new intObject("npoints", nullInt);
	return npoints;
};

object* queuestateGenerator()
{
	jsonObject* queuestate = new jsonObject("queueState", nullptr);
	return queuestate;
};

object* correct_mapObjectGenerator(std::string _name)
{
	objectGroup* cmoGroup = new objectGroup(3);
	jsonObject* correct_mapObject = new jsonObject(_name, cmoGroup);
	cmoGroup->addObject(correctnessGenerator());
	cmoGroup->addObject(hintGenerator());
	cmoGroup->addObject(msgGenerator());
	cmoGroup->addObject(npointsGenerator());
	cmoGroup->addObject(queuestateGenerator());
	return correct_mapObject;
};

object* correct_mapGenerator(jsonObject* answers)
{
	objectGroup* correct_mapGroup = new objectGroup(2);
	jsonObject* correct_map = new jsonObject("correct_map", correct_mapGroup);
	if (answers != nullptr)
	{
		objectPointer* ptr = answers->content->head;
		std::string ansName = "";
		if (ptr != nullptr)
		{
			ansName = ptr->obj->name;
			correct_map->content->addObject(correct_mapObjectGenerator(ansName));
			while (ptr->next != nullptr)
			{
				ptr = ptr->next;
				ansName = ptr->obj->name;
				correct_map->content->addObject(correct_mapObjectGenerator(ansName));
			};
		}
	};
	return correct_map;
};

object* gradeGenerator()//должно быть по-другому(зависит от answers и correct_map), но пока так
{
	intObject* grade = new intObject("grade", rand() % maxGrade);
	return grade;
};

object* max_gradeGenerator()//должно быть по-другому(зависит от answers и correct_map), но пока так
{
	intObject* max_grade = new intObject("max_grade", maxGrade);
	return max_grade;
};



object* problem_idGenerator()
{
	std::string problemName = "problem_";
	for (int i = 0; i < 15 + rand() % 10; ++i)
		problemName += (char)("A" + rand() % 26);
	stringObject* problem_id = new stringObject("problem_id", problemName);
	return problem_id;
};

object* doneGenerator()
{
	boolObject* done = new boolObject("done", rand() % 3 - 1);
	return done;
};

object* input_stateGenerator()//должно быть по-другому, но пока так
{
	objectGroup* inputStateGroup = new objectGroup(3);
	jsonObject* input_state = new jsonObject("input_state", inputStateGroup);
	return input_state;
};

object* seedGenerator()//информации о формате нет
{
	intObject* seed = new intObject("seed", 1);
	return seed;
};

object* student_answersGenerator()
{
	objectGroup* student_answersGroup = new objectGroup(3);
	jsonObject* student_answers = new jsonObject("student_answers", student_answersGroup);
	return student_answers;
};

object* stateGenerator()
{
	objectGroup* stateGroup = new objectGroup(2);
	jsonObject* state = new jsonObject("state", stateGroup);
	state->content->addObject(correct_mapGenerator(nullptr));
	state->content->addObject(doneGenerator());
	state->content->addObject(input_stateGenerator());
	state->content->addObject(seedGenerator());
	state->content->addObject(student_answersGenerator());
	return state;
};

object* submissionGenerator()//должна быть зависимость от correct_map, но пока так
{
	objectGroup* submissionGroup = new objectGroup(2);
	jsonObject* submission = new jsonObject("submission", submissionGroup);
	return submission;
};

object* successGenerator()//должно зависить от grade и max_grade, но пока так
{
	std::string isCorrect = "correct";
	if (rand() % 2 == 1)
		isCorrect = "in" + isCorrect;
	stringObject* success = new stringObject("success", isCorrect);
	return success;
};

object* eventGenerator()
{
	objectGroup* eventGroup = new objectGroup(1);
	jsonObject* event = new jsonObject("event", eventGroup);
	jsonObject* answers = answersGenerator();
	event->content->addObject(answers);
	event->content->addObject(attemptsGenerator());
	event->content->addObject(correct_mapGenerator(answers));
	event->content->addObject(gradeGenerator());
	event->content->addObject(max_gradeGenerator());
	event->content->addObject(problem_idGenerator());
	event->content->addObject(stateGenerator());
	event->content->addObject(submissionGenerator());
	event->content->addObject(successGenerator());
	return event;
};

object* event_sourceGenerator()//скорее всего связано с типом события, но для аналитики не важно
{
	const std::string sources[4] = { "browser","mobile","server","task" };
	stringObject* event_source = new stringObject("event_source", sources[rand() % 4]);
	return event_source;
};

object* event_typeGenerator()//вероятно важный параметр для предобработки, но не понятны возможные значения
{
	stringObject* event_type = new stringObject("event_type", "probken_check");
	return event_type;
};

object* hostGenerator()//скорее всего не значимый параметр
{
	stringObject* host = new stringObject("host", "precise64");
	return host;
};

object* refererGenerator()//скорее всего не значимый параметр
{
	stringObject* referer = new stringObject("referer", someStr);
	return referer;
};

object* accept_languageGenerator()//скорее всего не значимый параметр
{
	stringObject* accept_language = new stringObject("accept_language", someStr);
	return accept_language;
};

object* ipGenerator()//скорее всего не значимый параметр
{
	std::string ipStr = "";
	for (int i = 0; i < 3; ++i)
		ipStr += std::to_string(rand() % 256) + ".";
	ipStr += rand() % 256;
	stringObject* ip = new stringObject("ip", ipStr);
	return ip;
};

object* pageGenerator()//скорее всего не значимый параметр
{
	stringObject* page = new stringObject("page", someStr);
	return page;
};

object* timeGenerator()
{
	int year = minYear + rand() % (maxYear - minYear);
	int month = 1 + rand() % 12;
	int day = 1 + rand() % 28;
	int hour = rand() % 24;
	int minute = rand() % 60;
	int second = rand() % 60;
	std::string timeStr = "";
	timeStr += std::to_string(year) + "-";
	if (month < 10)
		timeStr += "0";
	timeStr += std::to_string(month) + "-";
	if (day < 10)
		timeStr += "0";
	timeStr += std::to_string(day) + "-";
	timeStr += "T";
	if (hour < 10)
		timeStr += "0";
	timeStr += std::to_string(hour) + ":";
	if (minute < 10)
		timeStr += "0";
	timeStr += std::to_string(minute) + ":";
	if (second < 10)
		timeStr += "0";
	timeStr += std::to_string(second) + ".";
	timeStr += "123456+00:00";
	stringObject* time = new stringObject("time", timeStr);
	return time;
};

object* usernameGenerator()//параметр важен, если является уникальным
{
	stringObject* username = new stringObject("username", someStr);
	return username;
};

objectGroup* mainGenerator()
{
	objectGroup* mainGroup = new objectGroup(0);
	object* agent = agentGenerator();
	mainGroup->addObject(agent);
	mainGroup->addObject(contextGenerator());
	mainGroup->addObject(eventGenerator());
	mainGroup->addObject(event_sourceGenerator());
	mainGroup->addObject(event_typeGenerator());
	mainGroup->addObject(hostGenerator());
	mainGroup->addObject(refererGenerator());
	mainGroup->addObject(accept_languageGenerator());
	mainGroup->addObject(ipGenerator());
	mainGroup->addObject(pageGenerator());
	mainGroup->addObject(timeGenerator());
	mainGroup->addObject(usernameGenerator());
	return mainGroup;
};

int main()
{
	std::ofstream output("log.txt");
	std::string outStr = "";
	for (int i = 0; i < 10000; ++i)
	{
		outStr = "\n\n";
		objectGroup* mainGroup = mainGenerator();
		mainGroup->signUp(outStr);
		output << outStr;
		//добавить деструкторы
	}
	return 0;
}