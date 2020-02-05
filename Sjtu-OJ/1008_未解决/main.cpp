#include <iostream>
#include <cstdio>

using namespace std; 

int calDay(int y, int m, int d) {
	int m1 = (m+9)%12;
	int y1 = y - m1/10;
	int res = y1*365+y1/4-y1/100+y1/400+(m1*306+5)/10+d-1; //just remember...
	return res;
}

int calWeekDay(int y, int m, int d) {
	if(m == 1 || m == 2)  {
		m+=12;
		-- y;
	}
	int res = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
	return res;
}

int calWeekends(int y, int m, int d, int days) {
	int s = calWeekDay(y, m, d);
	return (days/7)*2+(s+days%7)/6+(s+days%7)/7-s/6;
}

int calWeekendsout(int y, int m, int d, int days) {
	int s = calWeekDay(y, m, d);
	cout << "s|" << s << endl << "days|" << days << endl;
	return (days/7)*2+(s+days%7)/6+(s+days%7)/7-s/6;
}

int getSep(int * sep, int len, int days) {
	int left = 0, right = len-1;
	int mid;
	while(left < right) {
		mid = (left + right) / 2;
		if(sep[mid] > days)
			right = mid-1;
		else if(sep[mid] < days)
			left = mid+1;
		else
			return mid;
	}
	if(sep[left] > days)
		return left-1;
	return left;
}

int callim(int m) {
	switch(m) {
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			return 28;
		default:
			return 31;
	}
}

inline bool isleap(int y) {
	return (!(y%4)&&(y%100))||!(y%400);
}

int test_calWeekends() {
	int total = 0, whole = 0;
	for (int y = 1900; y < 9999; ++ y)  {
		for (int m = 1; m < 13; ++ m) {
			int lim = callim(m);
			if (isleap(y) && m == 2)
				++ lim;
			for (int d = 1; d <= lim; ++ d) {
				++ whole;
				if(calWeekDay(y, m, d) > 4)
					++ total;
				if(calWeekends(1900,1,1,whole) != total) {
					cout << "BREAK! AT " << y << '-' << m << '-' << d << endl;
					cout << "ORIG|" << total << endl;
					cout << "CALC|" << calWeekendsout(1900,1,1,whole) << endl;
					return 1;
				}

			}
		}
	}
	return 0;
}

int test_getSep(int * sep, int len) {
	int total = calDay(1900, 1, 1)-1, ind = 0;
	for (int y = 1900; y < 9999; ++ y)  {
		for (int m = 1; m < 13; ++ m) {
			int lim = callim(m);
			if (isleap(y) && m == 2)
				++ lim;
			for (int d = 1; d <= lim; ++ d) {
				++ total;
				if(total == sep[ind+1])
					++ind;
				if (y == 1900 && m == 1 && d == 1)
					continue;
				if(getSep(sep, len, total) != ind) {
					cout << "BREAK! AT "<< y << '-' << m << '-' << d << endl;
					cout << "ORIG|" << ind << endl;
					cout << "CALC|" << getSep(sep, len, total) << endl;
					return 1;
				}
			}
		}
	}
	return 0;
}

int main() {
	int n;
	int y1, m1, d1, y2, m2, d2, days1, days2, tmp;
	int res;
	int sep[200000]; //weekdays && holidays
	int len = 0;
	
	freopen("in.txt", "r", stdin);
	
	for (int i = 1850; i < 20000; ++ i) {
		if(calWeekDay(i,1,1)<5) {
			sep[len] = calDay(i,1,1);
			++ len;
		}
		for(int j = 1; j < 4; ++ j) {
			if(calWeekDay(i,5,j)<5) {
				sep[len] = calDay(i,5,j);
				++ len;
			}
		}
		for(int j = 1; j < 8; ++ j) {
			if (calWeekDay(i,10,j)<5) {
				sep[len] = calDay(i,10,j);
				++ len;
			}
		}
	}
	
	//cout << len << endl;
	
	scanf("%d", &n);
	for (int lm = 0; lm < n; ++ lm) {
		scanf("%d-%d-%d", &y1, &m1, &d1);
		scanf("%d-%d-%d", &y2, &m2, &d2);
		
		days1 = calDay(y1, m1, d1)-1;
		days2 = calDay(y2, m2, d2);
		tmp = days2 - days1;
		res = tmp - 
			(getSep(sep, len, days2) - getSep(sep, len, days1))
			- calWeekends(y1, m1, d1, tmp);
		//cout << "tmp -- " << tmp << " sep2 -- " << getSep(sep, len, days2)
		//	 << " sep1 -- " <<  getSep(sep, len, days1) << " wek -- " <<  
		//	 calWeekends(y1,m1,d1,tmp) << endl;
		printf("%d\n", res);
	}
	
	//test_calWeekends();
	//test_getSep(sep, len);
	
	fclose(stdin);
	
	return 0;
}