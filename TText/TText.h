#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include "TStack.h"
#define LinkSize 81
#define MemSize 100

class TTextLink;
class TText;

struct TTextMem
{
	TTextLink* pFirst;
	TTextLink* pLast;
	TTextLink* pFree;
};

class TTextLink
{
public:
	TTextLink* pNext;
	TTextLink* pDown;
	char str[LinkSize];
	static TTextMem MemHead;
	int rec;

	TTextLink(char* C = NULL, TTextLink* _pNext = NULL, TTextLink* _pDown = NULL);
	~TTextLink() {};

	static void InitMem(int size = MemSize);
	static void PrintFreeLinks();
	void* operator new(size_t size);
	void operator delete(void* p);
	static void MemClean(TText& txt);
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
	void WriteRec(std::ofstream& ofs, TTextLink* p);
	void Write(std::string fn);
	void PrintRec(TTextLink* p);
	void Print();

	int Reset();
	int IsEnd();
	int GoNext();
};