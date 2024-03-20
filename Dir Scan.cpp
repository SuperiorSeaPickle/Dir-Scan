// Dir Scan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <string>

#include <fstream>

#include <filesystem>

#include <cmath>

#include <deque>

#include "DataTree.h"

using namespace std;
namespace fs = std::filesystem;
using namespace datatree;

struct relitiveSize {
    float num;
    string unit;
};

bool isFolder(fs::path baseDir);
void copyDir(TreeNode** rootPtr);
void loadFileHirarchy(fs::path rootDir, TreeNode** rootPtr);
relitiveSize pickUnit(long num);

int main() {
    cout << "Wellcome to Directery Scanner!\n";
    cout << "**********************************\n\n";
    cout << "paste the directory you'd like to scan below\n";

    string dirPath;
    getline(cin, dirPath);

    TreeNode* fh_ptr = new TreeNode;
    loadFileHirarchy(dirPath, &fh_ptr);


    delete fh_ptr;

    return 0;
}
void copyDir(TreeNode** rootPtr) {

}
bool isFolder(fs::path baseDir) {
    if (fs::is_directory(fs::status(baseDir))) {
        return true;
    }
    else {
        return false;
    }
}
void loadFileHirarchy(fs::path rootDir, TreeNode** rootPtr) {
    DataTree fileHirarchy; //create a datatree object
    fs::path currentPath; //for keeping track of the path that is currently being added to an object
    fs::path relitivePath; //just the filename
    TreeNode* root; //what will contain all the data
    root = fileHirarchy.GetNewNode(rootDir, true); //create the first parant node
    TreeNode* currentParent = root; //this node is the current folder that is being iterated through
    deque < TreeNode* > forks; //list of all the forks that have been present
    deque < int > forkIterators; //list how many prongs are in the forks
    deque <TreeNode*> depthMap; //keeps track of where the iterator has been
    double totalParentSize = 0; //used to add the sum of file sizes
   
    bool isFork; //is the current folder a fork?

    while (true) {

        depthMap.push_back(currentParent);
        for (const auto& entry : fs::directory_iterator(currentParent->path)) {
            currentPath = entry.path();
            relitivePath = currentPath.filename();

            if (isFolder(currentPath))
            {
                fileHirarchy.addChild(currentParent, currentPath, true);
            }
            else
            {
                fileHirarchy.addChild(currentParent, relitivePath, false);
            }
            
        }
        
        if (currentParent->childrenFolders.size() > 1) //is fork
        {
            forks.push_back(currentParent); //last fork
            forkIterators.push_back(0);
            isFork = true;
        }
        else {
            isFork = false;
        }

        if (currentParent->childrenFolders.size() == 0) //if branch ends
        {
      

            
            
            forkIterators[forks.size() - 1]++;
            isFork = true;
            currentParent = forks[forks.size() - 1];//set current parrent to the last fork

        }
       
        if (forkIterators.size() != 0)
        {
            if (forkIterators[forks.size() - 1] == forks[forks.size() - 1]->childrenFolders.size()) //if iterated through all children folders in the fork
            {
                forks.pop_back();
                forkIterators.pop_back();

                if (forks.size() == 0) {
                    break;
                }
            }
        }
     
        //go deaper into tree
        if (isFork) {
            currentParent = currentParent->childrenFolders[forkIterators[forkIterators.size() -1]];
        }
        else {
            currentParent = currentParent->childrenFolders[0];
        }

    }

    *rootPtr = root;
}
relitiveSize pickUnit(long num) {
    float sizeRelitive;
    string unit;

    if (num < pow(10, 3) && num >= 0) //byte
    {
        unit = "byte";
        sizeRelitive = num / pow(10, 0);
    }
    else if (num < pow(10, 6) && num >= pow(10, 3)) //kilobyte
    {
        unit = "kilobyte";
        sizeRelitive = num / pow(10, 3);
    }
    else if (num < pow(10, 9) && num >= pow(10, 6)) //megabyte
    {
        unit = "megabyte";
        sizeRelitive = num / pow(10, 6);
    }
    else if (num < pow(10, 12) && num >= pow(10, 9)) //gigabyte
    {
        unit = "gigabyte";
        sizeRelitive = num / pow(10, 9);
    }
    else if (num < pow(10, 15) && num >= pow(10, 12)) //terabyte
    {
        unit = "terabyte";
        sizeRelitive = num / pow(10, 12);
    }

    if (sizeRelitive != 1) {
        unit = unit + "s";
    }

    return relitiveSize(sizeRelitive, unit);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file