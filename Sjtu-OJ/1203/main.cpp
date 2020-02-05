#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX 30000

using namespace std;

template <class elemType>
class MyList;

template <class elemType>
MyList<elemType> operator +  (const MyList<elemType> & obj1, const MyList<elemType> & obj2);

template <class elemType>
class MyList {
private:
    elemType * data;
    int currentlength;

public:
    MyList (int len = MAX);
    virtual ~MyList() {delete [] data;}

    int length () const {return currentlength;}
    void push_back (const elemType & x);
    void traverse();

friend MyList<elemType> operator + <> (const MyList<elemType> & obj1, const MyList<elemType> & obj2);
};

template <class elemType>
MyList <elemType>::MyList(int len) {
    data = new elemType [len];
    currentlength = 0;
}

template <class elemType>
void MyList<elemType>::push_back(const elemType & x) {
    data[currentlength] = x;
    ++ currentlength;
}

template <class elemType>
void MyList<elemType>::traverse() {
    for (int i = 0; i < currentlength; ++ i)
        cout << data [i] << " ";
}

template <class elemType>
MyList<elemType> operator +  (const MyList<elemType> & obj1, const MyList<elemType> & obj2) {
    MyList<elemType> ans;
    int len1 = obj1.length(), len2 = obj2.length();
    for (int i = 0; i < len1; ++ i)
        ans.data[i] = obj1.data[i];
    for (int i = 0; i < len2; ++ i)
        ans.data[len1 + i] = obj2.data[i];
    ans.currentlength = len1 + len2;
    return ans;
}

int main()
{
    char type[7], ctmp;
    int ind = 0, n, m;

    freopen("in.txt", "r", stdin);

    while (1) {
        scanf("%c", &ctmp);
        if (ctmp != '\n'){
            type[ind] = ctmp;
            ++ ind;
        } else
            break;
    }

    type [ind] = '\0';

    scanf("%d %d", &n, &m);

    if (strcmp (type, "int") == 0) {
        //printf("int!\n");
        int tmp;
        MyList<int> l1, l2;
        for (int i = 0; i < n; ++ i) {
            scanf("%d", &tmp);
            l1.push_back(tmp);
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d", &tmp);
            l2.push_back(tmp);
        }
        (l1+l2).traverse();
    } else if (strcmp (type, "double") == 0) {
        //printf("double!\n");
        double tmp;
        MyList<double> l1, l2;
        for (int i = 0; i < n; ++ i) {
            cin >> tmp;
            l1.push_back(tmp);
        }
        for (int i = 0; i < m; ++ i) {
            cin >> tmp;
            l2.push_back(tmp);
        }
        (l1+l2).traverse();
    } else if (strcmp (type, "char") == 0) {
        //printf("char!\n");
        char tmp;
        MyList<char> l1, l2;
        cin.get();
        for (int i = 0; i < n; ++ i) {
            scanf("%c", &tmp);
            l1.push_back(tmp);
            cin.get();
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%c", &tmp);
            l2.push_back(tmp);
            cin.get();
        }
        (l1+l2).traverse();
    } else {
        printf ("[error] unknown type\n");
    }

    fclose(stdin);

    return 0;
}
