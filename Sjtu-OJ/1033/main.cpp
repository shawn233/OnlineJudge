#include <iostream>
#include <cstdio>
#include <stack>
#include <cmath>

using namespace std;

int get_rank(char ch) {
    switch(ch) {
    case '+':
    case '-':   //Substruct: 8 - 3
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case '_':   //Negative: - 3
        return 4;
    default:
        return -1;
    }
}

bool calculate (char op, stack<long long> & nums) {
    //op: +- */ ^ _
    long long num1, num2;
    if (op == '_') {
        num1 = nums.top();
        nums.pop();
        nums.push(-num1);
        return true;
    }
    if (nums.empty()) {
        printf("Unexpected Error2");
        return false;
    }
    num2 = nums.top();
    nums.pop();
    if (nums.empty()) {
        printf("Unexpected Error3");
        return false;
    }
    num1 = nums.top();
    nums.pop();
    switch(op) {
    case '+':
        nums.push(num1+num2);
        return true;
    case '-':
        nums.push(num1-num2);
        return true;
    case '*':
        nums.push(num1 * num2);
        return true;
    case '/':
        if (num2)
            nums.push(num1 / num2);
        else
            return false;
        return true;
    case '^':
        nums.push((long long)pow(num1, num2));
        return true;
    default:
        printf("Unexpected Error4");
        return false;
    }
}

int main()
{
    char ch, op;
    stack<long long> nums;
    stack<char> ops;
    long long tmp, prev_rank, cur_rank;
    bool neg_op = true;

    prev_rank = -1;

    freopen("in", "r", stdin);

    while (~scanf("%c", &ch)) {
        if (ch >= '0' && ch <= '9') {
            tmp = ch-'0';
            while(~scanf("%c", &ch)) {
                if (ch >= '0' && ch <= '9') {
                    tmp *= 10;
                    tmp += (ch-'0');
                }
                else
                    break;
            }
            nums.push(tmp);
            neg_op = false;
        }
        if (ch == '\n')
            break;
        if (ch == ' ')
            continue;
        //Now, <char> ch must be an operator
        if (ch == '-' && neg_op) {
            ch = '_';
        }
        neg_op = true;
        if (ch == '(') {
            ops.push(ch);
            prev_rank = 0;
            continue;
        } else if (ch == ')') {
            while (!ops.empty()) {
                op = ops.top();
                ops.pop();
                if (op == '(')
                    break;
                if (!calculate(op, nums)) {
                    printf("Error\n");
                    return false;
                }
            }
            if (op != '(') {
                printf("Error\n");
                return 0;
            }
            op = ')';
            continue;
        }
        cur_rank = get_rank(ch);
        if (cur_rank > prev_rank ||(cur_rank == 3 && cur_rank == prev_rank)) {
            prev_rank = cur_rank;
            ops.push(ch);
        } else if (cur_rank != -1) {
            while (prev_rank >= cur_rank) {
                if (!ops.empty()) {
                    op = ops.top();
                    ops.pop();
                    if (!calculate(op, nums)) {
                        printf("Error\n");
                        return 0;
                    }
                }
                if (!ops.empty())
                    prev_rank = get_rank(ops.top());
                else
                    prev_rank = 0;
            }
            ops.push(ch);
            prev_rank = cur_rank;
        } else {
            printf("Unexpected Char Error %c\n", ch);
            return 1;
        }
    }

    while (!ops.empty()) {
        op = ops.top();
        ops.pop();
        if (op == '(') {
            printf("Error\n");
            return 0;
        }
        if(!calculate(op, nums)) {
            printf("Error\n");
            return 0;
        }
    }
    if (nums.size() != 1) {
        printf("Error\n");
        return 0;
    }

    printf("%lld\n", nums.top());
    nums.pop();

    return 0;
}
