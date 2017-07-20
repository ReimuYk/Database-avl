#include "AVLtree.h"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

node::node(int kk, datatype* vv, node* ff,int lr){
	key = kk;
	value = vv;
	father = ff;
	is_fresh = true;
	lchild = NULL;
	rchild = NULL;
	h = 1;
	LR = lr;
	address = -1;
}

node::node(int kk, node* ff,int lr,int adr){
	key = kk;
	value = NULL;
	father = ff;
	is_fresh = false;
	lchild = NULL;
	rchild = NULL;
	h = 1;
	LR = lr;
	address = adr;
}

int h(node* n) {
	if (n == NULL)
		return 0;
	else
		return n->h;
}

avl::avl() {
	root = NULL;
	number = 0;
	filesize = 0;
	dataname = "";
}

bool avl::insert(node* n,int kk, datatype* vv) {
	if (n == root && root==NULL) {
		root = new node(kk, vv, NULL, -1);
		number++;
		return true;
	}
	else {
		if (n->key == kk)
			return false;
		else if (kk < n->key) {
			if (n->lchild == NULL) {
				n->lchild = new node(kk, vv, n, 0);
				if (n->rchild == NULL)
					n->h = 2;
			}
			else {
				insert(n->lchild, kk, vv);
				balance(n);
			}
		}
		else if (kk > n->key) {
			if (n->rchild == NULL) {
				n->rchild = new node(kk, vv, n, 1);
				if (n->lchild == NULL)
					n->h = 2;
			}
			else {
				insert(n->rchild, kk, vv);
				balance(n);
			}
		}
	}
	balance(root);
	number++;
	return true;
}

bool avl::del(int kk) {
	node* high = seek(kk);//the node be deleted
	if (!high) {
		cout << "false" << endl;
		return false;
	}
	else {
		//file
		if (high->is_fresh == false) {
			overlap.push_back(high->address);
		}
		//tree
		node* low = high;
		if (high->lchild == NULL) {
			if (high->LR == -1) {
				root = high->rchild;
				if (root)
					root->LR = -1;
			}
			else if (high->LR == 0) {
				high->father->lchild = high->rchild;
				if(high->father->lchild)
					high->father->lchild->LR = 0;
			}
			else if (high->LR == 1) {
				high->father->rchild = high->rchild;
			}
		}
		else {
			low = high->lchild;//the node max of left
			while (low->rchild)
				low = low->rchild;
			high->key = low->key;
			high->value = low->value;
			high->is_fresh = low->is_fresh;
			high->address = low->address;
			if (low->LR == 0) {
				low->father->lchild = low->lchild;
				if(low->lchild)
					low->lchild->father = low->father;
			}
			else if (low->LR == 1) {
				low->father->rchild = low->lchild;
				if(low->lchild)
					low->lchild->father = low->father;
				if (low->father->rchild)
					low->father->rchild->LR = 1;
			}
		}
		node* tn = low->father;
		/*delete[](low->value);
		delete[]low;*/
		while (tn) {
			balance(tn);
			tn = tn->father;
		}
		number -= 1;
		return true;
	}
}

bool avl::change(int kk, datatype* vv) {
	node* n = seek(kk);
	if (n == NULL) {
		return false;
	}
	else {
		delete[](n->value);
		n->value = vv;
		overlap.push_back(n->address);
		n->is_fresh = true;
	}
}

void avl::lRotate(node* n) {
	node* newroot = n->rchild;
	n->rchild = newroot->lchild;
	newroot->lchild = n;
	if (n == root)
		root = newroot;
	else {
		if (n->LR == 0)
			n->father->lchild = newroot;
		else if (n->LR == 1)
			n->father->rchild = newroot;
	}
	//change "father"
	newroot->father = n->father;
	n->father = newroot;
	if (n->rchild)
		n->rchild->father = n;
	//change "height"
	n->h = (h(n->lchild) > h(n->rchild) ? h(n->lchild) + 1 : h(n->rchild) + 1);
	newroot->h = (h(newroot->lchild) > h(newroot->rchild) ? h(newroot->lchild) + 1 : h(newroot->rchild) + 1);
	//change LR
	newroot->LR = n->LR;
	n->LR = 0;
	if (n->rchild)
		n->rchild->LR = 1;
}

void avl::rRotate(node* n) {
	node* newroot = n->lchild;
	n->lchild = newroot->rchild;
	newroot->rchild = n;
	if (n == root)
		root = newroot;
	else {
		if (n->LR == 0)
			n->father->lchild = newroot;
		else if (n->LR == 1)
			n->father->rchild = newroot;
		//change "father"
		newroot->father = n->father;
		n->father = newroot;
		if (n->lchild)
			n->lchild->father = n;
		//change "height"
		n->h = (h(n->lchild) > h(n->rchild) ? h(n->lchild) + 1 : h(n->rchild) + 1);
		newroot->h = (h(newroot->lchild) > h(newroot->rchild) ? h(newroot->lchild) + 1 : h(newroot->rchild) + 1);
	}
	//change LR
	newroot->LR = n->LR;
	n->LR = 1;
	if (n->lchild)
		n->lchild->LR = 0;
}

void avl::balance(node* n) {
	n->h = (h(n->lchild) > h(n->rchild) ? h(n->lchild) + 1 : h(n->rchild) + 1);
	if (h(n->lchild) - h(n->rchild) == 2) {
		if (h(n->lchild->lchild) >= h(n->lchild->rchild)) {
			rRotate(n);
		}
		else {
			lRotate(n->lchild);
			rRotate(n);
		}
	}
	else if (h(n->lchild) - h(n->rchild) == -2) {
		if (h(n->rchild->lchild) > h(n->rchild->rchild)) {
			rRotate(n->rchild);
			lRotate(n);
		}
		else {
			lRotate(n);
		}
	}
}

node* avl::seek(int kk) {
	node* res = root;

	while (res) {
		if (res->key == kk)
			return res;
		else if (kk < res->key)
			res = res->lchild;
		else if (kk > res->key)
			res = res->rchild;
	}
	return NULL;
}

datatype* avl::scan(int kk) {
	node* n = seek(kk);
	if (n == NULL)
		return NULL;
	if ( n->value != NULL)
		return n->value;
	else {
		fstream dt((dataname + ".dat").c_str());
		dt.seekg(16 * (n->address), ios::beg);
		int temp_i=0;
		char temp_str[12] = { ' ' };
		dt.read((char*)&temp_i, sizeof(int));
		dt.read(temp_str, sizeof(char) * 12);
		datatype* new_data = new datatype;
		new_data->i = temp_i;
		strcpy_s(new_data->s, temp_str);
		n->value = new_data;
		return new_data;
	}
}

void avl::save(string index, string data) {
	ofstream idx((index+".id").c_str());
	fstream dat((data + ".dat").c_str(),ios::binary|ios::in|ios::out);
	rec_save(root, idx, dat, "r");
	idx << "overlap" << endl;
	if (overlap.size() == 0)
		idx << "null" << endl;
	else {
		for (int i = 0; i < overlap.size(); i++) {
			idx << overlap[i] << " ";
		}
		idx << endl;
	}
	idx << "filesize" << endl;
	idx << filesize << endl << endl;
	idx.close();
	dat.close();
}

void avl::rec_save(node* n, ofstream& idx, fstream& dt, string adr) {
	if (n == NULL)
		return;
	int datasize = sizeof(int) + sizeof(char) * 12;//DIY
	if (n->is_fresh == false) {
		idx << adr << " " << n->key << " " << n->address << endl;

	}
	else if (n->is_fresh =true){
		if (overlap.size() != 0) {
			n->address = overlap[0];
			overlap.erase(overlap.begin());
			
		}
		else {
			n->address = filesize;
			filesize++;
			
		}
		dt.seekp(datasize*(n->address), ios::beg);
		idx << adr << " " << n->key << " " << n->address << endl;
		
		dt.write((char*)&(n->value->i), sizeof(int));
		dt.write((char*)&(n->value->s)[0], sizeof(char) * 12);
	}
	n->is_fresh = false;
	rec_save(n->lchild, idx, dt, adr + "0");
	rec_save(n->rchild, idx, dt, adr + "1");
}

void avl::load(string index,string data) {
	dataname = data;
	fstream idx((index + ".id").c_str());
	string line;
	if (!idx) {
		cerr << "Error to open index file" << endl;
	}
	else {
		while (true) {
			getline(idx, line);
			if (line=="")break;
			if (line[0] == 'r') {
				stringstream ss;
				ss << line;
				string loca;ss >> loca;
				int kk; ss >> kk;
				int adr; ss >> adr;
				if (loca == "r") {
					root = new node(kk, NULL, -1, adr);
				}
				else {
					node* n = root;
					for (int i = 1; i < loca.size() - 1; i++) {
						if (loca[i] == '0')
							n = n->lchild;
						if (loca[i] == '1')
							n = n->rchild;
					}
					if (loca[loca.size() - 1] == '0') {
						n->lchild = new node(kk, n, 0, adr);
					}
					else {
						n->rchild = new node(kk, n, 1, adr);
					}
				}
			}
			else if (line[0] == 'o') {
				getline(idx, line);
				stringstream ss;
				ss << line;
				int i;
				while (ss >> i)
					overlap.push_back(i);
			}
			else if (line[0] == 'f') {
				getline(idx, line);
				stringstream ss;
				ss << line;
				ss >> filesize;
			}
		}
	}
	adjust_height(root);
}

void avl::adjust_height(node* n) {
	if (n == NULL)
		return;
	adjust_height(n->lchild);
	adjust_height(n->rchild);
	n->h = (h(n->lchild) > h(n->rchild) ? h(n->lchild) + 1 : h(n->rchild) + 1);
}