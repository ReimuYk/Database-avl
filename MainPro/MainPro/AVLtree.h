#pragma once
#include<string>
#include<vector>
using namespace std;

struct datatype {
	int i;
	char s[12];
};

class node {
public:
	node(int kk,datatype* vv,node* ff,int lr);
	node(int kk, node* ff, int lr,int adr);

	node* father;
	int LR;//0 stand for lchild of father ,1 stand for rchild,-1 stand for root;
	node* lchild;
	node* rchild;
	int h;//height

	int key;
	datatype* value;
	bool is_fresh;

	int address;//file
};

int h(node* n);

class avl {
public:
	avl();
	bool insert(node* n,int kk, datatype* vv);
	bool del(int kk);
	bool change(int kk, datatype* vv);
	void lRotate(node* n);
	void rRotate(node* n);
	void balance(node* n);
	node* seek(int kk);
	datatype* scan(int kk);
	void load(string index,string data);
	void adjust_height(node* n);
	void save(string index,string data);
	void rec_save(node* n, ofstream& idx, fstream& dt, string adr);

	node* root;
	int number;
	int filesize;
	string dataname;
	vector<int> overlap;
};