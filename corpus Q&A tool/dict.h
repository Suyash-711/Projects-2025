// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class NodeB{
    public:
    NodeB *left;
    NodeB *right;
    string data;
    long long val;
    int count;
    int height;
    float score;
    NodeB(string k){
        left=NULL;
        right=NULL;
        data=k;
        count=1;
        height=0;
        score=0.0;
    }
    NodeB(string k,long long v){
        left=NULL;
        right=NULL;
        data=k;
        val=v;
        height=0;
    }
    ~NodeB(){
        delete left;
        delete right;
    }
    int height2(NodeB *root);
    int getbalance(NodeB *root);
    NodeB* leftleftrotation(NodeB *root);
    NodeB* rightrightrotation(NodeB *root);
    NodeB* leftrightrotation(NodeB *root);
    NodeB* rightleftrotation(NodeB *root);
    NodeB* insert_word(NodeB *root,string k);
    int search(NodeB* root,string k);
};
class Dict {
private:
    // You can add attributes/helper functions here
    void printing(NodeB *root,ofstream &outf);
    
    
    
public:
    float scoresearch(NodeB *root,string k); 
    NodeB* root;
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};