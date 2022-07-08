#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <limits.h>
#include <bits/stdc++.h>
#include <fstream>
#include <ios>

using namespace std;
bool hasAdd, hasSub, hasDiv, hasMul, isFile = false;
string *num1 = new string; // 4-3
string *num2 = new string;

// Carlos Granados/Seth Clapis
string fileToString(string fname)
{
 string num;
 ifstream f(fname);

 if (f.is_open())
 {
  while (getline(f, num))
  {
   cout << num << endl;
  }
  f.close();
 }
 else
 {
  throw "File not found"; // 5-1 10-2
 }
 // 2-1,6-1
 // this checks for any chars in the file that are not numbers
 for (int i = 0; i < num.length(); i++)
 {
  if (!isdigit(num[i]))
   throw "Illegal chars in file. File must contain only nums"; // 5-2 10-3
  // cout << "Error" << endl; // special character in string
 }
 f.close();
 return num;
}

// takes the input string and returns index of math symbol
// Seth Clapis
int parser(string input)
{
 string file = ".txt";
 string operators = "+-*/";
 for (int i = 0; i < input.length(); i++)
 {
  if (input.find(file) != string::npos)
  {
   isFile = true;
  }
  // if(file.find_first_of(input[i]) != string::npos){//is true if any of the chars in file are found not just the whole string
  //     isFile = true;
  // }
  if (operators.find_first_of(input[i]) != string::npos)
  {
   if (input[i] == '+')
   {
    hasAdd = true;
    return i;
   }
   else if (input[i] == '-')
   {
    hasSub = true;
    return i;
   }
   else if (input[i] == '*')
   {
    hasMul = true;
    return i;
   }
   else if (input[i] == '/')
   {
    hasDiv = true;
    return i;
   }
  }
 }
 if (!isFile)
 {
  for (int i = 0; i < input.length(); i++)
  {
   if (isalpha(input[i]))
   {                                // 2-2,6-2,
    throw "Illegal chars in input"; // 10-4
    return 0;
   }
   if (!isdigit(input[i]) && input[i] != ' ')
   { // if not a num check what kind of math symbol
    if (input[i] == '+')
    {
     hasAdd = true;
     return i;
    }
    if (input[i] == '-')
    {
     hasSub = true;
     return i;
    }
    if (input[i] == '*')
    {
     hasMul = true;
     return i;
    }
    if (input[i] == '/')
    {
     hasDiv = true;
     return i;
    }
    return 0; // its not a num or a math; its illegal
   }
  }
 }

 return -1; // something went wrong if it gets here
}

// Carlos Granados
bool isSmaller(string str1, string str2)
{
 int n = str1.length(), m = str2.length();

 if (n < m)
  return true;
 if (m < n)
  return false;
 for (int i = 0; i < n; i++)
 {
  if (str1[i] < str2[i])
   return true;
  else if (str1[i] > str2[i])
   return false;
 }
 return false;
}

// Carlos Granados
void largeNumber(string splitInp1, string splitInp2)
{
 // get rid of white space
 splitInp1.erase(remove(splitInp1.begin(), splitInp1.end(), ' '), splitInp1.end());
 splitInp2.erase(remove(splitInp2.begin(), splitInp2.end(), ' '), splitInp2.end());
 for (int i = 0; i < splitInp1.length(); i++)
 {
  if (isalpha(splitInp1[i]))
  {                                      // 2-3 6-3
   throw "Illegal chars in first input"; // 10-5
  }
 }

 for (int i = 0; i < splitInp2.length(); i++)
 {
  if (isalpha(splitInp2[i]))
  {                                       // 2-4 6-4
   throw "Illegal chars in second input"; // 10-6
  }
 }

 try
 {
  string *num1 = new string; // 4-1
  string *num2 = new string;
  string answer;

  *num1 = splitInp1;
  *num2 = splitInp2;
  answer = "";

  if (hasDiv)
  {
   // base cases for div
   if (*num1 == "0")
   {
    answer = "0";
   }
   else if (*num2 == "0")
   {
    // 5-3
    throw "Division by zero"; // 10-7
    answer = "Cannot divide by 0";
   }
   else
   {

    // this else is how we store each digit into the storage string and
    // is how we avoid integer overflows
    long long mod = 0;
    long long m = stoll(splitInp2); // 3-1
    int n = splitInp1.length();

    for (int i = 0; i < n; i++)
    {
     int digit = splitInp1[i] - '0';
     mod = mod * 10 + digit;
     int quo = mod / m;
     answer.push_back(quo + '0'); // 1-4
     mod = mod % m;
    }

    answer.erase(0, answer.find_first_not_of('0'));
   }
  }
  else if (hasMul)
  {
   // base case
   if (*num1 == "0" || *num2 == "0")
   {
    answer = "0";
   }
   else
   {
    int carry = 0, n = splitInp1.length() - 1, m = splitInp2.length() - 1;
    for (int i = 0; i <= n + m || carry; ++i)
    { // 3-2
     for (int j = max(0, i - m); j <= min(i, m); ++j)
     {
      carry += (splitInp1[n - j] - '0') * (splitInp2[m - i + j] - '0');
     }
     answer += carry % 10 + '0';
     carry = carry / 10;
    }
    reverse(begin(answer), end(answer));
   }
  }
  else if (hasAdd)
  {
   // base case
   if (*num1 == "0" || *num2 == "0")
   {
    if (*num1 == "0")
    {
     answer = *num2;
    }
    else
    {
     answer = *num1;
    }
   }
   else
   {
    if (splitInp1.length() > splitInp2.length())
     swap(splitInp1, splitInp2);
    int n = splitInp1.length();
    int m = splitInp2.length();

    reverse(splitInp1.begin(), splitInp1.end());
    reverse(splitInp2.begin(), splitInp2.end());

    int carry = 0;

    for (int i = 0; i < n; i++)
    {
     int sum = ((splitInp1[i] - '0') + (splitInp2[i] - '0') + carry);
     answer.push_back(sum % 10 + '0'); // 1-1

     carry = sum / 10;
    }

    for (int i = n; i < m; i++)
    {
     int sum = ((splitInp2[i] - '0') + carry);
     answer.push_back(sum % 10 + '0'); // 1-2
     carry = sum / 10;
    }
    if (carry)
    {
     answer.push_back(carry + '0'); // 3-3
    }

    reverse(answer.begin(), answer.end());
   }
  }
  else if (hasSub)
  {
   // base case
   if (*num1 == "0" || *num2 == "0")
   {
    if (*num1 == "0")
    {
     answer = *num2;
    }
    else
    {
     answer = *num1;
    }
   }
   else
   {
    if (isSmaller(splitInp1, splitInp2))
     swap(splitInp1, splitInp2);

    int n = splitInp1.length();
    int m = splitInp2.length();

    reverse(splitInp1.begin(), splitInp1.end());
    reverse(splitInp2.begin(), splitInp2.end());

    int carry = 0;

    for (int i = 0; i < m; i++)
    {
     int sub = ((splitInp1[i] - '0') - (splitInp2[i] - '0') - carry);

     if (sub < 0)
     {
      sub = sub + 10;
      carry = 1;
     }
     else
     {
      carry = 0;
     }
     answer.push_back(sub + '0'); // 1-3
    }
    reverse(answer.begin(), answer.end());
   }
  }
  cout << "Answer is: " << answer << endl;

  // delete num1 and num2 from memory. no longer needed
  delete num1; // 4-2
  delete num2;
 }
 catch (std::bad_alloc &err)
 {                                 // 1-5
  throw "Out of memory exception"; // 10-8
 }
 catch (std::runtime_error &err)
 {
  throw err.what(); // 7-1//10-9
 }
}

int main()
{
 string input;
 int indexOfMath = 0;

 // getting math from the terminal
 cout << "enter ur math" << endl; // 10-1
 // was not supposed to make it to final version
 getline(cin, input);
 input += "\0";

 try
 {

  indexOfMath = parser(input);
  if (indexOfMath == 0 || indexOfMath == -1)
  {
   // 2-5
   throw "illegal chars in input";
   return -1;
  }

  // divide input into 2 strings of the 2 nums
  string splitInp1;
  string splitInp2;
  splitInp1 = input.substr(0, indexOfMath);
  splitInp2 = input.substr(indexOfMath + 1);
  splitInp1.erase(remove(splitInp1.begin(), splitInp1.end(), ' '), splitInp1.end());
  splitInp2.erase(remove(splitInp2.begin(), splitInp2.end(), ' '), splitInp2.end());

  if (isFile)
  {
   *num1 = fileToString(splitInp1);
   *num2 = fileToString(splitInp2);
   largeNumber(*num1, *num2);
   delete num1; // 4-4
   delete num2;
  }
  else
  {
   largeNumber(splitInp1, splitInp2);
  }
 }
 catch (const char *msg)
 {
  cerr << "Exception: " << msg << endl;
 }
}