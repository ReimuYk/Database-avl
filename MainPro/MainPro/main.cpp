#include<iostream>
#include<string>
#include"AVLtree.h"
using namespace std;

void test1(); void test2(); void test3();
void printTree(node* n);

int main() {
	test3();
	system("pause");
	return 0;
}

void test1() {
	avl atree;
	for (int i = 0; i < 20; i++) {
		atree.insert(atree.root, i, NULL);
	}
	printTree(atree.root);
}

void test2() {
	avl atree;
	for (int i = 0; i < 20; i++) {
		atree.insert(atree.root, i, NULL);
	}
	printTree(atree.root);
	for (int i = 0; i < 5; i++) {
		int temp;
		cin >> temp;
		atree.del(temp);
		printTree(atree.root);
	}
}

void test3() {
	avl t;
	for (int k = 0; k < 7; k++) {
		datatype* new_data = new datatype;
		new_data->i = k;
		strcpy_s(new_data->s, "this leaf");
		t.insert(t.root, k, new_data);
	}
	printTree(t.root);
	t.save("index","data");
	cout << endl;
	printTree(t.root);

	datatype* new_data = new datatype;
	new_data->i = 999;
	strcpy_s(new_data->s, "this root");
	t.change(1, new_data);
	t.del(3);
	t.del(1);

	cout << endl;
	printTree(t.root);
	t.save("index","data");
	cout << endl;
	printTree(t.root);
}

void printTree(node* n) {
	if (n != NULL) {
		cout << n->key << ":\t";
		if (n->lchild)
			cout << n->lchild->key << "\t";
		else
			cout << "N/A \t";
		if (n->rchild)
			cout << n->rchild->key << "\t";
		else
			cout << "N/A" << "\t";
		cout << n->LR << "\t" << n->h << "\t" << n->is_fresh << "\t" << n->address << "\t";
		if (n->father)cout << n->father->key;
		cout << endl;
		printTree(n->lchild);
		printTree(n->rchild);
	}
}