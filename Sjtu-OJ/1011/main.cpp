#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

class MyComplex
{
private:
  double x,y;
public:
	MyComplex(double a, double b): x(a), y(b) {}
	MyComplex(){}
	
	MyComplex operator+ (const MyComplex & obj) const {
		return MyComplex (x+obj.x, y+obj.y);
	}
	
	MyComplex operator- (const MyComplex & obj) const {
		return MyComplex (x-obj.x, y-obj.y);
	}
	
	MyComplex operator * (const MyComplex & obj) const {
		return MyComplex (x*obj.x-y*obj.y, x*obj.y+y*obj.x);
	}
	
	MyComplex operator / (const MyComplex & obj) const {
		return MyComplex ((x*obj.x+y*obj.y)/(obj.x*obj.x+obj.y*obj.y), 
						  (y*obj.x-x*obj.y)/(obj.x*obj.x+obj.y*obj.y));
	}
	
	MyComplex & operator += (const MyComplex & obj) {
		x = x+obj.x;
		y = y+obj.y;
		return * this;
	}
	
	MyComplex & operator *= (const MyComplex & obj) {
		double tmp_x = x*obj.x-y*obj.y;
		y = x*obj.y+y*obj.x;
		x = tmp_x;
		return * this;
	}
	
	MyComplex & operator -= (const MyComplex & obj) {
		x = x-obj.x;
		y = y-obj.y;
		return * this;
	}
	
	MyComplex & operator /= (const MyComplex & obj) {
		double tmp_x = (x*obj.x+y*obj.y)/(obj.x*obj.x+obj.y*obj.y);		
		y = (y*obj.x-x*obj.y)/(obj.x*obj.x+obj.y*obj.y);
		x = tmp_x;
		return * this;
	}

friend ostream & operator << (ostream & os, const MyComplex & t) {
	os  << setprecision(2) << fixed << t.x << " " << t.y;
	return os;
}

friend istream & operator >> (istream & in, MyComplex & t) {
	in >> t.x >> t.y;
	return in;
}
};

int main()
{
  MyComplex z1;
  MyComplex z2;
  
  freopen ("in.txt", "r", stdin);

  cin >> z1 >> z2;

  cout << z1 + z2 <<endl;
  cout << z1 - z2 <<endl;
  cout << z1 * z2 <<endl;
  cout << z1 / z2 <<endl;
  cout << (z1 += z2) <<endl;
  cout << (z1 -= z2) <<endl;
  cout << (z1 *= z2) <<endl;
  cout << (z1 /= z2) <<endl;

  fclose(stdin);
  
  return 0;
}