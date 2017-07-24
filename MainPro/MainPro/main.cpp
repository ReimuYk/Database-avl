#include<iostream>
#include<string>
#include"AVLtree.h"
#include<ctime>
#include<random>
#include<sstream>
using namespace std;

void commandGUI();
void MainTest(); //a test from ppt
void test1(); //insert()
void test2(); //insert() & del()
void test3(); //ins() & del() & datatype
void test4(); //load();scan();
void test5(); //1000 data
void test6(); //read file;

void printTree(node* n);

int main() {
	//MainTest();
	commandGUI();
	system("pause");
	return 0;
}

void MainTest() {
	double start, end;
	double cost;
	start = clock();
	avl t;
	for (int k = 0; k < 1000000; k++) {
		datatype* new_data = new datatype;
		new_data->i = k + 10;
		strcpy_s(new_data->s, "this leaf");
		t.insert(t.root, k, new_data);
	}
	end = clock();
	cost = end - start;
	cout << "Time cost(insert 100w):" << cost / 1000 << "s" << endl<< endl;

	start = clock();
	t.save("index", "data");
	end = clock();
	cost = end - start;
	cout << "Time cost(save):" << cost / 1000 << "s" << endl << endl;

	start = clock();
	t.load("index", "data");
	end = clock();
	cost = end - start;
	cout << "Time cost(load):" << cost / 1000 << "s" << endl << endl;

	start = clock();
	for (int k = 0; k < 1000000; k++) {
		t.scan(k);
	}
	end = clock();
	cost = end - start;
	cout << "Time cost(search 100w):" << cost / 1000 << "s" << endl << endl;

	//cycle test
	int temp;
	srand(time(NULL));
	start = clock();
	for (int k = 1; k < 500001; k++) {
		temp = rand() * 1000000;
		t.scan(temp);//(a);

		if (k % 37 == 0) {
			node* n = t.root;
			while (true) {
				int q = rand() * 3;
				if (q == 0) {
					t.del(n->key);
					break;
				}
				else if (q == 1) {
					if (n->lchild)
						n = n->lchild;
					else {
						t.del(n->key);
						break;
					}
				}
				else if (q == 2) {
					if (n->rchild)
						n = n->rchild;
					else {
						t.del(n->key);
						break;
					}
				}
			}
		}//(b)
		if (k % 11 == 0) {
			temp = rand() * 1000000 + 1000000;
			datatype* d = new datatype;
			d->i = temp;
			strcpy_s(d->s, "new insert");
			t.insert(t.root, temp, d);
		}//(c)
		if (k % 17 == 0) {
			node* n = t.root;
			temp = rand() * 1000000 + 1000000;
			datatype* d = new datatype;
			d->i = temp;
			strcpy_s(d->s, "new insert");
			while (true) {
				int q = rand() * 3;
				if (q == 0) {
					t.change(n->key,d);
					break;
				}
				else if (q == 1) {
					if (n->lchild)
						n = n->lchild;
					else {
						t.change(n->key,d);
						break;
					}
				}
				else if (q == 2) {
					if (n->rchild)
						n = n->rchild;
					else {
						t.change(n->key,d);
						break;
					}
				}
			}
		}//(d)
	}
	end = clock();
	cost = end - start;
	cout << "Time cost(cycle test):" << cost / 1000 << "s" << endl << endl;

	start = clock();
	for (int k = 1; k < 500001; k++) {
		temp = rand() * 1000000;
		k % 37;
		k % 11;
		k % 17;
	}
	end = clock();
	cost = end - start;
	cout << "Time cost(random):" << cost / 1000 << "s" << endl << endl;

	start = clock();
	while (t.root) {
		t.del((t.root)->key);
	}
	end = clock();
	cost = end - start;
	cout << "Time cost(del all):" << cost / 1000 << "s" << endl << endl;
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
	for (int i = 0; i < 10; i++) {
		atree.insert(atree.root, i, NULL);
	}
	printTree(atree.root);
	for (int i = 0; i < 10; i++) {
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

void test4() {
	avl t;
	for (int k = 0; k < 7; k++) {
		datatype* new_data = new datatype;
		new_data->i = k + 10;
		strcpy_s(new_data->s, "this leaf");
		t.insert(t.root, k, new_data);
	}
	t.save("index", "data");
	printTree(t.root);
	cout << endl;

	avl t2;
	t2.load("index", "data");
	printTree(t2.root);

	datatype* d = t.scan(5);
	cout << d->i << "\t" << d->s << endl;
	for (int k = 0; k < 7; k++) {
		d = t2.scan(k);
		cout << d->i << "\t" << d->s << endl;
	}
}

void test5() {
	double start, end;
	start = clock();
	avl t;
	for (int k = 0; k < 1000000; k++) {
		datatype* new_data = new datatype;
		new_data->i = k + 10;
		strcpy_s(new_data->s, "this leaf");
		t.insert(t.root, k, new_data);
	}
	t.save("index", "data");
	end = clock();
	double cost = end - start;
	cout << "Time cost:" << cost / 1000 << "s" << endl;

}

void test6() {
	avl t;
	double start, end;
	start = clock();
	t.load("index", "data");
	end = clock();
	double cost = end - start;
	cout << "Time cost:" << cost / 1000 << "s" << endl;

	int k;
	while (cin >> k) {
		start = clock();
		datatype* d = t.scan(k);
		end = clock();
		cout << d->i << "\t" << d->s << endl;
		double cost = end - start;
		cout << "Time cost:" << cost / 1000 << "s" << endl << endl;
	}
}





//key: l r LR h fresh adr
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

void commandGUI() {
	avl tree;
	string input;
	double start, end;
	while (true) {
		cout << ">>> ";
		getline(cin, input);
		stringstream ss;
		ss << input;
		string func;
		ss >> func;
		if (func == "quit") {
			cout << "Wait to save...";
			start = clock();
			tree.save("index2", "data2");
			end = clock();
			cout << "Have done." << (end - start) / 1000 << "s" << endl;
			return;
		}
		else if (func == "load") {
			cout << "Wait to load...";
			start = clock();
			tree.load("index2", "data2");
			end = clock();
			cout << "Have done." << (end - start) / 1000 << "s" << endl << endl;
		}
		else if (func == "save") {
			cout << "Wait to save...";
			start = clock();
			tree.savedata("data2");
			end = clock();
			cout << "Have done." << (end - start) / 1000 << "s" << endl << endl;
		}
		else if (func == "insert") {
			start = clock();
			int kk = 0;
			int v1 = 0;
			char v2[12];
			string _v2;
			ss >> kk;
			ss >> v1;
			ss >> _v2;
			strcpy_s(v2, _v2.c_str());
			datatype* d = new datatype;
			d->i = v1;
			strcpy_s(d->s, v2);
			tree.insert(tree.root, kk, d);
			end = clock();
			cout << "Have done." << (end - start) / 1000 << "s" << endl << endl;
		}
		else if (func == "find") {
			start = clock();
			int kk = 0;
			ss >> kk;
			datatype* d = tree.scan(kk);
			end = clock();
			double cost = (end - start) / 1000;
			if (d == NULL) {
				cout << "Not found." << cost << "s" << endl << endl;
			}
			else {
				cout << "int:\t" << d->i << endl;
				cout << "stirng:\t" << d->s << endl;
				cout << "Have done." << cost << "s" << endl << endl;
			}
		}
		


	}
}