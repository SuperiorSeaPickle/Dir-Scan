#pragma once

#ifndef _DataTree_h_included_
#define _DataTree_h_included_

#include <iostream>

#include <string>

#include <fstream>

#include <filesystem>

#include <cmath>

#include <deque>


using namespace std;
namespace fs = std::filesystem;

#endif

namespace datatree

{
    struct TreeNode {
        fs::path path;
        bool isFolder;
        deque < TreeNode* > childrenFiles;
        deque < TreeNode* > childrenFolders;
    };

    class DataTree {
    private:

    public:

        DataTree() {};

        ~DataTree() {};

        //functions

        TreeNode* GetNewNode(fs::path path, bool isFolder) //create new node
        {
            TreeNode* newNode = new TreeNode(); //HEAP ALLOC 
            newNode->path = path;
            newNode->isFolder = isFolder;
            return newNode;

        }

        void addChild(TreeNode* node, fs::path path, bool isFolder) //add child to a node
        {
            TreeNode* newNode = GetNewNode(path, isFolder);

            if (isFolder) {
                node->childrenFolders.push_back(newNode);
            }
            else {
                node->childrenFiles.push_back(newNode);
            }

        }

        void Print(TreeNode* root) {}

    };
}