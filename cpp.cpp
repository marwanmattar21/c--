#include <iostream>
using namespace std;

class Node{
    public:
        int data;
        Node* next;
    
    };
    class linkedlist{
    
     public:
        Node* head;
        linkedlist(){
           head=NULL;
        }
        bool isempty(){
    if(head==NULL)
    return true;
    else
    return false;
        }
    
        void insertfirst(int newitem){
            Node* newnode=new Node();
            newnode->data=newitem;
            if (isempty()){
            newnode->next=NULL;
            head=newnode;
        }
        else{
            newnode->next=head;
            head=newnode;
        }
    
    
        }
        
        void display(){
    
            Node*temp=head;
            while(temp!=NULL){
                cout<<temp->data<<" ";
                temp=temp->next;       
             }
      
    
        }
    
    };
    
    int main(){
        linkedlist lis;
        lis.insertfirst(10);
        lis.display();
    
    cout<<"maro";
    
    }