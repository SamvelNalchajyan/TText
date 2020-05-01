#include "TText.h"

static int rec;

TTextLink::TTextLink(char* C, TTextLink* _pNext, TTextLink* _pDown)
{
	pNext = _pNext;
	pDown = _pDown;
	rec = 0;
	if (C == NULL)
	{
		str[0] = '\0';
	}
	else
	{
		strcpy(str, C);
	}
}

void TTextLink::InitMem(int size)
{
	MemHead.pFirst = (TTextLink*) new char[sizeof(TTextLink) * size];
	MemHead.pFree = MemHead.pFirst;
	MemHead.pLast = MemHead.pFirst + (size - 1);
	TTextLink* pLink = MemHead.pFirst;
	for (int i = 0; i < size - 1; i++)
	{
		pLink->str[0] = '\0';
		pLink->pNext = pLink + 1;
		pLink++;
	}
	pLink->pNext = NULL;
}

void TTextLink::PrintFreeLinks()
{
	std::cout << "Free links" << std::endl;
	int count = 0;
	for (TTextLink* pLink = MemHead.pFree; pLink != NULL; pLink = pLink->pNext)
	{
		std::cout << pLink->str << std::endl;
		count++;
	}
	std::cout << count << std::endl;
}

void* TTextLink::operator new(size_t size)
{
	TTextLink* pLink = MemHead.pFree;
	if (MemHead.pFree)
	{
		MemHead.pFree = pLink->pNext;
	}
	return pLink;
}

void TTextLink::operator delete(void* p)
{
	TTextLink* pLink = (TTextLink*)p;
	pLink->pNext = MemHead.pFree;
	MemHead.pFree = pLink;
}

void TTextLink::MemClean(TText& txt)
{
	for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {
		std::string tmp = "&&&";
		tmp += txt.GetLine();
		txt.SetLine(tmp);
	}
	TTextLink* pLink;
	for (pLink = MemHead.pFree; pLink != NULL; pLink = pLink->pNext)
	{
		strcpy(pLink->str, "&&&");
	}
	for (pLink = MemHead.pFirst; pLink <= MemHead.pLast; pLink++)
	{
		if (std::strstr(pLink->str, "&&&") != NULL)
		{
			std::strcpy(pLink->str, pLink->str + 3);
		}
		else
		{
			delete pLink;
		}
	}
}

/*....................................................*/

TText::TText()
{
	pFirst = NULL;
	pCurr = NULL;
	stack.Clear();
}

void TText::GoFirstLink()
{
	pCurr = pFirst;
	stack.Clear();
}

void TText::GoDownLink()
{
	if (!pCurr)
	{
		throw -1;
	}
	if (!pCurr->pDown)
	{
		return;
	}
	stack.Push(pCurr);
	pCurr = pCurr->pDown;
}

void TText::GoNextLink()
{
	if (!pCurr)
	{
		throw -1;
	}
	if (!pCurr->pNext)
	{
		return;
	}
	stack.Push(pCurr);
	pCurr = pCurr->pNext;
}

void TText::GoPrevLink()
{
	if (!pCurr)
	{
		throw -1;
	}
	if (stack.IsEmpty())
	{
		return;
	}
	pCurr = stack.Pop();
}

void TText::SetLine(std::string str)
{
	if (!pCurr)
	{
		throw -1;
	}
	strcpy(pCurr->str, str.c_str());
}

std::string TText::GetLine()
{
	if (!pCurr)
	{
		throw -1;
	}
	return std::string(pCurr->str);
}

void TText::InsNextLine(std::string str)
{
	if (!pCurr)
	{
		throw -1;
	}
	TTextLink* tmp = new TTextLink;
	strcpy(tmp->str, str.c_str());
	tmp->pNext = pCurr->pNext;
	pCurr->pNext = tmp;
}

void TText::InsNextSection(std::string str)
{
	if (!pCurr)
	{
		throw -1;
	}
	TTextLink* tmp = new TTextLink;
	strcpy(tmp->str, str.c_str());
	tmp->pDown = pCurr->pNext;
	pCurr->pNext = tmp;
}

void TText::InsDownLine(std::string str)
{
	if (!pCurr)
	{
		throw -1;
	}
	TTextLink* tmp = new TTextLink;
	strcpy(tmp->str, str.c_str());
	tmp->pNext = pCurr->pDown;
	pCurr->pDown = tmp;
}

void TText::InsDownSection(std::string str)
{
	if (!pCurr)
	{
		throw - 1;
	}
	TTextLink* tmp = new TTextLink;
	strcpy(tmp->str, str.c_str());
	tmp->pDown = pCurr->pDown;
	pCurr->pDown = tmp;
}

void TText::DelNext()
{
	if (!pCurr)
	{
		throw -1;
	}
	if (!pCurr->pNext)
	{
		return;
	}
	TTextLink* tmp = pCurr->pNext;
	pCurr->pNext = tmp->pNext;
	delete tmp;
}

void TText::DelDown()
{
	if (!pCurr)
	{
		throw -1;
	}
	if (!pCurr->pDown)
	{
		return;
	}
	TTextLink* tmp = pCurr->pDown;
	pCurr->pDown = tmp->pNext;
	delete tmp;
}

TTextLink* TText::ReadRec(std::ifstream& ifs)
{
	TTextLink* pHead;
	TTextLink* p;
	TTextLink* tmp;
	pHead = p = NULL;
	char str[LinkSize];
	while (!ifs.eof())
	{
		ifs.getline(str, LinkSize - 1, '\n');
		if (str[0] == '}')
		{
			break;
		}
		else
		{
			if (str[0] == '{')
			{
				p->pDown = ReadRec(ifs);
			}
			else
			{
				tmp = new TTextLink(str);
				if (!pHead)
				{
					pHead = p = tmp;
				}
				else
				{
					p->pNext = tmp;
					p = p->pNext;
				}
			}
		}
	}
	return pHead;
}

void TText::Read(std::string fn)
{
	std::ifstream ifs(fn);
	rec = 0;
	pFirst = ReadRec(ifs);
}

void TText::WriteRec(std::ofstream& ofs, TTextLink* p)
{
	for (int i = 0; i < rec; i++)
	{
		ofs << " ";
	}
	ofs << p->str << std::endl;

	if (p->pDown)
	{
		rec++;
		ofs << '{' << std::endl;
		WriteRec(ofs, p->pDown);
		ofs << '}' << std::endl;
	}
	if (p->pNext)
	{
		WriteRec(ofs, p->pNext);
		rec++;
	}
	rec--;
}

void TText::Write(std::string fn)
{
	std::ofstream ofs(fn);
	rec = 0;
	WriteRec(ofs, pFirst);
}

void TText::PrintRec(TTextLink* p)
{
	for (int i = 0; i < rec; i++)
	{
		std::cout << "  ";
	}
	std::cout << p->str << std::endl;
	if (p->pDown)
	{
		rec++;
		PrintRec(p->pDown);

	}
	if (p->pNext) {
		PrintRec(p->pNext);
		rec++;
	}
	rec--;
}

void TText::Print()
{
	rec = 0;
	PrintRec(pFirst);
}

int TText::Reset()
{
	while (!stack.IsEmpty())
	{
		stack.Pop();
	}
	pCurr = pFirst;
	if (pCurr)
	{
		stack.Push(pCurr);
		if (pCurr->pNext)
		{
			stack.Push(pCurr->pNext);
		}
		if (pCurr->pDown)
		{
			stack.Push(pCurr->pDown);
		}
	}
	return IsEnd();
}

int TText::IsEnd()
{
	return stack.IsEmpty();
}

int TText::GoNext()
{
	if (!IsEnd())
	{
		pCurr = stack.Pop();
		if (pCurr != pFirst)
		{
			if (pCurr->pNext)
			{
				stack.Push(pCurr->pNext);
			}
			if (pCurr->pDown)
			{
				stack.Push(pCurr->pDown);
			}
		}
		return true;
	}
	return false;
}