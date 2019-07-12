#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

struct Person {
    string m_name;
    string m_surname;
    string m_email;
    unsigned int m_salary;
};




//bool comparenames()

/*
vector<Person> full;
                        vector<int> names;
                        vector<int> emails;
                        vector<int> salarys;
 */

    


class CPersonalAgenda {
private:
    vector<Person> full;
    vector<int> names;
    vector<int> emails;
   // vector<unsigned int> salarys;
    int peoplecount = 0;
   
int comparenames(const vector<Person> &ful,const vector<int> &iarr,int low,int hi,const string &name,const string &surname) const
    {
    if(hi >= low){
    int mid = low + (hi-low)/2;
    if (ful[iarr[mid]].m_surname == surname)
    {
        if(ful[iarr[mid]].m_name == name)
            return mid;
        
        else if (ful[iarr[mid]].m_name > name) return comparenames(ful,iarr,low,mid -1,name,surname);
            return comparenames(ful,iarr,mid+1,hi,name,surname);
    }
    
    else if (ful[iarr[mid]].m_surname > surname) return comparenames(ful,iarr,low,mid -1,name,surname);
    return comparenames(ful,iarr,mid+1,hi,name,surname);
    }
    return -1;
}



 
 int   compareemails(const vector<Person> &ful,const vector<int> &iarr,int low,int hi,const string &email)const
    {
    if(hi >= low){
    int mid = low+(hi-low)/2;
    if (ful[iarr[mid]].m_email < email)
    {
        return compareemails(ful,iarr,mid+1,hi,email);
    }
    else if (ful[iarr[mid]].m_email > email)
    {
        return compareemails(ful,iarr,low,mid -1,email);
    }
    else if (ful[iarr[mid]].m_email == email)
    {
        return mid;
    }
     }
    return -1;
    }


  int rankcount(const vector<Person> ful,const vector<int> iarr,int low,int hi,const unsigned int &salary,const string &email)
  {
      return 1;
  
  }
  int rankcount(const vector<Person> ful,const vector<int> iarr,int low,int hi,const unsigned int &salary,const string &name,const string &surname)
  {
      return 1;
  
  }
 int addpositionname(const vector<Person> ful,const vector<int> iarr,int low,int hi,const string &name,const string &surname)
 {
     int i=0;
     for (i=low;i<hi;i++)
     {

         if(ful[iarr[i]].m_surname > surname)
         {
             return i;
         }
         else if(ful[iarr[i]].m_surname == surname)
         {
             if(ful[iarr[i]].m_name > name) return i;
         }
     }
     return i;
 }
  int betteraddpositionname(const vector<Person> ful,const vector<int> iarr,int low,int hi,const string &name,const string &surname)
 {
      if(hi == low) 
      {
          if(ful[iarr[hi]].m_surname < surname)return hi+1;
      else if (ful[iarr[hi]].m_surname > surname) return hi;
      else if (ful[iarr[hi]].m_surname == surname)
        {
          if (ful[iarr[hi]].m_name < name) return hi+1;
          else if (ful[iarr[hi]].m_name > name) return hi;
        }
      }
      else if(hi > low){
    int mid = low+(hi-low)/2;
    if (ful[iarr[mid]].m_surname < surname)
    {
        return betteraddpositionname(ful,iarr,mid+1,hi,name,surname);
    }
    else if (ful[iarr[mid]].m_surname > surname)
    {
        if(mid == 0)mid ++;
        return betteraddpositionname(ful,iarr,low,mid -1,name,surname);
    }
    else if (ful[iarr[mid]].m_surname == surname)
    {
        if (ful[iarr[mid]].m_name < name) 
            return betteraddpositionname(ful,iarr,mid+1,hi,name,surname);
        
        
        else {
            if(mid == 0)mid++;
            return betteraddpositionname(ful,iarr,low,mid -1,name,surname);
        
        }
    }
    }
    else return -1;
    return -1;
 }
 int betteraddpositionemail(const vector<Person> ful,const vector<int> iarr,int low,int hi,const string &email)
 {
     if(hi == low) 
      {
          if(ful[iarr[hi]].m_email < email)return hi+1;
          else if (ful[iarr[hi]].m_email > email) return hi;
      }
     else if(hi > low){
    int mid = low+(hi-low)/2;
    if (ful[iarr[mid]].m_email < email)
    {
        return betteraddpositionemail(ful,iarr,mid+1,hi,email);
    }
    else if (ful[iarr[mid]].m_email > email)
    {
        if(mid == 0)mid++;
        return betteraddpositionemail(ful,iarr,low,mid -1,email);
    }
     }
    else return -1;
    return -1;
    }
 int addpositionemail(const vector<Person> &ful,const vector<int> &iarr,int low,int hi,const string &email)
 {
     int i=0;
    for (i=low;i<hi;i++)
     {
         if(ful[iarr[i]].m_email > email)
         {
             return i;
         }
     }
    return i;
 }
 int addpositionsalary(const vector<Person> &ful,const vector<unsigned int> &iarr,int low,int hi,const unsigned int &salary)
 {
     int i=0;
     for (i=low;i<hi;i++)
     {
         if(ful[iarr[i]].m_salary >= salary)
         {
             return i;
         }
     }
     return i;
 }
void nameshrink(vector<int> &names,int count,int what)
 {
    
     for(int i = 0;i<count;i++)
     {
         if(names[i] > what){
         //    //cout <<"::"<< names[i];
             names[i] = names[i]-1;
         //    //cout << names[i];
         }
     }
     
 }
void emailshrink(vector<int> &emails,int count,int what)
 {
     for(int i = 0;i<count;i++)
     {
         if(emails[i] > what){
            // //cout <<"::"<< emails[i];
             emails[i] = emails[i]-1;
            // //cout << emails[i];
         }
     }
 }
void salaryshrink(vector<unsigned int> &salarys,int count,int what)
 {
     for(int i = 0;i<count;i++)
     {
         if(salarys[i] > (unsigned int)what){
            // //cout <<"::"<< salarys[i];
             salarys[i] = salarys[i]-1;
           //  //cout << salarys[i];
         }
     }
 }
/*
int findlowsalary(const vector<Person> ful,const vector<int> iarr,int low,int hi,const unsigned int &salary)
{

    if(hi >= low){
    int mid = low+(hi-low)/2;
    if (ful[iarr[mid]].m_salary < salary)
    {
        return findlowsalary(ful,iarr,mid+1,hi,salary);
    }
    else if (ful[iarr[mid]].m_salary > salary)
    {
        return findlowsalary(ful,iarr,low,mid -1,salary);
    }
    else if (ful[iarr[mid]].m_salary == salary)
    {
        if(mid == 0) return mid;  //vracim souradnice na pole ve kterym *na techhle sour* je to co chci (rank)
        if(full[iarr[mid-1]].m_salary < salary)
        return mid;
        if(full[iarr[mid-1]].m_salary == salary)
            return findlowsalary(ful,iarr,low,mid -1,salary);
        return -1;
    }
     }
    return -1;

}
int findhisalary(const vector<Person> ful,const vector<int> iarr,int low,int hi,const unsigned int &salary)
{

    if(hi >= low){
    int mid = low+(hi-low)/2;
    if (ful[iarr[mid]].m_salary < salary)
    {
        return findlowsalary(ful,iarr,mid+1,hi,salary);
    }
    else if (ful[iarr[mid]].m_salary > salary)
    {
        return findlowsalary(ful,iarr,low,mid -1,salary);
    }
    else if (ful[iarr[mid]].m_salary == salary)
    {
        if(mid == peoplecount-1) return mid;  //vracim souradnice na pole ve kterym *na techhle sour* je to co chci (rank)
        if(full[iarr[mid+1]].m_salary > salary)
        return mid;
        if(full[iarr[mid+1]].m_salary == salary)
            return findlowsalary(ful,iarr,mid+1,hi,salary);
        return -1;
    }
     }
    return -1;

}
//*/

public:

    //public:

    CPersonalAgenda(void) {
        peoplecount = 0;
    };

    ~CPersonalAgenda(void) {

    };

    bool Add(const string & name,
            const string & surname,
            const string & email,
            unsigned int salary) {
       // //cout << peoplecount <<endl;
        
       // //cout <<endl<< "zde"<<person.m_name<<person.m_surname<<endl;
        if(peoplecount > 0){
        int lowname = comparenames(full,names,0,peoplecount-1,name,surname);
        if (lowname != -1) return 0;
        int lowemail = compareemails(full,emails,0,peoplecount-1,email);
        if (lowemail != -1) return 0;
       // int lowsalary = comparesalarys(full,salarys,0,peoplecount-1,salary,email);
       // if (lowname != -1) return 0;
       // //cout << peoplecount <<endl;
        
        
        //Person person = {name, surname, email, salary};
    //    int namepos = betteraddpositionname(full,names,0,peoplecount-1,name,surname);
    //    if(namepos == -1) return 0;
    //    cout << namepos<<endl;
        int namepos = addpositionname(full,names,0,peoplecount,name,surname);
    //    cout << namepos<<endl;
        
        
        
        
     //   int emailpos = betteraddpositionemail(full,emails,0,peoplecount-1,email);
      //  if(namepos == -1)return 0;
      //  cout << emailpos<<endl;
        int emailpos = addpositionemail(full,emails,0,peoplecount,email);
     //   cout << emailpos<<endl;
        //int salarypos = addpositionsalary(full,salarys,0,peoplecount,salary);
        
        int index = namepos;
         // //cout << index <<peoplecount<< endl;
        
        names.insert(names.begin()+index,peoplecount);
        /*
        if (index != peoplecount && peoplecount > 0) {
            if (index != peoplecount && full[index].m_surname == surname && full[index].m_name == name) {
                return 0;
            } else if (index > 0 && (index - 1) != peoplecount && full[index - 1].m_surname == surname && full[index - 1].m_name == name) {
                return 0;
            } else {
                names.insert(names.begin()+index,peoplecount); //full.push_back(person);
            }
        } else {

            names.insert(names.begin()+index,peoplecount);
        }
        */
        index = emailpos ; //email
        emails.insert(emails.begin()+index,peoplecount);
        
        /*
        if (peoplecount != 0) {
            if (index > 0 && (index - 1) != peoplecount && (full[index - 1].m_email == email)) {
                return 0;
            } else emails.insert(emails.begin()+index,peoplecount);
        } else emails.insert(emails.begin()+index,peoplecount);
      */ 
        /*       index = salarypos ; //salary
        salarys.insert(salarys.begin()+index,peoplecount);
        
   */     
        }
        else
        {
            names.push_back(peoplecount);
            emails.push_back(peoplecount);
          //  salarys.push_back(peoplecount);
        }
        Person person = {name, surname, email, salary};
        full.push_back(person);
        peoplecount++;
        return 1;

    }

    bool Del(const string & name,
            const string & surname) {
        Person person = {name, surname};
        int match = comparenames(full,names,0,peoplecount-1,name,surname);
        if(match < 0) return 0;
        int index = match;
        int what = names[index];
        if (full[what].m_name != name || full[what].m_surname != surname)return 0; // nenalezen
     //   //cout << "working w/h : " << full[what].m_name << full[what].m_surname << endl;
        person.m_email = full[what].m_email;
        person.m_salary = full[what].m_salary;
      //  //cout<<match<<endl;
        names.erase(match + names.begin());
        match = compareemails(full,emails,0,peoplecount-1,person.m_email);
        if(match < 0) return 0;
        emails.erase(match+emails.begin());
    //    match = findsalarys(full,salarys,0,peoplecount,person.m_salary,person.m_email);
    //    if(match < 0) return 0;
    //    salarys.erase(match+salarys.begin());
        for(int i = 0;i<peoplecount;i++)
     {
         if(names[i] > what){
           //  //cout <<"::"<< names[i];
             names[i] = names[i]-1;
           //  //cout << names[i];
         }
     }
  /*      for(int i = 0;i<peoplecount;i++)
     {
         if(salarys[i] > (unsigned int)what){
            // //cout <<"::"<< salarys[i];
             salarys[i] = salarys[i]-1;
            // //cout << salarys[i];
         }
     }
   */     for(int i = 0;i<peoplecount;i++)
     {
         if(emails[i] > what){
            // //cout <<"::"<< emails[i];
             emails[i] = emails[i]-1;
            // //cout << emails[i];
         }
     }
        
        /*nameshrink(names,peoplecount,what);
        emailshrink(emails,peoplecount,what);
        salaryshrink(salarys,peoplecount,what);*/
        peoplecount --;
        full.erase(what + full.begin());
       // //cout << peoplecount <<endl;
       // for (int i = 0; i < names.size(); i++)
         //               //cout << full[names[i]].m_name <<full[names[i]].m_surname<< ' ';
        /* if(names[index].m_surname == person.m_surname && names[index].m_name == person.m_name){
             person.m_email = names[index].m_email;
             person.m_salary = names[index].m_salary;
             names.erase(match);
              }
         else return 0; //nenalezen
         match = lower_bound(emails.begin(),emails.end(),person,compareemails());
         emails.erase(match);
         match = lower_bound(salarys.begin(),salarys.end(),person,comparesalarys());
         salarys.erase(match);
         */
        return 1;
    }
    bool Del(const string & email)
    {
    Person person = {" "," ",email};
 //   //cout << person.m_email;
    int match = compareemails(full,emails,0,peoplecount-1,email);
    if(match < 0) return 0;
    int what = emails[match];
    if (full[what].m_email != email)return 0; // nenalezen
        person.m_name = full[what].m_name;
        person.m_salary = full[what].m_salary;
        person.m_surname = full[what].m_surname;
        
        emails.erase(match + emails.begin());
        match = comparenames(full,names,0,peoplecount-1,person.m_name,person.m_surname);
        if(match < 0) return 0;
        names.erase(match+names.begin());
    //    match = findsalarys(full,salarys,0,peoplecount,person.m_salary,person.m_email);
    //    if(match < 0) return 0;
   //     salarys.erase(match+salarys.begin());
         
        for(int i = 0;i<peoplecount;i++)
     {
         if(names[i] > what){
           //  //cout <<"::"<< names[i];
             names[i] = names[i]-1;
           //  //cout << names[i];
         }
     }
/*        for(int i = 0;i<peoplecount;i++)
     {
         if(salarys[i] > (unsigned int)what){
            // //cout <<"::"<< salarys[i];
             salarys[i] = salarys[i]-1;
            // //cout << salarys[i];
         }
     }
  */      for(int i = 0;i<peoplecount;i++)
     {
         if(emails[i] > what){
            // //cout <<"::"<< emails[i];
             emails[i] = emails[i]-1;
            // //cout << emails[i];
         }
     }

        peoplecount --;
        full.erase(what + full.begin());
     /*   
        //cout<<endl;
        for (int i = 0; i < names.size(); i++)
               //cout << full[i].m_name <<full[i].m_surname<< ' ';
        //cout<<endl;
 for (int i = 0; i < names.size(); i++)
               //cout << full[names[i]].m_name <<full[names[i]].m_surname<< ' ';
       */ 
        return 1;
    
    }
    bool ChangeName(const string & email,
            const string & newName,
            const string & newSurname)
    {
        
    Person person = {" "," ",email};
   // //cout << person.m_email;
    
    int match = compareemails(full,emails,0,peoplecount-1,email);
    if(match < 0) return 0;
    int what = emails[match];
    match = comparenames(full,names,0,peoplecount-1,newName,newSurname);
        if(match != -1) return 0;
    if (full[what].m_email != email)return 0; // nenalezen
        person.m_name = full[what].m_name;
        person.m_surname = full[what].m_surname;
        person.m_salary = full[what].m_salary;
        
        match = comparenames(full,names,0,peoplecount-1,person.m_name,person.m_surname);
        if(match < 0) return 0;
        person.m_name = newName;
        person.m_surname = newSurname;
        names.erase(match + names.begin());
        
        int namepos = addpositionname(full,names,0,peoplecount-1,newName,newSurname);
   //     //cout << namepos<<"xdxdxdxdd";
        names.insert(namepos+names.begin(),what);
        full[what] = person;
  /*      //cout<<endl;
        for (int i = 0; i < names.size(); i++)
               //cout << full[i].m_name <<full[i].m_surname<< ' ';
        //cout<<endl;
 for (int i = 0; i < names.size(); i++)
               //cout << full[names[i]].m_name <<full[names[i]].m_surname<< ' ';
    
   * 
   * */    return 1;
        
    
    }
    bool ChangeEmail(const string & name,
            const string & surname,
            const string & newEmail)
    {
        
        
    Person person = {name,surname};
    int match = comparenames(full,names,0,peoplecount-1,name,surname);
    if(match < 0) return 0;
    int what = names[match];
    match = compareemails(full,emails,0,peoplecount-1,newEmail);
    if(match >= 0) return 0;
    if (full[what].m_name != name || full[what].m_surname != surname)return 0; // nenalezen
        person.m_salary = full[what].m_salary;
        person.m_email = full[what].m_email;
        
        match = compareemails(full,emails,0,peoplecount-1,person.m_email);
        if(match < 0) return 0;
        person.m_email = newEmail;
        emails.erase(match + emails.begin());
        
        int emailpos = addpositionemail(full,emails,0,peoplecount-1,newEmail);
        ////cout << emailpos<<"xdxdxdxdd";
        emails.insert(emailpos+emails.begin(),what);
        full[what] = person;
 /*       //cout<<endl;
        for (int i = 0; i < emails.size(); i++)
               //cout << full[i].m_email <<full[i].m_surname<< ' ';
        //cout<<endl;
 for (int i = 0; i < emails.size(); i++)
               //cout << full[emails[i]].m_name <<full[emails[i]].m_surname<<full[emails[i]].m_email<< ' ';
  */ 
       return 1;
    }
    bool SetSalary(const string & name,
            const string & surname,
            unsigned int salary)
    {
    Person person = {name,surname};
    int match = comparenames(full,names,0,peoplecount-1,name,surname);
    if(match < 0) return 0;
    int what = names[match];
    if (full[what].m_name != name || full[what].m_surname != surname)return 0; // nenalezen
        person.m_salary = salary;
        person.m_email = full[what].m_email;
        full[what] = person;
    /*    
        //cout<<endl;
        for (int i = 0; i < emails.size(); i++)
               //cout << full[i].m_salary <<full[i].m_surname<< ' ';
        //cout<<endl;
      */
       return 1;
    }
    bool SetSalary(const string & email,
            unsigned int salary)
    {
    
 //   //cout << person.m_email;
    int match = compareemails(full,emails,0,peoplecount-1,email);
    Person person = {" "," ",email};
    if(match < 0) return 0;
    int what = emails[match];
    if (full[what].m_email != email)return 0; // nenalezen
        person.m_name = full[what].m_name;
        person.m_surname = full[what].m_surname;
        person.m_salary = salary;
        full[what] = person;
     /*   
        //cout<<endl;
        for (int i = 0; i < emails.size(); i++)
               //cout << full[i].m_salary <<full[i].m_surname<< ' ';
        //cout<<endl;
     */
        
        return 1;
    
    }
    unsigned int GetSalary(const string & name,
            const string & surname) const
    {
    int match = comparenames(full,names,0,peoplecount-1,name,surname);
    if(match < 0) return 0;
    int what = names[match];
    if (full[what].m_name != name || full[what].m_surname != surname)return 0; // nenalezen
    return full[what].m_salary;
        
    }
    unsigned int GetSalary(const string & email) const //rip
    {
 //   //cout << person.m_email;
    int match = compareemails(full,emails,0,peoplecount-1,email);
    if(match < 0) return 0;
    int what = emails[match];
    if (full[what].m_email != email)return 0; // nenalezen
    return full[what].m_salary;
    }
    bool GetRank(const string & name,
            const string & surname,
            int & rankMin,
            int & rankMax)const
    {
    int match = comparenames(full,names,0,peoplecount-1,name,surname);
    if(match < 0) return 0;
    int what = names[match];
    if (full[what].m_name != name || full[what].m_surname != surname)return 0; // nenalezen
    unsigned int salary = full[what].m_salary;
    unsigned int salarycount = 0;
    unsigned int lowersalarycount = 0;
    
    for(int i = 0;i<peoplecount;i++)
    {
        if(full[i].m_salary == salary)salarycount ++;
        else if(full[i].m_salary < 
                salary)lowersalarycount ++;
    }
    
    rankMin = lowersalarycount;
    rankMax = lowersalarycount + (salarycount - 1);
    return 1;
    
    
    }
    bool GetRank(const string & email,
            int & rankMin,
            int & rankMax) const
    {
    
    int match = compareemails(full,emails,0,peoplecount-1,email);
    if(match < 0) return 0;
    int what = emails[match];
    if (full[what].m_email != email)return 0; // nenalezen
    
    unsigned int salary = full[what].m_salary;
    unsigned int salarycount = 0;
    unsigned int lowersalarycount = 0;
    
    for(int i = 0;i<peoplecount;i++)
    {
        if(full[i].m_salary == salary)salarycount ++;
        else if(full[i].m_salary < salary)lowersalarycount ++;
    }
    
    rankMin = lowersalarycount;
    rankMax = lowersalarycount + (salarycount - 1);
    return 1;
    
    
    }
    bool GetFirst(string & outName,
            string & outSurname) const
    {
        //cout << peoplecount;
        if(peoplecount == 0)return 0;
        int what = names[0];
        outName = full[what].m_name;
        outSurname = full[what].m_surname;
        
        
        return 1;
    
    }
    bool GetNext(const string & name,
            const string & surname,
            string & outName,
            string & outSurname) const
    {
        if(peoplecount < 2)return 0;
    int match = comparenames(full,names,0,peoplecount-1,name,surname);
    if(match < 0) return 0;
   // int what = names[match];
    if(match == peoplecount-1) return 0; //no next, match is already last
    int whatnext = names[match+1];
  //  if (full[what].m_name != name || full[what].m_surname != surname)return 0; // nenalezen
    outName = full[whatnext].m_name;
    outSurname = full[whatnext].m_surname;
        return 1;
    }

    // todo
};

#ifndef __PROGTEST__

int main(void) {
    string outName, outSurname;
    int lo, hi;

    CPersonalAgenda b1;
    assert ( !b1 . GetFirst ( outName, outSurname ));
    assert (! b1 . GetNext ( "", "2", outName, outSurname ));
    assert(b1 . Add("John", "Smith", "john", 30000));
    assert(b1 . GetSalary("John","Smith")==30000);
    
    assert ( b1 . GetFirst ( outName, outSurname ));
    assert (! b1 . GetNext ( "John", "Smith", outName, outSurname ));
    
    assert(b1 . Add("John", "Miller", "johnm", 35000));
    assert(b1 . GetSalary("John","Smith")==30000);
    assert(b1 . GetSalary("John","Miller")==35000);
    
    assert ( b1 . GetFirst ( outName, outSurname ));
    assert ( b1 . GetNext ( "John", "Miller", outName, outSurname ));
    
    assert(b1 . Add("Peter", "Smith", "peter", 23000));
    assert(b1 . GetSalary("Peter","Smith")==23000);
    assert(b1 . GetSalary("John","Miller")==35000);
    assert(b1 . GetSalary("John","Smith")==30000);
 
    assert(b1 . Add("John", "Smith2", "john2", 30000));
    assert(b1 . Add("John", "Miller2", "johnm2", 35000));
    assert(b1 . Add("Peter", "Smith2", "peter2", 23000));

    assert(b1 . Add("John", "Smith3", "john3", 30000));
    assert(b1 . Add("John", "Miller3", "johnm3", 35000));
    assert(b1 . Add("Peter", "Smith3", "peter3", 23000));

    assert(b1 . Del("John", "Miller2"));
    assert(b1 . Del("john3"));
    assert(b1 . ChangeName("john","Tvoje","Tata"));
    assert(b1 . ChangeEmail("Tvoje","Tata","seznam"));   //seznam nefunguje wtf //uz jo problem byl peoplecount
    assert(b1 . SetSalary("Tvoje","Tata",100));
    assert(b1 . SetSalary("seznam",42));
    
    assert(b1 . Add("lukas", "asdf", "nazdat", 999999));
    
     assert ( b1 . GetRank ( "nazdat", lo, hi ));
//    cout << lo <<" "<< hi;
    
    assert(b1 . GetSalary("lukas","asdf") == 999999);
    assert(b1 . GetSalary("Tvoje","Tata") == 42);
    assert(b1 . GetSalary("seznam") == 42);

    assert(b1 . Add("", "2", "", 0));
    assert(b1 . Add("John", "Miller4", "johnm4", 35000));
    assert(b1 . Add("Peter", "Smith4", "peter4", 23000));
    
    assert(b1 . Add("John", "Smith5", "john5", 30000));
    assert(b1 . Add("John", "Miller5", "johnm5", 35000));
    assert(b1 . Add("Peter", "Smith5", "peter5", 23000));
    
    assert(b1 . Add("John", "Smith6", "john6", 30000));
    assert(b1 . Add("John", "Miller6", "johnm6", 35000));
    assert(b1 . Add("Peter", "Smith6", "peter6", 23000));
    
    assert(b1 . Add("John", "Smith7", "john7", 30000));
    assert(b1 . Add("John", "Miller7", "johnm7", 35000));
    assert(b1 . Add("Peter", "Smi6", "peter7", 23000));
    
    assert(b1 . Add("John", "Smith7123", "john443", 30000));
    assert(b1 . Add("John", "Miller43", "johnm8", 35000));
    assert(b1 . Add("Peter", "th7", "peter8", 23000));
    assert(b1 . Add("AAA", "", "A", 1));
    assert(b1 . Add("A", "AA", "AA", 123));
    assert(b1 . Add("AaAAa", "", "aaaa", 3));
    assert(b1 . Add("AaaAa", "", "aAaa", 3));
    
    assert ( b1 . GetFirst ( outName, outSurname ));
    assert ( b1 . GetNext ( "", "2", outName, outSurname ));
    
    assert ( b1 . GetNext ( "", "2", outName, outSurname ));
    
    assert ( b1 . GetNext ( outName, outSurname, outName, outSurname ));
    assert ( b1 . GetNext ( outName, outSurname, outName, outSurname ));
    assert ( b1 . GetNext ( outName, outSurname, outName, outSurname ));
    assert ( b1 . GetNext ( outName, outSurname, outName, outSurname ));
    assert ( b1 . GetNext ( outName, outSurname, outName, outSurname ));
    
    assert ( b1 . GetRank ( "peter", lo, hi ));
   // cout << lo <<" "<< hi;
    assert ( b1 . GetRank ( "peter", lo, hi ));
    assert ( b1 . GetRank ( "peter", lo, hi ));
    assert ( b1 . GetRank ( "peter", lo, hi ));
    assert ( b1 . GetRank ( "peter", lo, hi ));
    assert ( b1 . GetRank ( "peter", lo, hi ));
    assert ( b1 . GetRank ( "peter", lo, hi ));
    assert ( b1 . GetRank ( "peter", lo, hi ));
    
    
    assert (! b1 . GetRank ( "","", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
    assert ( b1 . GetRank ( "John","Smith7123", lo, hi ));
  //  cout <<endl<< lo <<" "<< hi;
    
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "john2" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    assert ( b1 . GetSalary ( "John","Smith7123" ) ==  30000 );
    
    
    
    
//*/
    
 /*   assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( b1 . GetNext ( "John", "Smith", outName, outSurname )
             && outName == "Peter"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "Peter", "Smith", outName, outSurname ) );
    assert ( b1 . SetSalary ( "john", 32000 ) );
    assert ( b1 . GetSalary ( "john" ) ==  32000 );
    assert ( b1 . GetSalary ( "John", "Smith" ) ==  32000 );
    assert ( b1 . GetRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . GetRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetRank ( "johnm", lo, hi )
             && lo == 2
             && hi == 2 );
    assert ( b1 . SetSalary ( "John", "Smith", 35000 ) );
    assert ( b1 . GetSalary ( "John", "Smith" ) ==  35000 );
    assert ( b1 . GetSalary ( "john" ) ==  35000 );
    assert ( b1 . GetRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . GetRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetRank ( "johnm", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . ChangeName ( "peter", "James", "Bond" ) );
    assert ( b1 . GetSalary ( "peter" ) ==  23000 );
    assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
    
    
    
    assert ( b1 . GetSalary ( "Peter", "Smith" ) ==  0 );
    
    
    
    assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "James"
             && outSurname == "Bond" );
    assert ( b1 . GetNext ( "James", "Bond", outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . ChangeEmail ( "James", "Bond", "james" ) );
    assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . GetSalary ( "james" ) ==  23000 );
    assert ( b1 . GetSalary ( "peter" ) ==  0 );
    assert ( b1 . Del ( "james" ) );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 0
             && hi == 1 );
    assert ( b1 . Del ( "John", "Miller" ) );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . Del ( "john" ) );
    assert ( ! b1 . GetFirst ( outName, outSurname ) );
    assert ( b1 . Add ( "John", "Smith", "john", 31000 ) );
    assert ( b1 . Add ( "john", "Smith", "joHn", 31000 ) );
    assert ( b1 . Add ( "John", "smith", "jOhn", 31000 ) );

 // */
    
   /* 
    CPersonalAgenda b2;
    assert ( ! b2 . GetFirst ( outName, outSurname ) );
    assert ( b2 . Add ( "James", "Bond", "james", 70000 ) );
    assert ( b2 . Add ( "James", "Smith", "james2", 30000 ) );
    assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( ! b2 . Add ( "James", "Bond", "james3", 60000 ) );
    assert ( ! b2 . Add ( "Peter", "Bond", "peter", 50000 ) );
    assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
    
    
    assert ( ! b2 . SetSalary ( "Joe", "Black", 90000 ) );
    assert ( ! b2 . SetSalary ( "joe", 90000 ) );
    assert ( b2 . GetSalary ( "Joe", "Black" ) ==  0 );
    assert ( b2 . GetSalary ( "joe" ) ==  0 );
    assert ( ! b2 . GetRank ( "Joe", "Black", lo, hi ) );
    assert ( ! b2 . GetRank ( "joe", lo, hi ) );
    assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . Del ( "Joe", "Black" ) );
    assert ( ! b2 . Del ( "joe" ) );
    assert ( ! b2 . ChangeName ( "james2", "James", "Bond" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "james" ) );
    assert ( ! b2 . ChangeName ( "peter", "Peter", "Smith" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter" ) );
    assert ( b2 . Del ( "Peter", "Smith" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter2" ) );
    assert ( ! b2 . SetSalary ( "Peter", "Smith", 35000 ) );
    assert ( b2 . GetSalary ( "Peter", "Smith" ) ==  0 );
    assert ( ! b2 . GetRank ( "Peter", "Smith", lo, hi ) );
    assert ( ! b2 . ChangeName ( "peter", "Peter", "Falcon" ) );
    assert ( ! b2 . SetSalary ( "peter", 37000 ) );
    assert ( b2 . GetSalary ( "peter" ) ==  0 );
    assert ( ! b2 . GetRank ( "peter", lo, hi ) );
    assert ( ! b2 . Del ( "Peter", "Smith" ) );
    assert ( ! b2 . Del ( "peter" ) );
    assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( b2 . GetSalary ( "peter" ) ==  40000 );
    // */
    return 0;
}
#endif /* __PROGTEST__ */