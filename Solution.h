#pragma once
#include <queue>
#include <string>
#include <typeinfo>
// Mathew Lister
// CSC 2431
// HW 4: Binary Search Tree Implementation

//You should encapsulate your code within the namespace SPU::CSC2431::Homework4.
//
//Create a templated BinarySearchTree class that implements the following functions, all of which return void :
//	Add - takes a single parameter of the templated type and adds it to the tree according to Binary Search Tree rules
//	PreorderDFS - see below
//	PostorderDFS - see below
//	InorderDFS - see below
//	BFS - see below
//
//	The DFS and BFS tree traversal functions all return void and take a function pointer as a parameter.
//	As the DFS / BFS function traverses the tree, it calls the function pointer on the tree node data as appropriate :
//pre - order, post - order, or in - order for DFS or just in BFS.
//
//Below you'll find all sorts of examples. A test program that creates two BinarySearchTrees, adds stuff,
//and traverses the trees in all ways with my own test functions like Print, which works on string and int,
//and Double, which works on int.
//
//Additionally, create two functions of your own that can be passed into the tree traversal functions :
//Capitalize - is a function that takes an std::string and capitalizes it.This will obviously fail to compile if
//passed into a binary search tree of any type other than std::string.
//AccumulatePrint - is a templated function that takes the templated type and keeps and prints a running accumulation
//of all the visited nodes.For example, in intTree, it prints the running sum as each node is visited.
//For stringTree, it prints the string concatenation as each node is visited.
using namespace std;
namespace SPU {
	namespace CSC2431 {
		namespace Homework4 {
			template<class T>
			class BinarySearchTree
			{
			public:
				// Constructor
				BinarySearchTree()
				{
					_root = NULL;
					_size = 0;
				}
				//takes a single parameter of the templated type and adds it to the tree according to Binary Search Tree rules
				void Add(T other)
				{
					if (_root == NULL) // If tree is empty
					{
						node *ptrNew = new node;
						ptrNew->data = other;
						_root = ptrNew;
						ptrNew->left = NULL;
						ptrNew->right = NULL;
						_size++;
						return;
					}
					AddHelp(_root, other);
				}

				// ***Root, Left, Right
				void PreorderDFS(void(*visit) (T&))
				{
					if (_root == NULL)
						return;
					PreorderDFSHelp(_root, visit);
				}

				// ***Left, Right, Root
				void PostorderDFS(void(*visit) (T&))
				{
					if (_root == NULL)
						return;
					PostorderDFSHelp(_root, visit);
				}

				// ***Left, Root, Right
				void InorderDFS(void(*visit) (T&))
				{
					if (_root == NULL)
						return;
					InorderDFSHelp(_root, visit);
				}

				//*** Level order traversal
				void BFS(void(*visit) (T&))
				{
					if (_root == NULL)
						return;
					queue <node*> q; // Make new queue to store nodes
					q.push(_root); // Enqueue root

					while (q.empty() == false)
					{
						// visit and remove
						node *ptr = q.front();
						visit(ptr->data);
						q.pop();
						// Left child
						if (ptr->left != NULL)
							q.push(ptr->left);
						// Right child
						if (ptr->right != NULL)
							q.push(ptr->right);
					}
				}

				// Destructor
				~BinarySearchTree()
				{
					if (_root != NULL)
					{
						DestructorHelp(_root);
					}
				}

			private:
				struct node
				{
					T data;
					node* left;
					node* right;
				};
				node* _root;
				int _size;
//**********************************HELPERS*******************************************************************
				node* AddHelp(node* ptr, T other)
				{
					
					if (other <= ptr->data) // Go left
					{
						if (ptr->left == NULL) // Found leaf
						{
							node *ptrNew = new node;
							ptrNew->data = other;
							ptr->left = ptrNew;
							ptrNew->left = NULL;
							ptrNew->right = NULL;
							_size++;
							return ptr;
						}
						return AddHelp(ptr->left, other); // Keep going down
					}
						else // Go right 
						{
							if (ptr->right == NULL) // Found a leaf
							{
								node *ptrNew = new node;
								ptrNew->data = other;
								ptr->right = ptrNew;
								ptrNew->left = NULL;
								ptrNew->right = NULL;
								_size++;
								return ptr;
							}
							return AddHelp(ptr->right, other); // Keep going down
						}
					}
					void PreorderDFSHelp(node* other, void(*visit) (T&))
						{
							if (other == NULL)
								return;
							visit(other->data);
							PreorderDFSHelp(other->left, visit); // Go left
							PreorderDFSHelp(other->right, visit); // Go right
						}
					void PostorderDFSHelp(node* other, void(*visit) (T&))
						{
							if (other == NULL)
								return;
							PostorderDFSHelp(other->left, visit);
							PostorderDFSHelp(other->right, visit);
							visit(other->data);
						}
					void InorderDFSHelp(node* other, void(*visit) (T&))
						{
							if (other == NULL)
								return;
							InorderDFSHelp(other->left, visit);
							visit(other->data);
							InorderDFSHelp(other->right, visit);
						}
					void DestructorHelp(node* other)
					{
						if (other != NULL)
						{
							DestructorHelp(other->left);
							DestructorHelp(other->right);
							delete other;
						}
					}
					};

					// Add all the things
					template<class T>
					void AccumulatePrint(T& info)
					{
						static T add;
						add += info;
						cout << add << " ";
					}

					// Capitalize all the things
					void Capitalize(std::string & cap)
					{
						long len = cap.length();
						for (int i = 0; i < len; i++)
						{
							cap[i] = toupper(cap[i]);
						}
					}
				}
			}
		}

