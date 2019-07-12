#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;
class InvalidDateException
{
public:
    InvalidDateException(){
       // cout << "chybicka se vloudila"<<endl;
    
    }
};
#endif /* __PROGTEST__ */

// uncomment if your code implements the overloaded suffix operators
// #define TEST_LITERALS

//za tohle se stydim
//int globalstav = 0;
//vector<int> rotcev; // obsahuje na pozici [0] = pocet prvku;
//po resetu globalstavu se nastavi [0] na 0;
//vector<int> whatisit; // obsahuje typy cisel;
//na [0] je zase pocetprvku, analogicky reset = 0;
//



////wtf
//class Day
//{
//public:
//    Day(){
//    }
//   int getunit(){}
//};
class Day;
class Month;
class Year;

int    isleap(int year)
    {
        if(year%4 == 0)
        {
            if(year%100 == 0)
            {
                if(year%400 == 0)
                {
                if(year%4000 == 0)return 0;
                        return 1;
                }
                return 0;
            }
            return 1;
        }
        return 0;
    }

int leapmonthdays(int month)
{
    switch(month){
        case 1: return 31;
        case 2: return 29;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    }
    return 1;
}
int monthdays(int month)
{
    switch(month){
        case 1: return 31;
        case 2: return 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    }
    return 1;
}

void getdatedate()
{
//tohle bude dlouhy
    
}
void minusgetdateyear(int inyear, int &year,int &month,int &day)
{
    year -= inyear;
    //if(year < 1600) throw InvalidDateException();
}

void getdateyear(int inyear, int &year,int &month,int &day)
{
    year += inyear;
    if(year < 1600) throw InvalidDateException();
}
void minusgetdatemonth(int inmonth,int &year,int &month,int &day){
    int inyear = 0;
    
    if(inmonth >= month)
    {inmonth -= month;
    year -= 1;
    month = 12;
    
    inyear = inmonth/12;
    year -= inyear;
    month = 12 - (inmonth % 12);
    }
    else month -= inmonth;
}
void getdatemonth(int inmonth,int &year,int &month,int &day){
    int inyear = 0;
    inyear = (inmonth+month-1)/12;
 year += inyear;
 if(inyear)month += (inmonth-inyear*12);
 else month = inmonth+month;
}

int findmedays(int year)
{
    int a = (year-1)/4000;
    int b = (year-1)/400;
    int c = (year-1)/100;
    int d = (year-1)/4;
    
    int leapsofar = d-c+b-a;
    
//    leapsofar == year/4 - year/100 + year/400 -year/4000
//    1000-40+10-1== 969
//    
    
    int dayssofar = (leapsofar * 366) + ((year-leapsofar)*365);
    return dayssofar;

}

int findyearfromdays(int day)
{
    int a = (day-1)/1460969; //kolik je tam 4000-leti
    int b = (((day-1)%1460969)-1)/146097; //day - 1 nebo tak neco
    int c = (((((day-1)%1460969)-1)%146097)-1)/36524;
    int d = (((((((day-1)%1460969)-1)%146097)-1)%36524)-1)/1461;
    int wtf = ((((((((day-1)%1460969)-1)%146097-1)%36524)-1)%1461)-1)/365;
  //  int ret = (d-c+b-a);
    return a*4000 + b*400 + c*100 + d*4 + wtf;


}

void minusgetdateday(int inday, int &year,int &month,int &day)
{
int leap = isleap(year);
 //int pomocna = 0;
 int monthday;
 if(leap)monthday = leapmonthdays(month);
 else if(!leap)monthday = monthdays(month);
 
 if(day > inday){
     day = day - inday;
 }
 else{
     
            if(month == 1)
            {
                year -= 1;
                month = 12;
                inday -= day;
                day = 31;

            }
            else{
                if(leap)monthday = leapmonthdays(month-1);
        else if(!leap)monthday = monthdays(month-1);
        inday -= (day); //day-1
        month -= 1;
        day = monthday;
        }
     
            leap = isleap(year);
 for(int i = month;i>1;i--)
 {
     
 if(leap)monthday = leapmonthdays(i);
 else if(!leap)monthday = monthdays(i);
     
 if(monthday > inday){
     day = monthday - inday;
     month = i;
     inday = 0;
     break;
    }
 else{
     inday -= monthday;
 month -= 1;
 day = 31;
 }
 }
            
            //now at xxxx.31.1.
            if(inday != 0){
                
     if(monthday > inday){
     day = monthday - inday;
     inday = 0;
    }
     else{
         inday -= monthday;
         year -= 1;
         day = 31;
         month = 12;
         
         int daysofar = findmedays(year+1)-1; //pocet dnu zatim
     daysofar -= inday;
     int thing = findyearfromdays(daysofar);
     year = thing;
     int daysofarb = findmedays(thing);
     
     inday = daysofarb-daysofar;
     month = 1;
     day =1;
     
     while(1)
            {
                leap = isleap(year);
               if(leap)monthday = leapmonthdays(month);
              else if(!leap)monthday = monthdays(month);
               
               
               if(inday+1 == monthday+1)
               {
               if(month == 12)
                   {
                       year +=1;
                       month = 1;
                       day = 1;
                       inday -= monthday;
                       break;
                   }
                   else{
                       inday -= monthday;
                       month+=1;
                       day = 1;
                       break;
                   }
               }
               else if(inday + 1 > monthday){
                   if(month == 12)
                   {
                       year +=1;
                       month = 1;
                       day = 1;
                       inday -= monthday;
                   }
                   else{
                       inday -= monthday;
                       month+=1;
                   }
               }
               else{
                   day += inday;
                   break;
               }
            }
//     break;
     
     
            }
     }
     }
 
 
 
 
}


void getdateday(int inday, int & year,int & month,int & day)
{
 int leap = isleap(year);
// int pomocna = 0;
// dopocet do mesice
 int monthday;
 if(leap)monthday = leapmonthdays(month);
 else if(!leap)monthday = monthdays(month);
 if((inday+day) > monthday){
     inday -= monthday - day + 1;
     if(month == 12){
         month = 1;
         year += 1;
         day = 1;
     }
     else{
     month +=1;
     day = 1;
//     dopocet do roka
     leap = isleap(year);
     while(1)
     {
        if(leap)monthday = leapmonthdays(month);
       else monthday = monthdays(month);
        if(inday + 1 > monthday){
            if(month == 12)
            {
                year +=1;
                month = 1;
                day = 1;
                inday -= monthday;
                break;
            }
            else{
                inday -= monthday;
                month+=1;
            }
        }
        else{
            day += inday;
            inday = 0;
            break;
        }
     }
     }
     if(inday != 0){
     int daysofar = findmedays(year)+1; //pocet dnu zatim
     daysofar += inday;
     int thing = findyearfromdays(daysofar);
     int daysofarb = findmedays(thing)+1;
     year = thing;
     
    // cout << daysofar << " "<<year;
     inday = daysofar-daysofarb;
     
     
 //    cout << inday <<" hello "<<leap;
            
            while(1)
            {
                leap = isleap(year);
               if(leap)monthday = leapmonthdays(month);
              else monthday = monthdays(month);
               
               
               if(inday+1 == monthday+1)
               {
               if(month == 12)
                   {
                       year +=1;
                       month = 1;
                       day = 1;
                       inday -= monthday;
                       break;
                   }
                   else{
                       inday -= monthday;
                       month+=1;
                       day = 1;
                       break;
                   }
               }
               else if(inday + 1 > monthday){
                   if(month == 12)
                   {
                       year +=1;
                       month = 1;
                       day = 1;
                       inday -= monthday;
                   }
                   else{
                       inday -= monthday;
                       month+=1;
                   }
               }
               else{
                   day += inday;
                   break;
               }
            }
     }
 }
 else day += inday;
}

class Vektorek
{
    vector<int> rotcev;
    vector<int> typy;
    int n;
    
public:
    Vektorek(int value,int typecek)
    {
        n=0;
        rotcev.push_back(value);
        typy.push_back(typecek);
        n++;
    }
   void push(int value,int typecek)
    {
    
    rotcev.push_back(value);
        typy.push_back(typecek);
        n++;
    
    }
    int getn()
    {
        return n;
    }
    int gettype(int i)
    {
        return typy[i];
    }
    int getvalue(int i)
    {
        return rotcev[i];
    }
    

};



class Year
{
    int c_year;
    
public:
    Year(int inyear){
        c_year = inyear;
    }
    friend Vektorek operator +( Year x){
        Vektorek v(x.getunit(),1);
        return v;
    }
    friend Vektorek operator -(Year x){
        Vektorek v(x.getunit()*(-1),1);
        return v;
    }
    friend Vektorek operator +(Vektorek a,Year x){
        int unit = x.getunit();
        a.push(unit,1);
        return a;
    }
    friend Vektorek operator -(Vektorek a,Year x){
        int unit = x.getunit()*(-1);
        a.push(unit,1);
        return a;  
    }
    friend Vektorek operator -(const Day & ,const Year &);
    friend Vektorek operator +(const Day & ,const Year &);
    friend Vektorek operator -(const Month & ,const Year &);
    friend Vektorek operator +(const Month & ,const Year &);
    
    friend Vektorek operator +(Year a,Year x){
        Vektorek v(a.getunit(),1);
     v.push(x.getunit(),1);
    return v;
    }
    friend Vektorek operator -(Year a,Year x){
        Vektorek v(a.getunit(),1);
     v.push(x.getunit()*(-1),1);
    return v;
    }
    
int    getunit() const
    {return c_year;}
};



class Month
{
    int c_month;
    
public:
    Month(int inmonth){
        c_month = inmonth;
    }
    
    
    friend Vektorek operator +( Month x){
        Vektorek v(x.getunit(),2);
        return v;
    }
    friend Vektorek operator -(Month x){
        Vektorek v(x.getunit()*(-1),2);
        return v;
    }
    friend Vektorek operator -(const Year & ,const Month &);
    friend Vektorek operator +(const Year & ,const Month &);
    friend Vektorek operator -(const Day & ,const Month &);
    friend Vektorek operator +(const Day & ,const Month &);
//   friend Vektorek operator -(Day a,Month x){
//        Vektorek v(a.getunit(),3);
//        v.push(x.getunit()*(-1),2);
//        return v;
//    }
    friend Vektorek operator +(Vektorek a,Month x){
        int unit = x.getunit();
        a.push(unit,2);
        return a;
    }
    friend Vektorek operator -(Vektorek a,Month x){
        int unit = x.getunit()*(-1);
        a.push(unit,2);
        return a;  
    }
    friend Vektorek operator +(Month a,Month x){
        Vektorek v(a.getunit(),2);
     v.push(x.getunit(),2);
    return v;
    }
    friend Vektorek operator -(Month a,Month x){
        Vektorek v(a.getunit(),2);
     v.push(x.getunit()*(-1),2);
    return v;
    }
 int   getunit()const
    {return c_month;}
    
};



class Day
{
    int c_day;
    
public:
    Day(int inday){
        c_day = inday;
    }
    
    friend Vektorek operator +( Day x){
        Vektorek v(x.getunit(),3);
        return v;
    }
    friend Vektorek operator -(Day x){
        Vektorek v(x.getunit()*(-1),3);
        return v;
    }
    friend Vektorek operator +(Vektorek a,Day x){
        int unit = x.getunit();
        a.push(unit,3);
        return a;
    }
    friend Vektorek operator -(Vektorek a,Day x){
        int unit = x.getunit()*(-1);
        a.push(unit,3);
        return a;  
    }
    friend Vektorek operator +(Day a,Day x){
        Vektorek v(a.getunit(),3);
     v.push(x.getunit(),3);
    return v;
    }
    friend Vektorek operator -(Day a,Day x){
        Vektorek v(a.getunit(),3);
     v.push(x.getunit()*(-1),3);
    return v;
    }
    friend Vektorek operator -(const Year & ,const Day &);
    friend Vektorek operator +(const Year & ,const Day &);
    friend Vektorek operator -(const Month & ,const Day &);
    friend Vektorek operator +(const Month & ,const Day &);
    
  int  getunit() const
    {return c_day;}
};
//month
 Vektorek operator -(const Day & a,const Month & x)
{
     Vektorek v(a.getunit(),3);
     v.push(x.getunit()*(-1),2);
    return v;
}
 Vektorek operator +(const Day & a,const Month & x)
{
     Vektorek v(a.getunit(),3);
     v.push(x.getunit(),2);
    return v;
}
 Vektorek operator -(const Year & a,const Month & x)
{
     Vektorek v(a.getunit(),1);
     v.push(x.getunit()*(-1),2);
    return v;
}
 Vektorek operator +(const Year & a,const Month & x)
{
     Vektorek v(a.getunit(),1);
     v.push(x.getunit(),2);
    return v;
}
 // day
 Vektorek operator -(const Year & a,const Day & x)
{
     Vektorek v(a.getunit(),1);
     v.push(x.getunit()*(-1),3);
    return v;
}
 Vektorek operator +(const Year & a,const Day & x)
{
     Vektorek v(a.getunit(),1);
     v.push(x.getunit(),3);
    return v;
}
 Vektorek operator -(const Month & a,const Day & x)
{
     Vektorek v(a.getunit(),2);
     v.push(x.getunit()*(-1),3);
    return v;
}
 Vektorek operator +(const Month & a,const Day & x)
{
     Vektorek v(a.getunit(),2);
     v.push(x.getunit(),3);
    return v;
}
 //year
 Vektorek operator -(const Day & a,const Year & x)
{
     Vektorek v(a.getunit(),3);
     v.push(x.getunit()*(-1),1);
    return v;
}
 Vektorek operator +(const Day & a,const Year & x)
{
     Vektorek v(a.getunit(),3);
     v.push(x.getunit(),1);
    return v;
}
 Vektorek operator -(const Month & a,const Year & x)
{
     Vektorek v(a.getunit(),2);
     v.push(x.getunit()*(-1),1);
    return v;
}
 Vektorek operator +(const Month & a,const Year & x)
{
     Vektorek v(a.getunit(),2);
     v.push(x.getunit(),1);
    return v;
}

class CDate
{
private:
    int year,month,day;
    
 int   dayisvalid(int month,int day,int prestupnost)
    {
        if(prestupnost){
            
            if(month == 1 && day > 31) return 0;
            if(month == 2 && day > 29) return 0;
            if(month == 3 && day > 31) return 0;
            if(month == 4 && day > 30) return 0;
            if(month == 5 && day > 31) return 0;
            if(month == 6 && day > 30) return 0;
            if(month == 7 && day > 31) return 0;
            if(month == 8 && day > 31) return 0;
            if(month == 9 && day > 30) return 0;
            if(month == 10 && day > 31) return 0;
            if(month == 11 && day > 30) return 0;
            if(month == 12 && day > 31) return 0;
                
        }
        else{
        if(month == 1 && day > 31) return 0;
            if(month == 2 && day > 28) return 0;
            if(month == 3 && day > 31) return 0;
            if(month == 4 && day > 30) return 0;
            if(month == 5 && day > 31) return 0;
            if(month == 6 && day > 30) return 0;
            if(month == 7 && day > 31) return 0;
            if(month == 8 && day > 31) return 0;
            if(month == 9 && day > 30) return 0;
            if(month == 10 && day > 31) return 0;
            if(month == 11 && day > 30) return 0;
            if(month == 12 && day > 31) return 0;
        }
        
        return 1;
    }
    
    
  public:
      CDate(int inyear, int inmonth, int inday)
      {
          if(inyear < 1600 || inmonth > 12 || inmonth < 1 || inday < 1)throw InvalidDateException();
          int leap = isleap(inyear);
          int err = !dayisvalid(inmonth,inday,leap); // carefull about that "!"
          if(err)throw InvalidDateException();
          
          year = inyear;
          month = inmonth;
          day = inday;
      }
      
      friend std::ostream& operator<<(std::ostream& oss,CDate date)
    {
          if(date.month<10 && date.day <10)
              oss << date.year <<"-0"<<date.month<<"-0"<<date.day;
          else if(date.month<10 && date.day >=10)
              oss << date.year <<"-0"<<date.month<<"-"<<date.day;
          else if(date.month>=10 && date.day < 10)
              oss << date.year <<"-"<<date.month<<"-0"<<date.day;
          else
              oss << date.year <<"-"<<date.month<<"-"<<date.day;
          
          return oss;
    }
      
      CDate operator +(Year x)const
      {
          int unit = x.getunit();
          if(unit >= 0){
          int newyear = year, newmonth = month, newday = day;
          getdateyear(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
          else {
          unit= unit *(-1);
          int newyear = year, newmonth = month, newday = day;
          minusgetdateyear(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
      }
      CDate operator +(Month x)const
      {
          int unit = x.getunit();
          if(unit >= 0){
          int newyear = year, newmonth = month, newday = day;
          getdatemonth(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
          else{
          unit= unit *(-1);
          int newyear = year, newmonth = month, newday = day;
          minusgetdatemonth(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
//          int newyear = year, newmonth = month, newday = day;
//          int unit = x.getunit();
//          getdatemonth(unit,newyear,newmonth,newday);
//          return CDate(newyear,newmonth,newday);
      }
      CDate operator +(Day x)const
      {
          int unit = x.getunit();
          if(unit >= 0){
          int newyear = year, newmonth = month, newday = day;
          getdateday(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
          else {
          unit= unit *(-1);
          int newyear = year, newmonth = month, newday = day;
          minusgetdateday(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
//          int newyear = year, newmonth = month, newday = day;
//          int unit = x.getunit();
//          getdateday(unit,newyear,newmonth,newday);
//          return CDate(newyear,newmonth,newday);
      }
      CDate operator -(Year x)const
      {
          int unit = x.getunit();
          if(unit >= 0){
          int newyear = year, newmonth = month, newday = day;
          minusgetdateyear(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
          else {
          unit= unit *(-1);
          int newyear = year, newmonth = month, newday = day;
          getdateyear(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
      }
      CDate operator -(Month x)const
      {
          int unit = x.getunit();
          if(unit >= 0){
          int newyear = year, newmonth = month, newday = day;
          minusgetdatemonth(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
          else {
          unit= unit *(-1);
          int newyear = year, newmonth = month, newday = day;
          getdatemonth(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
//          int newyear = year, newmonth = month, newday = day;
//          int unit = x.getunit();
//          getdatemonth(unit,newyear,newmonth,newday);
//          return CDate(newyear,newmonth,newday);
      }
      CDate operator -(Day x)const
      {
          int unit = x.getunit();
          if(unit >= 0){
          int newyear = year, newmonth = month, newday = day;
          minusgetdateday(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
          else {
          unit= unit *(-1);
          int newyear = year, newmonth = month, newday = day;
          getdateday(unit,newyear,newmonth,newday);
          return CDate(newyear,newmonth,newday);
          }
//          int newyear = year, newmonth = month, newday = day;
//          int unit = x.getunit();
//          getdateday(unit,newyear,newmonth,newday);
//          return CDate(newyear,newmonth,newday);
      }
      
      int getyear()const
      {return year;}
      int getmonth()const
      {return month;}
      int getday()const
      {return day;}
      
      int operator -(CDate x)const
      {
          int newyear = year, newmonth = month, newday = day;
          int findaysl = 0, findaysr = 0;
          int ryear = x.getyear(),rmonth = x.getmonth(), rday = x.getday();
          
          int leap = isleap(ryear);
          for(int i= 1;i<rmonth;i++)
          {
              if(leap){
              findaysr += leapmonthdays(i);
              }
              else findaysr += monthdays(i);
          }
          
          findaysr+=rday;
          findaysr+= findmedays(ryear);
          
          leap = isleap(newyear);
          for(int i= 1;i<newmonth;i++)
          {
              if(leap){
              findaysl += leapmonthdays(i);
              }
              else findaysl += monthdays(i);
          }
          findaysl+=newday;
          
          findaysl+= findmedays(newyear);
//          cout <<" "<< findmedays(16)<<"  ";
          
          if (findaysl > findaysr) return findaysl - findaysr;
          else if (findaysl < findaysr) return (findaysr - findaysl)* (-1);
          else return 0;
      }
      
      int operator ==(CDate x)const
      {
          if(year == x.getyear() && month == x.getmonth() && day == x.getday())return 1;
          else return 0;
      }
      int operator !=(CDate x)const
      {
      if(year != x.getyear() || month != x.getmonth() || day != x.getday())return 1;
          else return 0;
      
      }
      int operator <(CDate x)const
      {
      if(year < x.getyear())
          return 1;
      else if(year == x.getyear()){
      if(month < x.month) return 1;
      else if (month == x.getmonth())
        {
          if(day < x.getday())return 1;
          else return 0;
        }
      else return 0;
      }
      else return 0;
      }
      
      void operator += (Day x)
      {   
          int y=year,m=month,d=day;
          int val = x.getunit();
          if(val >= 0)
          {
              getdateday(val,y,m,d);
          }
          else{
              val = val *(-1);
              minusgetdateday(val,y,m,d);
          }
          CDate(y,m,d);
          year = y;
          month =m;
          day = d;
      }
      void operator += (Month x)
      {   
          int y=year,m=month,d=day;
          int val = x.getunit();
          if(val >= 0)
          {
              getdatemonth(val,y,m,d);
          }
          else{
              val = val *(-1);
              minusgetdatemonth(val,y,m,d);
          }
          CDate(y,m,d);
          year = y;
          month =m;
          day = d;
      }
      void operator += (Year x)
      {   
          int y=year,m=month,d=day;
          int val = x.getunit();
          if(val >= 0)
          {
              getdateyear(val,y,m,d);
          }
          else{
              val = val *(-1);
              minusgetdateyear(val,y,m,d);
          }
          CDate(y,m,d);
          year = y;
          month =m;
          day = d;
      }
      
      void operator += (Vektorek x)
      {
          int y=year,m=month,d=day;
          int max = x.getn();
          for(int i=0;i<max;i++)
          {
              
              int type = x.gettype(i);
              int val = x.getvalue(i);
            //  cout << type << val <<" "<<i<<endl;
              if(val >= 0)
              {
                if(type == 1)
                {
                    getdateyear(val,y,m,d);
                }
                else if (type == 2)
                {
                    getdatemonth(val,y,m,d);
                }
                else if(type == 3)
                {
                    getdateday(val,y,m,d);
                }
              }
              else
              {
                  val = val * (-1);
                if(type == 1)
                {
                    minusgetdateyear(val,y,m,d);
                }
                else if (type == 2)
                {
                    minusgetdatemonth(val,y,m,d);
                }
                else if(type == 3)
                {
                    minusgetdateday(val,y,m,d);
                }
              }
             CDate wut(y,m,d);
          }
          year=y;month=m;day=d;
      }
      
      
      
      
      
      
      
    // operator(s) +
    // operator(s) -
    // operator ==
    // operator !=
    // operator <
    // operator(s) +=
  private:
    // todo
};

#ifndef __PROGTEST__
string             toString                                ( const CDate     & x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int                main                                    ( void )
{
    
  CDate tmp ( 2000, 1, 1 );

  assert ( toString ( CDate ( 2000, 1, 1 ) )  == "2000-01-01" );
 // assert ( CDate ( 2317, 9, 18 ) < CDate ( 137850, 7, 6 )   == true );
  
//  int x=findmedays(2018);
//  int c=findyearfromdays(369);
//  x=findmedays(c);
//  cout << x << endl;
 
//  CDate tmp ;
  assert ( toString ( CDate ( 2500, 12, 21 ) )  == "2500-12-21" );
  assert ( toString ( CDate ( 1685, 7, 11 ) )  == "1685-07-11" );


  try
  {
    tmp = CDate ( 1900, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2000, 2, 29 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 2004, 2, 29 ) )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 4000, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
// *
//
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 1 ) )  == "2019-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 7 ) )  == "2025-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 73 ) )  == "2091-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 3 ) )  == "2018-06-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 1 ) )  == "2018-04-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 285 ) )  == "2041-12-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 1 ) )  == "2018-03-16" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 12 ) )  == "2018-03-27" );
 
 
 // cout << toString ( CDate ( 2018, 3, 15 ) + Day ( 1234567 ) );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 1234567 ) )  == "5398-05-02" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 3 ) + Year ( 2 ) + Month ( 3 ) + Day ( 5 ) + Month ( 11 ) )  == "2021-05-23" );
 
 
  try
  {
    tmp = CDate ( 2000, 2, 29 ) + Year ( 300 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 3, 30 ) + Month ( 11 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
 
 // cout << toString ( CDate ( 2001, 2, 20 ) + Day ( 9 ) );
  assert ( toString ( CDate ( 2001, 2, 20 ) + Day ( 9 ) )  == "2001-03-01" );
 
  assert ( toString ( CDate ( 2000, 1, 1 ) + Day ( 28 ) + Month ( 1 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 1999, 1, 1 ) + Year ( 1 ) + Day ( 28 ) + Month ( 1 ) )  == "2000-02-29" );

   // cout << toString ( CDate ( 2001, 1, 1 ) + Day ( 1095 ) + Day ( 28 ) + Month ( 1 ));

    assert ( toString ( CDate ( 2001, 1, 1 ) + Day ( 1095 ) + Day ( 28 ) + Month ( 1 ) )  == "2004-02-29" );
 
 
  try
  {
    tmp = CDate ( 2001, 1, 1 ) + Day ( 28 ) + Month ( 1 ) + Day ( 1095 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
 
    try
  {
    tmp = CDate ( 2000, 1, 1 ) + Day ( 28 ) + Month ( 1 ) + Year ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
//  */
    tmp = CDate ( 2000, 1, 1 );
  assert ( toString ( tmp - Year ( 5 ) + Month ( 2 ) )  == "1995-03-01" );
  assert ( toString ( tmp ) == "2000-01-01" );
 // cout << ( CDate ( 2000, 1, 1 ) - Year ( 1 ) - Month ( 3 ) - Day ( 10 ) );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 1 ) - Month ( 3 ) - Day ( 10 ) )  == "1998-09-21" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 2 ) - Month ( -3 ) + Day ( -10 ) )  == "1998-03-22" );
//  cout <<toString ( CDate ( 2000, 1, 1 ) + Day ( 59 ) - Month ( 1 ) - Year ( 2 ));
  assert ( toString ( CDate ( 2000, 1, 1 ) + Day ( 59 ) - Month ( 1 ) - Year ( 2 ) )  == "1998-01-29" );
 
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + Day ( 59 ) - Year ( 2 ) - Month ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
 
 
  tmp = CDate ( 2000, 1, 1 );
//  tmp +=  - Year ( 2 );
  tmp +=  - Year ( 2 ) - Month ( -3 ) + Day ( -10 );
 // cout << tmp << endl;
  assert ( toString ( tmp ) == "1998-03-22" );
  tmp = CDate ( 2000, 1, 1 );
  tmp += Day ( 59 ) - Month ( 1 ) - Year ( 2 );
//  cout << tmp << endl;
  assert ( toString ( tmp ) == "1998-01-29" );
 
  try
  {
    tmp = CDate ( 2000, 1, 1 );
    tmp += Day ( 59 ) - Year ( 2 ) - Month ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
 
  tmp = CDate ( 2018, 3, 15 ) + Day ( -3 );
  assert ( toString ( tmp ) == "2018-03-12" );
  assert ( !( CDate ( 2018, 3, 15 ) == CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) != CDate ( 2000, 1, 1 ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) == CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) != CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( 1 ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( 1 ) != CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( 1 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( -1 ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) != CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) < CDate ( 2018, 3, 15 ) );
  //cout<<( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ));
  assert ( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ) == 6648 );
  assert ( CDate ( 2000, 1, 1 ) - CDate ( 2018, 3, 15 ) == -6648 );
  assert ( CDate ( 2018, 3, 15 ) + Year ( 3 ) + Month ( -18 ) - CDate ( 2000, 1, 1 ) == 7197 );
  assert ( CDate ( 5398, 5, 2 ) - CDate ( 2018, 3, 15 ) == 1234567 );
//  CDate ( 1900, -1, 1 );
  
  tmp = CDate ( 1601, 12, 31 ) ;
//  tmp += Day ( 2 ) + Day(1)+Day(2);
//  cout << tmp;
  tmp +=  Day (1) ;
  cout << tmp;
 
//  */
#ifdef TEST_LITERALS
 
  assert ( toString ( CDate ( 2000, 1, 1 ) )  == "2000-01-01" );
  assert ( toString ( CDate ( 2500, 12, 21 ) )  == "2500-12-21" );
  assert ( toString ( CDate ( 1685, 7, 11 ) )  == "1685-07-11" );
  try
  {
    tmp = CDate ( 1900, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2000, 2, 29 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 2004, 2, 29 ) )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 4000, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_year )  == "2019-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 7_years )  == "2025-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 73_years )  == "2091-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 3_months )  == "2018-06-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_month )  == "2018-04-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 285_months )  == "2041-12-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_day )  == "2018-03-16" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 12_days )  == "2018-03-27" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1234567_days )  == "5398-05-02" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 3_days + 2_years + 3_months + 5_days + 11_months )  == "2021-05-23" );
  try
  {
    tmp = CDate ( 2000, 2, 29 ) + 300_years;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 3, 30 ) + 11_months;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2001, 2, 20 ) + 9_days )  == "2001-03-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + 28_days + 1_month )  == "2000-02-29" );
  assert ( toString ( CDate ( 1999, 1, 1 ) + 1_year + 28_days + 1_month )  == "2000-02-29" );
  assert ( toString ( CDate ( 2001, 1, 1 ) + 1095_days + 28_days + 1_month )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 2001, 1, 1 ) + 28_days + 1_month + 1095_days;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + 28_days + 1_month + 1_year;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  assert ( toString ( tmp - 5_years + 2_months )  == "1995-03-01" );
  assert ( toString ( tmp ) == "2000-01-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - 1_year - 3_months - 10_days )  == "1998-09-21" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - 2_years - ( -3_months ) + ( -10_days ) )  == "1998-03-22" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + 59_days - 1_month - 2_years )  == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + 59_days - 2_years - 1_month;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  tmp +=  - 2_years - ( -3_months ) + ( -10_days );
  assert ( toString ( tmp ) == "1998-03-22" );
  tmp = CDate ( 2000, 1, 1 );
  tmp += 59_days - 1_month - 2_years;
  assert ( toString ( tmp ) == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 );
    tmp += 59_days - 2_years - 1_month;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2018, 3, 15 ) + ( -3_days );
  assert ( toString ( tmp ) == "2018-03-12" );
  assert ( !( CDate ( 2018, 3, 15 ) == CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) != CDate ( 2000, 1, 1 ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) == CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) != CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + 1_day == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + 1_day != CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) + 1_day < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + ( -1_day ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + ( -1_day ) != CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) + ( -1_day ) < CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ) == 6648 );
  assert ( CDate ( 2000, 1, 1 ) - CDate ( 2018, 3, 15 ) == -6648 );
  assert ( CDate ( 2018, 3, 15 ) + 3_years + ( -18_months ) - CDate ( 2000, 1, 1 ) == 7197 );
  assert ( CDate ( 5398, 5, 2 ) - CDate ( 2018, 3, 15 ) == 1234567 );
  ostringstream oss;
  oss << setfill ( 'x' ) << left << hex << CDate ( 2000, 1, 1 ) << ' ' << setw ( 10 ) << 65536;
  assert ( oss . str () == "2000-01-01 10000xxxxx" );
#endif /* TEST_LITERALS */
  return 0;
}
#endif /* __PROGTEST__ */