#include <iostream>
using namespace std;
 template<class T>
 class stack{
private:
    T*arr;
    int capacity;
    int currentop;
public:
    stack(int size=2){
        arr=new T[size];
        capacity=size;
        currentop=-1;  
    }
    ~stack(){
        delete []arr;
    }
     void resize(int newcapacity){
        T*newarr=new T[newcapacity];
        for(int i=0;i<=currentop;++i){
            newarr[i]=arr[i];
        }
        delete []arr;
        arr=newarr;
        capacity=newcapacity;
     }
     void push(T val){
        if(currentop==capacity){
            resize(2*capacity);
        
        }
        arr[++currentop]=val;
        cout<<val<<" pushed";
        cout<<"\n";

     }

     void pop(){
        if(currentop==-1){
            cout<<"stack is full";
            return ;
        }
       cout<<arr[currentop]<<"popped";
       currentop--; 
     }
     bool isempty(){
        return currentop==-1;
     }
     int size(){
        return currentop+1;
     }
     void print(){
        cout<<" stack elements \n";
        for(int i=0; i <= currentop;++i){
            cout<<arr[i]<<" ";
        }
        cout<<"\n";
     }


 };
int main(){

stack<int> s;
s.push(10);
s.push(20);
s.push(30);
s.push(40);

s.print();


}