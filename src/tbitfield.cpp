// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len<0) 
		(throw" Error created");
	this->BitLen = len;
	MemLen = (BitLen + 31) / 32;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	pMem[i] = 0;
	 
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() //Деструктор
{
	delete pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / 32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1 << (n % 32));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ( (n > -1 ) && (n < BitLen) )
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	else (throw "Error when set bit");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1 ) && (n < BitLen))
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
	else (throw "Error when set bit");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1 ) && (n < BitLen))
	return pMem[GetMemIndex(n)] & GetMemMask(n);
	else (throw "Error when set bit");
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen) {
		MemLen = bf.MemLen;
		if (pMem != NULL) delete pMem;
		pMem = new TELEM [MemLen];
	}
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int r = 1;
	if (BitLen != bf.BitLen) r = 0;
	else
		for(int i=0;i<MemLen;i++)
			if (pMem[i] != bf.pMem[i]) {
				r = 0;
				break;
			}
  return r;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int r = 1;
	if (BitLen == bf.BitLen) r = 0;
	else
		for (int i = 0; i<MemLen; i++)
			if (pMem[i] == bf.pMem[i]) {
				r = 0;
				break;
			}
	return r;

}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, l = BitLen;
	if (bf.BitLen > l) l = bf.BitLen;
	TBitField t(l);
	for (i = 0; i < MemLen; i++) t.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) t.pMem[i] |= bf.pMem[i];
	return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, l = BitLen;
	if (bf.BitLen > 1) l = bf.BitLen;
	TBitField t(l);
	for (i = 0; i < MemLen; i++) t.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) t.pMem[i] &= bf.pMem[i];
	return t;
}

TBitField TBitField::operator~(void) // отрицание
{
	int l = BitLen;
	TBitField t(l);
	for (int i = 0; i < MemLen - 1; i++)
		t.pMem[i] = (~pMem[i]);
	for (int i = 0; i < (BitLen % 32); i++) {
		if (!GetBit(i + ((MemLen - 1) * 32)))
			t.SetBit(i + ((MemLen - 1) * 32));
	}
	return t;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char ch;
	{
		do { istr >> ch; } while (ch != ' ') ;
		while (1) {
			istr >> ch;
			if (ch == '0') bf.ClrBit(i++);
			else if (ch == '1') bf.SetBit(i++);
			else break;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{ 
	for (int i = 0; i < bf.GetLength(); i++) {
		if (bf.GetBit(i))
			ostr << 1;
		else ostr << 0;
	}
	return ostr;
}
