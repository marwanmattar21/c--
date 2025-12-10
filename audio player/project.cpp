#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

class Audio{
private:
       string name;
       string path;
       string alias;
public:
      Audio(string songName,string songPath,string songAlias){
        name=songName;
        path=songPath;
        alias=songAlias;
      }

      void play(){

        string closeCmd = "close " + alias; 
        mciSendString(closeCmd.c_str(), NULL, 0, NULL);

        string openCmd = "open \"" + path + "\" alias " + alias;
         mciSendString(openCmd.c_str(), NULL, 0, NULL);
        
        string playCmd = "play " + alias;
        mciSendString(playCmd.c_str(),NULL,0,NULL);
      }

      void pause(){
        string cmd = "pause " + alias;
        mciSendString(cmd.c_str(),NULL,0,NULL);
      }

      void resume(){
        string cmd = "resume " + alias;
        mciSendString(cmd.c_str(),NULL,0,NULL);
      }
      
      void stop(){
        string cmd = "close " + alias;
        mciSendString(cmd.c_str(),NULL,0,NULL);
      }
       
      string getName(){
        return name;
      }
      string getpath(){
        return path;
      }
};


  struct Node{
    Audio* data;
    Node* next;
    Node* prev;
    
    Node(Audio* song){
        data=song;
        next=NULL;
        prev=NULL;
    }

  };


  class PlayList{
private:
       string playlistname;
       Node* head;
       Node* tail;
       Node* current;
public:
    PlayList(string name){
      playlistname=name;
        head=tail=current=NULL;
    }

    string getname(){
      return playlistname;
    }

    void addSong(Audio* song){
        Node* newnode=new Node(song);
        if (head==NULL)
        {
            head=tail=current=newnode;
        }
        else{
            tail->next=newnode;
            newnode->prev=tail;
            tail=newnode;
        }
    }
    

     void displaysong(){
      if(head==NULL){
        cout<<"playlist is empty\n";
        return;
      }

      Node*temp=head;
      int i=1;
      while (temp)
      {
        cout<<" "<<i++<<". "<<temp->data->getName()<<" <<"<<endl;
        temp=temp->next;
      }

     } 
     
     void startplaying(){
      if(current){
        cout<<"\n now playing: "<<current->data->getName()<<" "<<endl;
        current->data->play();
      }
      else if(head){
        current=head;
        startplaying();
      }
      else{
        cout<<" playlist is empty"<<endl;
      }
     }

     void nextsong(){
      if(current&&current->next){
        current->data->stop();
        current=current->next;
        startplaying();
      }
      else{
        cout<<"end of playlist. "<<endl;
      }
     }

     void playprev(){
        if(current&&current->prev){
        current->data->stop();
        current=current->prev;
        startplaying();
      }
      else{
        cout<<" start of playlist. "<<endl;
      }
     }
      void pausecurrent(){
      if (current)
      
        current->data->pause();
      }

      void resumecurrent(){
        if(current){
          current->data->resume();
        }
      }

      void stopcurrent(){
        if(current){
        current->data->stop();
        }
      }

      bool removeSong(int index) {
        if (head == NULL || index < 1) return false;

        Node* node = head;
        int count = 1;

        while (node && count < index) {
            node = node->next;
            count++;
        }

        if (!node) return false; 

        if (current == node) {
            current->data->stop();
            current = NULL; 
        }

        
        if (node->prev) node->prev->next = node->next;
        else head = node->next; 

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        delete node;
        return true;
    }

    bool swapSongs(int i, int j) {
        if (i == j) return true;

        Node *a = head, *b = head;
        int c1 = 1, c2 = 1;

        while (a && c1 < i) { a = a->next; c1++; }
        while (b && c2 < j) { b = b->next; c2++; }

        if (!a || !b) return false; 

        Audio* temp = a->data;
        a->data = b->data;
        b->data = temp;

        return true;
    }
    
    ~PlayList() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }





      void saveSongsToFile(ofstream& file){
        Node* temp=head;
        while (temp)
        {
          file<<temp->data->getName()<<"|"<<temp->data->getpath()<<endl;
          temp=temp->next;
        }
        
      }



    };
      
      struct playlistnode{
        PlayList*data;
        playlistnode*next;
        playlistnode*prev;

        playlistnode(PlayList* pl){
          data=pl;
          next=prev=NULL;
        }
      };

      class playlistManager{
      private:
        playlistnode*head;
        playlistnode* tail;
      public:
        playlistManager(){
          head=tail=NULL;
        }
        void addplaylist(string name){
          PlayList*newPL=new PlayList(name);
          playlistnode* newNode= new playlistnode(newPL);
          if(head==NULL){
            head=tail=newNode;
          }
          else{
            tail->next=newNode;
            newNode->prev=tail;
            tail=newNode;
          }
          cout<<"\nSUCCESS play list"<<name<<"created.\n";

        }
        void displayAll(){
          if(head==NULL){
            cout<<"\nno playlist available. create one first\n";
            return;
          }
          playlistnode* temp=head;
          int i=1;
          while (temp)
          {
            cout<<i<<". "<<temp->data->getname()<<endl;
            temp=temp->next;
            i++;
          }
        }

          PlayList*getplaylistIndex(int index){
            playlistnode* temp=head;
            int count=1;
            while(temp){
              if (count==index)
              {
                return temp->data;
              }
              temp=temp->next;
              count++;   
            }
            return NULL;
          }
          
          bool removePlaylist(int index) {
        if (head == NULL || index < 1) return false;

        playlistnode* temp = head;
        int count = 1;

        while (temp && count < index) {
            temp = temp->next;
            count++;
        }

        if (!temp) return false; 

        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next; 

        if (temp->next) temp->next->prev = temp->prev;
        else tail = temp->prev; 

        delete temp->data; 
        delete temp;       
        
        cout << "\n[SUCCESS] Playlist removed.\n";
        return true;
    }


        
          void saveALL(string filename){
          ofstream file(filename);
          playlistnode*temp=head;
          while (temp)
          {
            file<<"PLAYLIST:"<<temp->data->getname()<<endl;
            temp->data->saveSongsToFile(file);
            file<<"END"<<endl;
            temp=temp->next;
          }
          file.close();
          cout<<" SUCCESS saved to"<<filename<<endl;
          }

          void loadALL(string filename){
          ifstream file(filename);
          if(!file.is_open()){
          cout<<"ERROR file is not found"<<endl;
          return;
          }
          string line;
          PlayList*currentPL=NULL;
          while (getline(file,line))
          {
            if(line.empty())continue;

            if(line.find("PLAYLIST:")==0){
            string PlName=line.substr(9);
            addplaylist(PlName);
            if(tail) currentPL=tail->data;
            
            }
            else if(line=="END"){
            currentPL=NULL;
            }
            else if(currentPL!=NULL){
            int halfName=line.find('|');
            if(halfName!=-1){
            string sname=line.substr(0,halfName);
            string spath=line.substr(halfName+1);
            string sAlias="a"+to_string(rand());

            currentPL->addSong(new Audio(sname,spath,sAlias));


            }
            
            }

 

          }
          file.close();
          cout<<" SUCCESS data loaded succesfully"<<endl;
          }
          
        };

  void drawMenu() {
    system("cls"); 
    cout << "\n\t   Audio Player Project\n";
    cout << "\t     Data Structure Course\n\n";
    cout << "+=======================================================+\n";
    cout << "|              MAIN MENU                                |\n";
    cout << "+=======================================================+\n";
    cout << "| 1. Create New Playlist                                |\n";
    cout << "| 2. Add Song to a Playlist                             |\n";
    cout << "| 3. Display All Playlists                              |\n";
    cout << "| 4. Display Songs in a Playlist                        |\n";
    cout << "| 5. PLAY Playlist (Player Mode)                        |\n";
    cout << "|                                                       |\n";
    cout << "| 6. Remove Audio from an exisiting playlist            |\n";
    cout << "| 7. Update the order of exisiting playlist             |\n";
    cout << "| 9. Save Data to File (Save)                           |\n";
    cout << "| 10. Load Data from File (Load)                        |\n";
    cout << "| 11. Remove an exisiting playlist                      |\n";
    cout << "|                                                       |\n";
    cout << "| 12. Exit                                              |\n";
    cout << "+=======================================================+\n";
    cout << "Your choice: ";
}
      void playermode(PlayList* pl) {
    system("cls");
    cout << "--- Player Mode: " << pl->getname() << " ---\n";
    cout << "\n[Right] Next\n[Left] Prev\n[Up] Pause\n[Down] Resume\n[Q]Quit\n";
    
    pl->startplaying();

    int key; 

    while (true) {
        if (_kbhit()) { 
            key = _getch();

            if (key == 'q' || key == 'Q') {
                pl->stopcurrent();
                break;
            }
            
            else if (key == -32 || key == 224 || key == 0) { 
                
                int arrowCode = _getch(); 
                
                switch (arrowCode) {
                 case 77: 
                        cout << " [Next] ";
                        pl->nextsong(); 
                        break;   
                    case 75: 
                        cout << " [Prev] ";
                        pl->playprev(); 
                        break;   
                    case 72: 
                        pl->pausecurrent(); 
                        cout << "\n(Paused)"; 
                        break; 
                    case 80:  
                        pl->resumecurrent(); 
                        cout << "\n(Resumed)"; 
                        break;
                }
            }
        }
        Sleep(100); 
    }
}


int main(){
   playlistManager manager;
   manager.addplaylist("Mix tape");
   PlayList*p1=manager.getplaylistIndex(1);
   if (p1)
   {
    p1->addSong(new Audio("Song 1","test.mp3","s1"));
    p1->addSong(new Audio("Song 2","test2.mp3","s2"));
     p1->addSong(new Audio("Song 3","test3.mp3","s3"));

   }
   int choice;
   while (true)
   {
    drawMenu();
    if (!(cin>>choice))
    {
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    if (choice==12)
    {
    break;
    }
    switch (choice)
    {
    case 1:{
      cout<<"enter playlist name: ";
      string name;
      cin>>name;
      manager.addplaylist(name);
      system("pause");
      break;}

    
    case 2:{
      cout<<"\nAvailable playlist:\n";
      manager.displayAll();
      cout<<"select playlist id: ";
      int id;
      cin>>id;
      PlayList*pl=manager.getplaylistIndex(id);
      if(pl){
        string sName,sPath,sAlias;
        cout<<"song name: ";
        cin>>sName;
        cout<<"file path: ";
        cin>>sPath;
        sAlias="a"+to_string(rand());
        pl->addSong(new Audio(sName,sPath,sAlias));
        cout<<"song added\n";
      }
      else{
        cout<<"invalid id\n";
      }
      system("pause");
      break;
    }

    case 3:{
      manager.displayAll();
      system("pause");
      break;
    }

    case 4:{
      cout<<"\nSelect playlist to view songs:\n";
      manager.displayAll();
      int id;
      cin>>id;
      PlayList*pl=manager.getplaylistIndex(id);
      if(pl){
        pl->displaysong();
      }
      system("pause");
      break;
    }
    case 5:{
      cout<<"\nSelect playlist to PLAY:\n";
      manager.displayAll();
      int id;
      cin>>id;
      PlayList*pl=manager.getplaylistIndex(id);
      if (pl){
        playermode(pl);
      }
      break;
    }
    default:
    cout<<"invalid option.\n";
    system("pause");

   case 6: {
        cout << "\nSelect Playlist ID to remove song from: ";
        manager.displayAll();
        int pid; cin >> pid;
        PlayList* pl = manager.getplaylistIndex(pid);
        if (pl) {
            pl->displaysong();
            cout << "Enter Song Number to Remove: ";
            int sid; cin >> sid;
            if (pl->removeSong(sid)) {
                cout << "Song removed successfully.\n";
            } else {
                cout << "Failed to remove song (Invalid ID).\n";
            }
        } else {
            cout << "Invalid Playlist ID.\n";
        }
        system("pause");
        break;
    } 

    case 7: {
        cout << "\nSelect Playlist ID to swap songs: ";
        manager.displayAll();
        int pid; cin >> pid;
        PlayList* pl = manager.getplaylistIndex(pid);
        if (pl) {
            pl->displaysong();
            int id1, id2;
            cout << "Enter First Song ID: "; cin >> id1;
            cout << "Enter Second Song ID: "; cin >> id2;
            if (pl->swapSongs(id1, id2)) {
                cout << "Songs Swapped Successfully.\n";
            } else {
                cout << "Invalid Song IDs.\n";
            }
        } else {
            cout << "Invalid Playlist ID.\n";
        }
        system("pause");
        break;
    }

    case 9:{
    cout<<"Saving data to 'data.txt'..\n";
    manager.saveALL("data.txt");
    system("pause");
    break;
    }
    case 10:{
    cout<<"loading data from 'data.txt'..\n";
    manager.loadALL("data.txt");
    system("pause");
    break;
    }
 
    case 11: {
        cout << "\n--- DELETE PLAYLIST ---\n";
        manager.displayAll();
        cout << "Enter Playlist ID to delete: ";
        int id; cin >> id;
        if (manager.removePlaylist(id)) {
        } else {
            cout << "Invalid Playlist ID.\n";
        }
        system("pause");
        break;
    }



    }
      
    
   }
   
   
    
    return 0;
} 
