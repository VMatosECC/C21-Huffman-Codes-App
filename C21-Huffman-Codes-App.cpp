//Goal: To implement the Huffman coding algorithm to compress text data.

#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;


// --------------------------------------------------------------------
struct Node
{
	int	    frequency;		// relative weight
	string  symbol;			// symbol to be encoded
	string  bitCode;		// will store node's binary code
	bool	isleft;			// T if node is left child
	Node* left;			// pointers to left, right, and parent
	Node* right;
	Node* parent;
	Node* loc;			// location of this node

	Node(string symValue, int freqValue) {
		frequency = freqValue;
		symbol = symValue;
		bitCode = "";
		isleft = true;
		left = right = parent = nullptr;
		loc = this;
	}

	~Node()
	{
		//cout << " +++ Deleting " << symbol << endl;
	}

	//this order (frequency ASC) will be enforced in STL containers (set)
	bool operator< (const Node& other) const {
		return (this->frequency < other.frequency);
	}

	// operator<< is overloaded for debugging convenience
	friend ostream& operator<< (ostream& sout, const Node& n) {
		sout << " Node["

			<< "   left:  " << setw(6) << (n.left == nullptr ? "null" : n.left->symbol)
			<< ",  right: " << setw(6) << (n.right == nullptr ? "null" : n.right->symbol)
			<< ",  parent:" << setw(6) << (n.parent == nullptr ? "null" : n.parent->symbol)
			<< ",  isLeft:" << (n.isleft ? " T" : " F")
			<< ",  freq:  " << setw(3) << n.frequency
			<< ",  symbol:" << n.symbol
			<< "]";
		return sout;
	}
};

// Prototypes -------------------------------------------------------------------------------
void destroyTree(Node* p);
void preorderLabel(Node* n, map<string, string>& dictionary);
void getText(map<string, int>& m, string& plainText);
void printMessage(map<string, string>& dictionary, string& plainText);


// User-Defined Functions ---------------------------------------------------------------------
// This function is used to get the text from the user and store it in a vector of pairs
void getText(map<string, int>& m, string& plainText) {
	cout << "Enter the text: ";
	getline(cin, plainText);

	// Loop through the text and store the frequency of each character in the map
	for (int i = 0; i < plainText.length(); i++) {
		// If the character is not in the map, add it with a frequency of 1
		string key = string(1, plainText[i]);
		if (m.find(key) == m.end()) {
			m[key] = 1;
		}
		// If the character is already in the map, increment its frequency
		else {
			m[key]++;
		}
	}

}

// While traversing in preorder mark each node. 
// A left branch is marked with "0" and a right branch is marked with "1"
void preorderLabel(Node* n, map<string, string>& dictionary) {
	//Base case
	if (n == nullptr) return;

	//If the node is not the root, assign the corresponding bit code
	if (n->parent != nullptr) {
		n->bitCode = n->parent->bitCode + (n->isleft ? "0" : "1");
	}
	//If the node is a leaf, print the symbol and its bit code, copy to the dictionary
	if (n->left == nullptr && n->right == nullptr) {
		cout << "  " << n->symbol << "\t" << n->bitCode << endl;
		dictionary[n->symbol] = n->bitCode;
	}
	//Continue the traversal, first to the left, then to the right
	preorderLabel(n->left, dictionary);
	preorderLabel(n->right, dictionary);

}

//	free memory
void destroyTree(Node* p)
{
	//postorder traversal, delete children first, then parent.
	if (p == nullptr)
		return;
	destroyTree(p->left);
	destroyTree(p->right);
	delete p;
}

// Print the dictionary and the encoded text
void printMessage(map<string, string>& dictionary, string& plainText) {
	cout << "\nDictionary\n";
	for (const auto& pair : dictionary) {
		cout << "  " << pair.first << "\t" << pair.second << endl;
	}

	cout << "\nEncoded text\n";
	for (int i = 0; i < plainText.length(); i++) {
		cout << dictionary[string(1, plainText[i])];
	}
	cout << endl;
}
// ------------------------------------------------------------------------------------------------
int main()
{
	// Use the following map to test the plain-text "MISSISSIPPI". The <key,value> pairs 
	// represent chars in the text and their respective frequency
	// string plainText = "MISSISSIPPI";
	// map<string, int> m = { {"I", 4}, {"M",1}, { "S", 4}, {"P", 2}, };

	// Use this function to get the plain text from the user (uncomment the following three lines)
	string plainText;
	map<string, int> m;
	getText(m, plainText);

	// Use a multiset to keep Nodes in ascending order. 
	// The struct Node overloads operator< to sorting by frequency
	multiset<Node> s;
	for (const auto& pair : m) {
		//Traverse the map, create Nodes in the machine's HEAP, insert each node in the multiset
		Node* n = new Node(pair.first, pair.second);
		s.insert(*n);
	}
	//Debugging. Show the starting nodes
	for (auto p = s.begin(); p != s.end(); p++) {
		Node n = *p;
		cout << n << endl;
	}
	cout << endl;

	// Huffman tree construction. Remove smaller pairs, create new parent nodes.
	while (s.size() > 1) {
		//remove two smallest nodes (lowest frequencies)
		Node n1 = *s.begin(); s.erase(s.begin());
		Node n2 = *s.begin(); s.erase(s.begin());

		//create a new parent node combining previous two children nodes
		Node* pNew = new Node((n1.symbol + n2.symbol), (n1.frequency + n2.frequency));

		//connect new root node with its children (the two previous smallest)
		pNew->left = n1.loc; (n1.loc)->parent = pNew; (n1.loc)->isleft = true;
		pNew->right = n2.loc; (n2.loc)->parent = pNew; (n2.loc)->isleft = false;

		//add the new parent node to the set
		s.insert(*pNew);
		cout << *pNew << endl;

	}
	// The single remaining node in the set is the root of the Huffman tree
	Node* root = s.begin()->loc;
	cout << "\n ROOT \n" << *root << endl;
	cout << "\n Huffman Code \n";

	// Traverse the tree in preorder to label each node with its bit code
	map<string, string> dictionary;
	preorderLabel(root, dictionary);

	// Print the dictionary & the encoded text
	printMessage(dictionary, plainText);

	// No zombies -  must free captive memory
	destroyTree(root);

	return 0;
}
