/*==================================================== The Beginning of the Copyright Notice=================================================
' The AUTHOR of this file is Alexander Borisovich Prokopyev born on December 20,1977 resident at Uritskogo str., Kurgan, Russia
' More info can be found at the AUTHOR's website: http://www.aulix.com/resume
' Contact: alexander.prokopyev at aulix dot com
' Copyright (c) Alexander B. Prokopyev, 1995
' Copyright notice improved in 2021
' 
' All materials contained in this file are protected by copyright law.
' Nobody except the AUTHOR may alter or remove this copyright notice from copies of the content.
' 
' The AUTHOR explicitly prohibits to use this content by any method without a prior authentic written hand-signed permission of the AUTHOR.
'================================= The End of the Copyright Notice ========================================================================*/

/***************************************************************************
 *                     ����� ��� ������ �� ��������                        *
 *                       (c) ��������� �. 7.03.95                          *
 ***************************************************************************/


#include <stdlib.h>
#include <math.h>
//#include <ctype.h>
#include <iostream.h>
#include <conio.h>
//#include <windows.h>
#include <string.h>
#include <mem.h>
#if !defined(__STR_H)
  #define __STR_H

// ����� ��� ������ �� ��������
class Str
{
protected:
  char *place; // ��������� �� ������
  size_t place_len;
public:
  Str(const char *st="",size_t len_=unsigned(-1));  // ����������� ������������� �� char*
  Str(const Str &str);     // ���������� �����������
  Str& Str::operator =( const Str& sourceStr ); //�������� �����������
  virtual ~Str() { delete place; }

  size_t len() { return place_len-1; } // ����� ������

  const char* st() { return place; }

  void resize(size_t new_len);

  char& operator[](size_t ind); // ������ � �������� ������

  Str operator+(Str &str); // ������������ �����

  Str& operator+=(Str &str) // ������������� ������ ������ � ������
  {  return *this=*this+str; }

  Str mid(size_t beg, size_t count=unsigned(-1)); // ���������� count ��������, ������� � beg

  // �������� count ��������, ������� � beg �� str
  Str &mid(size_t beg, size_t count, Str &str);

// ������� ��������� ������ str � ������
  long inStr(size_t start, Str &str);

  // ����������� str, ������� � beg
  void ins(size_t beg,Str &str); // ��������� ������ str, ������� � beg

  // ������� �� ������ ������ count ��������, ������� � beg
  void del(size_t beg, size_t count);

  Str left(int count); // ���������� count ����� �������� ������ ������

  Str right(int count); // ���������� count ������ �������� ������ ������

  void lTrimSelf(); // ������� ����� �������

  void rTrimSelf(); // ������� ������ �������

  // ������� ������� ������ � �����
  void TrimSelf() { lTrimSelf(); rTrimSelf(); }

  //���������� ������ � ���������� ������ ���������
  Str lTrim();

  //���������� ������ � ���������� ��������� ���������
  Str rTrim();

  //���������� ������ � ���������� ������ � ������� ���������
  Str Trim();

  // ��������� ������ ������ �� ����� newSize, �������� ����� ������� padCh
  void lPadSelf(size_t newSize, char padCh=' ');

  // ��������� ������ ������ �� ����� newSize, �������� ������ ������� padCh
  void rPadSelf(size_t newSize, char padCh=' ');

  // ��������� ������ ������ �� ����� newSize,
  //   �������� ����������� ����� � ������ ������� padCh
  void padSelf(size_t newSize, char padCh=' ');

  // �� ��, ��� padLSelf, �� ����������� ������ ����������
  Str lPad(size_t newSize, char padCh=' ');

  // �� ��, ��� padLSelf, �� ����������� ������ ����������
  Str rPad(size_t newSize, char padCh=' ');

  // �� ��, ��� padCSelf, �� ����������� ������ ����������
  Str pad(size_t newSize, char padCh=' ');

// ����������� ������ ������ ������������� ����� value,
// ��� ndig - ����� ���������� �������� � ����������� ������
  Str &str(double value, unsigned short ndig=10);

  // ����������� ������ ������ � �����
  double val() { return atof(st()); }

  int words(); // ���������� ���-�� ���� � ������

  Str word(int needW); // ���������� needW-�� �����, ���� �� �������, �� ""

  static Str space(size_t count) { return string(count,' '); }
  static Str string(size_t count, char fillCh=' ');
};

istream& operator>>(istream& i, Str& str); // ������ ������ �� ������

#endif