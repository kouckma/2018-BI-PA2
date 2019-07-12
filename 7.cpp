#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>
using namespace std;

class CRect
{
  public:
                             CRect                         ( double            x,
                                                             double            y,
                                                             double            w,
                                                             double            h )
                             : m_X ( x ),
                               m_Y ( y ),
                               m_W ( w ),
                               m_H ( h )
    {
    }
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CRect     & x )
    {
      return os << '(' << x . m_X << ',' << x . m_Y << ',' << x . m_W << ',' << x . m_H << ')';
    }
    double                   m_X;
    double                   m_Y;
    double                   m_W;
    double                   m_H;
};
#endif /* __PROGTEST__ */
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                              CELEM
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Celem
{
public:
    int id;
    double x,y,w,h;
    double absx,absy,absw,absh;
public:
    virtual Celem* copy()
    {
        return NULL;
    }
    
    Celem(const int iid, const CRect & relPos){
        id = iid;
        x = relPos.m_X;
        y = relPos.m_Y;
        w = relPos.m_W;
        h = relPos.m_H;
    }
    Celem(const Celem & inelem){
        id = inelem.id;
        x = inelem.x;
        y = inelem.y;
        w = inelem.w;
        h = inelem.h;
    }
    Celem( int iid,double inx, double iny, double inw, double inh){
        id = iid;
        x = inx;
        y = iny;
        w = inw;
        h = inh;
    }
    
    void setabs(double inx, double iny, double inw, double inh)
    {
        absx=inx;
        absy=iny;
        absw=inw;
        absh=inh;
    }
    
    virtual Celem * getptr()
     {
         return NULL;
     }
 
   virtual ~Celem() {}
   
   virtual Celem * clone()const{
       return NULL;
   }
   
   virtual void print (ostream & os)const
{
    os << "["<< id <<"] " ;
}
   virtual void print (ostream & os,double absx, double absy,double absw,double absh,int type = 0)const
{
    os << "["<< id <<"] " ;
}
   virtual void print2 (ostream & os,double absx, double absy,double absw,double absh)const
{
//       cout<<absx<<endl<<absy<<endl<<absw<<endl<<absh<<endl;
       absx = absw*x + absx;
       absy = absh*y + absy;
       absw = absw*w;
       absh = absh*h;
    os << "("<<absx<<"," <<absy<<"," <<absw<<"," <<absh<<")" ;
}
    
};

//=======================================WINDOW============================================================
//=======================================WINDOW============================================================
//=======================================WINDOW============================================================
class CWindow
{
public:
CWindow ( const string    & title,
     const CRect & absPos )
{
    name = title;
    x=absPos.m_X;
    y=absPos.m_Y;
    w=absPos.m_W;
    h=absPos.m_H;
    size = 0;
}

CWindow (CWindow & src)
{
    size = src.size;
    name = src.name;
    x = src.x;
    y = src.y;
    w = src.w;
    h = src.h;
    for(int i=0; i<size;i++){
        Celem * newel = src.elements[i]->copy();
//        unique_ptr<Celem> elemptr; = make_unique<newel>();
        elements.push_back(newel);
    }
}
CWindow & operator = (CWindow & src)
{
    for(int i = 0; i<size; i++)
    {
        delete elements[i];
    }
    vector<Celem*> elements2;
    size = src.size;
    name = src.name;
    x = src.x;
    y = src.y;
    w = src.w;
    h = src.h;
    for(int i=0; i<size;i++){
        Celem * newel = src.elements[i]->copy();
        elements2.push_back(newel);
    }
    elements = elements2;
    return *this;
}
void SetPosition (const CRect & absPos)
{
    x=absPos.m_X;
    y=absPos.m_Y;
    w=absPos.m_W;
    h=absPos.m_H;
}

Celem * Search (int inid)
{
    for(int i= 0 ; i<size;i++)
    {
//        Celem * newel = elements[i]; //->clone()
        if(inid == elements[i]->id){
//            cout<<"start...."<<endl;
//            newel->print(cout,x,y,w,h);
//            cout<<"....end"<<endl;
//            CComboBox * box = elements[i]->clone();
            elements[i]->setabs(x,y,w,h);
            return elements[i]->getptr();
        }
    }
    return NULL;
}


CWindow & Add (const Celem & element){
    Celem * newel = element.clone();
    elements.push_back(newel);
    size ++;
    return *this;
}

friend ostream & operator << (ostream & os,const CWindow & window)
{
    os << "Window " << "\""<<
            window.name   <<"\" ("<< window.x <<","<< window.y <<","<< window.w <<","<<window.h<<")\n";
    for (int i = 0;i < window.size; i++)
    {
        if(i+1 < window.size)
        window.elements[i]->print(os,window.x,window.y,window.w,window.h,1);
        else
        window.elements[i]->print(os,window.x,window.y,window.w,window.h,2);
    }
    return os;
}
~CWindow(){
    for(int i = 0; i<size; i++)
    {
        delete elements[i];
    }

}
int getsize()
{
    return size;
}
    vector<Celem*> elements;
//    vector<unique_ptr<Celem>> elements;
//    unique_ptr<Celem> elemptr;
    double x;
    double y;
    double w;
    double h;
    int size;
    string name;
};

//=======================================BUTTO0000000000000000oN===============================
class CButton : public Celem
{
public:
CButton ( int               id,
     const CRect     & relPos,
     const string    & name ): Celem(id,relPos),m_name(name){
         
     }
     CButton( int inid,double inx,double iny,double inw,double inh,string inMname):Celem(inid,inx,iny,inw,inh),m_name(inMname){
    }
     Celem * getptr()
     {
         return this;
     }
     Celem * copy()
     {
         return new CButton(id,x,y,w,h,m_name);
     }
     
     Celem * clone()const
     {
         return new CButton(*this);
     }
     void print (ostream & os,double x, double y,double w,double h,int type = 0)const
    {
         if(type)os << "+- ";
             Celem::print(os);
        os << "Button \""<< m_name<<"\" ";
                Celem::print2(os,x,y,w,h);
                os<<"\n" ;
    }
private:
    string m_name;
};

class CInput : public Celem
{
public:
CInput  ( int               id,
     const CRect     & relPos,
     const string    & value ):Celem(id,relPos),value(value){
     }
     CInput( int inid,double inx,double iny,double inw,double inh,string invalue):Celem(inid,inx,iny,inw,inh),value(invalue){
    }
     CInput(const CInput & inelem):Celem(inelem.id,inelem.x,inelem.y,inelem.w,inelem.h),value(inelem.value){
    }
     Celem * getptr()
     {
         return this;
     }
     Celem * copy()
     {
         return new CInput(id,x,y,w,h,value);
     }
     Celem * clone()const
     {
         return new CInput(*this);
     }
     string GetValue(){
         return value;
     }
     void SetValue(const string str){
         value = str;
     }
     void print (ostream & os,double x, double y,double w,double h,int type = 0)const
    {
         if(type)os << "+- ";
             Celem::print(os);
        os << "Input \""<< value<<"\" ";
                Celem::print2(os,x,y,w,h);
                os<<"\n" ;
    }
// SetValue
// GetValue
public:
    string value;
     
};
class CLabel  :public  Celem
{
public:
CLabel  ( int               id,
     const CRect     & relPos,
     const string    & label ) : Celem(id, relPos),label(label){
     }
     
     CLabel( int inid,double inx,double iny,double inw,double inh,string inlabel):Celem(inid,inx,iny,inw,inh),label(inlabel){
         
    }
     Celem * getptr()
     {
         return this;
     }
     Celem * copy()
     {
         return new CLabel(id,x,y,w,h,label);
     }
     
     Celem * clone()const
     {
         return new CLabel(*this);
     }
     void print (ostream & os,double x, double y,double w,double h,int type = 0)const
    {
         if(type)os << "+- ";
             Celem::print(os);
        os << "Label \""<< label<<"\" ";
                Celem::print2(os,x,y,w,h);
                os<<"\n" ;
    }
private:
    string label;
};

class CComboBox : public Celem
{
public:
CComboBox ( int               id,
     const CRect     & relPos ) : Celem(id, relPos){
     }
private:
    vector<string> combobox;
    int index=0;
    int size = 0;
public:
    CComboBox( int inid,double inx,double iny,double inw,double inh):Celem(inid,inx,iny,inw,inh){
         
    }
//    --------------------------------------------------------------
    Celem * getptr()
     {
         return this;
     }
     Celem * copy()
     {
         CComboBox * boxik = new CComboBox(id,x,y,w,h);
         for(int i = 0 ; i<size;i++)
         boxik->Add(combobox[i]);
         boxik->SetSelected(index);
         return boxik;
     }
     void SetSelected(int id){
         index = id;
     }
     int GetSelected(){
         return index;
     }
     
    CComboBox & Add(const string & stringik)
    {
        combobox.push_back(stringik);
        size++;
        return *this;
    }
    Celem * clone()const
     {
         return new CComboBox(*this);
     }
     void print (ostream & os,double x, double y,double w,double h,int type = 0)const
    {
         if(type == 0)
         {
             Celem::print(os);
        os << "ComboBox ";
                Celem::print2(os,x,y,w,h);
                os<<"\n" ;
             for(int i = 0; i<size;i++)
                {
                    if(i==index)
                    {
                        os<<"+->"<<combobox[i]<<"<\n";
                    }
                    else{
                        os<<"+- "<<combobox[i]<<"\n";
                    }
                }
         }
         else{
             os << "+- ";
             Celem::print(os);
        os << "ComboBox ";
                Celem::print2(os,x,y,w,h);
                os<<"\n" ;
                for(int i = 0; i<size;i++)
                {
                    if(i==index)
                    {
                        if(type == 1)
                        os<<"|  +->"<<combobox[i]<<"<\n";
                        else
                        os<<"   +->"<<combobox[i]<<"<\n";
                    }
                    else{
                        if(type == 1)
                        os<<"|  +- "<<combobox[i]<<"\n";
                        else
                        os<<"   +- "<<combobox[i]<<"\n";
                    }
                }
         }
     }
};
    ostream & operator << (ostream & os,const Celem & element)
{
    element.print(os,element.absx,element.absy,element.absw,element.absh);
    return os;
}
// output operators

#ifndef __PROGTEST__
template <typename _T>
string toString ( const _T & x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int main ( void )
{
  assert ( sizeof ( CButton ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  assert ( sizeof ( CInput ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  assert ( sizeof ( CLabel ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  CWindow a ( "Sample window", CRect ( 10, 10, 600, 480 ) );
  a . Add ( CButton ( 1, CRect ( 0.1, 0.8, 0.3, 0.1 ), "Ok" ) ) . Add ( CButton ( 2, CRect ( 0.6, 0.8, 0.3, 0.1 ), "Cancel" ) );
  a . Add ( CLabel ( 10, CRect ( 0.1, 0.1, 0.2, 0.1 ), "Username:" ) );
  a . Add ( CInput ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ) );
  a . Add ( CComboBox ( 20, CRect ( 0.1, 0.3, 0.8, 0.1 ) ) . Add ( "Karate" ) . Add ( "Judo" ) . Add ( "Box" ) . Add ( "Progtest" ) );
 
//  cout << (CInput ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ));
//  cout << (CLabel ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ));
 
//  cout << toString(a);
 
  assert ( toString ( a ) ==
    "Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
    "+- [20] ComboBox (70,154,480,48)\n"
    "   +->Karate<\n"
    "   +- Judo\n"
    "   +- Box\n"
    "   +- Progtest\n"
  );
 
  CWindow b = a;
 
//  cout << toString( *b . Search ( 11 ) );
  
  
//  cout<< "ted B:"<<endl;
//  cout << toString(b);
//  cout << toString( *a . Search ( 20 ));
  assert ( toString ( *a . Search ( 20 ) ) ==
    "[20] ComboBox (70,154,480,48)\n"
    "+->Karate<\n"
    "+- Judo\n"
    "+- Box\n"
    "+- Progtest\n" );
  assert ( dynamic_cast<CComboBox &> ( *b . Search ( 20 ) ) . GetSelected () == 0 );
  dynamic_cast<CComboBox &> ( *b . Search ( 20 ) ) . SetSelected ( 3 );
  assert ( dynamic_cast<CInput &> ( *b . Search ( 11 ) ) . GetValue () == "chucknorris" );
  dynamic_cast<CInput &> ( *b . Search ( 11 ) ) . SetValue ( "chucknorris@fit.cvut.cz" );
  b . Add ( CComboBox ( 21, CRect ( 0.1, 0.5, 0.8, 0.1 ) ) . Add ( "PA2" ) . Add ( "OSY" ) . Add ( "Both" ) );
  assert ( toString ( b ) ==
    "Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
    "+- [20] ComboBox (70,154,480,48)\n"
    "|  +- Karate\n"
    "|  +- Judo\n"
    "|  +- Box\n"
    "|  +->Progtest<\n"
    "+- [21] ComboBox (70,250,480,48)\n"
    "   +->PA2<\n"
    "   +- OSY\n"
    "   +- Both\n" );
  assert ( toString ( a ) ==
    "Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
    "+- [20] ComboBox (70,154,480,48)\n"
    "   +->Karate<\n"
    "   +- Judo\n"
    "   +- Box\n"
    "   +- Progtest\n" );
//  cout << toString(a);
//  cout << toString(b);
  a = b;
  a . SetPosition ( CRect ( 20, 30, 640, 520 ) );
//  cout << toString(a);
  assert ( toString ( a ) ==
    "Window \"Sample window\" (20,30,640,520)\n"
    "+- [1] Button \"Ok\" (84,446,192,52)\n"
    "+- [2] Button \"Cancel\" (404,446,192,52)\n"
    "+- [10] Label \"Username:\" (84,82,128,52)\n"
    "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
    "+- [20] ComboBox (84,186,512,52)\n"
    "|  +- Karate\n"
    "|  +- Judo\n"
    "|  +- Box\n"
    "|  +->Progtest<\n"
    "+- [21] ComboBox (84,290,512,52)\n"
    "   +->PA2<\n"
    "   +- OSY\n"
    "   +- Both\n" );
  return 0;
}
#endif /* __PROGTEST__ */