// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class NodeA{
    public:
    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    string sentence;
    NodeA *next;
    NodeA(int b,int p1,int p2,int s1,string s){
        next=NULL;
        book_code=b;
        page=p1;
        paragraph=p2;
        sentence_no=s1;
        sentence=s;
    }
    ~NodeA(){
        delete next;
    }

};
class SearchEngine {
private:
    // You can add attributes/helper functions here
    NodeA *head;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};
