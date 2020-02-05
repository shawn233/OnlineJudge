#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#define MAX 20000

using namespace std;

/**
 *This is just shit | 2017-12-11 00:46
 *Just Pure shit
 *Without knowledge
 *Just shit
 *Which cost me 2 hours
 *Plus good mood
 *Hate this fucking shit
**/

struct Stock {
	int id, val;
};

//Mercy my poor knowledge about quick sort. I am just an idiot.
void make_sort(Stock * s, int * pos,int l, int r) {
	if (l >= r)
		return;
	int left = l, right = r, val, p;
	val = s[l].val;
	p = s[l].id;
	while (left < right) {
		while (right > left && (s[right].val > val || (s[right].val == val && s[right].id < p) ))
			-- right;
		if (left != right)
			pos[s[right].id] = left;
		s[left] = s[right];
		while (left < right && (s[left].val < val ||(s[left].val == val && s[left].id > p))) 
			++ left;
		if (left != right)
			pos[s[left].id] = right;
		s[right] = s[left];
	}
	pos[p] = left;
	s[left].val = val;
	s[left].id = p;
	make_sort(s, pos, l, left-1);
	make_sort(s, pos, left+1, r);
}

int main () {
	int N, K, tmp, n1, n2;
	char ch;
	string cmd;
	Stock s[MAX+1];
	int pos[MAX+1];
	
	freopen("in.txt", "r", stdin);
	
	scanf("%d", &N);
	for (int i = 1; i <= N; ++ i) {
		scanf("%d", &tmp);
		s[i].id = i;
		s[i].val = tmp;
		pos[i] = i;
	}
	cin >> K;
	for (int i = 0; i < K; ++ i) {
		cin >> ch;
		switch(ch) {
		case 'M':
			cin >> n1 >> n2;
			s[pos[n1]].val = n2;
			break;
		case 'Q':
		{
			make_sort(s, pos,1, N);
			cin >> tmp;
			getline(cin, cmd);
			stringstream ss(cmd);
			for (int j = 0; j < tmp; ++ j) {
				ss >> n1;
				printf("%d ", s[N+1-n1].id);
			}
			printf("\n");}
			break;
		default:
			printf("error");
			return 0;
		}
	}
}