/**
 * A testbed for an augmented implementation of an AVL tree
 * @author William Duncan, YOUR NAME
 * @see AVLTree.h
 * <pre>
 * Date: DATE LAST MODIFIED
 * Course: CSC 3102 
 * Programming Project # 2
 * Instructor: Dr. Duncan 
 * </pre>
 */

#include <iostream>
#include <cstdlib>  
#include <stdexcept>
#include <iomanip>
#include <fstream> 
#include <algorithm>
#include <vector>
#include "AVLTree.cpp"


using namespace std;


int main(int argc, char** argv) 
{
    string usage = "Dendrologist <order-code> <command-file>\n";
    usage += "  <order-code>:\n";
    usage += "  0 ordered by increasing string length, primary key, and reverse lexicographical order, secondary key\n";
    usage += "  -1 for reverse lexicographical order\n";
    usage += "  1 for lexicographical order\n";
    usage += "  -2 ordered by decreasing string\n";
    usage += "  2 ordered by increasing string\n";
    usage += "  -3 ordered by decreasing string length, primary key, and reverse lexicographical order, secondary key\n";
    usage += "  3 ordered by increasing string length, primary key, and lexicographical order, secondary key\n";  
    if (argc != 3)
    {
        cout<<usage<<endl;
        throw invalid_argument("There should be 3 command line arguments.");
    }
   
    
    
    int order = atoi(argv[1]);
    if(order != -3 && order != -2 && order != -1 && order != 0 && order != 1 && order != 2 && order != 3){
        cout << usage;
        throw invalid_argument("Order code must be valid.");
    }
    
    ifstream MyFile(argv[2]);

    //AVLTree<string> fibTree;
    std::function<int(string,string)> autoComp = [](string TreeOne, string TreeTwo) -> int{return TreeOne < TreeTwo? -1 : (TreeOne == TreeTwo? 0 : 1);};
    
    auto comp = [](string TreeOne, string TreeTwo) -> int{return TreeOne < TreeTwo? -1 : (TreeOne == TreeTwo? 0 : 1);};

    string TreeOne;
    string TreeTwo;

    // switch (order)
    // {
    // case -3:
    //     //ordered by decreasing string length, primary key, and reverse lexicographical order, secondary key
    //     if (TreeOne.length() - TreeTwo.length() != 0){
    //         return -1;
    //     }
    //     return -1 * comp(TreeOne, TreeTwo);

    //     break;
    
    // case -2:
    //     //Ordered by decreasing string length
    //     return -1 * TreeOne.length() - TreeTwo.length();
    
    // case -1:
    //     //Ordered by reverse lexicographical order
    //     return -1 * comp(TreeOne, TreeTwo);

    // case 0:
    //     //Ordered by increasing string length, primary key, and reverse lexicographical order, secondary key
    //     if(TreeOne.length() - TreeTwo.length() != 0){
    //         return TreeOne.length() - TreeTwo.length();
    //     }
    //     return -1 * comp(TreeOne, TreeTwo);

    // case 1:
    //     //Lexicographical order
    //     return comp(TreeOne, TreeTwo);

    
    // case 2:
    //     //Ordered by increasing string length
    //     if(TreeOne.length() - TreeTwo.length() != 0){
    //         return TreeOne.length() - TreeTwo.length();
    //     }
    //     else{
    //         return comp(TreeOne, TreeTwo);
    //     }

    // case 3:
    //     //Ordered by increasing string length, primary key, and lexicographical order, second key
    //     if(TreeOne.length() - TreeTwo.length() != 0){
    //         return TreeOne.length() - TreeTwo.length();
    //     }
    //     else {
    //         return comp(TreeOne, TreeTwo);
    //     }
    // default:
    //     break;
    // }


    const int SIZE = 47; //number of words in strings.avl
    string array[SIZE]; //creating an array for all words in strings.avl
    string line;
    int i = 0;
    while(MyFile >> line){
        array[i] = line;
        i++;
    }

    AVLTree<string> fibTree;

    for(int i =0; i < SIZE; i++){
        if(array[i] == "insert" && array[i+1] != "remove"){
            fibTree.insert(array[i+1]);
            cout << "Inserted: " << array[i+1] << endl;
        }
        else if(array[i] == "delete"){
            fibTree.remove(array[i+1]);
            cout << "Removed: " << array[i+1] << endl;
        }
        else if(array[i] == "stats"){
            cout << "Stats: size = " << fibTree.size() << ", height = " << fibTree.height() << ", # full nodes = " << fibTree.fullCount() 
            << ", fibonacci? = " << fibTree.isFibonacci() << endl;
        }
        else if(array[i] == "paths"){
            cout << "Paths: " << endl;
            for(string i: fibTree.genPaths()){
            cout << i << "->";
        }
        cout << endl;
        }
        else if(array[i] == "traverse"){
            cout << "In-Order Traversal: " << endl;
            //fibTree.traverse(array[i], cout << TreeOne);
            
        }
        else if(array[i] == "insert" && array[i+1] == "remove"){
            cout << "Error: Command not recognized" << endl;
        }
    }

    MyFile.close();

    return 0;
}

