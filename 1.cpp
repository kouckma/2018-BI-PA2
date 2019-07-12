#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */

string intarrToString( int ** array,int size,int shift)
{
    string result = "";
    
    for(; shift < size; shift++)
    {
        //cout <<endl<< size << "  "<< shift <<endl;
        result+= std::to_string(array[0][shift]);
    }
    return result;
}


int decodesbits(string sbits)
{
    int i = 0;
    if("000" == sbits)i=0;
    else if("011" == sbits)i=8;
    else if("100" == sbits)i=16;
    
            return i;
}
int decodesfactor(string sfactor)
{
    int i = 0;
    if("000" == sfactor)i=1;
    else if("001" == sfactor)i=2;
    else if("010" == sfactor)i=4;
    else if("011" == sfactor)i=8;
    else if("100" == sfactor)i=16;
    else if("101" == sfactor)i=32;
    else if("110" == sfactor)i=64;
            return i;
}
int decodeschannel(string schannel)
{
    int i = 0;
    if("00" == schannel)i=1;
    else if("01" == schannel)i=0;
    else if("10" == schannel)i=3;
    else if("11" == schannel)i=4;
            return i;
}
int decodeendian(string endian)
{
    int i = 0;
    if("0100100101001001" == endian)i=1; // little endian
    else if("0100110101001101" == endian)i=2; //big endian
    //cout << endian;
            return i;
}

vector<vector<uint16_t>> cutheader(vector<vector<uint16_t>> arr,int width)
{
    for(int i = 0;i<width;i++)
    {
        arr[0][i]=arr[0][i+8];
    }
    return arr;
}

int getoutfactor(int factor)
{
    int result = 7; //nonvalid
    switch(factor)
    {
        case(1): result = 0x0;break;
        case(2): result = 0x20;break;
        case(4): result = 0x40;break;
        case(8): result = 0x60;break;
        case(16): result = 0x80;break;
        case(32): result = 0xa0;break;
        case(64): result = 0xc0;break;
    }
    return result;
}

vector<vector<uint16_t>> swap(vector<vector<uint16_t>> arr,int height,int newwidth,int det)
{
    
    //cout<< "sem tady"<<endl;
    uint16_t temp1=0;
    uint16_t templast=0;
    int i = 0,swith=0;
    if(det==2)
        for (int k=0;k<(newwidth*height)+8;k++)
        {
            if((k%2) == 0 || k == 0){
               // cout<<arr[i][k]<<endl;
                temp1 = arr[i][k];
                arr[i][k] =arr[i][k+1];
               // cout<<arr[i][k]<<endl;
            }
            else{
                arr[i][k] = temp1;
            }
        }
    else{
    for(int f = 0;f<height;f++)
    {
        if(swith == 0)swith=1;
        else swith = 0;
        if(f==0){ //99 correct, update: seems like not 99
        for (int k=0;k<(newwidth+8);k++)
        {
            
            if((k%2) == 0 || k == 0){
                if((k+1)>=(newwidth+8))
                {
                templast = arr[f][k];
                arr[f][k] =arr[f+1][0];
                }
                else {
                temp1 = arr[f][k];
                arr[f][k] =arr[f][k+1];
                }
            }
            else if ((k%2) != 0){
                arr[f][k] = temp1;
            }
        }
        }
        else//todo
        {
                for (int k=0;k<newwidth;k++)
            {
                    if(newwidth%2 != 0)
                        {
                        if(swith== 1)
                        {
                            if((k+1)>=(newwidth+8))
                            {
                            templast = arr[f][k];
                            arr[f][k] =arr[f+1][0];   //i+1 can be dangerous
                            }
                            else if(k == 0){
                                arr[f][k] = templast;
                            }
                            else if((k%2) == 0 )
                            {
                                temp1 = arr[f][k];
                                arr[f][k]= arr[f][k+1];
                            }
                            else if((k%2) != 0)
                            {
                                arr[f][k] = temp1;
                            }
                        }
                        else if(swith == 0)
                        {
                            if(k == 0){
                                temp1 = arr[f][k];
                            }
                            else if((k%2) == 0 )
                            {
                                arr[f][k] = temp1;
                            }
                            else if((k%2) != 0)
                            {
                                temp1 = arr[f][k];
                                arr[f][k]= arr[f][k+1];
                            }
                        }
                        }
               
                    else{
                            if((k%2) == 0 )
                            {
                                temp1 = arr[f][k];
                                arr[f][k]= arr[f][k+1];
                            }
                            else if((k%2) != 0)
                            {
                                arr[f][k] = temp1;
                            }
                        }
            }
        }
            
    }
    }
    /*
    for(int i = 0;i<height;i++)
    {
        if(firstrow)newwidth = widthinit + 8;
        else newwidth = widthinit;
        for (int k=0;k<newwidth;k++)
        {
            
            if((k%2) == 0 || k == 0){
                if( (newwidth%2) != 0 && i > 0)
                {
                temp2 = arr[i][k];
                arr[i][k] = temp1;
                }
                else if((k+1) >= newwidth){
                    if((i + 1) >= height){break;}
                    temp1 = arr[i][k];
            arr[i][k] = arr[i+1][0];}
                    else 
                    {
                    temp1 = arr[i][k];
            arr[i][k] = arr[i][k+1];
                    } 
            }
            else{
                if((newwidth%2) != 0 && i > 0) //k == 0 && (i != 0 || (k%2)!=0) && 
                {
            arr[i][k] = temp2;
                }
                else arr[i][k] = temp1;
            }
        }
    }
    */
    return arr;
}


int createfile(vector<vector<uint16_t>> inarr,int interleave,int bits,
                        int channel,int width,int height,
                   const char  * dstFileName,
                   int           factor,
                   uint16_t      byteOrder)
{
    //cout <<"........"<< inarr[0][10]<<endl;
    vector<vector<uint16_t>> outarr(1,vector<uint16_t>(5,0));
    outarr.resize(1);
    for(int m=0;m<1;m++)
    {
        if(m == 0)outarr[m].resize(((width)*height)+16);
        else outarr[m].resize(width+1);
    }
    //cout <<(((width+1)*height)+8)<<endl;
    //outarr.resize(999,vector<uint16_t>(999,0));
    /*
    uint16_t ** outarr; //outarray
    outarr = new uint16_t *[999];
    for(int i = 0; i <height; i++)outarr[i] = new uint16_t[999];
    */
    ofstream outfile;
    outfile.open(dstFileName, ios::binary );
    if(outfile.fail()){
    outfile.close();
                return 0;
    }
    if(!outfile.is_open()){
    outfile.close();
                return 0;
    }
    
    
    if (bits == 1)bits = 8; //until 1bit is resolved
    int pixelsize = 0;
    pixelsize = (bits/8) * channel;
    int facstate = 0;
    int pfacpart = 1;
    int first = 1;
    if (factor == 1)facstate = 1;   //zmenit factor na interleave
    //cout << "hahahhahahahah"<<endl;
    for(int i = 0;i<8;i++)
    {
        outarr[0][i]=inarr[0][i];
    }
    
    if(byteOrder == 0x4d4d && bits != 16){
    int shifting = outarr[0][6] & 0x1f;
    outarr[0][6] = shifting | getoutfactor(factor);
    }
    else {
    int shifting = outarr[0][6] & 0x1f;
    outarr[0][6] = shifting | getoutfactor(factor);
    }
    
    inarr = cutheader(inarr,width); //header out for easier approach
   // factor = pixelsize * factor; //wrong
    int counter = 8;
    for(int facpart = factor; facpart>0;facpart/=2)
    {
     //   cout << facpart<< endl;
        for(int i = 0; i<height; i++) //rows
        {
       //     cout << i << "novej radek"<< width << endl; 
            
                //cout<<"kricim"<<endl<<i<<endl<<endl;
            if(i == 0 || (i%facpart == 0)){
                pfacpart = facpart * pixelsize;
                for(int j = 0;j<width;j+=pfacpart) //indexes at row
                {   
                   // cout << "cekuju cekuju "<<j<<" i:"<<i<<" "<<facpart<<" "<<pfacpart<<" "<<pfacpart*2<<endl;
                if((j == 0 || j%pfacpart==0) && !((j%(pfacpart*2) == 0 && (i==0 || i%(facpart*2) == 0)) && first == 0))
                    {
                        for(int l = 0;l<pixelsize;l++)
                        {
                      // cout  << i <<";"<< j << "+" << l<<endl;
                           // cout <<"  nst "<< inarr[i][j+l]<<" "<<facpart
                             //       <<endl;
                        outarr[0][counter] = inarr[i][j+l];
                      //  cout << counter <<"i;j"<<i<<";"<<j+l<<" px"<<pixelsize; 
                  //~~~ cout<<" ["<<outarr[0][counter]<<"] "<< endl;
           //             //cout << endl <<"!!!!"<< outarr[0][counter] <<" na "<< counter << endl;
                        counter ++;
                        }
             //           //cout << endl << inarr[i][j]<<" <-- "<< i<<j <<endl;
                    }
                        
                }
            }
        }
        if (facpart == 1)
        {if (facstate == 1) break;else if(facstate == 0)facstate = 1;}
        first = 0;
    }
   // cout << inarr[0][16];
    
   // cout << dstFileName << outarr[0][10];
    
    if(byteOrder == 0x4d4d)
    {
        //cout<<dstFileName;
        if(bits == 16)outarr = outarr=swap(outarr,height,width,2);
        else{
            int temp1 = 0;
            for(int d = 0;d<8;d++)
            {
            if((d%2) == 0 || d == 0){
               // cout<<arr[i][k]<<endl;
                temp1 = outarr[0][d];
                outarr[0][d] =outarr[0][d+1];
               // cout<<arr[i][k]<<endl;
            }
            else{
                outarr[0][d] = temp1;
            }
            }
        }
        //outarr=swap(outarr,height,width,2);
        outarr[0][1] = 0x4d;
        outarr[0][0] = 0x4d;
    }
  //  outarr[0][1] = 0x32;
  //  outarr[0][0] = 0x01;
    
    
    for(int v = 0;v<((height*width)+8);v++)
    {
    if(!outfile.write((char*)&outarr[0][v], sizeof(uint8_t)))
    {outfile.close();
    return 0;}
    }
    outfile.close();
    
    return 1;
    
    //outarr.~vector();
}

vector<vector<uint16_t>> decipher(vector<vector<uint16_t>> array,int newwidth,int height,
                                        int factor,int pixelsize)
{
    vector<vector<uint16_t>> outarr(1,vector<uint16_t>(10,0));
    //outarr.resize(999,vector<uint16_t>(999,0));
    /*
    uint16_t ** outarr;
    outarr = new uint16_t *[999];
    for(int i = 0; i <height; i++)outarr[i] = new uint16_t[999];
    */
    outarr.resize(height);
    for(int m=0;m<height;m++)
    {
        if(m == 0)outarr[m].resize((newwidth+1)+8);
        else outarr[m].resize(newwidth+1);
    }
    int first=1;
    int count=0,row = 0,firstrow=1;
    
   // cout << array[0][8+6]<<endl;
   // cout << "sem tady ))))))))))))))))))"<< newwidth<< "height:" <<height<<  endl;
    int helppls = 0;
    
    for(int i = 0;i<8;i++)
    {
        outarr[0][i]=array[0][i];
    }
    
    array = cutheader(array,newwidth);
    
    
    
    for(int i = factor;i > 0;i/=2)
    {
        for(int k =0;k<height;k++)
        {
            if(k == 0 || (k%i)==0)
            {
                
                for(int u = 0;u<newwidth;u+=(i*pixelsize))
                {
                    //if(k==18)cout << "X"<<k<<" "<<u<<" "<<i<<" ";
                    if
((u == 0 || u%(i*pixelsize)==0) && !(((u%(i*pixelsize*2) == 0||u==0) && (k==0 || k%(i*2) == 0)) && first == 0))
                    {
                        //for()
                        
                       // if(k==18)cout << "Y";
                        
                        if(firstrow && (count >= (newwidth))){row++;count = 0; //newwidth + 8 was here
                        firstrow = 0;
                        //cout << " reset "<<endl;
                        }
                        if(!firstrow && ((count) >= (newwidth))){row++;count = 0;
                        firstrow = 0;
                       // cout << "reset2" << endl;
                        }
                        //cout << "VA"<< k<<";"<<u<<endl;
                            for(int h=0;h<pixelsize;h++)
                            {
                                //if(k==0)helppls = 8;else helppls=0;
                                //cout << k<<" "<<u << endl;
                                if(k==0)outarr[k][u+h+helppls+8] = array[row][count+h];
                                else outarr[k][u+h+helppls] =
                                        array[row][count+h];
                                if((array[row][count+h] == 6 )|| row==18)
                                {
                                    //cout << "RVA"<< k<<";"<<u<<endl<<row<<";"<<count<<endl<<"cotamje:"<<array[row][count+h]<<endl<<endl;
                                }
                             //   cout <<endl << "wh,count " <<array[row][count+h]<<","<< count 
                             //           << " [][] "<<row<<", "<<count +h <<" factor {{ "<< i <<endl;
                              //  cout <<"pixelsize: "<<pixelsize<<" "<< outarr[k][u+h]<<"  "
                                //        << array[row][count+h] <<" "<< array[row][count+h+8];
                            }
                        count += pixelsize;
                    }
                }
                
            }
        }
        first = 0;
        // do something with count
        //cout<< "count :::"  << count << endl;
        //cout<<height<<" "<<newwidth<<factor<<38*3<<" hp "<<newwidth*height<<endl;
        
    }
    /*
    for(int i = 0;i<8;i++)
    {
        outarr[0][i]=array[0][i];
    }
    */
    //cout <<endl<< shift<<endl;
    //return array;
    //array.~vector();
    return outarr;
}


bool recodeImage ( const char  * srcFileName,
                   const char  * dstFileName,
                   int           interleave,
                   uint16_t      byteOrder )
{
    
    /*if((interleave != 1)&& ((interleave%2) != 0))
    return 0;*/
    if((interleave == 1)||(interleave == 2)||(interleave == 4)||
        (interleave == 8)||(interleave == 16)||(interleave == 32)||(interleave == 64));
    else return 0;
    
    if((byteOrder != 0x4d4d) && (byteOrder != 0x4949))
        return 0;
    
        
        
    
    
    
    vector<vector<uint16_t>> inarray2(1,vector<uint16_t>(10,0));
    
    
    int * arr3 = new int [10];
    int ** inarray; //todo 
    inarray = new int *[100];
    for(int i = 0; i <1; i++) inarray[i] = new int[100];
    /*
    uint16_t ** inarray2; //todo
    inarray2 = new uint16_t *[999];
    for(int i = 0; i <100; i++)inarray2[i] = new uint16_t[999];
    */
    
    
    string endian = "", swidth = "", sheight = "", sfactor ="",
            schannel = "", sbits = "";
    int width = 0,height = 0,factor = 0,channel = 0,bits =0;
    int x=0,y=0,counter=0,j=0;
    ifstream infile;
    infile.open(srcFileName, ios::binary | ios::in);
    if(infile.fail()){
    infile.close();
                delete [] arr3;
                for(int z=0;z<1;z++)
                {
                    delete[] inarray[z];
                }
                delete [] inarray;
                return 0;
    }
    if(!infile.is_open()){
    infile.close();
                delete [] arr3;
                for(int z=0;z<1;z++)
                {
                    delete[] inarray[z];
                }
                delete [] inarray;
                return 0;
    }
    
    char c;
    int endianstate = 0;
    int firstrowstate = 0;
    int pixelsize = 1;
    int newwidth = 0,errorr = 0;
    while (infile.get(c))
    {
        if(width){
            pixelsize = (bits/8) * channel;
                    if((((counter) - 8) + 1) > (width*height*pixelsize))
                {
                   // cout << "wtf  " <<width<<endl<<height<<endl;
                  //  cout << (counter - 8)/pixelsize << "  " << width*height<<endl;

                infile.close();
                delete [] arr3;
                for(int z=0;z<1;z++)
                {
                    delete[] inarray[z];
                }
                delete [] inarray;
                return 0;
                }
        }
       // cout << counter;
     counter ++;
     
     
     
     
        if(width != 0)
        {
            pixelsize = (bits/8) * channel;
            newwidth = width * pixelsize;  
            if(((j+1) > (newwidth+8) ) && (firstrowstate == 0))
            {
                x+=1;
                firstrowstate = 1;
                j=0;
                //cout << "nt" << endl;
            }
            else if((j+1) > newwidth && (firstrowstate == 1))
            {
                x += 1;
               // cout <<endl<< x << " nohhhhhhhhhhhhelooo  "  << endl;
                j=0;
                
            }
        }
        if(firstrowstate == 0 && x == 0 && j < 8)arr3[j] = (int)(unsigned char)c;
        inarray2[x][j] = (int)(unsigned char)c;
        //cout<< " [" << hex << inarray2[x][j]<<"] ";
        if(y <90){
        for(int i = 7; i >= 0; i--)
        {
            
            if(y < 16)
            {
                inarray[0][y] = ((c >> i) & 1);    //todo
            }            
            if(y == 15)
            {
                endian = intarrToString(inarray, 16, 0);
                //cout << endian << endl;
                endianstate = decodeendian(endian);
                if ((endianstate != 2 )&&(endianstate != 1 ))
                {
                infile.close();
                            delete [] arr3;
                            for(int z=0;z<1;z++)
                            {
                                delete[] inarray[z];
                            }
                            delete [] inarray;
                            return 0;
                
                }
                    
                //cout << "endian: " << decodeendian(endian)<<endl;
            }
            //todo podle endiana
            
            if(endianstate == 1)
            {
                inarray[0][y] = ((c >> i) & 1);
                if(y == 63)
                {
                    sfactor = intarrToString(inarray, 51, 48);
                    //cout << sfactor << endl;
                    factor = decodesfactor(sfactor);
                    if(factor == 0)errorr=1;
                    sbits = intarrToString(inarray, 54, 51);
                    //cout << sbits << endl;
                    bits = decodesbits(sbits);
                    if(bits == 0)errorr=1;
                    schannel = intarrToString(inarray, 56, 54);
                    //cout << schannel << endl;
                    channel = decodeschannel(schannel);
                    if(channel == 0)errorr=1;
                    
                    if(errorr)
                        {
                            infile.close();
                            delete [] arr3;
                            for(int z=0;z<1;z++)
                            {
                                delete[] inarray[z];
                            }
                            delete [] inarray;
                            return 0;
                            }
                    //cout << "no heloooo" << endl << factor <<endl << channel <<endl<< bits;
                }
            }       
            else if(endianstate == 2)
            {
                inarray[0][y] = ((c >> i) & 1);    //todo
                if(y == 63)
                {   
                    sfactor = intarrToString(inarray, 51+8, 48+8);
                    //cout << sfactor << endl;
                    factor = decodesfactor(sfactor);
                    if(factor == 0)errorr=1;
                    sbits = intarrToString(inarray, 54+8, 51+8);
                    //cout << sbits << endl;
                    bits = decodesbits(sbits);
                    if(bits == 0)errorr=1;
                    schannel = intarrToString(inarray, 56+8, 54+8);
                    //cout << schannel << endl;
                    channel = decodeschannel(schannel);
                    if(channel == 0)errorr=1;
                    
                    if(errorr)
                        {
                            infile.close();
                            delete [] arr3;
                            for(int z=0;z<1;z++)
                            {
                                delete[] inarray[z];
                            }
                            delete [] inarray;
                            return 0;
                            }
                }   
            }
            y++;
        }
        }
        if( ((j == 7) &&(inarray2[0][0] == 0x49 )&& (inarray2[0][1] == 0x49))) // == endianstate == 1
        {
            pixelsize = (bits/8) * channel;
            width = inarray2[0][2] + (256*inarray2[0][3]);
            height = inarray2[0][4] + (256*inarray2[0][5]);
            if(width == 0 || height == 0)
            {
                infile.close();
                delete [] arr3;
                for(int z=0;z<1;z++)
                {
                    delete[] inarray[z];
                }
                delete [] inarray;
                return 0;
            }
            inarray2.resize(height);
            for(int m=0;m<height;m++)
            {
                if(m == 0)inarray2[m].resize(((width+1)*pixelsize)+8);
                else inarray2[m].resize((width+1)*pixelsize);
            }
            
            //cout << "endianek"<< endianstate <<endl;
            //cout <<dec<<j << inarray[0][40]<< "size"<<height <<width;
        }
        else if( ((j == 7) &&(inarray2[0][0] == 0x4d )&& (inarray2[0][1] == 0x4d))) // == endianstate == 1
        {
            pixelsize = (bits/8) * channel;
            width = (inarray2[0][3] + (256*inarray2[0][2]));
            height = (inarray2[0][5] + (256*inarray2[0][4]));
            //cout << width<<" "<<height<<endl;
            if(width == 0 || height == 0)
            {
                infile.close();
                delete [] arr3;
                for(int z=0;z<1;z++)
                {
                    delete[] inarray[z];
                }
                delete [] inarray;
                return 0;
            }
            inarray2.resize(height);
            for(int m=0;m<height;m++)
            {
                pixelsize = (bits/8) * channel;
                if(m == 0)inarray2[m].resize(((width+1)*pixelsize)+8);
                else inarray2[m].resize((width+1)*pixelsize);
            }
            
            
            //cout << "endianek"<< endianstate <<endl;
            //cout <<dec<<j << inarray[0][40]<< "size"<<height <<width;
        }
        j++;
        
    }

    if(! infile.eof())
        {
        infile.close();
                delete [] arr3;
                for(int z=0;z<1;z++)
                {
                    delete[] inarray[z];
                }
                delete [] inarray;
                return 0;
        }
    
    if((counter - 8) != (width*height*pixelsize))
    {
      //  cout << "wtf  " <<width<<endl<<height<<endl;
      //  cout << (counter - 8)/pixelsize << "  " << width*height<<endl;
        
    infile.close();
    delete [] arr3;
    for(int z=0;z<1;z++)
    {
        delete[] inarray[z];
    }
    delete [] inarray;
    return 0;
    }
    //outfile.write(reinterpret_cast<char const*>(inarray2), sizeof inarray2);
    ////cout<<endianstate<<endl<<endl;
    if(endianstate  == 2){
        if(bits == 16)inarray2=swap(inarray2,height,newwidth,1);
        else{
            int temp1 = 0;
            for(int d = 0;d<8;d++)
            {
            if((d%2) == 0 || d == 0){
               // cout<<arr[i][k]<<endl;
                temp1 = inarray2[0][d];
                inarray2[0][d] =inarray2[0][d+1];
               // cout<<arr[i][k]<<endl;
            }
            else{
                inarray2[0][d] = temp1;
            }
            }
        }
        
        inarray2[0][0]=0x49;
        inarray2[0][1]=0x49;
    }
    
    for(int z = 0; z<(height);z++)
    {
        for(int g = 0; g<(width*pixelsize);g++)
        {
            if(inarray2[z][g]==6)
            {
                //cout <<"["<<z<<"]"<<g;
            }
        }
    }
    
    
    inarray2=decipher(inarray2,newwidth,height,factor,pixelsize);
    
    int fin = 0;
    fin = createfile(inarray2,factor,bits,channel,newwidth,height,dstFileName,
                interleave,byteOrder);
    if (fin == 0)
    {
    infile.close();
    delete [] arr3;
    for(int z=0;z<1;z++)
    {
        delete[] inarray[z];
    }
    delete [] inarray;
    
    return 0;
    }
    else
    {
   // inarray2.~vector();
    //inarray.delete();
  // todo
    infile.close();
    delete [] arr3;
    for(int z=0;z<1;z++)
    {
        delete[] inarray[z];
    }
    delete [] inarray;
    
    return 1;
    }
}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
  // DIY
    return 1;
}

int main ( void )
{
 /* 
    assert ( recodeImage ( "input_00.img", "output_00.img", 1, ENDIAN_LITTLE )
           && identicalFiles ( "output_00.img", "ref_00.img" )
          );

  assert ( recodeImage ( "input_01.img", "output_01.img", 8, ENDIAN_LITTLE )
           && identicalFiles ( "output_01.img", "ref_01.img" ) );

  assert ( recodeImage ( "input_02.img", "output_02.img", 8, ENDIAN_LITTLE )
           && identicalFiles ( "output_02.img", "ref_02.img" ) );
*/
  assert ( recodeImage ( "in1.bin", "out1.bin", 8, ENDIAN_LITTLE )
           && identicalFiles ( "output_03.img", "ref_03.img" ) );
/*
  assert ( recodeImage ( "input_03.img", "output_03.img", 2, ENDIAN_LITTLE )
           && identicalFiles ( "output_03.img", "ref_03.img" ) );

  assert ( recodeImage ( "input_04.img", "output_04.img", 1, ENDIAN_LITTLE )
           && identicalFiles ( "output_04.img", "ref_04.img" ) );

  assert ( recodeImage ( "input_05.img", "output_05.img", 1, ENDIAN_LITTLE )
           && identicalFiles ( "output_05.img", "ref_05.img" ) );

  assert ( recodeImage ( "input_06.img", "output_06.img", 8, ENDIAN_LITTLE )
           && identicalFiles ( "output_06.img", "ref_06.img" ) );

  assert ( recodeImage ( "input_07.img", "output_07.img", 4, ENDIAN_LITTLE )
           && identicalFiles ( "output_07.img", "ref_07.img" ) );

  assert ( recodeImage ( "input_08.img", "output_08.img", 8, ENDIAN_LITTLE )
           && identicalFiles ( "output_08.img", "ref_08.img" ) );
*/
 // assert ( ! recodeImage ( "input_09.img", "output_09.img", 1, ENDIAN_LITTLE ) );

 // assert ( ! recodeImage ( "input_10.img", "output_10.img", 5, ENDIAN_LITTLE ) );

  // extra inputs (optional & bonus tests)
 
//  assert ( recodeImage ( "extra_input_00.img", "extra_out_00.img", 8, ENDIAN_LITTLE )
//           && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
  
//  assert ( recodeImage ( "extra_input_01.img", "extra_out_01.img", 4, ENDIAN_BIG )
//           && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
/*  
  assert ( recodeImage ( "extra_input_02.img", "extra_out_02.img", 16, ENDIAN_BIG )
           && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
  
  assert ( recodeImage ( "extra_input_03.img", "extra_out_03.img", 1, ENDIAN_LITTLE )
           && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
  
  assert ( recodeImage ( "extra_input_04.img", "extra_out_04.img", 8, ENDIAN_LITTLE )
           && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
 
  assert ( recodeImage ( "extra_input_05.img", "extra_out_05.img", 4, ENDIAN_LITTLE )
    && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
 
 assert ( recodeImage ( "extra_input_06.img", "extra_out_06.img", 16, ENDIAN_BIG )
          && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
 
  assert ( recodeImage ("extra_input_07.img", "extra_out_07.img", 1, ENDIAN_BIG )
           && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
*/
 //  assert ( recodeImage ("progin1.bin", "asd.img", 4, ENDIAN_LITTLE )
 //          && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
  
 //"extra_input_07.img"  "extra_outik_07.img" ,test endianu: "extra_outik3_07.img"
  
//  assert ( recodeImage ( "extra_input_08.img", "extra_out_08.img", 8, ENDIAN_LITTLE )
 //          && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
 
//  assert ( recodeImage ( "extra_input_09.img", "extra_out_09.img", 4, ENDIAN_LITTLE )
//           && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
//  assert ( recodeImage ( "extra_input_10.img", "extra_out_10.img", 16, ENDIAN_BIG )
 //          && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
 
 // assert ( recodeImage ( "extra_input_11.img", "extra_out_11.img", 1, ENDIAN_BIG )
 //          && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
 /**/
   return 0;
}
#endif /* __PROGTEST__ */