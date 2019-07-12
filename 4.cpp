#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CMail
{
  private:
      char * cfrom;
      char * cto;
      char * cbody;
      CMail * thiss = this;
      //deep copies given array
     char * copystringarr(const char * arr)
     {
     int size = strlen(arr);
     char* outarray = new char[size + 1];
     memcpy(outarray,arr,size);
     outarray[size] = '\0';
     return outarray;
     }
  public:
 CMail                           ( const char      * from,
                                 const char      * to,
                                 const char      * body )
 {
     cfrom = copystringarr(from);
     cto = copystringarr(to);
     cbody = copystringarr(body);
 }
 char &getcfrom()const
 {
     return *cfrom;
 }
 char &getcto()const
 {
     return *cto;
 }
 char & getcbody()const
 {
     return *cbody;
 }
 CMail * getptr()const
 {
     return thiss;
 }
    bool                     operator ==                   ( const CMail     & x ) const
    {
        int det = strcmp(cfrom, x.cfrom);
        int det2 = strcmp(cto, x.cto);
        int det3 = strcmp(cbody, x.cbody);
        if(!det && !det2 && !det3)
            {
            return 1;
            }
        return 0;
    }
   ~ CMail                         (  )
 {
       delete[] cfrom;
       delete[] cto;
       delete[] cbody;
 }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class SharedPointer
{
private:
    CMail *** ptrs; // array of pointers to pointers to pointers to mails
    int ptrscount=0;
    int countref=0;
    int mailcount=0;
public:
    SharedPointer()
    {
        ptrs = new CMail**[25];
        countref = 0;
    }
    ~SharedPointer() //must be freed in subone
    {
    }
    void setcountemails(int cnt)
    {
        mailcount = cnt;
    }
    
    void addmailcount()
    {
        mailcount++;
    }
    void insertptr(CMail ** ptr)
    {
        ptrs[ptrscount] = ptr;
        ptrscount++;
    }
    int getptrscount()
    {
        return ptrscount;
    }
    CMail ** getlastmail() // getting the newest/current pointer
    {
        CMail ** concretemail = ptrs[ptrscount-1];
        return concretemail;
    }
    void addone()
    {
        countref++;
    }
    void subone() //basically destructor but dependent on count of outside references
    {
        countref--;
        if(countref <= 0 )
        {
            int count = ptrscount-1;
            CMail ** tmpdel = ptrs[count];
            for(int i = 0;i<mailcount;i++){
                delete tmpdel[i]->getptr();
            }
            delete[] ptrs[count];
            delete[]ptrs;
            if(this)
            delete this;
        }
    }
   SharedPointer * getptr()
   {
       return this;
   }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CMailIterator 
{
private:
    SharedPointer* sharedobj ;
    CMail ** carr;
    int pos = 0;
    int size =0;
    
  public:
      CMailIterator(SharedPointer* shared,int insize) // iterator gets soft reference to form/to array and size which it is allowed to read
      {
          if(shared)
          shared->addone();
          size = insize;
          sharedobj = shared;
          pos = 0;
          if(insize != 0)
          carr = sharedobj->getlastmail();
      
      }
      ~CMailIterator() // if iterator dies, it needs to let the shared pointer know
      {
          if(size != 0)
          sharedobj->subone();
          
      }
 operator bool                 ( void ) const // checks if iterator position is valid
    {
     if (pos >= size)
         return 0;
     else
         return 1;
    }
    bool                     operator !                    ( void ) const// checks if iterator position is invalid
    {
        if ( pos >= size)
         return 1;
     else
         return 0;
    }
    const CMail            & operator *                    ( void ) const // returns mail on position
    {
        return *sharedobj->getlastmail()[pos];
    }
    CMailIterator          & operator ++                   ( void )//increments position
    {
        if( pos < size)
        carr = sharedobj->getlastmail();
        pos++;
        return *this;
    }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Mailbox
{
public:
    int fromsize = 0;
    int fromcount = 0;
    int tosize = 0;
    int tocount = 0;
    CMail ** fromarr=nullptr;
    CMail ** toarr=nullptr;
    Mailbox * ptr=this;
    char * email;
    SharedPointer * sharefrom=nullptr;
    SharedPointer * shareto=nullptr;
    int sharefromex = 0;
    int sharetoex = 0;
    
    void createfromptr()//creates reference to sharedpointer
    {
        sharefrom = new SharedPointer();
        sharefrom->addone();
        sharefromex = 1;
    }
    void createtoptr()//creates reference to sharedpointer
    {
        shareto = new SharedPointer();
        shareto->addone();
        sharetoex = 1;
    }
    Mailbox()
    {
        sharefrom=nullptr;
        shareto=nullptr;
        fromsize = 0;
        fromcount = 0;
        tosize = 0;
        tocount = 0;
        sharefromex = 0;
        sharetoex = 0;
    }
    ~Mailbox()//already handled elsewhere
    {
    }
    Mailbox * getptr()const //gets pointer to Mailbox
        {
              return ptr;
        }
};
class CMailServer 
{
private:
    Mailbox ** accounts; // array of pointers for mailboxes // (pointers because of binary search)
    int accountcount=0;
    int accountsize=0;
public: void writeout() //for debugging
    {
    cout <<endl<<endl;
    for(int i = 0;i<accountcount;i++)
    {
        cout<<accounts[i]->email<<"; ;"<<accountcount<<";";
    }
    for(int i = 0;i<accountcount;i++)
    {
        cout <<endl<<"FROM mails of: "<<
                accounts[i]->email<<
                accounts[i]->fromcount<<endl;
                for(int x = 0;x<accounts[i]->fromcount;x++)
            {
                cout<<accounts[i]->fromarr[x]->getcfrom()<<
                        accounts[i]->fromarr[x]->getcto()<<"#";
            }
        cout<<endl;
        cout <<endl<<"TO mails of: "<<accounts[i]->email<<accounts[i]->tocount<<endl;
                for(int x = 0;x<accounts[i]->tocount;x++)
            {
                cout<<accounts[i]->toarr[x]->getcfrom()<<
                        accounts[i]->toarr[x]->getcto()<<"#";
            }
        cout<<endl;
    }
    }
private:   
    void addmail(const char* email, Mailbox * box)//adds new instance of Mailbox
    {
        int added = 0;
        Mailbox * tmpbox = nullptr;
        Mailbox *tmpbox2 =nullptr;
        
        if(strcmp(email,accounts[accountcount-1]->email) > 0) //solves first email problem (which may already be solved)
        {
            accounts[accountcount]=box->getptr();
        }
        else{
            int index = lowerboundsearchemail(email,0,accountcount-1); // performs binary search for new email position
            for(int i = index;i<accountcount;i++) //inserts new email, incerements position of emails to the left by one
            {
                if(added)
                {
                    tmpbox2 = accounts[i]->getptr();
                    accounts[i] = tmpbox->getptr();
                    tmpbox = tmpbox2->getptr();
                }
                else
                {
                    if(strcmp(accounts[i]->email, email) > 0)
                    {
                        tmpbox = accounts[i]->getptr();
                        accounts[i] = box->getptr();
                        added = 1;
                    }
                }
            }
            accounts[accountcount]=tmpbox->getptr();//inserting last email
        }
    }
    
    int lowerboundsearchemail(const char* email,int low,int hi)// performs binary search for new email position
    {
//        cout << "x"; // for debugging
        if(hi <= low){
            if(strcmp(accounts[hi]->email,email)<0)return hi+1;
            else if(strcmp(accounts[hi]->email,email)>0)return hi;
        }
        if(hi > low){
            int mid = low+(hi-low)/2;
            if (strcmp(accounts[mid]->email,email) < 0)
            {
                return lowerboundsearchemail(email,mid+1,hi);
            }
            else if (strcmp(accounts[mid]->email,email) > 0)
            {
                if(mid == 0)mid++;
                return lowerboundsearchemail(email,low,mid-1);
            }
        }
//                cout<<low<<";"<<hi;   // for debugging
            return -1;
    }
    
    int binarysearchemail(const char* email,int low,int hi)// performs binary search of email, if it doesnt find it, returns '-1'
    {
        if(hi >= low){
    int mid = low+(hi-low)/2;
    if (strcmp(accounts[mid]->email,email) < 0)
    {
        return binarysearchemail(email,mid+1,hi);
    }
    else if (strcmp(accounts[mid]->email,email) > 0)
    {
        return binarysearchemail(email,low,mid-1);
    }
    else if (strcmp(accounts[mid]->email,email) == 0)
    {
        return mid;
    }
     }
    return -1;
    }
    
    
    int searchmails(const char* emailm)//searches for emails, if database contains 0 emails, return '-1'
    {
        int index = 0;
        if(accountcount==0){
            return -1;
        }
        else  index = binarysearchemail(emailm,0,accountcount-1); // performs binary search of email, if it doesnt find it, returns '-1'
        return index;
    }
    SharedPointer * findmailpointer(const char * emailm,int type,int & arrsize)const // searches for email, then returns its pointer to shared reference
    {
    for(int i=0;i<accountcount;i++)
        {
            if(strcmp(accounts[i]->email, emailm)==0){
                if(type){
                    arrsize = accounts[i]->fromcount;
                    return accounts[i]->sharefrom;
                }
                else{
                    arrsize = accounts[i]->tocount;
                    return accounts[i]->shareto;   
                }
            }
    }
        return nullptr;    
    }
void    addemail(const char * memail) //creates and inserts new Mailbox instance
     {
        
        
        if(accountsize == 0){
        accounts = new Mailbox*[2];
        accountsize = 2;
        }
        else if(accountsize <= accountcount+1){
            Mailbox ** tmpacc = new Mailbox*[accountsize*2];
            copy(accounts,accounts+accountcount,tmpacc);
            delete []accounts;
            accounts = tmpacc;
            accountsize = accountsize * 2;
        }
        Mailbox * box = new Mailbox();
        int size = strlen(memail);
        char * em = new char[size+1];
        memcpy(em,memail,size);
        em[size] = '\0';
        box->email=em;
        if(accountcount == 0)
        {
            accounts[accountcount] = box;
        }
        else addmail(memail,box); // partly-binary adds email
        accountcount++;
     }
    void addfrom(const CMail     & m,int index)//inserts new CMail at end of inbox mail array of [index]
    {
        int size = accounts[index]->fromsize;
        int count = accounts[index]->fromcount;
        
        if(size == 0){
        accounts[index]->fromarr = new CMail*[2];
        accounts[index]->createfromptr();
        accounts[index]->sharefrom->insertptr(accounts[index]->fromarr);
        size = 2;
        accounts[index]->fromsize = size;
        }
        else if(size <= count+1){
            CMail ** tmpfromarr = new CMail*[size*2];
            copy(accounts[index]->fromarr,accounts[index]->fromarr+count,tmpfromarr);
            delete[] accounts[index]->fromarr;
            accounts[index]->fromarr = tmpfromarr;
            accounts[index]->sharefrom->insertptr(accounts[index]->fromarr);
            accounts[index]->fromsize = size * 2;
        }
    CMail * n= new CMail(&m.getcfrom(),&m.getcto(),&m.getcbody());
    accounts[index]->fromarr[count]= n;
    accounts[index]->fromcount = count + 1;
    accounts[index]->sharefrom->addmailcount();
    }
    void addto(const CMail     & m,int index)//inserts new CMail at end of outbox mail array of [index]
    {
        int size = accounts[index]->tosize, count = accounts[index]->tocount;
        
        if(size == 0){
        accounts[index]->toarr = new CMail*[2];
        accounts[index]->createtoptr();
        accounts[index]->shareto->insertptr(accounts[index]->toarr);
        size = 2;
        accounts[index]->tosize = size;
        }
        else if(size <= count+1){
            CMail ** tmptoarr ;
            tmptoarr = new CMail*[size*2];
            copy(accounts[index]->toarr,accounts[index]->toarr+count,tmptoarr);
            delete[] accounts[index]->toarr;
            accounts[index]->toarr = tmptoarr;
            accounts[index]->shareto->insertptr(accounts[index]->toarr);
            accounts[index]->tosize = size * 2;
        }
        CMail * n = new CMail(&m.getcfrom(),&m.getcto(),&m.getcbody());
    accounts[index]->toarr[count] = n;
    accounts[index]->tocount = count + 1;
    accounts[index]->shareto->addmailcount();
    }
    
    void fill(const CMailServer & src) // copies server instance to this array
{
        if(src.getcount() == 0)
        {
        accountcount = src.getcount();
        accountsize = src.getsize();
        }
    else{
        accountcount = src.getcount();
        accountsize = src.getsize();
        accounts = new Mailbox*[accountsize];
        Mailbox ** tmpaccounts = src.getaccounts();
        for(int i = 0;i<accountcount;i++)
        {
            Mailbox * box = new Mailbox();
            int size=strlen(tmpaccounts[i]->email);
            char * em = new char[size+1];
            memcpy(em,tmpaccounts[i]->email,size);
            em[size] = '\0';
            box->email=em;
            accounts[i]=box;
            int mailcnt=tmpaccounts[i]->fromcount;
            accounts[i]->fromcount=mailcnt;
            if(mailcnt)accounts[i]->fromarr = new CMail* [mailcnt];
            
            if(mailcnt){
            accounts[i]->createfromptr();
            accounts[i]->sharefrom->insertptr(accounts[i]->fromarr);
            accounts[i]->sharefrom->setcountemails(mailcnt);
            }
            accounts[i]->fromsize = mailcnt;
            for(int x = 0;x<mailcnt;x++)
            {
                char * frarr = &tmpaccounts[i]->fromarr[x]->getcfrom();
                char * toarr = &tmpaccounts[i]->fromarr[x]->getcto();
                char * boarr = &tmpaccounts[i]->fromarr[x]->getcbody();
                CMail * mail = new CMail(frarr,toarr,boarr);
                accounts[i]->fromarr[x] = mail;
            }
            mailcnt=tmpaccounts[i]->tocount;
            if(mailcnt)accounts[i]->toarr = new CMail* [mailcnt];
            accounts[i]->tosize = mailcnt;
            
            if(mailcnt){
            accounts[i]->createtoptr();
            accounts[i]->shareto->insertptr(accounts[i]->toarr);
            accounts[i]->shareto->setcountemails(mailcnt);
            }
            accounts[i]->tocount= mailcnt;
            for(int x = 0;x<mailcnt;x++)
            {
                char * frarr = &tmpaccounts[i]->toarr[x]->getcfrom();
                char * toarr = &tmpaccounts[i]->toarr[x]->getcto();
                char * boarr = &tmpaccounts[i]->toarr[x]->getcbody();
                CMail * mail = new CMail(frarr,toarr,boarr);
                accounts[i]->toarr[x] = mail;
            }
        }
    }
}
    
  public:
      
      int getcount()const
 {
     return accountcount;
 }
    int getsize()const
 {
     return accountsize;
 }
    Mailbox **getaccounts()const
 {
     return accounts;
 }
      
    CMailServer ( void )
    {
        accountcount = 0;
        accountsize = 0;
    }
    CMailServer ( const CMailServer & src ) //copies from source server
        {
                fill(src);
        }
    CMailServer  & operator = ( const CMailServer & src )   //copies from source server and deletes previous instance
    {
        if(&src == this)
        {
            return *this;
        }
        
        if(accountcount > 0){
        for(int i = 0;i<accountcount;i++)
        {
            delete[] accounts[i]->email;
            if(accounts[i]->fromcount)
                accounts[i]->sharefrom->subone();
            if(accounts[i]->tocount)
                accounts[i]->shareto->subone();
            delete accounts[i]->getptr();
        }
        delete[] accounts;
        }
        fill(src);
        return *this;
    }
    ~CMailServer ( void )//server destructor
    {
        if(accountcount > 0){
        for(int i = 0;i<accountcount;i++)
        {
            delete[] accounts[i]->email;
            if(accounts[i]->fromcount)
                accounts[i]->sharefrom->subone();
            if(accounts[i]->tocount)
                accounts[i]->shareto->subone();
            delete accounts[i]->getptr();
        }
        delete[] accounts;
        }
    }
    void SendMail ( const CMail     & m )//adds mails to inbox or outbox, or creates email boxes if they dont exist
{
    int idfrom = searchmails(&m.getcfrom());
    if(idfrom == -1)
    {
    //make new email
       addemail(&m.getcfrom());
            
       idfrom = searchmails(&m.getcfrom());
    }
    //insert to fromarr
    addfrom(m,idfrom);
    
    int idto = searchmails(&m.getcto()); 
    if(idto == -1)
    {
    //make new mail
       addemail(&m.getcto());
       idto = searchmails(&m.getcto()); 
    }
    //insert to toarr
    addto(m,idto);  
}
CMailIterator            Outbox                        ( const char      * email ) const
{
    int arrsize = 0;
    SharedPointer* a=findmailpointer(email,1,arrsize); // 1 indicates that return should be outbox
    // searches for email, then returns its pointer to shared reference
    return CMailIterator(a,arrsize); //creates new iterator with reference to shared pointer and allowed read size
}
CMailIterator            Inbox                         ( const char      * email ) const
{
    int arrsize = 0;
    SharedPointer* a = findmailpointer(email,0,arrsize); // 0 indicates that return should be inbox 
    // searches for email, then returns its pointer to shared reference
    return CMailIterator(a,arrsize);//creates new iterator with reference to shared pointer and allowed read size
}
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef __PROGTEST__
int main ( void )
{
  char from[100], to[100], body[1024];

  assert ( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "peter", "progtest deadline" ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "progtest deadline", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "john", "progtest deadline" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "progtest deadline", "john" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "john", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "peter", "john" ) ) );
  CMailServer s0;
//  CMailServer s90;
  s0 . SendMail ( CMail ( "john", "peter", "some important mail" ) );
//  s0 . SendMail ( CMail ( "john", "peterr", "some important mail" ) );
  strncpy ( from, "john", sizeof ( from ) );
//  s0.writeout();

  strncpy ( to, "thomas", sizeof ( to ) );
  strncpy ( body, "another important mail", sizeof ( body ) );
  s0 . SendMail ( CMail ( from, to, body ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "alice", sizeof ( to ) );
  strncpy ( body, "deadline notice", sizeof ( body ) );
  s0 . SendMail ( CMail ( "john", "alice", "deadline notice" ) );
  s0 . SendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
  s0 . SendMail ( CMail ( "peter", "alice", "PR bullshit" ) );
//  s0 . SendMail ( CMail ( "aaa", "bbb", "PR bullshit" ) );
 
  CMailIterator i0 = s0 . Inbox ( "alice" );
//  s0.writeout();
//  s0 . SendMail ( CMail ( from, to, body ) );
//  s0 . SendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
//  s0 . SendMail ( CMail ( "peter", "alice", "PR bullshit" ) );
//  s0 . SendMail ( CMail ( from, to, body ) );
//  s0 . SendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
//  s0 . SendMail ( CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( i0 );
  assert ( i0 && *i0 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i0 && *i0 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ! ++i0 );
  
  CMailIterator i1 = s0 . Inbox ( "john" );
  i1 = s0.Outbox("john");
  i1 = s0.Inbox("john");
  assert ( i1 && *i1 == CMail ( "alice", "john", "deadline confirmation" ) );
  assert ( ! ++i1 );

  CMailIterator i2 = s0 . Outbox ( "john" );
  assert ( i2 && *i2 == CMail ( "john", "peter", "some important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "thomas", "another important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ! ++i2 );

  CMailIterator i3 = s0 . Outbox ( "thomas" );
  assert ( ! i3 );

  CMailIterator i4 = s0 . Outbox ( "steve" );
  CMailIterator i5 = s0 . Outbox ( "thomas" );
  s0 . SendMail ( CMail ( "thomas", "boss", "daily report" ) );
  assert ( ! i5 );

  CMailIterator i6 = s0 . Outbox ( "thomas" );
  assert ( i6 && *i6 == CMail ( "thomas", "boss", "daily report" ) );
  assert ( ! ++i6 );

  CMailIterator i7 = s0 . Inbox ( "alice" );
  s0 . SendMail ( CMail ( "thomas", "alice", "meeting details" ) );
  assert ( i7 && *i7 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i7 && *i7 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ! ++i7 );

  CMailIterator i8 = s0 . Inbox ( "alice" );
  assert ( i8 && *i8 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i8 && *i8 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i8 && *i8 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ! ++i8 );

  CMailServer s1 ( s0 );
  s1 = s1;
  s0 . SendMail ( CMail ( "joe", "alice", "delivery details" ) );
  s0=s0;
  s1=s1;
  s1=s1;
  s1 . SendMail ( CMail ( "sam", "alice", "order confirmation" ) );
  s1=s1;
  CMailIterator i9 = s0 . Inbox ( "alice" );
  assert ( i9 && *i9 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i9 && *i9 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i9 && *i9 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i9 && *i9 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ! ++i9 );

  CMailIterator i10 = s1 . Inbox ( "alice" );
  assert ( i10 && *i10 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i10 && *i10 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i10 && *i10 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i10 && *i10 == CMail ( "sam", "alice", "order confirmation" ) );
  assert ( ! ++i10 );
  
  CMailServer s2;
  CMailIterator i21 = s2.Inbox("alice");
  assert (! i21);
  s2 . SendMail ( CMail ( "alice", "alice", "mailbox test" ) );
  CMailIterator i11 = s2 . Inbox ( "alice" );
  assert ( i11 && *i11 == CMail ( "alice", "alice", "mailbox test" ) );
  assert ( ! ++i11 );
//  s2.writeout();
  s2 = s0;
  s0 . SendMail ( CMail ( "steve", "alice", "newsletter" ) );
  s2 . SendMail ( CMail ( "paul", "alice", "invalid invoice" ) );
  CMailIterator i12 = s0 . Inbox ( "alice" );
  assert ( i12 && *i12 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i12 && *i12 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i12 && *i12 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i12 && *i12 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ++i12 && *i12 == CMail ( "steve", "alice", "newsletter" ) );
  assert ( ! ++i12 );

  CMailIterator i13 = s2 . Inbox ( "alice" );
  assert ( i13 && *i13 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i13 && *i13 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i13 && *i13 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i13 && *i13 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ++i13 && *i13 == CMail ( "paul", "alice", "invalid invoice" ) );
  assert ( ! ++i13 );
  s2.SendMail(CMail ( "john", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john123", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "joh23n", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john23", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "joh24n", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john25", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john5", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john44", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john444", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john123", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john12312", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john12311232", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john12311231232", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "joh4324432n12312", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john12312234909238012", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john1234412", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john12312", "alice", "deadline notice" ) );
  s2.SendMail(CMail ( "john1231211111", "alicawde", "deadline notice" ) );
  s2.SendMail(CMail ( "john12312101010", "adwalice", "deadline notice" ) );
  s2.SendMail(CMail ( "john12312", "aliwdace", "deadline notice" ) );
  s2.SendMail(CMail ( "321938john12312", "alicdwe", "deadline notice" ) );
  s2.SendMail(CMail ( "321938  john12312", "adwalice", "deadline notice" ) );
  s2.SendMail(CMail ( "321938  john12312", "adwalice", "deadline notice" ) );
  s2.SendMail(CMail ( "321938  john12312", "adwalice", "deadline notice" ) );
  s2.SendMail(CMail ( "321938  john12312", "adwalice", "deadline notice" ) );
  s2.SendMail(CMail ( "321938  john12312", "adwalice", "deadline notice" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ) );
  s2.SendMail(CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ) );
  s2.SendMail(CMail ( "", "", "" ) );
  s2.SendMail(CMail ( "", "", "" ) );
  s2.SendMail(CMail ( "", "", "" ) );
  s2.SendMail(CMail ( "", "", "" ) );
  s2.SendMail(CMail ( "", "", "" ) );
//  s2.writeout();
  CMailServer s22(s2);
  s22 = s2;
  CMailServer s69;
  CMailServer s40;
  CMailServer s51;
  s51 = s51;
  CMailServer s70(s69);
  s70 = s69;
  CMailServer s80 ;
  s80 = s69;
  CMailServer s82 = s70;
  CMailIterator i31 = s40 . Inbox ( "alice" );
  CMailIterator i32 = s40 . Inbox ( "" );
  
//  s2.writeout();
  
  CMailServer s31;
  
  assert ( ! ++i31 );
  assert ( ! ++i31 );
  assert ( ! ++i31 );
  assert ( ! ++i31 );
  assert ( ! ++i31 );
  assert ( ! ++i31 );
  assert ( ! ++i31 );
  assert ( ! ++i31 );
  assert ( ! ++i31 );
  assert ( ! i31 );
  assert ( ! i31 );
  assert ( ! i31 );
  assert ( ! i31 );
  assert ( ! i31 );
  assert ( ! i31 );
  assert ( ! i31 );
  assert ( ! i31 );
  assert ( ! i31 );
//  assert ( *i32 ==CMail ( "adwalice", "adwalice", "asdasdsadasdaa sa dsa s" ));
  assert ( !i32);
//*/
  return 0;
}
#endif /* __PROGTEST__ */