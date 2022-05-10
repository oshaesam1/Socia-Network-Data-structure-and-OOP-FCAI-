//1-Usama Mohamed Gebril Id: 20190087
//2-Salma adel abubkr    Id: 20190241
//3-Heba_tullah Adel Abd_elgaber Id: 20190609
//4-Huda Mohamed Ramdan  Id:20190610
//5-Samah Mostafa Hussein Id:20190248
//6-Aya tullah Essam-eldien Mohammed Id:20190123


#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class User{
    public:
    string userName;
    string name;
    string email;
    User(){}
};

struct TNode
{
friend class myList ;
 string key;
 int pr;
 User *user;
 TNode *left, *right;


};

class Treap{
friend class myList ;
public:
Treap (TNode *root )
{
//    root->newNode(0);

}


TNode *rightRotate(TNode *r)
{
 TNode *s = r->left, *T1 = s->right;

 // Perform rotation
 s->right = r;
 r->left = T1;

 // Return new root
 return s;
}


TNode *leftRotate(TNode *s)
{
 TNode *r = s->right, *T1 = r->left;

 // Perform rotation
 r->left = s;
 s->right = T1;

 // Return new root
 return r;
}

TNode* newNode(string key , User *user)
{
 TNode* temp = new TNode;
 temp->key = key;
 temp->pr = rand()%100;
 temp->left = temp->right = NULL;
 temp->user =user;
//cout<<"inside newNode "<<temp->user->email<<endl<<"thanks"<<endl;
 return temp;
}

TNode* find(TNode* root, string key)
{
 // Base Cases: root is null or key is present at root
 if (root == NULL || root->key == key)
 return root;

 // Key is greater than root's key
 if (root->key < key)
 return find(root->right, key);

 // Key is smaller than root's key
 if (root->key > key)
 return find(root->left, key);

 else return 0 ;
}

TNode* addFriend(TNode* root, string key, User * use)
{
 // If root is NULL, create a new node and return it
 if (!root)
  return newNode(key , use);
 // If key is smaller than root
 if (key <= root->key)
 {
  // Insert in left subtree
  root->left = addFriend(root->left, key,use);

  // Fix Heap property if it is violated
  if (root->left->pr> root->pr)
   root = rightRotate(root);
 }
 else // If key is greater
 {
  // Insert in right subtree
  root->right = addFriend(root->right, key, use);

  // Fix Heap property if it is violated
  if (root->right->pr > root->pr)
   root = leftRotate(root);
 }

 return root;
}

TNode* deleteFriend(TNode* root, string key)
{
	if (root == NULL)
		return root;

	if (key < root->key){
		root->left = deleteFriend(root->left, key);
	}
	else if (key > root->key){
		root->right = deleteFriend(root->right, key);
	}

	else if (root->left == NULL)
	{
		TNode *temp = root->right;
		delete(root);
		root = temp;
	}

	else if (root->right == NULL)
	{
		TNode *temp = root->left;
		delete(root);
		root = temp;
	}

	else if (root->left->pr < root->right->pr)
	{
		root = leftRotate(root);
		root->left = deleteFriend(root->left, key);
	}
	else
	{
		root = rightRotate(root);
		root->right = deleteFriend(root->right, key);
	}

	return root;
}

void printFriends( User *(* info))
{
    int i=0;
    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Your Friends: "<<endl;
    while(info[i]!=NULL)
    {
        cout<<"-"<<i+1<<"- "<<info[i]->userName<<" , "<<info[i]->name<<endl;
        i++;
    }
    cout<<"-----------------------------------------------------"<<endl;
}

void printTreap(TNode* root ,string *friends,int &counter , User *(* info))
{

    if (root)
    {
      printTreap(root->left,friends,counter ,info);
     // cout << "key : "<< root->key ;
     // cout << "email : "<< root->user->email ;

//      <<"  priority  "<<root->priority
      friends[counter]=root->key;
      info[counter]=root->user;
      counter++;
      if (root->left)
      {
        //  cout << " -|- left child : " << root->left->key;
        //  cout << "email : "<< root->left->user->email ;
          friends[counter]=root->left->key;
          info[counter]=root->left->user;
          counter++;
      }
      if (root->right)
      {
        // cout << " -|- right child : " << root->right->key;
        // cout << "email : "<< root->right->user->email ;
          friends[counter]=root->right->key;
          info[counter]=root->right->user;
          counter++;
      }

      //cout << endl;
      printTreap(root->right,friends,counter , info);

    }
    friends[counter]="0";
    info[counter]=NULL;
    //cout <<endl ;

  //  return friends;
}

};


struct Node
{
//    string userName;
//    string name;
//    string email;
    User *user;
    Treap *friendsBST;
    Node *next;

    Node(){user =new User();}
    void userData(string userName, string name, string email)
            {
                user =new User();
                this->user->userName = userName;
                this->user->name = name;
                this->user->email= email;
                friendsBST=0;
            }
    void setFriendsBST (Treap *friendsBST)
    {
        this ->friendsBST = friendsBST;
    }
    string getUserName(){return user->userName;}
    string getName(){return user->name;}
    string getEmail(){return user->email;}
};

 class myList
 {
//    friend class Treap ;
//    friend class TreapNode;
    private:
//    string userName;
//    string name;
//    string email;

    Node *head;
    Node *tail;

 public:
    User *user;
    myList ()
    {
        head = 0;
        tail=0;
        user =new User();
        user->userName= user->name= user->email = " ";

    }

    Node * gethead(){return head;}
    void setUser(string userName, string name, string email)
    {
        user =new User();
        this->user->userName = userName;
        this->user->name = name;
        this->user->email = email;
    }
    myList(string userName, string name, string email)
            {
                user =new User();
                head = 0;
                tail=0;
                this->user->userName = userName;
                this->user->name = name;
                this->user->email = email;
            }
            string getUserName(){return user->userName;}
            string getName(){return user->name;}
            string getEmail(){return user->email;}


   void insert (string userName, string name, string email)
   {
       Node * newNode;
       newNode = new Node() ;
       if(head == 0)
        {
            newNode->userData(userName, name, email);
            setUser(userName,name,email);
           // cout<<"new node "<<newNode->getName()<<endl;
            head = newNode;
            tail = newNode;
        }

       if (head != 0)
       {
           newNode->next = head;
           newNode->userData(userName, name, email);
           setUser(userName,name,email);
           //cout<<"new node "<<newNode->getName()<<endl;
           head = newNode;
           tail->next=0;
       }

   }

   void print ()
   {
    Node  *curr;
    curr=head;
    while(curr!=0)
    {
        cout<< curr->getUserName() + ", " + curr->getName() +", "+ curr->getEmail() <<endl;
        curr=curr->next;
    }

   }


 Node* findByUserName (string userName)
   {
    Node *curr=head;
    TNode *root=0;
    //User *use;

    while (curr!=0)
    {
        //cout<<"curr->user->userName "<<curr->user->userName<<"user->userName "<<user->userName<<endl;
        if (curr->user->userName != userName)
        {
            curr = curr->next;
        }
        else
        {

          root=curr->friendsBST->addFriend(root,userName,curr->user);
        //cout<<"curr "<<curr->getEmail()<<endl;
        return curr;
        }
    }
    return 0;/////////////
   }

   void ListAllFirends( TNode *root  )
{

    myList obj ;
cout <<  root->key<<endl ;
if (root != 0)
 {

  if (root->left)
  {
     cout << root->left->key<<endl;

  }

  if (root->right)
   {cout << root->right->key<<endl;

   }
   ListAllFirends(root->left);
   ListAllFirends(root->right);

 }
    while (root!=0)
    {

    cout << root->key <<","<< endl ;
//    obj.findByUserName(root->key))->getName()<<
    cout << root->left->key;
    cout << root->right->key;
    }

}


   ~myList ()
   {

   }
 };


 myList buildLinkedList(){

    myList userList ;
    string username,name,email;
    fstream userData("all-users.in",ios::in) ;
    userData.seekg(0,ios::beg);
    while (!userData.eof()){
    getline(userData, username,',');
    getline(userData, name,',');
    getline(userData, email,'\n');
    userList.insert(username,name,email);
   // cout<<"hello "<<userList.user->userName<<endl;
    userData.peek();

    }
    userData.close();
   // userList.print();
    return userList;
 }

 Treap* buildTreap(Node*  newNode , string USERNAME ,TNode *(&root) ,myList userList){


     Treap *treap =new Treap(root) ;
    // Node*  newNode = (userList.findByUserName(USERNAME));
        // add friends
    fstream newfile;
    newfile.open("all-users-relations.in",ios::in);
    if (newfile.is_open()){
    newfile.seekg(0,ios::beg);
    string u1,u2;
    /****************search to get user information*************************************/
    Node*  n = (userList.findByUserName(USERNAME));
    /////////////////////////////////////////////////////////////////////////////////////
    root=treap->addFriend(root,USERNAME , n->user);
    while(!newfile.eof()){
        getline(newfile, u1,',');
        getline(newfile, u2,'\n');
        if (u1==USERNAME )
        {
            n = (userList.findByUserName(u2));
            root=treap->addFriend(root,u2,n->user);
            &newNode;
        }
        if (u2==USERNAME)
        {
            n = (userList.findByUserName(u1));
            root=treap->addFriend(root,u1 ,n->user);

        }
        else continue;

            newfile.peek();
            }

        }

        newNode->setFriendsBST(treap);

        ///////////////////////////////////////////////////////////////////////////////////////


    return treap;

 }



 void peopleYouMayKnow(myList newlist , string USERNAME ,string* friends)
 {

        TNode *root=0;
        Node  *curr;
        curr=newlist.gethead();
        int counterPeople=0;
        int counter=0;
        /////////////////////////////for main user/////////////////////////////////////////

        string *peopleYouMayKnow=new string[20];
        string *peopleUserName=new string[20];
        //treap->printFriends(friends);
        ///////////////////////////////////////////////////////////////////////////////////
        while(curr!=0)
        {
            if(curr->getUserName()!=USERNAME)
            {
                /********************************************************************************/
                int kk=0, flag=0;
                while(friends[kk]!="0")
                    {
                        if(curr->getUserName()==friends[kk])
                        {
                            flag=1;
                            break;
                        }
                        kk++;
                    }
                    ////////////////////////////////////////////////////////////////////////////////
//                    if(counterPeople==5)
//                    {
//                        break;
//                    }
                    if(flag==0)
                    {
                        peopleYouMayKnow[counterPeople]=curr->getUserName();
                        peopleUserName[counter]=newlist.findByUserName(curr->getUserName())->getName();
                        counterPeople++;
                        counter++;
                    }
                    flag=0;
                    ///////////////////////////////////////////////////////////////////////////////
                }


            curr=curr->next;
        }

        /****************************************Print array***************************************/
        cout<<"-----------------------------------------------------"<<endl;
        cout<<"People You May Know: "<<endl;
        for(int j=0;j<counterPeople;j++)
        {
            cout<<"-"<<j+1<<"-"<<peopleYouMayKnow[j]<<" , "<<peopleUserName[j]<<endl;
        }
        cout<<"-----------------------------------------------------"<<endl;
        /****************************************Print array***************************************/
        cout<<"-----------------------------------------------------"<<endl;
        cout<<"People You May Know(Recommended): "<<endl;
        for(int j=0;j<5;j++)
        {
            cout<<"-"<<j+1<<"-"<<peopleYouMayKnow[j]<<" , "<<peopleUserName[j]<<endl;
        }
        cout<<"-----------------------------------------------------"<<endl;

 }
User* * deleteDuplicate(User * (*info))
{
    User* (*newfriends)=new User * [100];
    int coun=0,flag=0;

    for(int i=0; info[i]!=NULL;i++)
    {
        for(int j=i+1; info[j]!=NULL; j++)
        {
            //cout<<friends[i]<<" :: "<<friends[j]<<endl;
            if((info[i]->userName==info[j]->userName)&& (i!=j))
            {
                //cout<<friends[i]<<" :-: "<<friends[j]<<endl;
                flag=1;
                break;
            }
        }
        //cout<<"************************************************************"<<endl;
        if(flag==0)
        {
            newfriends[coun]=info[i];
            coun++;
            //cout<<friends[i]<<endl;
        }
        flag=0;
    }
    newfriends[coun]=NULL;
return newfriends;
}
int alreadyFriend(string name,User *(*user))
{
    int flag=0;
    for(int i=0; user[i]!=NULL; i++)
    {
        if((user[i]->userName==name))
        {
            flag=1;
            break;
        }
    }
    return flag;
}
int main()
{
     string *newfriends=new string[100];
     int choose1,choose2;
     string username;
     //string *friends;
    while(true){

         cout<<"1-Login"<<endl<<"2-Exit"<<endl;
         cin>>choose1;
         if(choose1==1){
             cout<<"Please Enter User Name: ";
             cin>>username;
            myList newlist = buildLinkedList();
           // cout<<"test "<<newlist.getName()<<endl;
            Node*  newNode=newlist.findByUserName(username);
            //cout<<"jojo"<<newNode->getName()<<endl<<endl;
            TNode *root=0;
            //root->user->name=(newNode->getName());

            //cout<<root->user->email<<endl;
            if(newNode!=0){
                cout<<"\n           Hello "<<username<<endl<<endl;
                /******************************************************************************************/
                 Treap *treap =new Treap(root) ;
                        treap=buildTreap(newNode , username ,root , newlist);

                //////////////////////////////**application**////////////////////////////////////////////
                while(true)
                {
                    cout<<"1-List all friends"<<endl<<"2-Search by UserName"<<endl;
                    cout<<"3-Add friend"<<endl<<"4-Remove friend"<<endl;
                    cout<<"5-People you may know"<<endl<<"6-logout"<<endl;
                    cin>>choose2;
                    if (choose2==1){
                        string *friends=new string[100];
                        User *(*user)=new  User *[100];
                        int coun=0;
                        treap->printTreap(root,friends,coun,user);
                        user=deleteDuplicate(user);
                        //newfriends=deleteDuplicate(user);
                        treap->printFriends( user);
                    }
                    else if(choose2==2){
                        string USERNAME;
                        cout << "Enter User Name: ";
                        cin>>USERNAME;
                        TNode *res = treap->find(root, USERNAME);
                        if(res == NULL){
                                cout << "\n Not Found "<<endl;
                                cout<<"-----------------------------------------------------"<<endl;
                        }
                        else


                           cout << USERNAME <<", "<< newlist.findByUserName(USERNAME)->getName()
                           <<", "<<newlist.findByUserName(USERNAME)->getEmail()<<endl;
                           cout<<"-----------------------------------------------------"<<endl;


                    }
                    else if(choose2==3){
                        int i=0;
                        string USERNAME;
                        cout << "Enter Friend Name: ";
                        cin>>USERNAME;
                        /***************Make sure that friend name is one of users***************************/
                        /////////////////////////////////////////////

//
//                        string *friends=new string[100];
//
//                        int coun=0;
//                        treap->printTreap(root,friends,coun);
//                        friends=deleteDuplicate(friends);
//                        newfriends=deleteDuplicate(friends);
//
//
//                        cout<<"-----------------------------------------------------"<<endl;
//                        cout<<"Your Friends: "<<endl;
//                        while(newfriends[i]!="0")
//                        {
//                            cout<<"-"<<i+1<<"- "<<newfriends[i]<<endl;
//                            i++;
//                        }

                        Node * n=newlist.findByUserName(USERNAME);
                        //Node * n2=newlist.findByUserName(USERNAME);
                        string *friends=new string[100];
                        User *(*user)=new  User *[100];
                        int coun=0;
                        treap->printTreap(root,friends,coun,user);
                        user=deleteDuplicate(user);
        /*************************************check if already friend****************************************/
                        int flag0=0;
                        flag0=alreadyFriend(USERNAME,user);
        /***************************************************************************************************/

                            //cout<<endl<<endl<<n->getUserName()<<endl<<endl;
                        if( (n!=0) && (n->getUserName()!= username) && (flag0==0) ){
                            root=treap->addFriend(root,USERNAME,n->user);
                            cout<<"You are now friends "<<endl;
                            cout<<"-----------------------------------------------------"<<endl;
                            treap->printTreap(root,friends,coun,user);
                            user=deleteDuplicate(user);
                        }

                        else if(flag0==1 &&n->getUserName()!= username ){
                            cout<<"You are already friends"<<endl;
                            cout<<"-----------------------------------------------------"<<endl;
                            continue;
                        }

                        else{
                            cout<<"Sorry friend can't be added"<<endl;
                            cout<<"-----------------------------------------------------"<<endl;
                            continue;
                        }

                    }
                    else if(choose2==4){

                        string USERNAME;
                        cout << "Enter Friend Name: ";
                        cin>>USERNAME;
                        /***************Make sure that friend name is one of users***************************/
                        TNode *res = treap->find(root, USERNAME);
                        if(res == NULL){
                                cout << "\n Friend is Not Found "<<endl;
                                cout<<"-----------------------------------------------------"<<endl;
                        }
                        else{
                            root=treap->deleteFriend(root,USERNAME);
                            cout << "\n Remove Friend successfully"<<endl;
                            cout<<"-----------------------------------------------------"<<endl;
                            string *friends=new string[100];
                            User *(*user)=new  User *[100];
                            int coun=0;
                            treap->printTreap(root,friends,coun,user);
                            user=deleteDuplicate(user);
                        }

                    }
                    else if(choose2==5){
                        string *friends=new string[100];
                        User *(*user)=new  User *[100];
                        int coun=0;
                        treap->printTreap(root,friends,coun,user);
                        user=deleteDuplicate(user);
                        treap->printFriends(user);
                        peopleYouMayKnow(newlist , username , friends);
                    }
                    else if(choose2==6){
                        break;
                    }
                    else
                        cout<<"Please Enter Valid Number"<<endl;





                }

            }
            else{
                cout<<"Not Found Please Enter Valid UserName "<<endl;
            }




         }

         else if (choose1==2){
            break;
         }
         else
            cout<<"Please Enter Valid Number"<<endl;

    }
 return 0;


}

