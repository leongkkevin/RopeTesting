// C++ program to concatenate two strings using rope data structure.
//Sourced from GeeksForGeeks - https://www.geeksforgeeks.org/ropes-data-structure-fast-string-concatenation/

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Maximum no. of characters to be put in leaf nodes
const int LEAF_LEN = 2;

// Rope structure
class Rope
{
public:
    Rope *left, *right, *parent;
    char *str;
    int lCount;
};

// Function that creates a Rope structure.
// node --> Reference to pointer of current root node
// l --> Left index of current substring (initially 0)
// r --> Right index of current substring (initially n-1)
// par --> Parent of current node (Initially NULL)
void createRopeStructure(Rope *&node, Rope *par,
                         char a[], int l, int r)
{
    Rope *tmp = new Rope();
    tmp->left = tmp->right = NULL;

    // We put half nodes in left subtree
    tmp->parent = par;

    // If string length is more
    if ((r-l) > LEAF_LEN)
    {
        tmp->str = NULL;
        tmp->lCount = (r-l)/2;
        node = tmp;
        int m = (l + r)/2;
        createRopeStructure(node->left, node, a, l, m);
        createRopeStructure(node->right, node, a, m+1, r);
    }
    else
    {
        node = tmp;
        tmp->lCount = (r-l);
        int j = 0;
        tmp->str = new char[LEAF_LEN];
        for (int i=l; i<=r; i++)
            tmp->str[j++] = a[i];
    }
}

// Function that prints the string (leaf nodes)
void printstring(Rope *r)
{
    if (r==NULL)
        return;
    if (r->left==NULL && r->right==NULL)
        cout << r->str;
    printstring(r->left);
    printstring(r->right);
}

// Function that efficiently concatenates two strings
// with roots root1 and root2 respectively. n1 is size of
// string represented by root1.
// root3 is going to store root of concatenated Rope.
void concatenate(Rope *&root3, Rope *root1, Rope *root2, int n1)
{
    // Create a new Rope node, and make root1
    // and root2 as children of tmp.
    Rope *tmp = new Rope();
    tmp->parent = NULL;
    tmp->left = root1;
    tmp->right = root2;
    root1->parent = root2->parent = tmp;
    tmp->lCount = n1;

    // Make string of tmp empty and update
    // reference r
    tmp->str = NULL;
    root3 = tmp;
}

// Tests the time of a string and a rope's concatenation cycle
void testConcatenate(string stringCat, Rope *ropeCat){
    cout << "SIZE: " << stringCat.size() << endl;
    chrono::time_point<std::chrono::high_resolution_clock> startString = chrono::high_resolution_clock::now();
    string final = stringCat + stringCat;
    chrono::time_point<std::chrono::high_resolution_clock> stopString = chrono::high_resolution_clock::now();
    chrono::duration<double> durationString = stopString - startString;

    chrono::time_point<std::chrono::high_resolution_clock> startRope = chrono::high_resolution_clock::now();
    Rope *newRoot = NULL;
    concatenate(newRoot, ropeCat, ropeCat, stringCat.size());
    chrono::time_point<std::chrono::high_resolution_clock> stopRope = chrono::high_resolution_clock::now();
    chrono::duration<double> durationRope = stopRope - startRope;

    cout << "String Time: " << durationString.count() << endl;
    cout << "Rope Time: " << durationRope.count() << endl << endl;
}

// Driver code
int main()
{
    char ten[11] = "**********";
    char hundred[101] = "";
    for(int i = 0; i < 10; ++i){
        strcat(hundred, ten);
    }
    char thousand[1001] = "";
    for(int i = 0; i < 10; ++i){
        strcat(thousand, hundred);
    }
    char tenThousand[10001] = "";
    for(int i = 0; i < 10; ++i){
        strcat(tenThousand, thousand);
    }
    char hundredThousand[100001] = "";
    for(int i = 0; i < 10; ++i){
        strcat(hundredThousand, tenThousand);
    }

    string tenStr = ten;
    string hundredStr = hundred;
    string thousandStr = thousand;
    string tenThousandStr = tenThousand;
    string hundredThousandStr = hundredThousand;

    Rope *tenRoot = NULL;
    createRopeStructure(tenRoot, NULL, ten, 0, 9);
    Rope *hundRoot = NULL;
    createRopeStructure(hundRoot, NULL, hundred, 0, 99);
    Rope *thouRoot = NULL;
    createRopeStructure(thouRoot, NULL, thousand, 0, 999);
    Rope *tenThouRoot = NULL;
    createRopeStructure(tenThouRoot, NULL, tenThousand, 0, 9999);
    Rope *hundThouRoot = NULL;
    createRopeStructure(hundThouRoot, NULL, hundredThousand, 0, 99999);

    testConcatenate(tenStr, tenRoot);
    testConcatenate(hundredStr, hundRoot);
    testConcatenate(thousandStr, thouRoot);
    testConcatenate(tenThousandStr, tenThouRoot);
    testConcatenate(hundredThousandStr, hundThouRoot);

    return 0;
}
