#include <iostream>
#include <string>

#define SIZE 26
struct node;

struct Trie{
    bool isEnd;
    char data;
    Trie* element[SIZE];
    std::string meaning;

    Trie(): isEnd(false),data(' '),meaning(""){
        for(int i=0;i<SIZE;i++){
            element[i] = nullptr;
        }
    }
};

Trie* getNewNode(){
    Trie* node = new Trie();
    node->isEnd=false;
    return node;
}
    
Trie* find(Trie* root,char key){
    int index= key - 'a';
    while(root != NULL){
        if(root->element[index] != NULL)
            if(root->element[index]->data == key ) return root;
        root=root->element[index];
    }
    if(root == NULL) return 0;
    else if(root->data == key) return root;
    return 0;
}

void insert(Trie*& root, const std::string& str, const std::string& meaning){
    if(root == NULL) root = getNewNode();
    Trie* temp = root;
    for(int i=0;i<str.length();i++){
        char x = str[i];
        if(find(temp, x) == NULL){
            temp->element[x - 'a']=getNewNode();
            temp->element[x - 'a']->data=x;
        }
        temp = temp->element[x - 'a'];
    }
    temp->isEnd=true;
    temp->meaning=meaning;
}
std::string getMeaning(Trie* root, const std::string& word){
    if(root == NULL){
        return "";
    }
    Trie* temp = root;
    for(int i=0;i<word.length();i++){
        temp = temp->element[word[i] - 'a'];
        if(temp == NULL) {
            return "";
        }
    }
    if(temp->isEnd){
        return temp->meaning;
    }
    return "";

}
//DFS
bool getWordFromLetter(Trie* root,std::string key){
    // checking one by one word (key)
    int i = int(key[0]) - 'a';
    if(key.size() && root->element[i] != nullptr){
        key.erase(0,1);
        // recursivly setting place to start
        return getWordFromLetter(root->element[i],key);
    }else if(key.size() == 0){
        // temporary variable to sign return to the previous letter
        bool output = false;
        if(root->meaning != ""){
            output=true;
            std::cout << root->meaning << std::endl;
        }
        for(int j=0;j<SIZE;j++){
            if(root->element[j] != nullptr){
                output=true;
                getWordFromLetter(root->element[j], key);
            }
        }
        return output;
    }
    return false;
}


int main() {
    
    Trie* root = new Trie();
    char comm;
    std::string word,meaning;
    while(std::cin >> comm){
        if(comm == '+'){
            std::cin >> word;
            std::cin >> meaning;
            insert(root, word, meaning);
        }else if(comm == '?'){
            std::cin >> word;
            if(getMeaning(root, word).empty()) std::cout << "-" <<std::endl;
            else std::cout << getMeaning(root, word) << std::endl;
        }else if(comm == '*'){
            std::cin >> word;
            if(!getWordFromLetter(root, word)){
                std::cout << "-" <<std :: endl;
            }
        }
    }
    return 0;
}
