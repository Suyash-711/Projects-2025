// Do NOT add any other includes
using namespace std;
#include "dict.h"
int NodeB:: height2(NodeB *root){
    if(root==NULL){
        return -1;
    }
    return root->height;
}
int NodeB::getbalance(NodeB *root){
    if(root==NULL){
        return -1;
    }
    int lh=height2(root->left);
    int rh=height2(root->right);
    return lh-rh;
}
NodeB* NodeB::leftleftrotation(NodeB *root){
    NodeB *x=root->left;
    root->left=x->right;
    x->right=root;
    root->height=max(height2(root->left),height2(root->right))+1;
    x->height=max(height2(x->left),height2(x->right))+1;
    return x;
}
NodeB* NodeB::rightrightrotation(NodeB *root){
    NodeB *x=root->right;
    root->right=x->left;
    x->left=root;
    root->height=max(height2(root->left),height2(root->right))+1;
    x->height=max(height2(x->left),height2(x->right))+1;
    return x;
}
NodeB* NodeB::leftrightrotation(NodeB *root){
    root->left=rightrightrotation(root->left);
    return leftleftrotation(root);
}
NodeB* NodeB::rightleftrotation(NodeB *root){
    root->right=leftleftrotation(root->right);
    return rightrightrotation(root);
}
NodeB* NodeB::insert_word(NodeB *root,string k){
    if(root==NULL){
        root=new NodeB(k);
        return root;
    }
    if(k<root->data){
        root->left=insert_word(root->left,k);
    }
    else if(k>root->data){
        root->right=insert_word(root->right,k);
    }
    else{
        root->count+=1;
        return root;
    }
    root->height=max(height2(root->left),height2(root->right))+1;
    int balance=getbalance(root);
    if(balance > 1 && k < root->left->data){
        return leftleftrotation(root);
    }
    else if(balance < -1 && k > root->right->data){
        return rightrightrotation(root);
    }
    else if(balance > 1 && k > root->left->data){
        return leftrightrotation(root);
    }
    else if(balance < -1 && k < root->right->data){
        return rightleftrotation(root);
    }
    return root;
}
int NodeB::search(NodeB *root,string k){
    if(root==NULL){
        return 0;
    }
    if(root->data==k){
        return root->count;
    }
    if(k<root->data){
        return search(root->left,k);
    }
    else{
        return search(root->right,k);
    }
}
float Dict::scoresearch(NodeB *root,string k){
    if(root==NULL){
        return 0;
    }
    if(root->data==k){
        return root->score;
    }
    if(k<root->data){
        return scoresearch(root->left,k);
    }
    else{
        return scoresearch(root->right,k);
    }
}
Dict::Dict(){
    root=NULL;

}

Dict::~Dict(){  
    delete root; 
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here 
    string s=sentence;
    int i=0;
    while(i<s.size()){

        if(s[i]==' ' || s[i]=='.' || s[i]==',' || s[i]=='-' || s[i]==':' || s[i]=='!' || s[i]=='"' || s[i]=='\'' || s[i]=='(' || s[i]==')' || s[i]=='?' || s[i]=='[' || s[i]==']' ||  s[i]==';' || s[i]=='@'){
            i++;
            continue;
        }
        string word="";
        while(i<s.size() && s[i]!=' ' && s[i]!='.' && s[i]!=',' && s[i]!='-' && s[i]!=':' && s[i]!='!' && s[i]!='\"' && s[i]!='\'' && s[i]!='(' && s[i]!=')' && s[i]!='?' && s[i]!='[' && s[i]!=']'  && s[i]!=';' && s[i]!='@'){
            if(s[i]>=65 && s[i]<=90){
                s[i]=s[i]+32;
            }
            word+=s[i];
            i++;
        }
        root=root->insert_word(root,word);
        
    } 
}

int Dict::get_word_count(string word){
    // Implement your function here 
    for(int i=0;i<word.size();i++){
        if(word[i]>=65 && word[i]<=90){
            word[i]+=32;
        }
    }
    return root->search(root,word); 
}
void Dict::printing(NodeB *root,ofstream &outf){
    if(root==NULL){
        return ;
    }
    printing(root->left,outf);
    outf<<root->data<<", "<<root->count<<endl;
    printing(root->right,outf);
}
void Dict::dump_dictionary(string filename){
    // Implement your function here  
    ofstream outf(filename,ios::out);
    printing(root, outf);
    outf.close();
    return;
}




