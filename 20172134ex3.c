
/*
조건 1: 단어(word)를 기준(key값)으로 하여 이진 탐색 트리(BST)를 이용하여 만든다.
조건 2 : 단어(word)는 영문으로 의미(meaning)은 한글로 구성한다. (한글 입출력이 안 될 경우 둘 다 영문으로 작성 가능함.)
조건 3 : 단어(word)는 대문자 소문자를 같은 단어로 취급합니다.
	예) GooD 과 gOOD 은 같은 단어가 된다.
조건 4: 단어(word)의 순서는 알파벳 순서로 a가 b보다 작은 것으로 간주한다.두 단어가 같은 단어로 시작한다면 그 뒤에 단어로 비교한다. (사전과 같은 방식으로 처리)
	예) after 와 again 은 after가 작은(먼저 나오는) 단어이다.
조건 5: 출력(5.print)는 BST의 탐색을 이용(inorder traversal)하여 출력합니다.
조건 6 : 의미 검색(4.search(meaning)) 역시 BST의 탐색을 이용(inorder traversal)하여 각 단어의 의미 값을 검색하여 표시합니다.
조건 7 : 단어(word) 입력 시 영어가 아닌 값이나 특수문자, 공백 등이 입력되지 않는 다고 가정합니다.의미(meaning) 입력은 공백만 제외하고 어떠한 문자도 가능합니다.
조건 8 : 위 화면 출력 예를 잘 보고 예외 상황의 출력에 맞게 프로그래밍 하시오.
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
	while (str1[i] != '\0' || str2[i] != '\0') {	// 문자열 하나가 끝날때까지
		if (str1[i] == str2[i] || str1[i] + 32 == str2[i] || str1[i] == str2[i] + 32) {		// 대문자 소문자 아스키코드로 비교 (같은 취급)
			i++;
			continue;
		}
		else if (str1[i] > str2[i])return 1;		// str1이 더 크면 1 
		else if (str1[i] < str2[i])return -1;		// str2가 더 크면 -1
	}

	// 어느 한쪽 문자열이 끝났고 i - 1 까지 모두 같은 상태
	if (str1[i] == str2[i] || str1[i] + 32 == str2[i] || str1[i] == str2[i] + 32)return 0; // 아스키코드 대소문자같거나 문자 비교 결과 '\0' 
	else if (str1[i] != '\0')return 1; // str1이 더 크면 1
	else return -1;	// str2가 더 크면 -1
}


void insert(TNode** root, char word[]) {
	TNode* newNode = (TNode*)malloc(sizeof(TNode));
	strcpy(newNode->word, word);
	newNode->left = NULL;	newNode->right = NULL;
	
	TNode* currRoot = *root;
	TNode* currNode = *root;
	while (currNode) {		//NULL일 때까지
		int compare = my_strcmp(currNode->word, word);
		if (compare == 0) {		//currNode와 word값이 일치
			printf("  This word already exists !!\n");
			return;
		}
		currRoot = currNode;
		if (compare == 1) {		// currNode가 word보다 큰 값
			currNode = currNode->left;
		}
		else if(compare == -1){		// word가 currNode보다 큰 값
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
		if (compare == 1) {		//currRoot가 word보다 큰 값
			currRoot->left = newNode;
		}
		else if(compare == -1){			//word가 currRoot보다 큰 값
			currRoot->right = newNode;
		}
	}
}
void deleteTree(TNode* root, char word[]) {
	TNode* find = root;
	TNode* roo = root;
	TNode* parent = NULL;
	
	if (find == NULL) {
		printf("노 루트");
		return;
	}
	else{
		int compare = my_strcmp(find->word, word);
		while (find != NULL && compare != 0) { // root 존재하고 삭제 word값 찾을때까지 반복
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
	else {// 부모노드와 삭제할 노드를 넣음 parent, p
		// 삭제할 노드가 자식을 갖지 않는 단말 노드일 경우
		if (find->left == NULL && find->right == NULL) {
			printf("0\n");
			if (parent == NULL) {
				root = NULL;
			}
			else {
				if (parent->left == find) parent->left = NULL;
				else parent->right = NULL;	//연결을 끊어줌
			}
		}
		// 삭제할 노드가 자식 하나를 갖는 경우
		else if(find->left == NULL || find->right == NULL){
			TNode* child;
			printf("1\n");
			if (find->left != NULL) {		//삭제될 노드의 자식 노드를 찾음
				child = find->left;
			}
			else {
				child = find->right;
			}
			if (find == roo) {//삭제할 노드가 루트 노드
				roo = child;
			}
			else {
				if (parent->left == find) parent->left = child;
				else parent->right = child;
			}
		}
		else {// 삭제할 노드가 자식 두개를 갖는 경우
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
		printf("삭제된 단어 %s", find->word);
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