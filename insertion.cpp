#include<iostream>
#include<queue>
using namespace std;
struct node{
    node *next;
    int arr[50];//key array
    node *add[50+1];//address array
    int n;//no of elements
};
struct path{
    node *adr;
    int p;
};
void insert(node *ptr,int value,node *left,node *right);
int split(node *ptr,node**left,node**right,int degree);
void tree(node **root,int value,int degree);
void print(node *root);
void insert_null(node *root,int degree);
void level_order(node *root);
int main(){
    node *root=NULL;
    int input;
    cin>>input;
while(input!=-1){
    tree(&root,input,4);
    cout<<endl;
    cin>>input;
}
node *temp=root;
/*for(int i=0;i<temp->n;i++){
    cout<<temp->arr[i]<<" ";
}*/
level_order(root);
    return 0;
}
path* trace_path(node *root,int value,int *no){
    node *temp=root;
    path *ptr=new path[50];
    int num=0;
    while(1){
      ptr[num].adr=temp;
      int pos=temp->n;
      for(int i=0;i<temp->n;i++){
          if(value<=temp->arr[i]){
              pos=i;
              break;
          }
      }
        ptr[num++].p=pos;
        temp=temp->add[pos];
        if(temp==NULL){
            *no=num;
            return ptr;
         }
    }
}
void tree(node **root,int value,int degree){
    if(*root==NULL){
        *root=new node;
        (*root)->n=1;
        (*root)->arr[0]=value;
        insert_null(*root,degree);
        return;
    }

    int num=0;
    path *ptr=trace_path(*root,value,&num);
    cout<<" trace num "<<num;
    node *temp=ptr[num-1].adr;
    node *left=NULL,*right=NULL;
    int flag=0;
    while(num){
        temp=ptr[num-1].adr;
        insert(temp,value,left,right);
        cout<<" new n "<<temp->n;
        if(temp->n<degree){
            flag=1;
            break;
        }
        value=split(temp,&left,&right,degree);
        num--;
    }
    if(flag==0){
        *root=new node;
         insert_null(*root,degree);
        (*root)->arr[0]=value;
        (*root)->n=1;
        (*root)->add[0]=left;
        (*root)->add[1]=right;
    }
}
int split(node *ptr,node**left,node**right,int degree){
    int mid=(degree)/2;
    cout<<"mid "<<mid;
     *left=new node;
      insert_null(*left,degree);
     (*left)->n=0;
    for(int i=0;i<mid;i++){
        (*left)->arr[i]=ptr->arr[i];
        (*left)->n++;
    }
    for(int i=0;i<=mid;i++){
        (*left)->add[i]=ptr->add[i];
    }
    *right=new node;
     insert_null(*right,degree);
    (*right)->n=0;
    for(int i=mid+1,j=0;i<ptr->n;i++,j++){
        (*right)->arr[j]=ptr->arr[i];
        (*right)->n++;
    }
    for(int i=mid+1,j=0;i<=ptr->n;i++,j++){
        (*right)->add[j]=ptr->add[i];
    }
    int temp=ptr->arr[mid];
     delete ptr;
    return temp;
}
void insert(node *ptr,int value,node *left,node *right){
    int pos=ptr->n;
    for(int i=0;i<ptr->n;i++){
        if(value<=ptr->arr[i]){
            pos=i;
            break;
        }
    }
    for(int i=ptr->n-1;i>=pos;i--){
        ptr->arr[i+1]=ptr->arr[i];
    }
    for(int i=ptr->n-1;i>=pos;i--){
        ptr->add[i+2]=ptr->add[i];
    }
    ptr->arr[pos]=value;
    ptr->add[pos]=left;
    ptr->add[pos+1]=right;
    ptr->n=ptr->n+1;
}
void insert_null(node *root,int degree){
    for(int i=0;i<=degree;i++){
        root->add[i]=NULL;
    }
}
void level_order(node *root){
cout<<endl;
queue <node*> q;
q.push(root);
node *temp;
 while(!q.empty()){
    temp=q.front();
    q.pop();
    if(temp==NULL)continue;
    for(int i=0;i<temp->n;i++){
        cout<<temp->arr[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<=temp->n;i++){
        q.push(temp->add[i]);
    }
 }
}

