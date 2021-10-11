// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) { throw - 1; }
   BitLen = len;
   MemLen = len / (sizeof(TELEM) * 8) + 1;
  pMem = new TELEM[this->MemLen];
   for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
}

TBitField::~TBitField()
{
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int size;
    size = sizeof(TELEM) * 8;
    int pos;
    pos = (n-1) * size;
    return pos;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int k;
    k = GetMemIndex(n);
    return 1 << k;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
}

void TBitField::ClrBit(const int n) // очистить бит
{
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= 0 && n < BitLen) {
       int r = pMem[GetMemIndex(n)];
        return r;
    }
    else throw - 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField C(BitLen);
    for (int i = 0; i++; i < BitLen) {
        if (pMem[i] == 1 && bf.pMem[i] == 1)
            C.pMem[GetMemIndex(i)] = 1;

        else C.pMem[GetMemIndex(i)] = 0;
    }
    return C;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField C(BitLen);
    for (int i = 0; i++; i < BitLen) {
        if (pMem[i] == 1)
            C.pMem[i] = 0;
        else C.pMem[i] = 1;
    }
    
    return C;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
