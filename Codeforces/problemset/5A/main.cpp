#include<iostream>
#include<cstdio>
#include<cstdlib>

#define MAX_LINE 200

using namespace std;

int read_till(char dest) {
	char tmp;
	int cnt = 0;
	while (~scanf("%c", &tmp)) {
		//cout << "tmp:" << tmp << " ";
		++ cnt;
		if (tmp == dest) {
			break;
		}
	}
	return cnt;
}

int main() {
	char tmp;
	int state = 0;
	int n_users = 0;
	int ans = 0;

	//freopen("in.txt", "r", stdin);

	while (true) {
		//cout << "tmp:" << tmp << " state:" << state << " n_users:" << n_users << " ans:" << ans << endl;
		if (state == 0) {
			if (scanf("%c", &tmp) == EOF)
				break;
			if (tmp == '+'){
				state = 1;
				++ n_users;
			} else if (tmp == '-') {
				state = 1;
				-- n_users;
			} else {
				state = 2;
				read_till(':');
			}
		} else if (state == 1) {
			state = 0;
			read_till('\n');
		} else if (state == 2) {
			state = 0;
			ans += (read_till('\n') - 1) * n_users;
		}
	}

	cout << ans << endl;

	//fclose(stdin);

	return 0;
}
