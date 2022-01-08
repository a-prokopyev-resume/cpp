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
 *                     Класс для работы со строками                        *
 *                       (c) Прокопьев А. 7.03.95                          *
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

// Класс для работы со строками
class Str
{
protected:
  char *place; // Указатель на строку
  size_t place_len;
public:
  Str(const char *st="",size_t len_=unsigned(-1));  // Конструктор инициализации от char*
  Str(const Str &str);     // Коструктор копирования
  Str& Str::operator =( const Str& sourceStr ); //Оператор копирования
  virtual ~Str() { delete place; }

  size_t len() { return place_len-1; } // Длина строки

  const char* st() { return place; }

  void resize(size_t new_len);

  char& operator[](size_t ind); // Доступ к символам строки

  Str operator+(Str &str); // Конкатенация строк

  Str& operator+=(Str &str) // Присоединение другой строки к данной
  {  return *this=*this+str; }

  Str mid(size_t beg, size_t count=unsigned(-1)); // Возвращает count символов, начиная с beg

  // Заменяет count символов, начиная с beg на str
  Str &mid(size_t beg, size_t count, Str &str);

// Позиция вхождения строки str в данную
  long inStr(size_t start, Str &str);

  // Вставллляет str, начиная с beg
  void ins(size_t beg,Str &str); // Вставляет строку str, начиная с beg

  // Удаляет из данной строки count символов, начиная с beg
  void del(size_t beg, size_t count);

  Str left(int count); // Возвращает count левых символов данной строки

  Str right(int count); // Возвращает count правых символов данной строки

  void lTrimSelf(); // Удаляет левые пробелы

  void rTrimSelf(); // Удаляет правые пробелы

  // Удаляет пробелы справа и слева
  void TrimSelf() { lTrimSelf(); rTrimSelf(); }

  //Возвращает строку с удаленными левыми пробелами
  Str lTrim();

  //Возвращает строку с удаленными пробелами пробелами
  Str rTrim();

  //Возвращает строку с удаленными левыми и правыми пробелами
  Str Trim();

  // Дополняет данную строку до длины newSize, добавляя слева символы padCh
  void lPadSelf(size_t newSize, char padCh=' ');

  // Дополняет данную строку до длины newSize, добавляя справа символы padCh
  void rPadSelf(size_t newSize, char padCh=' ');

  // Дополняет данную строку до длины newSize,
  //   добавляя симметрично слева и справа символы padCh
  void padSelf(size_t newSize, char padCh=' ');

  // То же, что padLSelf, но дополненную строку возвращает
  Str lPad(size_t newSize, char padCh=' ');

  // То же, что padLSelf, но дополненную строку возвращает
  Str rPad(size_t newSize, char padCh=' ');

  // То же, что padCSelf, но дополненную строку возвращает
  Str pad(size_t newSize, char padCh=' ');

// Присваивает данной строке представление числа value,
// где ndig - общее количество символов в формируемой строке
  Str &str(double value, unsigned short ndig=10);

  // Преобразует данную строку в число
  double val() { return atof(st()); }

  int words(); // Возвращает кол-во слов в строке

  Str word(int needW); // Возвращает needW-ое слово, если не находит, то ""

  static Str space(size_t count) { return string(count,' '); }
  static Str string(size_t count, char fillCh=' ');
};

istream& operator>>(istream& i, Str& str); // Вводит строку из потока

#endif