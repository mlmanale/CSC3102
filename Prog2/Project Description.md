Augmenting and Using an AVL Tree ADT

In this project you will augment the implementation of a parametric extensi- ble AVL tree ADT (abstract data type). You will then write a program that instantiates an AVL tree to store strings. Your program will execute a series of statements from the grammar shown in Listing 1. The program will be called Dendrologist. It will take the order-code and name of a command-file as a command line arguments and execute the instructions in the file while performing a trace of the instructions as they are executed. The command file consists of instructions in one of these formats:

Listing 1: Simple AVL ADT Grammar
insert <word>
delete <word>
traverse
paths
stats

The insert command in the file is followed by a word. When your program reads this instruction, it inserts the item into the AVL tree and displays a trace message Inserted: < item >. Similarly, the delete command is followed by a word. When your program reads this instruction, it removes the item from the AVL tree and displays a trace message Deleted: < item >. When the traverse command is executed, it displays the heading In-Order Traver- sal: followed by the in-order traversal of the entries in the tree, displayed one per line. When the paths command is executed, it displays the heading #Root-to-Leaf Paths: X, where X is the number of root-to-leaf paths in the tree. The paths are displayed from the left-most to the right-most. Each path is represented string that denotes a sequence of vertices from the root to a leaf node. The → symbol is shown between every pair of vertices along the path. The paths are displayed one per line. When the stats instruction is read, your program displays the following trace message: Stats: size = ..., height = ..., #full-nodes = ..., fibonacci? = ... The ellipsis are re- placed with values obtained by invoking the relevant methods/functions of the AVL abstract data type. The #full-nodes label is followed by a non- negative integer and the fibonacci? label is followed by either true or false, depending on whether the AVL tree is a fibonacci tree. Prior to parsing the command-file, after the command line tokens are accessed, an AVL tree is instantiated using a comparator based on the order-code. The valid order codes are shown in Listing 2. To run the program:

Listing 2: Running Dendrologist
Dendrologist <order=code> <command=file > <order=code>:
0 ordered by increasing string length , primary
key , and reverse lexicographical order , secondary key
-1 for reverse lexicographical order
1 for lexicographical order
-2 orderedb y decreasing string length
2 ordered by increasing string length
-3 ordered by decreasing string length , primary key , and reverse lexicographical order, secondary key
3 ordered by increasing string length , primary key, lexicographical order , secondary key

Your program throws an exception and terminates if the correct number of command line arguments are not entered: invalid argument for C++ programmers. It also displays the usage information shown in Listing 2, throws an exception and terminates if an invalid order-code flag is provided and gracefully exits. It also displays the Augmenting an AVL Tree ADT CSc 3102: Project # 2 usage information and throws an exception if the command-file does not ex- ist. It throws an exception and displays “parsing error” and terminates if a command in the file is invalid.
