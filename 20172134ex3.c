
/*
���� 1: �ܾ�(word)�� ����(key��)���� �Ͽ� ���� Ž�� Ʈ��(BST)�� �̿��Ͽ� �����.
���� 2 : �ܾ�(word)�� �������� �ǹ�(meaning)�� �ѱ۷� �����Ѵ�. (�ѱ� ������� �� �� ��� �� �� �������� �ۼ� ������.)
���� 3 : �ܾ�(word)�� �빮�� �ҹ��ڸ� ���� �ܾ�� ����մϴ�.
	��) GooD �� gOOD �� ���� �ܾ �ȴ�.
���� 4: �ܾ�(word)�� ������ ���ĺ� ������ a�� b���� ���� ������ �����Ѵ�.�� �ܾ ���� �ܾ�� �����Ѵٸ� �� �ڿ� �ܾ�� ���Ѵ�. (������ ���� ������� ó��)
	��) after �� again �� after�� ����(���� ������) �ܾ��̴�.
���� 5: ���(5.print)�� BST�� Ž���� �̿�(inorder traversal)�Ͽ� ����մϴ�.
���� 6 : �ǹ� �˻�(4.search(meaning)) ���� BST�� Ž���� �̿�(inorder traversal)�Ͽ� �� �ܾ��� �ǹ� ���� �˻��Ͽ� ǥ���մϴ�.
���� 7 : �ܾ�(word) �Է� �� ��� �ƴ� ���̳� Ư������, ���� ���� �Էµ��� �ʴ� �ٰ� �����մϴ�.�ǹ�(meaning) �Է��� ���鸸 �����ϰ� ��� ���ڵ� �����մϴ�.
���� 8 : �� ȭ�� ��� ���� �� ���� ���� ��Ȳ�� ��¿� �°� ���α׷��� �Ͻÿ�.
	*/

#define _CRT_SECURE_NO_WARNINGS
#define LEN 81
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef char TElement;
typedef struct BinTrNode {
	TElement word[LEN];
	TElement mean[LEN];
	struct BinTrNode* left;
	struct BinTrNode* right;
}TNode;

int my_strcmp(char* str1, char* str2)
{
	int i = 0;	
	while (str1[i] != '\0' || str2[i] != '\0') {	// ���ڿ� �ϳ��� ����������
		if (str1[i] == str2[i] || str1[i] + 32 == str2[i] || str1[i] == str2[i] + 32) {		// �빮�� �ҹ��� �ƽ�Ű�ڵ�� �� (���� ���)
			i++;
			continue;
		}
		else if (str1[i] > str2[i])return 1;		// str1�� �� ũ�� 1 
		else if (str1[i] < str2[i])return -1;		// str2�� �� ũ�� -1
	}

	// ��� ���� ���ڿ��� ������ i - 1 ���� ��� ���� ����
	if (str1[i] == str2[i] || str1[i] + 32 == str2[i] || str1[i] == str2[i] + 32)return 0; // �ƽ�Ű�ڵ� ��ҹ��ڰ��ų� ���� �� ��� '\0' 
	else if (str1[i] != '\0')return 1; // str1�� �� ũ�� 1
	else return -1;	// str2�� �� ũ�� -1
}


void insert(TNode** root, char word[]) {
	TNode* newNode = (TNode*)malloc(sizeof(TNode));
	strcpy(newNode->word, word);
	newNode->left = NULL;	newNode->right = NULL;
	
	TNode* currRoot = *root;
	TNode* currNode = *root;
	while (currNode) {		//NULL�� ������
		int compare = my_strcmp(currNode->word, word);
		if (compare == 0) {		//currNode�� word���� ��ġ
			printf("  This word already exists !!\n");
			return;
		}
		currRoot = currNode;
		if (compare == 1) {		// currNode�� word���� ū ��
			currNode = currNode->left;
		}
		else if(compare == -1){		// word�� currNode���� ū ��
			currNode = currNode->right;
		}
	}
	char mean[LEN];
	getchar();
	printf("  Meaning: ");
	fgets(mean, LEN, stdin);
	mean[strlen(mean) - 1] = 0;
	strcpy(newNode->mean, mean);


	if (*root == NULL) {
		*root = newNode;
	}
	else{
		int compare = my_strcmp(currRoot->word, word);
		if (compare == 1) {		//currRoot�� word���� ū ��
			currRoot->left = newNode;
		}
		else if(compare == -1){			//word�� currRoot���� ū ��
			currRoot->right = newNode;
		}
	}
}
void deleteTree(TNode* root, char word[]) {
	TNode* find = root;
	TNode* roo = root;
	TNode* parent = NULL;
	
	if (find == NULL) {
		printf("�� ��Ʈ");
		return;
	}
	else{
		int compare = my_strcmp(find->word, word);
		while (find != NULL && compare != 0) { // root �����ϰ� ���� word�� ã�������� �ݺ�
			parent = find;
			compare = my_strcmp(find->word, word);
			if (compare == -1)
				find = find->right;
			else if (compare == 1)
				find = find->left;
		}
	}

	if (find == NULL) {
		printf("  This word is not found !!\n");
	}
	else {// �θ���� ������ ��带 ���� parent, p
		// ������ ��尡 �ڽ��� ���� �ʴ� �ܸ� ����� ���
		if (find->left == NULL && find->right == NULL) {
			printf("0\n");
			if (parent == NULL) {
				root = NULL;
			}
			else {
				if (parent->left == find) parent->left = NULL;
				else parent->right = NULL;	//������ ������
			}
		}
		// ������ ��尡 �ڽ� �ϳ��� ���� ���
		else if(find->left == NULL || find->right == NULL){
			TNode* child;
			printf("1\n");
			if (find->left != NULL) {		//������ ����� �ڽ� ��带 ã��
				child = find->left;
			}
			else {
				child = find->right;
			}
			if (find == roo) {//������ ��尡 ��Ʈ ���
				roo = child;
			}
			else {
				if (parent->left == find) parent->left = child;
				else parent->right = child;
			}
		}
		else {// ������ ��尡 �ڽ� �ΰ��� ���� ���
			printf("2\n");
			TNode* delParent,* delChild;
			delParent = find;
			delChild = find->right;
			while (delChild->left != NULL) {
				delParent = delChild;
				delChild = delChild->left;
			}
			if (delParent->left == delChild) {
				delParent->left = delChild->right;
			}
			else {
				delParent->right = delChild->right;
			}
			find = delChild;

		}
		printf("  This word is deleted successfully from My Dictionary.\n");
		printf("������ �ܾ� %s", find->word);
		//free(find);
	}
}


void display(TNode* root) {		//Inorder
	TNode* p = root;
	if (p != NULL){
		display(p->left);
		printf("  %s : %s\n", p->word, p->mean);
		display(p->right);
	}
}

void searchWord(TNode* root, char word[], bool* wordFlag) {
	TNode* p = root;
	if (p != NULL) {
		int compare = my_strcmp(p->word, word);
		searchWord(p->left, word, wordFlag);
		if (compare == 0) {
			if (*wordFlag == false) {
				printf("  << Search Result >>\n");
				*wordFlag = true;
			}
			printf("  %s : %s\n", p->word, p->mean);
		}
		searchWord(p->right, word, wordFlag);
	}
}
void searchMean(TNode* root, char mean[], bool* meanFlag) {
	TNode* p = root;
	if (p != NULL) {
		searchMean(p->left, mean, meanFlag);
		int compare = my_strcmp(p->mean, mean);
		if (compare == 0) {
			if (*meanFlag == false) {
				printf("  << Search Result >>\n");
				*meanFlag = true;
			}
			printf("  %s : %s\n", p->word, p->mean);
		}
		searchMean(p->right, mean , meanFlag);
	}
}


int main() {

	TNode* root = NULL;
	bool flag = true;
	int n;
	TElement word[LEN];

	while (flag) {
		printf("[1.input 2.delete 3.search(word) 4.search(meaning) 5.print 0.Exit] : ");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("  Word: ");
			scanf("%s", word);
			insert(&root, word);
			break;
		case 2:
			if (root != NULL) {
				printf("  Search(Word): ");
				scanf("%s", word);
				deleteTree(root, word);
			}
			else {
				printf("  BST is empty !!\n");
			}
			break;
		case 3:
			if (root != NULL) {
				printf("  Search(Word): ");
				scanf("%s", word);
				bool wordFlag = false;
				searchWord(root, word, &wordFlag);
				if (wordFlag == false) {
					printf("  This word is not found !!\n");
				}
			}
			else {
				printf("  BST is empty !!\n");
			}
			break;
		case 4:
			if (root != NULL) {
				printf("  Search(meaning): ");
				getchar();
				fgets(word, LEN, stdin);
				word[strlen(word) - 1] = 0;
				bool meanFlag = false;
				searchMean(root, word, &meanFlag);
				if (meanFlag == false) {
					printf("  This word is not found !!\n");
				}
			}
			else {
				printf("  BST is empty !!\n");
			}
			break;
		case 5:
			if(root != NULL){
				printf("  << My Dictionary >>\n");
				display(root);
			}
			else {
				printf("  BST is empty !!\n");
			}
			break;
		case 0:
			flag = false;
			break;
		}
	}
	return 0;
}