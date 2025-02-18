// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(1)
{
	if (mp < 0) throw " No Correct";
	MaxPower = mp;
	BitField = TBitField(MaxPower);
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(1)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{

}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem > MaxPower || Elem < 0) throw "No correct";
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem > MaxPower || Elem < 0) throw "No correct";
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem > MaxPower || Elem < 0) throw "No correct";
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	this->MaxPower = s.MaxPower;
	this->BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	//if (s.MaxPower != MaxPower) return 0;
	if (s.BitField != BitField) return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !operator==(s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int MP;
	if (MaxPower > s.MaxPower)
		MP = MaxPower;
	else
		MP = s.MaxPower;
	TSet t(MP);
	t.BitField = BitField | s.BitField;
	return t;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower || Elem < 0) throw "No correct";
	BitField.SetBit(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower || Elem < 0) throw "No correct";
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int m = MaxPower;
	if (m < s.MaxPower)
		m = s.MaxPower;
	TSet t(m);
	t.BitField = BitField & s.BitField;
	return t;
}

TSet TSet::operator~(void) // дополнение
{
	for (int i = 0; i< MaxPower; i++)
		if (BitField.GetBit(i) != 0)
			BitField.ClrBit(i);
		else
			BitField.SetBit(i);
	return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}
