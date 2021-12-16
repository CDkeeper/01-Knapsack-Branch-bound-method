#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, vo; //物品数目以及背包容量
int v[N], w[N]; //每件物品的价值和重量
int x[N];
int maxV;  //获取的最大价值
//物品类型
void init() {  //用于初始传入待计算数据
	printf("请输入待选取的物品数n与容量vo：");
	scanf("%d%d", &n, &vo);
	printf("请依次输入对应的物品重量wi: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &w[i]);
	printf("请依次输入对应的物品价值vi: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);
}
struct Node { //构造用于进行分支限界搜索的树结点
	Node() {
		value = 0;
		weight = 0;
		LE = 0;
		parent = 0;
		bound = 0;
	}
	int value;           //当前结点的最大总价值
	int weight;          //当前结点的最大总重量
	double bound;        //当前结点为根子树可以达到的价值上界
	int LE;           //该节点所处层次，即深度，从0开始计算
	struct Node *parent; //指向父节点，用于回溯过程
	//重载括号用于计算
	bool operator()(const Node &b) const {
		return bound < b.bound;
	}
};

struct Item {
	int ID;     //物品序号
	int value;  //物品所带的价值
	int weight; //物品所需的重量
	double avg; //单重量物体价值
} IT[N];
//按单重量物体价值从大到小排序
bool cmp(Item x, Item y) {
	return x.avg > y.avg;
}
double maxBound(Node *node) {//计算限界函数
	double maxV = node->value;
	int rest = vo - node->weight; //计算当前背包剩余容积
	int i = node->LE;
	//计算期望最大值
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
	priority_queue<Node *> Q; //构造优先队列计算
	int maxV;             //保存当前为主处的最大价值
	Node *maxNode;            //保存当前为主处最大价值的叶子节点
	Node *FN, *CURN;

	FN = new Node();
	FN->bound = maxBound(FN);
	FN->parent = NULL;
	Q.push(FN); //第一个结点开始
	maxV = 0;
	maxNode = FN;
	while (!Q.empty()) {
		CURN = Q.top();
		Q.pop();
		if (CURN->weight + IT[CURN->LE].weight <= vo) {		//计算左孩子结点
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
		if (CURN->bound > maxV) {		//计算右孩子结点
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
void print() {	//打印结果
	cout << "最大价值为:" << bfs() << endl;
	cout << "选取方案为:" << endl;
	for (int i = 0; i < n; i++) {
		if (x[i]) {
			cout << i + 1 << " ";
		}
	}
	cout << endl;
}
int main() {
	init();//输入待求解数据
	ansbybranch_and_bound(); //采用当前算法解决问题
	print(); //打印求解答案
	return 0;
}
