#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#define MAX_LEN 2010

/**
CLASS HighPrecisionInt
Properties
1. Only consider POSITIVE INTEGERS!!
**/

class HighPrecisionInt {

//<FINISHED>Addition Operation; assume the result doesn't exceed max_len
friend HighPrecisionInt operator + (const HighPrecisionInt &, const HighPrecisionInt &); 
//<FINISHED>Division Operation
friend HighPrecisionInt operator / (const HighPrecisionInt &, const HighPrecisionInt &);
//<FINISHED>Multiplication Operation; assume the result dosen't exceed max_len
friend HighPrecisionInt operator * (const HighPrecisionInt &, const HighPrecisionInt &);
//<FINISHED>Comparison Operator
friend bool operator < (const HighPrecisionInt &, const HighPrecisionInt &);
friend bool operator > (const HighPrecisionInt &, const HighPrecisionInt &);
friend bool operator == (const HighPrecisionInt &, const HighPrecisionInt &);
friend bool operator != (const HighPrecisionInt &, const HighPrecisionInt &);

friend ostream & operator << (ostream & out, const HighPrecisionInt & obj);
	
private:
	int max_len;	//Length of array
	int * arr; 		//pointer of array
	int len; 		//length of integer
	
	//<FINISHED>HighPrecisionInt multiplies a number between 0 and 10
	HighPrecisionInt singleMultiply(int i) const;
	
	//<FINISHED>HighPrecisionInt multiplies a number between 0 and 10
	//Note the HighPrecisionInt itself is changed
	HighPrecisionInt & selfSingleMultiply(int i);
	
	//<FINISHED>Precise comparison;
		//Range: *this[low, high] and num[num_low, num_high]
		//return value: 0(less), 1(equal), 2(larger)
	int comparison(const HighPrecisionInt & num, int num_low = 0, 
					int num_high = MAX_LEN, int low = 0, int high = MAX_LEN) const;
	
public:
	//<FINISHED> convert int to HighPrecisionInt
	HighPrecisionInt(int val, int m_len = MAX_LEN);  
	//construction function with no arguments
	HighPrecisionInt();
	//<FINISHED>convert char array to HighPrecisionInt, assume array ends with \0
	HighPrecisionInt(const char * val, int m_len = MAX_LEN);
	//<FINISHED>convert string to HighPrecisionInt
	HighPrecisionInt(const string & val, int m_len = MAX_LEN);
	//<FINISHED>Copy Construction Function
	HighPrecisionInt(const HighPrecisionInt &);
	//<FINISHED> deconstruct function
	~HighPrecisionInt() {delete [] arr;}
	
	void show() const; //<FINISHED> show the integer
	
	int getlen() {
		return len;
	}
	
	//<FINISHED>
	HighPrecisionInt & operator=(const HighPrecisionInt & num);
};

HighPrecisionInt::HighPrecisionInt(int val, int m_len): max_len(m_len) {
	max_len = min(max_len, MAX_LEN);
	arr = new int [max_len];
	if(val == 0) {
		arr[0] = 0;
		len = 1;
		return;
	}
	int tmp, cnt = 0;
	while(val > 0) {
		tmp = val % 10;
		val /= 10;
		arr[cnt ++] = tmp;
	}
	len = cnt;
}

HighPrecisionInt::HighPrecisionInt() {
	max_len = MAX_LEN;
	len = 1;
	arr = new int [max_len];
	arr[0] = 0;
}

HighPrecisionInt::HighPrecisionInt(const string & val,int m_len):max_len(m_len){
	max_len = min(max_len, MAX_LEN);
	arr = new int [max_len];
	len = val.size();
	for (int i = 0; i < len; ++ i)
		arr[i] = val[len-i-1]-'0';
}

HighPrecisionInt::HighPrecisionInt(const HighPrecisionInt & num) {
	max_len = num.max_len;
	len = num.len;
	arr = new int[max_len];
	for (int i = 0; i < len; ++ i) 
		arr[i] = num.arr[i];
}

void HighPrecisionInt::show() const {
	for(int i = len-1; i >= 0; -- i) 
		printf("%d", arr[i]);
}

HighPrecisionInt HighPrecisionInt::singleMultiply(int t) const{
	HighPrecisionInt ans(0);
	if(t > 1 && t < 10) {
		int tmp, ics = 0, i;
		for (i = 0; i < len; ++ i)  {
			tmp = arr[i]*t + ics;
			ans.arr[i] = tmp%10;
			ics = tmp/10;
		}
		if(ics) {
			ans.arr[i] = ics;
			ans.len = len + 1;
		} else
			ans.len = len;
	} else if(t == 10) {
		for (int i = len; i > 0; -- i)
			ans.arr[i] = arr[i-1];
		ans.arr[0] = 0;
		ans.len = len + 1;
	} else if (t == 1) {
		return *this;
	} else if(t == 0) {
	} else {
		printf("<error> Invalid use of HighPrecisionInt::singleMultiply\n");
		this->show();
		cout << endl << " t -- " << t << endl;
		cin.get();
	}
	return ans;
}

HighPrecisionInt & HighPrecisionInt::selfSingleMultiply(int t) {
	if(t > 1 && t < 10) {
		int tmp, ics = 0, i;
		for (i = 0; i < len; ++ i)  {
			tmp = arr[i]*t + ics;
			arr[i] = tmp%10;
			ics = tmp/10;
		}
		if(ics) {
			arr[i] = ics;
			len = len + 1;
		}
	} else if(t == 10) {
		if(!(len == 1 && arr[0] == 0)) {
			for (int i = len; i > 0; -- i)
				arr[i] = arr[i-1];
			arr[0] = 0;
			++ len;
		}
	} else if (t == 1) {
	} else if(t == 0) {
		len = 1;
		arr[0] = 0;
	} else {
		printf("<error> Invalid use of HighPrecisionInt::selfSingleMultiply\n");
	}
	return * this;
}

int HighPrecisionInt::comparison(const HighPrecisionInt & num, int num_low
	, int num_high, int low, int high) const {
		num_low = max(0, num_low);
		num_high = min(num.len-1, num_high);
		low = max(0, low);
		high = min(len-1, high);
		
		int num_dif = num_high - num_low + 1,
			dif = high - low + 1;
		if(dif < num_dif)
			return 0;
		else if(dif > num_dif)
			return 2;
		else {
			int i, j;
			for(i = high, j = num_high; i >= low; -- i, -- j) {
				if(arr[i] < num.arr[j])
					return 0;
				else if(arr[i] > num.arr[j])
					return 2;
			}
			return 1;
		}
	}

HighPrecisionInt & HighPrecisionInt::operator=(const HighPrecisionInt & num){
	if(this == &num) return * this;
	if(len != num.len) {
		delete [] arr;
		len = num.len;
		arr = new int[num.max_len];
	}
	max_len = num.max_len;
	for (int i = 0; i < len; ++ i)
		arr[i] = num.arr[i];
	return * this;
}

HighPrecisionInt operator + (const HighPrecisionInt & num1, const HighPrecisionInt & num2){
	int bigger_len = max(num1.len, num2.len),
		maxer_len = max(num1.max_len, num2.max_len);
	int ics = 0, tmp, i, n1, n2;
	HighPrecisionInt ans(0, maxer_len);
	for(i = 0; i < bigger_len; ++ i) {
		n1 = (i >= num1.len)?0:num1.arr[i];
		n2 = (i >= num2.len)?0:num2.arr[i];
		tmp = n1 + n2 + ics;
		ans.arr[i] = tmp%10;
		ics = tmp/10;
	}
	if(ics) {
		ans.arr[i] = ics;
		ans.len = bigger_len + 1;
	} else
		ans.len = bigger_len;
	return ans;
}

HighPrecisionInt operator * (const HighPrecisionInt & num1, const HighPrecisionInt & num2){
	HighPrecisionInt ans(0), tmp(0);
	for (int i = 0; i < num2.len; ++ i) {
		tmp = num1.singleMultiply(num2.arr[i]);
		for(int j = 0; j < i; ++ j)
			tmp.selfSingleMultiply(10);
		ans = ans + tmp;
	}
	return ans;
}

HighPrecisionInt operator / (const HighPrecisionInt & num1_orig, const HighPrecisionInt & num2) {
	if(num1_orig > num2) {
		HighPrecisionInt num1(num1_orig);
		int left = num1.len-1;
		int right = left - num2.len + 1;
		int i = 0;
		HighPrecisionInt ans(0);
		HighPrecisionInt tmp(0), prev(0);
		
		while(right >= 0) {
			i = 0;
			tmp = prev = HighPrecisionInt(0);
			//cout << "left -- " << left << " right -- " << right << endl;
			while(tmp.comparison(num1, right, left) != 2) {
				++ i;
				prev = tmp;
				tmp = num2.singleMultiply(i);
			}
			ans.selfSingleMultiply(10);
			ans = ans + (i-1);
			
			//Actually this part implements partial subtraction, which is an important
			// part in the algorithm of division operation
			if(prev != 0){
				int dcs = 0, tmp, num_prev;
				int dis = left-right+1;
				for(int ind = 0; ind < dis; ++ ind) {
					num_prev = (ind < prev.len)?prev.arr[ind]:0;
					tmp = num1.arr[ind+right] - num_prev - dcs;
					if(tmp < 0) {
						num1.arr[ind+right]=tmp+10;
						dcs = 1;
					} else {
						num1.arr[ind+right]=tmp;
						dcs = 0;
					}
				}
				-- right;
				for(; left >= right && num1.arr[left] == 0; -- left, -- num1.len);
			}
			else {
				-- right;
				for(; left >= right && num1.arr[left] == 0; -- left, --num1.len);
			}
		}
		return ans;
	} else if(num1_orig == num2)
		return HighPrecisionInt(1);
	else
		return HighPrecisionInt(0);
}

bool operator < (const HighPrecisionInt & num1, const HighPrecisionInt & num2) {
	if(num1.len < num2.len)
		return true;
	else if(num1.len > num2.len)
		return false;
	else {
		for (int i = num1.len-1; i >= 0; -- i) {
			if (num1.arr[i] < num2.arr[i])
				return true;
			else if(num1.arr[i] > num2.arr[i])
				return false;
		}
	}
	return false;
}

bool operator > (const HighPrecisionInt & num1, const HighPrecisionInt & num2) {
	if(num1.len > num2.len)
		return true;
	else if(num1.len < num2.len)
		return false;
	else {
		for (int i = num1.len-1; i >= 0; -- i) {
			if (num1.arr[i] > num2.arr[i])
				return true;
			else if(num1.arr[i] < num2.arr[i])
				return false;
		}
	}
	return false;
}

bool operator == (const HighPrecisionInt & num1, const HighPrecisionInt & num2) {
	if(num1.len == num2.len) {
		for(int i = num1.len -1 ; i >= 0; -- i)
			if (num1.arr[i] != num2.arr[i])
				return false;
		return true;
	}
	return false;
}

bool operator != (const HighPrecisionInt & num1, const HighPrecisionInt & num2) {
	return !(num1 == num2);
}

ostream & operator << (ostream & out, const HighPrecisionInt & obj) {
	for (int i = obj.len-1; i>= 0; -- i)
		out << obj.arr[i];
	return out;
}

/*
int main() {
	string test1("104"), test2("5");
	HighPrecisionInt demo1(test1);
	HighPrecisionInt demo2(test2);
	
	HighPrecisionInt demo3(demo1/demo2);
	
	HighPrecisionInt demo4;
	
	cout << demo1 << endl << demo2 << endl << demo3 << endl << demo4 << endl;
	return 0;
}
*/

int main() {
	int a, b, c, N;
	HighPrecisionInt A, B, C, tmp;
	
	scanf("%d %d %d %d", &a, &b, &c, &N);
	A = 1;
	B = C = 0;
	
	//use hash table to eliminate later
	for (int i = 0; i < N; ++ i) {
		tmp = 0;
		tmp = A*a+B*b+C*c;
		C = C + B;
		B = A;
		A = tmp;
	}
	
	cout << A+B+C << endl;
	
	return 0;
}