#include <assert.h>
#include <sstream>
#include "qna_tool.h"


using namespace std;

#define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"

NodeB* insert_wordcsv(NodeB *root,string k,long long val){
    if(root==NULL){
        root=new NodeB(k,val);
        return root;
    }
    if(k<root->data){
        root->left=insert_wordcsv(root->left,k,val);
    }
    else if(k>root->data){
        root->right=insert_wordcsv(root->right,k,val);
    }
    else{
        return root;
    }
    root->height=max(root->height2(root->left),root->height2(root->right));
    int balance=root->getbalance(root);
    if(balance>1 && k<root->left->data){
        return root->leftleftrotation(root);
    }
    else if(balance<-1&& k>root->right->data){
        return root->rightrightrotation(root);
    }
    else if(balance>1 && k>root->left->data){
        return root->leftrightrotation(root);
    }
    else if(balance<-1 && k<root->right->data){
        return root->rightleftrotation(root);
    }
    return root;
}
long long search(NodeB *root,string k){
    if(root==NULL){
        return 0;
    }
    if(root->data==k){
        return root->val;
    }
    if(k<root->data){
        return search(root->left,k);
    }
    else{
        return search(root->right,k);
    }

}
QNA_tool::QNA_tool(){
    root_csv=NULL;
    d=Dict();
    std::ifstream input("unigram_freq.csv");
    if(!input.is_open()){
        std::cerr<<"unable to open the file"<<endl;
    }
    string line;
    getline(input,line);
    while(getline(input,line)){
        istringstream iss(line);
        string word;
        string count_str;
        if(getline(iss,word,',') && getline(iss,count_str)){
            long long count=stoll(count_str);
            root_csv=insert_wordcsv(root_csv,word,count);
        }
    }
    input.close();
    para=vector<vector<vector<Dict>>>(99,vector<vector<Dict>>(600,vector<Dict>(50)));
    
}
void QNA_tool::inorder(NodeB *&root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    root->score=float(root->count+1)/(search(root_csv,root->data)+1);
    inorder(root->right);
}

QNA_tool::~QNA_tool(){
    delete root_csv;
}

vector<NodeC> mergehelper(vector<NodeC> arr1,vector<NodeC> arr2){
    vector<NodeC> ans;
    int i=0;
    int j=0;
    while(i<arr1.size() && j<arr2.size()){
        if(arr1[i].score<arr2[j].score){
            ans.push_back(arr1[i]);
            i++;
        }
        else{
            ans.push_back(arr2[j]);
            j++;
        }
    }
    while(i<arr1.size()){
        ans.push_back(arr1[i]);
        i++;
    }
    while(j<arr2.size()){
        ans.push_back(arr2[j]);
        j++;
    }
    return ans;
}
void mergesort(vector<NodeC> &arr){
    if(arr.size()<=1){
        return;
    }
    int start=0;
    int end=arr.size()-1;
    vector<NodeC> arr1,arr2;
    int mid=(start+end)/2;
    for(int i=start;i<=mid;i++){
        arr1.push_back(arr[i]);
    }
    for(int i=mid+1;i<=end;i++){
        arr2.push_back(arr[i]);
    }
    mergesort(arr1);
    mergesort(arr2);
    arr=mergehelper(arr1,arr2);
}
void reverse(Node *&head){
    Node* prev,*nextptr,*current;
    prev=NULL;
    current=head;
    while(current!=NULL){
        nextptr=current->right;
        current->right=prev;
        prev=current;
        current=nextptr;
    }
    head=prev;
}
Node* QNA_tool::get_top_k_para(string question, int k) {
    // Implement your function here
    inorder(d.root);
    vector<string> words;
    string s=question;
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
        words.push_back(word);
    }

    vector<NodeC> head;
    for(int i=1;i<99;i++){
        for(int j=0;j<600;j++){
            for(int kk=0;kk<50;kk++){
                float score=0;
                for(int z=0;z<words.size();z++){
                    score+=(para[i][j][kk].get_word_count(words[z]))*d.scoresearch(d.root,words[z]);
                    
                }
                if(score==0.0){
                    continue;
                }
                head.push_back(NodeC(score,i,j,kk));
            }
        }
    }
    mergesort(head);
    Node* ans=NULL;
    for(int i=head.size()-1;i>=head.size()-k;i--){
        if(ans==NULL){
            ans=new Node(head[i].book_code,head[i].page,head[i].paragraph,0,0);
            continue;
        }
        
        Node* current;
        current=new Node(head[i].book_code,head[i].page,head[i].paragraph,0,0);
        current->right=ans;
        ans=current;
    }
    reverse(ans);
    return ans;
}

void QNA_tool::query(string question, string filename){
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: Studying COL106 :)" << std::endl;
    return;
}
void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here 
    d.insert_sentence(book_code,page,paragraph, sentence_no, sentence);
    para[book_code][page][paragraph].insert_sentence(book_code, page,paragraph, sentence_no, sentence);  
    
}
std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}
// int main(){
//     QNA_tool a;
//     Node* ans=a.get_top_k_para("what is the purpose of life",15);
//     Node* curr=ans;
//     for(;curr!=NULL;curr=curr->right){
//         cout<<curr->book_code<<" "<<curr->page<<" "<<curr->paragraph<<" "<<endl;
//     }
// }