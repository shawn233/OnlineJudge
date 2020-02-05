// 1008.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int workday[150000] = { 0 };
int totalday[401] = { 0 };
int total = 0;


bool isleap(int x)
{
	if ((x % 4 == 0 && x % 100 != 0) || (x % 400 == 0))
		return 1;
	else
		return 0;
}

int dateadd(int date[])
{
	date[3] = (date[3] + 1) % 7;
	date[2] = date[2] + 1;
	if ((date[1] == 4 || date[1] == 6 || date[1] == 9 || date[1] == 11) && date[2] > 30)
	{
		date[1] ++;
		date[2] = 1;
	}
	else if (date[1] == 2 && ((isleap(date[0]) && date[2] > 29) || (!isleap(date[0]) && date[2] > 28)))
	{
		date[1] ++;
		date[2] = 1;
	}
	else if (date[2] > 31)
	{
		date[1] ++;
		date[2] = 1;
	}
	if (date[1] > 12)
	{
		date[0] ++;
		date[1] = 1;
		return 1;
	}
	return 0;
}

int num_in_a_year(int y, int m, int d)
{
	int ans = 31 * (m - 1) + d;
	if (m > 2)
	{
		ans -= ((4 * m + 23) / 10);
		ans += isleap(y);
	}
	return ans;
}

int get_date(string s)
{
	int res = 0;
	int st = s.find('-');
	int i;
	for (i = st + 1; s[i] != '-'; i++);
	for (int j = i + 1; j < s.length(); j++)
		res = res * 10 + s[j] - '0';
	return res;
}

int get_month(string s)
{
	int res = 0;
	int st = s.find('-');
	
	for (int i = st + 1; s[i] != '-'; i++)
		res = res * 10 + s[i] - '0';
	return res;
}

int get_year(string s)
{
	int res = 0;
	for (int i = 0; i < 4; i++)
		res = res * 10 + s[i] - '0';
	return res;
}

int doit(string sst, string sed)
{
	int sty = get_year(sst);
	int edy = get_year(sed);
	int stm = get_month(sst);
	int edm = get_month(sed);
	int std = get_date(sst);
	int edd = get_date(sed);
	int stcir = sty / 400;
	int edcir = edy / 400;
	int res = (edcir - stcir) * workday[total];
	int stnum = totalday[sty % 400] + num_in_a_year(sty, stm, std) - 1;
	int ednum = totalday[edy % 400] + num_in_a_year(edy, edm, edd) - 1;
	if (stnum >= 1)
		res = res + workday[ednum] - workday[stnum - 1];
	else res = res + workday[ednum];
	return res;
}


int main()
{
	int n;
	cin >> n;
	
	int date[4] = { 0, 1, 1, 6 };
	while (date[0] < 400)
	{
		total++;
		int change = dateadd(date);
		
		if (1 <= date[3] && date[3] <= 5 && !(date[1] == 1 && date[2] == 1) && !(date[1] == 5 &&
			date[2] >= 1 && date[2] <= 3) && !(date[1] == 10 && date[2] >= 1 && date[2] <= 7))
			workday[total] = workday[total - 1] + 1;
		else workday[total] = workday[total - 1];
		
		if (change)
			totalday[date[0]] = totalday[date[0] - 1] + 365 + isleap(date[0] - 1);
		//if (date[0] == 10)
		//	cout << date[1] << ' ' << date[2] << ' ' << date[3] << ' ' << workday[total] << endl;
	}

	total -= 1;
	for (int i = 0; i < n; i++)
	{
		string s1, s2;
		cin >> s1 >> s2;
		cout << doit(s1, s2) << endl;
	}
	
	
	return 0;
}

