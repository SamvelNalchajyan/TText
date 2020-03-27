#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include "TStack.h"
#define LinkSize 81

class TTextLink
{
public:
	TTextLink* pNext;
	TTextLink* pDown;
	char str[LinkSize];

	TTextLink(char* C = NULL, TTextLink* _pNext = NULL, TTextLink* _pDown = NULL);
};

class TText
{
private:
	TTextLink* pFirst;
	TTextLink* pCurr;
	TStack<TTextLink*> stack;
public:
	TText();
	~TText() {};

	void GoFirstLink();
	void GoDownLink();
	void GoNextLink();
	void GoPrevLink();

	void SetLine(std::string str);
	std::string GetLine();
	void InsNextLine(std::string str);
	void InsNextSection(std::string str);
	void InsDownLine(std::string str);
	void InsDownSection(std::string str);
	void DelNext();
	void DelDown();

	TTextLink* ReadRec(std::ifstream& ifs);
	void Read(std::string fn);
};