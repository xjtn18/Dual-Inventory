#pragma once
#include <unistd.h>
#include <thread>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <ctype.h>

#define kDEBUG 1 // set this to 0 if you dont want to see any of your logs

#define uint unsigned int
#define kRefresh true
#define CLEAR_SHELL_COMMAND "clear"

//directions
enum Direction {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};

namespace mystd {
	void shclear();
	void catfile(std::string filename);
	std::vector<std::string> splitOnSpace(std::string s);
}



////////////////////////////////////////
// Log functions
////////////////////////////////////////

template <typename T>
void buffer(T input){
	std::cout << input << std::endl;
	std::string _;
	std::getline(std::cin, _);
}


// this template prints anything (singular value)
template <typename T>
void log(T x, bool nl = true, uint sleeptime = 0){
	if (!kDEBUG)
		return;
	std::cout << x;
	if (nl)
		std::cout << "\n";
	usleep(sleeptime * 100000);
}


// this template prints arrays
template <typename T>
void log(T* x, int len){
	for (int y = 0; y < len; y++){
		log(x[y], false);
		if (y != len-1){
			log(", ", false);
		}
	}
	log("");

}

// this template prints vectors
template <typename T>
void log(std::vector<T> v){
	std::cout << '[';
	for (int i = 0; i < v.size(); ++i){
		std::cout << v[i];
		if (i != v.size()-1)
			std::cout << ", ";
	}
	std::cout << ']' << std::endl;
}





////////////////////////////////////////
// Linked Lists
////////////////////////////////////////


// standard (LeetCode) linked list node structure
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// template to intitialize and fill a linked list from a given vector
template <typename T>
ListNode* createLL(std::vector<T> v){
	ListNode* head = new ListNode(v[0]);
	ListNode* curr = head;
	for (int i = 1; i < v.size(); ++i){
		curr->next = new ListNode(v[i]);
		curr = curr->next;
	}
	return head;
}






////////////////////////////////////////
// Binary Trees
////////////////////////////////////////


// standard (LeetCode) binary tree node structure
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// recursive function that fills binary tree row by row left to right
template <typename T>
void fill(TreeNode* node, std::vector<T> v, int i){
	node->val = v[i]; // assign value
	if (2*i+1 < v.size()){
		node->left = new TreeNode();
		fill(node->left, v, 2*i+1);
	}
	if (2*i+2 < v.size()){
		node->right = new TreeNode();
		fill(node->right, v, 2*i+2);
	}
}


// initialize and fill a binary tree (row by row) from a given vector
template <typename T>
TreeNode* createBinaryTree(std::vector<T> v){
	if (v.empty()) return nullptr;
	TreeNode* head = new TreeNode(v[0]);
	fill(head, v, 0);
	return head;

}







