//#include <set>
//#include <vector>
//#include <string>
//#include <sstream>
//#include <iomanip>
//#include <iostream>
//using namespace std;
//
//// ---------------------------------------------------------
//struct Node
//{
//	int	    frequency;
//	string  symbol;
//	string  bitlabel;
//	bool	isleft;
//	Node* left;
//	Node* right;
//	Node* loc;
//
//	Node(int freqValue, string symValue) {
//		frequency = freqValue;
//		symbol = symValue;
//		bitlabel = "";
//		isleft = true;
//		left = right = nullptr;
//		loc = this;
//	}
//
//	string toString() {
//		ostringstream sout;
//		sout << this << " Node[ symbol:" << symbol << ", freq:" << frequency
//			<< ", left:" << left << ", right:" << right
//			<< ", loc:" << loc;
//		return sout.str();
//	}
//	//this order will be enforced in STL containers (set)
//	bool operator< (const Node& other) const {
//		return (this->frequency < other.frequency);
//	}
//
//	friend ostream& operator<< (ostream& os, Node& n) {
//		os << " Node[loc:" << n.loc
//			<< ", left:" << n.left << ", right:" << n.right
//			<< ", isLeft: " << (n.isleft ? "T" : "F")
//			<< ", freq:" << setw(3) << n.frequency
//			<< ", symbol:" << n.symbol
//			<< ", bitlabel:" << n.bitlabel
//			<< "]";
//		return os;
//	}
//};
//
//
//
//
//// Driver program to test above functions 
//int main()
//{
//	//vector<> contains {frequency,symbol} pairs
//	vector<pair<int, string>> v{ {5, "a"}, {9, "b"}, {12, "c"}, {13, "d"}, {16, "e"}, {45, "f"}, };
//
//	// sets work like heaps with no duplicates. 
//	// The struct Node overloads operator< to sort the elements by frequency
//	set<Node> s;
//	for (int i = v.size() - 1; i >= 0; i--) {
//		s.insert(*(new Node(v[i].first, v[i].second)));
//	}
//
//	for (auto p = s.begin(); p != s.end(); p++) {
//		Node n = *p;
//		cout << n << endl;
//	}
//	cout << endl;
//
//	while (s.size() > 1) {
//		//extract (and remove) first two smallest Nodes from the heap (set)
//		Node n1 = *s.begin(); s.erase(s.begin());
//		Node n2 = *s.begin(); s.erase(s.begin());
//		//create a new node combining previous two smallest
//		Node* pnew = new Node((n1.frequency + n2.frequency), (n1.symbol + n2.symbol));
//		//connect new root node with its children (the two previous smallest)
//		pnew->left = n1.loc; n1.isleft = true; n1.bitlabel = n1.bitlabel + "0";
//		pnew->right = n2.loc; n2.isleft = false; n2.bitlabel = n2.bitlabel + "1";
//		//add new node to the set
//		s.insert(*pnew);
//		cout << "NEW  " << *pnew << endl;
//
//	}
//	// The single node in the set is the root of the Huffman tree
//	Node* p = s.begin()->loc;
//	cout << "ROOT " << *p << endl;
//
//	return 0;
//}




























/////////////////////////////////////////////////////////////////////////////////////////////////
//// C++ program for Huffman Coding 
//// REF. https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
////--------------------------------------------------------------------
//#include <iostream> 
//#include <cstdlib> 
//using namespace std;
//
//// This constant can be avoided by explicitly 
//// calculating height of Huffman Tree 
//#define MAX_TREE_HT 100 
//
//// A Huffman tree node 
//struct MinHeapNode {
//
//	// One of the input characters 
//	char data;
//
//	// Frequency of the character 
//	unsigned freq;
//
//	// Left and right child of this node 
//	struct MinHeapNode* left, * right;
//};
//
//// A Min Heap: Collection of 
//// min-heap (or Huffman tree) nodes 
//struct MinHeap {
//
//	// Current size of min heap 
//	unsigned size;
//
//	// capacity of min heap 
//	unsigned capacity;
//
//	// Attay of minheap node pointers 
//	struct MinHeapNode** array;
//};
//
//// A utility function allocate a new 
//// min heap node with given character 
//// and frequency of the character 
//struct MinHeapNode* newNode(char data, unsigned freq)
//{
//	struct MinHeapNode* temp
//		= (struct MinHeapNode*)malloc
//		(sizeof(struct MinHeapNode));
//
//	temp->left = temp->right = NULL;
//	temp->data = data;
//	temp->freq = freq;
//
//	return temp;
//}
//
//// A utility function to create 
//// a min heap of given capacity 
//struct MinHeap* createMinHeap(unsigned capacity)
//
//{
//
//	struct MinHeap* minHeap
//		= (struct MinHeap*)malloc(sizeof(struct MinHeap));
//
//	// current size is 0 
//	minHeap->size = 0;
//
//	minHeap->capacity = capacity;
//
//	minHeap->array
//		= (struct MinHeapNode**)malloc(minHeap->
//			capacity * sizeof(struct MinHeapNode*));
//	return minHeap;
//}
//
//// A utility function to 
//// swap two min heap nodes 
//void swapMinHeapNode(struct MinHeapNode** a,
//	struct MinHeapNode** b)
//
//{
//
//	struct MinHeapNode* t = *a;
//	*a = *b;
//	*b = t;
//}
//
//// The standard minHeapify function. 
//void minHeapify(struct MinHeap* minHeap, int idx)
//
//{
//
//	int smallest = idx;
//	int left = 2 * idx + 1;
//	int right = 2 * idx + 2;
//
//	if (left < minHeap->size && minHeap->array[left]->
//		freq < minHeap->array[smallest]->freq)
//		smallest = left;
//
//	if (right < minHeap->size && minHeap->array[right]->
//		freq < minHeap->array[smallest]->freq)
//		smallest = right;
//
//	if (smallest != idx) {
//		swapMinHeapNode(&minHeap->array[smallest],
//			&minHeap->array[idx]);
//		minHeapify(minHeap, smallest);
//	}
//}
//
//// A utility function to check 
//// if size of heap is 1 or not 
//int isSizeOne(struct MinHeap* minHeap)
//{
//
//	return (minHeap->size == 1);
//}
//
//// A standard function to extract 
//// minimum value node from heap 
//struct MinHeapNode* extractMin(struct MinHeap* minHeap)
//
//{
//
//	struct MinHeapNode* temp = minHeap->array[0];
//	minHeap->array[0]
//		= minHeap->array[minHeap->size - 1];
//
//	--minHeap->size;
//	minHeapify(minHeap, 0);
//
//	return temp;
//}
//
//// A utility function to insert 
//// a new node to Min Heap 
//void insertMinHeap(struct MinHeap* minHeap,
//	struct MinHeapNode* minHeapNode)
//
//{
//
//	++minHeap->size;
//	int i = minHeap->size - 1;
//
//	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
//
//		minHeap->array[i] = minHeap->array[(i - 1) / 2];
//		i = (i - 1) / 2;
//	}
//
//	minHeap->array[i] = minHeapNode;
//}
//
//// A standard function to build min heap 
//void buildMinHeap(struct MinHeap* minHeap)
//
//{
//
//	int n = minHeap->size - 1;
//	int i;
//
//	for (i = (n - 1) / 2; i >= 0; --i)
//		minHeapify(minHeap, i);
//}
//
//// A utility function to print an array of size n 
//void printArr(int arr[], int n)
//{
//	int i;
//	for (i = 0; i < n; ++i)
//		cout << arr[i];
//
//	cout << "\n";
//}
//
//// Utility function to check if this node is leaf 
//int isLeaf(struct MinHeapNode* root)
//
//{
//
//	return !(root->left) && !(root->right);
//}
//
//// Creates a min heap of capacity 
//// equal to size and inserts all character of 
//// data[] in min heap. Initially size of 
//// min heap is equal to capacity 
//struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
//
//{
//
//	struct MinHeap* minHeap = createMinHeap(size);
//
//	for (int i = 0; i < size; ++i)
//		minHeap->array[i] = newNode(data[i], freq[i]);
//
//	minHeap->size = size;
//	buildMinHeap(minHeap);
//
//	return minHeap;
//}
//
//// The main function that builds Huffman tree 
//struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
//
//{
//	struct MinHeapNode* left, * right, * top;
//
//	// Step 1: Create a min heap of capacity 
//	// equal to size. Initially, there are 
//	// modes equal to size. 
//	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
//
//	// Iterate while size of heap doesn't become 1 
//	while (!isSizeOne(minHeap)) {
//
//		// Step 2: Extract the two minimum 
//		// freq items from min heap 
//		left = extractMin(minHeap);
//		right = extractMin(minHeap);
//
//		// Step 3: Create a new internal 
//		// node with frequency equal to the 
//		// sum of the two nodes frequencies. 
//		// Make the two extracted node as 
//		// left and right children of this new node. 
//		// Add this node to the min heap 
//		// '$' is a special value for internal nodes, not used 
//		top = newNode('$', left->freq + right->freq);
//
//		top->left = left;
//		top->right = right;
//
//		insertMinHeap(minHeap, top);
//	}
//
//	// Step 4: The remaining node is the 
//	// root node and the tree is complete. 
//	return extractMin(minHeap);
//}
//
//// Prints huffman codes from the root of Huffman Tree. 
//// It uses arr[] to store codes 
//void printCodes(struct MinHeapNode* root, int arr[], int top)
//
//{
//
//	// Assign 0 to left edge and recur 
//	if (root->left) {
//
//		arr[top] = 0;
//		printCodes(root->left, arr, top + 1);
//	}
//
//	// Assign 1 to right edge and recur 
//	if (root->right) {
//
//		arr[top] = 1;
//		printCodes(root->right, arr, top + 1);
//	}
//
//	// If this is a leaf node, then 
//	// it contains one of the input 
//	// characters, print the character 
//	// and its code from arr[] 
//	if (isLeaf(root)) {
//
//		cout << root->data << ": ";
//		printArr(arr, top);
//	}
//}
//
//// The main function that builds a 
//// Huffman Tree and print codes by traversing 
//// the built Huffman Tree 
//void HuffmanCodes(char data[], int freq[], int size)
//
//{
//	// Construct Huffman Tree 
//	struct MinHeapNode* root
//		= buildHuffmanTree(data, freq, size);
//
//	// Print Huffman codes using 
//	// the Huffman tree built above 
//	int arr[MAX_TREE_HT], top = 0;
//
//	printCodes(root, arr, top);
//}
//
//// Driver program to test above functions 
//int main()
//{
//
//	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
//	int freq[] = { 5, 9, 12, 13, 16, 45 };
//
//	int size = sizeof(arr) / sizeof(arr[0]);
//
//	HuffmanCodes(arr, freq, size);
//
//	return 0;
//}
