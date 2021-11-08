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
   if (len % 32 == 0) MemLen = len / (sizeof(TELEM) * 8);
   MemLen = len / (sizeof(TELEM) * 8) + 1;
  pMem = new TELEM[MemLen];
   for (int i = 0; i < MemLen; i++) { 
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0) {
        throw - 2;
    }
    int index;
    index = n/(sizeof(TELEM) * 8);
    return index;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0) {
        throw -3;
    }
    int k;
    k = n % (sizeof(TELEM) * 8);
    return 1 << k;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n >= BitLen) || (n < 0)) throw - 4;
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n > BitLen) || (n < 0)) throw -5;
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > BitLen) {
        throw - 5;
    }
    int k = (pMem[GetMemIndex(n)] & GetMemMask(n));
    return k;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) 
        return *this;
    else  delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int cond1 = 1, cond2=1, cond3=1; 

    if (bf.BitLen != BitLen) cond1 = 0;
    if (MemLen != bf.MemLen) cond2 = 0;
    for (int i = 0; i < MemLen; i++) {
        if (bf.pMem[i] != pMem[i])
            cond3=0;
    }
    if ((cond1 == 1) && (cond2 == 1) && (cond3 == 1)) {
        return 1;
    }
    return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (*this == bf)
        return 0;
    return 1;  
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;

    TBitField NewBf(len);
    for (int i = 0; i < bf.MemLen; i++)
    {
        NewBf.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return NewBf;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;

    TBitField NewBf(len);
    for (int i = 0; i < bf.MemLen; i++)
    {
        NewBf.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return NewBf;
}

TBitField TBitField::operator~(void) // отрицание
{
    int len = BitLen;
    TBitField war(len);
    for (int i = 0; i < MemLen; i++)
        war.pMem[i] = ~pMem[i];
    int k = len % (sizeof(TELEM) * 8);
    int v = (1 << k) - 1;
    war.pMem[MemLen - 1] &= v;
    return war;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int len, val;
    cout << "Enter Bitlen: ";
    cin >> len;
    TBitField NewBf(len);
    cout << "Enter Bitfield: " << endl;
    for (int i = 0; i < NewBf.GetLength(); i++) {
        cin >> val;
        if (val == 1)
            NewBf.SetBit(i);
    }
    bf = NewBf;
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        if (bf.GetBit(i) == 0)
            ostr << 0;
        else ostr << 1;
    return ostr;
}
