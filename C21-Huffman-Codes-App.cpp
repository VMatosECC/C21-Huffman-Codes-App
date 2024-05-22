#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

// ---------------------------------------------------------
struct Node 
{
	int	    frequency;		// relative weight
	string  symbol;			// symbol to be encoded
	string  bitCode;		// will store node's binary code
	bool	isleft;			// T if node is left child
	Node*   left;			// pointers to left, right, and parent
	Node*   right;
	Node*	parent;
	Node*   loc;			// location of this node

	Node(int freqValue, string symValue) {
		frequency = freqValue;
		symbol = symValue;
		bitCode = "";
		isleft = true;
		left = right = parent = nullptr;
		loc = this;
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
			<< ",  isLeft:" << (n.isleft?" T":" F")
			<< ",  freq:  " << setw(3) << n.frequency
			<< ",  symbol:" << n.symbol
			<< "]";
		return sout;
	}
};

// while traversing in preorder mark each node. A left branch is marked with "0"
// and a right branch is marked with "1"
void preorderLabeling(Node* p)
{
	if (p == nullptr)
		return;
	if (p->parent != nullptr) {
		if(p->isleft)
			p->bitCode = p->parent->bitCode + "0";
		else
			p->bitCode = p->parent->bitCode + "1";
	}
	//show the code of single characters
	if(p->symbol.size() == 1)
		cout << " " << p->symbol << "\t" << p->bitCode << endl;
	preorderLabeling(p->left);
	preorderLabeling(p->right);
}

// ------------------------------------------------------------------------------------------------
int main()
{
	//vector<> contains {frequency,symbol} pairs
	//vector<pair<int, string>> v{ {5, "a"}, {9, "b"}, {12, "c"}, {13, "d"}, {16, "e"}, {45, "f"}, };
	vector<pair<int, string>> v{ {4, "I"}, {1, "M"}, {4, "S"}, {2, "P"},  };

	// sets work like heaps with no duplicates. 
	// The struct Node overloads operator< to sort the elements by frequency
	multiset<Node> s;
	for (int i = v.size() - 1; i >= 0; i--) {
		s.insert(*(new Node(v[i].first, v[i].second)));
	}
	//Debugging. Show the starting nodes
	for (auto p = s.begin(); p != s.end(); p++) {
		Node n = *p;
		cout << n << endl;
	}
	cout << endl;

	while (s.size() > 1) {
		//remove two smallest nodes (lowest frequencies)
		Node n1 = *s.begin(); s.erase(s.begin());
		Node n2 = *s.begin(); s.erase(s.begin());

		//create a new parent node combining previous two children nodes
		Node* pNew = new Node((n1.frequency + n2.frequency), (n1.symbol + n2.symbol));
		//connect new root node with its children (the two previous smallest)
		pNew->left = n1.loc; (n1.loc)->parent = pNew;  (n1.loc)->isleft = true;
		pNew->right = n2.loc; (n2.loc)->parent = pNew; (n2.loc)->isleft = false;

		//add new node to the set
		s.insert(*pNew);
		cout <<  *pNew << endl;

	}
	// The single node in the set is the root of the Huffman tree
	Node* root = s.begin()->loc;
	cout << " ROOT \n" << *root << endl;
	cout << "\n Huffman Code \n";
	preorderLabeling(root);
	return 0;
}
