/* 2014726074 �ְ��� */
#include <iostream>
using namespace std;

int N;
char** bestset;
char** temp;
int bestchoice;
bool flag = false;
bool promising(int i, int j, char** input);
void knapsack(int i, int j, char** input);
void flipping(int i, int j, char** input);
bool allOff(char** input);

void main() {
	int n, count = 0;
	char** input;

	cout << "Input size : ";
	cin >> n;
	cout << endl << "INPUT" << endl;

	input = new char*[n];
	bestset = new char*[n];
	temp = new char*[n];

	N = n;
	bestchoice = N * N;

	for (int i = 0; i < n; i++) {
		input[i] = new char[n];
		bestset[i] = new char[n];
		temp[i] = new char[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> input[i][j];
			if (input[i][j] == 'O') count++;
		}
	}

	// �ϳ��� ������ ���
	if (count > 0) {
		knapsack(0, 0, input);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				bestset[i][j] = temp[i][j];
	}
	// ��� ������ ���
	else {
		flag = true;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				bestset[i][j] = input[i][j];
	}
	cout << endl << "OUTPUT" << endl;
	if (flag == true) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				cout << bestset[i][j] << " ";
			cout << endl;
		}
	}
	else {
		cout << "no solution.\n";
	}
	system("pause");
}
// knapsack( [2^n(worst): ���, n^2: �迭 ��ü] => O(n^2 2^n) )
void knapsack(int i, int j, char** input) {
	if (i == N || j == N) return;

	if (promising(i, j, input)) {
		// backtracking ���� �������� ���ư��� ���� flip ����
		flipping(i, j, input);
		bestset[i][j] = 'O';
		// ������ �迭 ������ �� ���ҿ� �ٴٶ��� �� ��ĭ ������ ����
		if (j == N - 1)
			knapsack(i + 1, 0, input);
		else
			knapsack(i, j + 1, input);

		flipping(i, j, input);
		bestset[i][j] = '#';
		if (j == N - 1)
			knapsack(i + 1, 0, input);
		else
			knapsack(i, j + 1, input);
	}
	// knapsack �� ������ ����(��� ���� ��)�� �� ���� �ּҷ� ������ ��� Ž��
	if (allOff(input)) {
		int o_count = 0;
		for (int a = 0; a < N; a++) {
			for (int b = 0; b < N; b++) {
				if (bestset[a][b] == 'O')
					o_count++;
			}
		}

		if (o_count < bestchoice && o_count > 0) {
			// ���� ���� ���� ���� ����
			bestchoice = o_count;
			flag = true;
			for (int m = 0; m < N; m++) {
				for (int n = 0; n < N; n++)
					temp[m][n] = bestset[m][n];
			}
		}
	}
}
// �������� �Ǵ�
bool promising(int i, int j, char** input) {
	if (i == 0) return true;
	if (j == 0) {
		if (i > 1) {
			if (input[i - 2][N - 1] == 'O') return false;
		}
	}
	else {
		if (input[i - 1][j - 1] == 'O') return false;
	}
	return true;
}
// ������Ű������ �Լ�
void flipping(int i, int j, char** input) {
	int d1[4] = { -1,1,0,0 };
	int d2[4] = { 0,0,-1,1 };
	// ��/��/��/�� ����
	for (int k = 0; k < 4; k++) {
		int mi = i + d1[k];
		int mj = j + d2[k];
		if (mi < 0 || mi == N || mj < 0 || mj == N) continue;

		if (input[mi][mj] == 'O') {
			input[mi][mj] = '#';
		}
		else {
			input[mi][mj] = 'O';
		}
	}
	// ���� ��ġ ����
	if (input[i][j] == 'O') input[i][j] = '#';
	else input[i][j] = 'O';
}
// ��� ���� ������ ���� �˻� (n^2)
bool allOff(char** input) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			if (input[i][j] == 'O') return false;
	}
	return true;
}