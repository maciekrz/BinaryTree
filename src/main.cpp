//#include "headers/node.h" // with header files the compiler can't
//#include "headers/tree.h" // compile and throws errors - no idea why
#include "node.cpp"
#include "tree.cpp"

void run(std::string inFileName, std::string outFileName);
void flags(int argc, char* argv[], std::string* inFileName, std::string* outFileName, bool* r_flag);

int main(int argc, char* argv[])
{
    bool r_flag = false;
    std::string inFile, outFile = "";
    flags(argc, argv, &inFile, &outFile, &r_flag);

    if (r_flag == false)
    {
        std::cout << "\nAvailable flags:\n"
        << "-i / --input path_to_file  --  specifies the input file (data/input.txt if not used)\n"
        << "-o / --output path_to_file  --  specifies the output file (data/output.txt if not used)\n"
        << "-r / --run  --  runs the program\n\n";
        return 0;
    }

    Tree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(20);
    tree.insert(7);
    tree.insert(7);
    tree.insert(7);
    tree.insert(2);
    tree.insert(2);

    tree.printTree();

    /*
     *  TO DO:
     *  * SPLIT THE FILE INTO HEADERS
     */
}

void run(std::string inFileName, std::string outFileName)
{
    std::string option = "";
}

void flags(int argc, char* argv[], std::string* inFileName, std::string* outFileName, bool* r_flag)
{
    for (int i = 1; i < argc; i++)
    {
        auto argument = std::string(argv[i]);
        if (argument == "-i" || argument == "--input")
        {
            *inFileName = std::string(argv[i+1]);
            std::cout << "Input data file name: " << *inFileName << "\n";
        }
        else if (argument == "-o" || argument == "--output")
        {
            *outFileName = std::string(argv[i+1]);
            std::cout << "Output data file name: " << *outFileName << "\n";
        }
        else if (argument == "-r" || argument == "--run")
        {
            *r_flag = true;
        }
    }
    std::cout << "Done\n";
    return;
}
