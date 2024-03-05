
// C++ Program for Huffman Coding using Priority Queue
#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 100 // Maximum Height of Huffman Tree.
class HuffmanTreeNode {
public:
 char data;
 int freq;
 HuffmanTreeNode* left;
 HuffmanTreeNode* right;
 HuffmanTreeNode(char character, int frequency)
 {
 data = character;
 freq = frequency;
 left = right = NULL;
 }
};
// Custom compare class
class Compare {
public:
 bool operator()(HuffmanTreeNode* a, HuffmanTreeNode* b)
 {
 return a->freq > b->freq;
 }
};
HuffmanTreeNode* generateTree(priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, Compare> pq)
{
 while (pq.size() != 1) {
 
 HuffmanTreeNode* ni= pq.top();
 pq.pop();
 HuffmanTreeNode* nj= pq.top();
 pq.pop();
 char newSymbol='#';
 int new_Frequency= ni->freq + nj->freq;
 HuffmanTreeNode* newNode= new HuffmanTreeNode (newSymbol, new_Frequency);
 newNode->left= ni;
 newNode->right=nj;
 pq.push(newNode);
 }
 return pq.top();
}
void printCodes(HuffmanTreeNode* root, map<char,string> &m) {
 if (!root)
 return;
 map<HuffmanTreeNode*, string> huffmanCodes;
 stack<HuffmanTreeNode*> stk;
 stk.push(root);
 huffmanCodes[root] = "";
 while (!stk.empty()) {
 HuffmanTreeNode* curr = stk.top();
 stk.pop();
 if (!curr->left && !curr->right) {
 cout << curr->data << ": " << huffmanCodes[curr] << endl;
 m[curr->data]=huffmanCodes[curr];
 }
 
 if (curr->left) {
 huffmanCodes[curr->left] = huffmanCodes[curr] + "0";
 stk.push(curr->left);
 }
 
 if (curr->right) {
 huffmanCodes[curr->right] = huffmanCodes[curr] + "1";
 stk.push(curr->right);
 }
 
 }
 
 
}
HuffmanTreeNode* HuffmanCodes(vector <char> data, vector <int> freq, map<char,string> &CharToString, map<char,int> &frequencyy, int size)
{

 priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, Compare> pq;

 for (int i = 0; i < size; i++) {
 HuffmanTreeNode* newNode = new HuffmanTreeNode(data[i], freq[i]);
 pq.push(newNode);
 }
 HuffmanTreeNode* root = generateTree(pq);

 int arr[MAX_SIZE], top = 0;
 printCodes(root,CharToString);
 
 return root;
 
}

string Encode(string text, map <char,string> m)
{
    string Encoding="";
    int i=0;
    while (text[i] != '\0')
    {
        Encoding=Encoding+m[text[i]];
        i+=1;
    }
    return Encoding;
}

string decode(string encodedText, HuffmanTreeNode* root) {
    string decodedText = "";
    HuffmanTreeNode* curr = root;
    for (int i=0; i<encodedText.length();i++) {
        if (encodedText[i] == '0') {
            curr = curr->left;
        }
        else if (encodedText[i] == '1') {
            curr = curr->right;
        }
        if (!curr->left && !curr->right) {
            decodedText += curr->data;
            curr = root;
        }
    }
    return decodedText;
}
    

int main()
{
 string text;
 
 getline(cin,text);
 
 map <char,int> frequencyy;
 
 map<char,string> C_To_S;
 
 for (int i=0;i<text.length();i++)
 {
     frequencyy[text[i]]+=1;
 }
vector <int> freq;
vector <char> dat;

for( auto x= frequencyy.begin(); x!=frequencyy.end(); x++ )
{
    dat.push_back(x->first);
    freq.push_back(x->second);
}
 HuffmanTreeNode* root= HuffmanCodes(dat, freq, C_To_S, frequencyy,frequencyy.size());
 
 string BinaryBits= Encode(text,C_To_S);
 
 cout<< "Encoded Version : " << BinaryBits <<endl<< "Decoded Version: ";
 cout<< decode(BinaryBits,root);
 
 return 0;
}
