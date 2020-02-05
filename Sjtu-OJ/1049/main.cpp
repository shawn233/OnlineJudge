#include <iostream>
#include <cstdio>
#include <stack>
#define MAX 1000

using namespace std;

bool test(int N, int M, int * order) {
    int prev = -1, b = -1;
    stack<int> st;
    for (int i = 0; i < N; ++ i) {
        if (order[i] < prev) {
            if (st.empty()) {
                return false;
            } else if (order[i] == st.top()) {
                st.pop();
            } else {
                return false;
            }
        } else if (order[i] > prev) {
            if (order[i] > b) {
                ++ b;
                for (; b < order[i]; ++ b) {
                    st.push(b);
                }
                if (st.size() > M)
                    return false;
                } else {
                    if (st.empty())
                        return false;
                    else if (st.top() == order[i])
                        st.pop();
                    else
                        return false;
                }
        } else {
            printf("<error>\n");
        }
        prev = order[i];
    }
    return true;
}

int main()
{
    int T, N, M;
    int order[MAX];

    freopen("in.txt", "r", stdin);

    scanf("%d", &T);

    for (int t = 0; t < T; ++ t) {
        scanf("%d %d", &N, &M);
        for (int i = 0; i < N; ++ i)
            scanf("%d", &order[i]);
        bool res = test(N, M, order);
        if (res)
            printf("YES\n");
        else
            printf("NO\n");
    }

    fclose(stdin);

    return 0;
}
