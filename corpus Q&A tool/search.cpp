// Do NOT add any other includes
#include "search.h"
SearchEngine::SearchEngine(){
    head=NULL;
}

SearchEngine::~SearchEngine(){
    delete head;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){ 
    if(head==NULL){
        head=new NodeA(book_code,page,paragraph,sentence_no,sentence);
        return;
    }
    NodeA *current=new NodeA(book_code,page,paragraph,sentence_no,sentence);
    current->next=head;
    head=current;
}
vector<int> prefixfunc(string &s){
    if(s[0]>=65 && s[0]<=90){
        s[0]+=32;
    }
    int n=s.size();
    vector<int> pi(n,0);
    for(int i=1;i<n;i++){
        if(s[i]>=65 && s[i]<=90){
            s[i]+=32;
        }
        int j=pi[i-1];
        while(j>0 && s[i]!=s[j]){
            j=pi[j-1];   
        }
        if(s[i]==s[j]){
            j++;
        }
        pi[i]=j;
    }
    return pi;
}
Node* SearchEngine::search(string pattern, int& n_matches){
    Node* front=NULL;
    vector<int> prefix=prefixfunc(pattern);
    NodeA *current;
    for(current=head;current!=NULL;current=current->next){
        string t=current->sentence;
        int i=0;
        int j=0;
        while(i<t.size()){
            if(t[i]>=65 && t[i]<=90){
                t[i]+=32;
            }
            if(t[i]==pattern[j]){
                i++;
                j++;
            } 
            else{
                if(j!=0){
                    j=prefix[j-1];
                }
                else{
                    i++;
                }
            } 
            if(j==pattern.size()){
                if(front==NULL){
                    front=new Node(current->book_code,current->page,current->paragraph,current->sentence_no,i-pattern.size());
                    
                }
                else{
                    Node *curr=new Node(current->book_code,current->page,current->paragraph,current->sentence_no,i-pattern.size());
                    curr->right=front;
                    front=curr;
                }
                n_matches++;
                j=prefix[j-1];
            } 
        }
    }
    return front;
}
