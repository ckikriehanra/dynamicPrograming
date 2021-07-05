#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
string add_op(string str1, string str2)
{
    // Before proceeding further, make sure length
    // of str2 is larger.
    if (str1.length() > str2.length())
        swap(str1, str2);

    // Take an empty string for storing result
    string str = "";

    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();

    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');

        // Calculate carry for next step
        carry = sum/10;
    }

    // Add remaining digits of larger number
    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }

    // Add remaining carry
    if (carry)
        str.push_back(carry+'0');

    // reverse resultant string
    reverse(str.begin(), str.end());

    return str;
}
string multi_op(string str1, string str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    vector<int> num1(len1);
    vector<int> num2(len2);
    for(int i = 0; i < len1; i++)
        num1[i] = str1[i] - '0';
    for(int i = 0; i < len2; i++)
        num2[i] = str2[i] - '0';
    if (len1 == 0 || len2 == 0)
    return "0";

    // will keep the result number in vector
    // in reverse order
    vector<int> result(len1 + len2, 0);

    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i];

        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;

        // Go from right to left in num2
        for (int j=len2-1; j>=0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j];

            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration
            carry = sum/10;

            // Store result
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }

    // ignore '0's from the right
    int i = result.size() - 1;
    while (i>=0 && !result[i])
    i--;

    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
    return "0";

    // generate the result string
    string s = "";

    while (i >= 0)
        s += (result[i--] + '0');
    return s;
}
string fibonacciModified(int t1, int t2, int n)
{
    string n1 = to_string(t1);
    string n2 = to_string(t2);
    string ans;
    for(int i = 2; i < n; i++)
    {
        ans = add_op(n1, multi_op(n2, n2));
        n1 = n2;
        n2 = ans;
    }
    return ans;
}
int main()
{
    int t1, t2, n;
    cout << "put number1, number2, and nth: " <<endl;
    cin >> t1 >> t2 >> n;
    cout << fibonacciModified(t1, t2, n);

    return 0;
}
