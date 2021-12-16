#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, vo; //��Ʒ��Ŀ�Լ���������
int v[N], w[N]; //ÿ����Ʒ�ļ�ֵ������
int x[N];
int maxV;  //��ȡ������ֵ
//��Ʒ����
void init() {  //���ڳ�ʼ�������������
	printf("�������ѡȡ����Ʒ��n������vo��");
	scanf("%d%d", &n, &vo);
	printf("�����������Ӧ����Ʒ����wi: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &w[i]);
	printf("�����������Ӧ����Ʒ��ֵvi: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);
}
struct Node { //�������ڽ��з�֧�޽������������
	Node() {
		value = 0;
		weight = 0;
		LE = 0;
		parent = 0;
		bound = 0;
	}
	int value;           //��ǰ��������ܼ�ֵ
	int weight;          //��ǰ�������������
	double bound;        //��ǰ���Ϊ���������Դﵽ�ļ�ֵ�Ͻ�
	int LE;           //�ýڵ�������Σ�����ȣ���0��ʼ����
	struct Node *parent; //ָ�򸸽ڵ㣬���ڻ��ݹ���
	//�����������ڼ���
	bool operator()(const Node &b) const {
		return bound < b.bound;
	}
};

struct Item {
	int ID;     //��Ʒ���
	int value;  //��Ʒ�����ļ�ֵ
	int weight; //��Ʒ���������
	double avg; //�����������ֵ
} IT[N];
//�������������ֵ�Ӵ�С����
bool cmp(Item x, Item y) {
	return x.avg > y.avg;
}
double maxBound(Node *node) {//�����޽纯��
	double maxV = node->value;
	int rest = vo - node->weight; //���㵱ǰ����ʣ���ݻ�
	int i = node->LE;
	//�����������ֵ
	while (i < n && rest > IT[i].weight) {
		maxV += IT[i].value;
		rest -= IT[i].weight;
		i++;
	}
	if (rest != 0) {
		maxV += rest * IT[i].avg;
	}
	return maxV;
}

int bfs() {
	priority_queue<Node *> Q; //�������ȶ��м���
	int maxV;             //���浱ǰΪ����������ֵ
	Node *maxNode;            //���浱ǰΪ��������ֵ��Ҷ�ӽڵ�
	Node *FN, *CURN;

	FN = new Node();
	FN->bound = maxBound(FN);
	FN->parent = NULL;
	Q.push(FN); //��һ����㿪ʼ
	maxV = 0;
	maxNode = FN;
	while (!Q.empty()) {
		CURN = Q.top();
		Q.pop();
		if (CURN->weight + IT[CURN->LE].weight <= vo) {		//�������ӽ��
			Node *LN = new Node();
			LN->value = CURN->value + IT[CURN->LE].value;
			LN->weight = CURN->weight + IT[CURN->LE].weight;
			LN->LE = CURN->LE + 1;
			LN->parent = CURN;
			LN->bound = maxBound(LN);
			if (LN->LE < n) {
				Q.push(LN);
			}
			if (maxV < LN->value) {
				maxV = LN->value;
				maxNode = LN;
			}
		}
		if (CURN->bound > maxV) {		//�����Һ��ӽ��
			Node *RN = new Node();
			RN->value = CURN->value;
			RN->weight = CURN->weight;
			RN->LE = CURN->LE + 1;
			RN->parent = CURN;
			RN->bound = maxBound(RN);
			if (RN->LE < n) {
				Q.push(RN);
			}
		}
	}
	CURN = maxNode;
	while (CURN) {
		int tempValue = CURN->value;
		CURN = CURN->parent;
		if (CURN && CURN->value != tempValue)
			x[IT[CURN->LE].ID] = 1;
	}
	return maxV;
}
void ansbybranch_and_bound() {
	for (int i = 0; i < n; i++) {
		IT[i].ID = i;
		IT[i].value = v[i];
		IT[i].weight = w[i];
		IT[i].avg = (double)v[i] / w[i];
	}
	sort(IT, IT + n, cmp);
}
void print() {	//��ӡ���
	cout << "����ֵΪ:" << bfs() << endl;
	cout << "ѡȡ����Ϊ:" << endl;
	for (int i = 0; i < n; i++) {
		if (x[i]) {
			cout << i + 1 << " ";
		}
	}
	cout << endl;
}
int main() {
	init();//������������
	ansbybranch_and_bound(); //���õ�ǰ�㷨�������
	print(); //��ӡ����
	return 0;
}
