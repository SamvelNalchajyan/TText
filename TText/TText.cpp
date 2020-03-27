#include "TText.h"

TTextLink::TTextLink(char* C, TTextLink* _pNext, TTextLink* _pDown)
{
	pNext = _pNext;
	pDown = _pDown;
	if (C == NULL)
	{
		str[0] = '\0';
	}
	else
	{
		strcpy(str, C);
	}
}

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
	pFirst = ReadRec(ifs);
}