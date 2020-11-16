#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <ctime>
#include <limits>
#include <stdlib.h>
using namespace std;

list<string> numList;

void Initialize();
string RanddomNum();
int CountN(const string &guess, const string &str);
int CountP(const string &guess, const string &str);
string GetNextGuess();

int main()
{
 Initialize();   // 初始化
 string guess = "1234";//RanddomNum(); // 第1回合随机猜数
 int n, p;    // 分别表示有几个数字猜对，有几个数字位置也对
 while (1)
 {
  cout << "emmmmm...   " << guess << endl;
  cin >> n >> p;
  if (n == 4 && p == 4)
  {
   cout << guess << "    goodgame!" << endl;
   break;
  } // 猜中
  for (list<string>::iterator it = numList.begin();
   it != numList.end();)
  {
   if (CountN(guess, *it) != n) // 如果没有n个数字对
   {
    it = numList.erase(it);  // 不可能是被猜数，筛掉
    continue;
   }
   if (CountP(guess, *it) != p) // 如果没有p个数字位置对
   {
    it = numList.erase(it);  // 不可能是被猜数，筛掉
    continue;
   }
   ++it;
  }
  if (numList.empty()) // 没有候选数了，人欺骗计算机
  {
   cout << "wrong" << endl;
   break;
  }
  guess = GetNextGuess();
 }
 return 0;
}

void Initialize()
{
 char buf[5] = {0};
 for (int i = '1'; i <= '9'; i++)
  for (int j = '0'; j <= '9'; j++)
   for (int k = '0'; k <= '9'; k++)
    for (int l = '0'; l <= '9'; l++)
    {
     buf[0] = i;
     buf[1] = j;
     buf[2] = k;
     buf[3] = l;
     numList.push_back(buf);
    }
}
string RanddomNum()
{
 srand(time(NULL));
 int i = rand() % 9000 + 1000;
 char buf[5] = {0};
 sprintf(buf, "%d", i);
 return buf;
}

int CountN(const string &guess, const string &num)
{
 string s = num;  // 复制num，用于下面避免重复匹配的操作
 int count = 0;
 for (int i = 0; i < 4; i++) // 对guess中每一个数字
 {
  string::size_type pos = s.find(guess[i]);
  if (pos != string::npos)
  {
   count++;
   s[pos] = 'x';  // 为避免重复匹配，将它替换为字符’x’
  }
 }
 return count;
}


int CountP(const string &guess, const string &str)
{
 int count = 0;
 for (int i = 0; i < 4; i++)
  count += (guess[i] == str[i]);
 return count;
}

string GetNextGuess()
{
 int min = numeric_limits<int>::max();
 string guess;   // 猜这个数
 for (list<string>::iterator it = numList.begin();
  it != numList.end(); ++it)
 {
  int a[5][5] = {0};
  for (list<string>::iterator it2 = numList.begin();
   it2 != numList.end(); ++it2)
  {
   int x = CountN(*it, *it2);
   if (x == 0)
    a[0][0]++;    // 如果n=0，p一定=0
   else
    a[x][CountP(*it, *it2)]++;
  }
  int sum = 0;
  for (int i = 0; i < 5; i++)
   for (int j = 0; j <=i; j++) // 位置对的数字个数不会超过猜对的数字个数
    sum += a[i][j] * a[i][j];
  if (sum < min)
  {
   sum = min;
   guess = *it;
  }
 }
 return guess;
}
