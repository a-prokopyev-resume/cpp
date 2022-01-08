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

#include "str_w.hpp"

Str::Str(const char *st, size_t len_)
{   if (st==0) st = "";
    if(len_==unsigned(-1)) len_=strlen(st);
    place_len = len_ + 1;
    place = new char[ place_len ];
    strncpy(place,st,len_);
    place[len_]='\0';
}

Str::Str( const Str& sourceStr )
{   place_len = sourceStr.place_len;
    place = new char[ place_len ];
    strcpy( place, sourceStr.place );
}

Str& Str::operator =( const Str& sourceStr )
{ if(place != sourceStr.place || place_len!=sourceStr.place_len )
  { if ( place_len != sourceStr.place_len )
    { delete place;
      place_len = sourceStr.place_len;
      place = new char[ place_len ];
    }
    strcpy(place, sourceStr.place);
  }
  return *this;
}

char& Str::operator[](size_t ind)
{ if (ind<len()) return *(place+ind);
  else throw "Выход за границы строки";
}

Str Str::operator+(Str &str)
{ int l=len()+str.len()+1;
  char *buf=new char[l];
  strcpy(buf, place);
  strcpy(buf+len(), str.place);
  Str res; delete res.place; res.place=buf; res.place_len=l;
  res.place[l-1]='\0';
  return res;
}

void Str::resize(size_t new_len)
{ if(new_len == len()) return;
  char * buf=new char[new_len+1];
  if(place_len<new_len+1)
  { strncpy(buf,place,place_len-1);
    for(size_t i=place_len-1;i<new_len;i++) buf[i]=' ';
  }
  else
    strncpy(buf,place,new_len);
  buf[new_len]='\0';
  delete place;
  place=buf;
  place_len=new_len+1;
}

Str Str::mid(size_t beg, size_t count) // возвращает count символов, начиная с beg
{ Str res;
  if(count==unsigned(-1)) count=len()-beg;
  if(count==0 && beg+count<=len()) return "";
  if(beg>=len() || count+beg > len()) throw "Выход за границы строки в Str::mid(size_t,size_t)";
  if(!place_len || !count) return res;
  res.resize(count);
  strncpy(res.place, place+beg, count);
  *(res.place+count)='\0';
  return res;
}

// Заменяет count символов, начиная с beg на str
Str &Str::mid(size_t beg, size_t count, Str &str)
{ if(beg>=len() || count+beg >len()) throw "Выход за границы строки в Str::mid(size_t,size_t)";
  return *this=mid(0,beg)+str.mid(0,count)+mid(beg+count);
}

// Позиция вхождения строки str в данную
long Str::inStr(size_t start, Str &str)
{ if(start>=len()) throw " Выход за границу строки в Str::inStr ";
  const char *p=strstr(st()+start, str.st());
  return p ? (const char *)p-st() : -1;
}

void Str::ins(size_t beg,Str &str)
{ if(beg>=len()) throw " Выход за границу строки в Str::ins";
  *this=mid(0,beg)+str+mid(beg); }

void Str::del(size_t beg, size_t count)
{ if(!count) return;
  if(beg>=len() || beg+count>len()) throw "Переданы неверные аргументы в Str::del()";
  *this=mid(0,beg)+mid(beg+count);
}


Str Str::left(int count)
{ if(count>len()) throw "Выход за конец строки в Str::left";
  return mid(0,count);
}

Str Str::right(int count)
{ if(count>len()) throw "Выход за конец строки в Str::right";
  return mid(len()-count,count);
}

void Str::lTrimSelf()
{ int i=0; while((*this)[i]==' ' && i<len()) i++;
  del(0,i); }

void Str::rTrimSelf()
{ int i=0; while((*this)[len()-1-i]==' ' && i<len()) i++;
  del(len()-i,i);
}
Str Str::lTrim() { Str str=*this; str.lTrimSelf(); return str; }

//Возвращает строку с удаленными пробелами пробелами
Str Str::rTrim() { Str str=*this; str.rTrimSelf(); return str; }

//Возвращает строку с удаленными левыми и правыми пробелами
Str Str::Trim() { return lTrim().rTrim(); }

Str Str::string(size_t count, char fillCh)
{ Str str; str.resize(count);
  setmem(str.place, count, fillCh);
  return str;
}

void Str::lPadSelf(size_t newSize, char padCh)
{ if(newSize<len()) *this=left(newSize);
  else ins(0,string(newSize-len(), padCh));
}

void Str::rPadSelf(size_t newSize, char padCh)
{ if(newSize<len())*this=left(newSize);
  else *this+=string(newSize-len(), padCh);
}

void Str::padSelf(size_t newSize, char padCh)
{ if(newSize<len()) *this=left(newSize);
  else
  { int lPad=(newSize-len())/2, rPad=newSize-len()-lPad;
    *this=string(lPad, padCh)+*this+string(rPad, padCh);
  }
}

// То же, что padLSelf, но дополненную строку возвращает
Str Str::lPad(size_t newSize, char padCh)
{ Str str=*this; str.lPadSelf(newSize, padCh); return str; }

// То же, что padLSelf, но дополненную строку возвращает
Str Str::rPad(size_t newSize, char padCh)
{ Str str=*this; str.rPadSelf(newSize, padCh); return str; }

// То же, что padCSelf, но дополненную строку возвращает
Str Str::pad(size_t newSize, char padCh)
{ Str str=*this;
  str.padSelf(newSize, padCh);
  return str; }

Str &Str::str(double value, unsigned short ndig)
{ int sign, decPoint;
  if (!(1<=ndig && ndig<=310))
    throw " Передано неверное количество цифр в Str::str ";
  if (value==+HUGE_VAL || value==-HUGE_VAL)
    throw " Передано неверное значение для преобразования в STr::str";
  *this=Str(fcvt(value, ndig, &decPoint, &sign));
  if(decPoint<=0) *this=Str("0,")+string(-decPoint,'0')+*this;
  else
    if(decPoint>ndig) *this+=Str(",")+string(decPoint,'0');
    else
      if(decPoint!=ndig) this->ins(decPoint,",");
  rPadSelf(ndig,'0');
  if(sign) ins(0,"-");
  if((*this)[len()-1]==',') { del(len()-1, 1); ins(0," "); }
  return *this;
}

istream& operator>>(istream& i, Str& str)
{ char ch;
  str.resize(0);
  i.flags(i.flags()&~istream::skipws);
  i>>ch;
  while(ch!='\n')
  { i.flags(i.flags()&~istream::skipws);
    str+=" "; str[str.len()-1]=ch; i>>ch;
  }
  return i;
}

/*
int Str::words()
{ int w=0;
  char prev=' ';
  for(size_t i=0; i<len(); i++)
    if(!isspace((*this)[i]) && isspace(prev))
    { w++; prev=(*this)[i]; }
    else
      if(!isspace(prev) && isspace((*this)[i])) prev=(*this)[i];
  return w;
}

Str Str::word(int needW)
{ char prev=' ';
  int f=0, w=0;  // flag, is set when the needed word begins
  Str str;
  for(size_t i=0; i<len(); i++)
    if(f)
      if(!isspace((*this)[i])) str+=(*this)[i];
      else return str;
    else
      if(!isspace((*this)[i]) && isspace(prev))
      { w++; prev=(*this)[i];
	if(w==needW) { f=1; str+=(*this)[i]; }
      }
      else
	if(!isspace(prev) && isspace((*this)[i])) prev=(*this)[i];
  return str; // empty str
}

*/

