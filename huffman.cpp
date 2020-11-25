#include<iostream>
#include<fstream>
#include<vector>
#include<numeric>
#include<bits/stdc++.h>
using namespace std;

struct Node{
int main_char;
double frequency;
string binary;
struct Node *right;
struct Node *left;
};

map<char,string> final_coded;

void string_join(Node *k){
    Node *a=k;
    if(a->left==NULL && a->right==NULL){
        final_coded[a->main_char]=a->binary;
        char c=a->main_char;
        cout<<c<<" "<<a->binary<<endl;
        return;
    }
    if(a->right!=NULL){
        string bst("1");
        a->right->binary=a->binary+bst;
        string_join(a->right);
    }
    if(a->left!=NULL){
        string bst("0");
        a->left->binary=a->binary+bst;
        string_join(a->left);
    }

}

int main(){
vector <pair<double,int> > arr(128);
fstream text;
text.open("cleaniness.txt",ios::in);
char ch;
for(int i=0;i<128;i++){
    arr[i].first=0;
}
while(text>>ch){
    if(ch<128)
    arr[ch].first+=1;
}
float s=0;
for(int i=0;i<128;i++){
    s+=arr[i].first;
}
for(int i=0;i<128;i++){
    arr[i].second=i;
    arr[i].first=arr[i].first/s;
}


vector <Node *> storing_node;

Node *a;
for(int i=0;i<128;i++){
    a=new Node;
    a->frequency=arr[i].first;
    a->main_char=arr[i].second;
    a->right=NULL;
    a->left=NULL;
    storing_node.push_back(a);
}
sort(arr.begin(),arr.end());

vector <pair<double,int> > non_zero;
vector<pair<double,int> >::iterator itr;
for(int i=127;i>=0;i--){
    if(arr[i].first!=0){
        int gg=arr[i].second;
        float gh=arr[i].first;
        non_zero.push_back(make_pair(gh,gg));
    }
    else{
        break;
    }
}
sort(non_zero.begin(),non_zero.end());
float l;
float b;
int root;
while(!non_zero.empty()){
    if(non_zero.size()==1){
        root=non_zero[0].second;
        break;
    }
    l=non_zero[0].first;
    b=non_zero[1].first;
    Node *k=new Node();
    k->frequency=l+b;
    k->main_char=storing_node.size();
    k->left=storing_node[non_zero[0].second];
    k->right=storing_node[non_zero[1].second];
    non_zero.push_back(make_pair(l+b,storing_node.size()));
    storing_node.push_back(k);
    non_zero.erase(non_zero.begin(),non_zero.begin()+2);
    sort(non_zero.begin(),non_zero.end());
}
a=storing_node[root];
string hh("");
storing_node[root]->binary=storing_node[root]->binary+hh;
string_join(a);
ofstream output_file("outputfile.txt");
text.close();
text.open("cleaniness.txt",ios::in);
while(text>>ch){
    string bin=final_coded[ch];
    output_file<<bin;
}
output_file.close();
ifstream outp("outputfile.txt");
while(outp>>ch){
    cout<<ch;
}
cout<<endl;
output_file.close();
}
