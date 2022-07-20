#include <iostream>
#include <string>

using namespace std;

class Byte
{
    int n;
public:
    int* b;

    Byte()
    {
        n = 1;
        b = new int[n];
        b[0] = 0;
    }

    Byte(int a, int n)
    {
        this->n = n;
        b = new int[n];
        if (a == 0)
        {
            for(int i = 0; i<n; i++)
                b[i] = 0;
        }
        else
        {
            for (int i = n - 1; i >= 0; i--)
            {
                int aa = a;
                a /= 2;
                b[i] = aa - 2 * a;
            }
        }
    }
};

void Swap(int* a, int* b, int n)
{
    int tmp;
    for (int i = 0; i < n; i++)
    {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

long int Fact(int n)
{
    int f = 1;
    for (int i = 0; i < n; i++)
        f *= i + 1;
    return f;
}

void Sum(string* bracket, int cor, int al)
{
    for (int i = 0; i <= cor; i++)
    {
        int fact = Fact(cor) / (Fact(cor - i) * Fact(i));
        int pw = 2 * (cor - i) - 2 * i;
        if (cor % 2 == 0)
            *bracket += "+";
        else
            *bracket += "-";
        if(fact == 1)
            *bracket += "a(" + to_string(al + pw) + ")";
        else
            *bracket += to_string(fact) + "a(" + to_string(al + pw) + ")";
    }
}

void String(string* bracket)
{
    string str = *bracket, str1;
    long int n = str.length(), a = 0, b = 0;
    bool flag = false, br = false, brSgn = false, boo = false;

    for (int i = 0; i < n; i++)
    {
        if (str[i] == '(')
            br = true;
        if (str[i] == ')')
        {
            br = false;
            if (boo == true)
            {
                str1 += str[i];
                boo = false;
                for (int j = 0; j < a; j++)
                {
                    if (flag == true)
                        str += '-' + str1;
                    else
                        str += '+' + str1;
                }
                if (flag == true)
                    str1 = '-' + to_string(a) + str1;
                else
                    str1 = '+' + to_string(a) + str1;
                b = str.find(str1, 0);
                str.erase(b, str1.length());
                i -= str1.length();
                str1.clear();
                a = 0;
            }
            flag = false;
        }
        if (br == false && str[i] == '-')
            flag = true;
        if (br == false && (str[i] >= '0' && str[i] <= '9'))
        {
            if (brSgn == false)
                brSgn = true;
            else
                a *= 10;
            a += str[i] - '0';

        }
        if (brSgn == true && str[i] == 'a')
        {
            boo = true;
            brSgn = false;
        }
        if (boo == true)
            str1 += str[i];
    }

    br = flag = boo = false;
    n = str.length();
    for (int i = 0, j; i < n; i++)
    {
        if (str[i] == '(')
            br = true;
        if (br == false && str[i] == '-')
            flag = true;
        if (str[i] == '+')
            boo = true;
        if (str[i] != ')')
            str1 += str[i];
        else
        {
            br = false;
            if (flag == true)
            {
                str1.erase(0, 1);
                str1 = '+' + str1 + ')';
                a = str.find(str1, i);
                if (a > -1)
                {
                    str.erase(a, str1.length());
                    str.erase(i - str1.length() + 1, str1.length());
                    i -= str1.length();
                }
            }
            else
            {
                if (boo == true)
                    str1.erase(0, 1);
                str1 = '-' + str1 + ')';
                a = str.find(str1, i + 1);
                if (a > -1)
                {
                    str.erase(a, str1.length());
                    if (boo == true)
                    {
                        str.erase(i - (str1.length() - 1), str1.length());
                        i -= str1.length();
                        boo = false;
                    }
                    else
                    {
                        str.erase(i - (str1.length() - 2), str1.length() - 1);
                        i -= str1.length() - 1;
                    }

                }
            }
            str1.clear();
            flag = false;
            n = str.length();
        }
    }

    flag = false;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == ')')
        {
            flag = false;
            boo = false;
        }
        if (str[i] == '-')
            boo = true;
        if (i == 0 && str[i] != '-')
            flag = true;
        if (i > 0 && str[i] == '0' && str[i - 1] == '(')
        {
            if (flag == true)
            {
                i -= 2;
                str.erase(i, 4);
                str = str + "+1";
            }
            else
            {
                i -= 3;
                str.erase(i, 5);
                if (boo == true)
                    str = str + "-1";
                else
                    str = str + "+1";
            }
            n = str.length();
        }
    }

    flag = boo  = br = false;
    a = 0;
    string s;
    for (int i = 0; i < n; i++)
    {
        str1 += str[i];
        if (str1 == s)
            break;
        if (i == 0 && str[i] != '-' && str[i] != '+')
            boo = true;
        if (str1 == "-")
            flag = true;
        if (str[i] == ')')
        {
            int k = 1;
            if (boo == true)
                str1 = '+' + str1;
            do
            {
                b = str.find(str1, i + 1);
                if (b != -1)
                {
                    k++;
                    str.erase(b, str1.length());
                }
            } while (b != -1);
            if (boo == true)
            {
                str.erase(i - (str1.length() - 2), str1.length() - 1);
                i -= str1.length() - 1;
            }
            else
            {
                str.erase(i - (str1.length() - 1), str1.length());
                i -= str1.length();
            }
            if (flag == true)
                str += '-';
            else
                str += '+';

            str1.erase(0, 1);
            if (k > 1)
                str += to_string(k);
            str += str1;

            if (a == 0)
            {
                if (flag == true)
                    s += '-';
                else
                    s += '+';
                if (k > 1)
                    s += to_string(k);
                s += str1;
            }

            str1.clear();
            boo = false;
            flag = false;
            n = str.length();
            a++;
        }
        
        if (i > 0 && str[i] == '1' && str[i-1] == '+')
        {
            str1 += '+';
            int k = 1;
            do
            {
                b = str.find(str1, i + 1);
                if (b != -1)
                {
                    k++;
                    str.erase(b, str1.length() - 1);
                }
            } while (b != -1);
            str.erase(i - 1, 2);
            str += '+' + to_string(k);
            break;
        }
    }
    if (str[0] == '+')
        str.erase(0, 1);

    *bracket = str;
}

int Alpha(int* sgn, int n, Byte b)
{
    
    int al = 0;
    for (int i = 0; i < n; i++)
    {
        if (sgn[i] * b.b[i] == -1) al++;
        
    }
    for (int i = 0; i < n; i++)
    {
        if (b.b[i] == 1)
            continue;
        if (sgn[i] == 1) al++;
    }
    

    return al;
}

int Beta(int n, int al)
{
    return n - al;
}

int Rank(int** a, int n)
{
    int rank = 0;

    for (int i = 0; i < n; i++)
    {

        bool flag = true;
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                if (a[k][j] == 1)
                    flag = false;
        if (flag == true)
            return rank;
        flag = true;
        for (int j = 0; j < n; j++)
            if (a[i][j] > 0)
                flag = false;
        if (flag == true)
            continue;

        if (i == n - 1)
        {
            rank++;
            break;
        }

        if (a[i][i] == 0 && i != n - 1)
        {
            int m = i;
            for (int j = i + 1; j < n; j++)
                if (a[j][i] != 0 && a[j][i] != a[m][i])
                    m = j;
            Swap(a[i], a[m], n);
        }

        for (int k = i + 1; k < n; k++)
        {
            bool flag = false;
            for (int j = 0; j < n; j++)
                if (a[i][j] != a[k][j])
                    flag = true;
            if (flag == false)
            {
                for (int j = 0; j < n; j++)
                    a[k][j] = 0;
                continue;
            }

            int del;
            if (a[i][i] != 0 && a[k][i] != 0)
                del = a[k][i] / a[i][i];
            else
                del = 0;
            for (int j = 0; j < n; j++)
                a[k][j] -= del * a[i][j];
            
        }

        rank++;
    }

    return rank;
}

int Corank(int** a, int n, Byte b)
{
    int m = 0;
    for (int i = 0; i < n; i++)
        if (b.b[i] == 1)
            m++;
    if (m == 0) return 0;

    int** aa = new int* [m];
    for (int i = 0; i < m; i++)
        aa[i] = new int[m];

    for (int i = 0, k = -1; i < n; i++)
        if (b.b[i] == 1)
        {
            k++;
            for (int j = 0, g = -1; j < n; j++)
                if (b.b[j] == 1)
                {
                    g++;
                    aa[k][g] = a[i][j];
                }
        }
    return m - Rank(aa, m);
}

int TwistNumber(int** a, int* sgn, int n)
{
    int** e = new int* [n];
    int** c = new int* [n];
    int** aa = new int* [n];
    int cor = 0;
    Byte b(pow(2, n) - 1, n);
    for (int i = 0; i < n; i++)
    {
        e[i] = new int[n];
        c[i] = new int[n];
        aa[i] = new int[n];
        for (int j = 0; j < n; j++)
            c[i][j] = e[i][j] = 0;
        e[i][i] = 1;
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        c[i][i] = 1;
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
                aa[k][j] = (a[k][j] + e[k][j] + c[k][j]) % 2;
        }
        sum += pow(-1, Corank(aa, n, b)) * sgn[i];
        c[i][i] = 0;
    }
    return sum;
}

void JonesPolynomial(string bracket, int sum)
{
    string polynomial = "";
    int n = bracket.length(), a = 0;
    bool flag = false, sgn = false, br = false;

    if (sum == 0)
        polynomial = bracket;
    else
    {
        if (bracket[0] == 'a')
        {
            polynomial += '-';
            polynomial += bracket[0];
        }

        for (int i = 1; i < n; i++)
        {
            if (flag == false && bracket[i] == '-')
            {
                polynomial += '+';
                continue;
            }
            if (bracket[i] == '+')
            {
                polynomial += '-';
                continue;
            }
            if (flag == false)
                polynomial += bracket[i];
            if (bracket[i] == '(')
                flag = true;
            if (flag == true && bracket[i] == '-')
                sgn = true;
            if (flag == true && (bracket[i] >= '0' && bracket[i] <= '9'))
            {
                if (br == true)
                    a *= 10;
                else
                    br = true;
                a += bracket[i] - '0';
            }
            if (bracket[i] == ')')
            {
                if (sgn == true)
                    a *= -1;
                polynomial += to_string(a - 3 * sum) + ')';
                a = 0;
                flag = sgn = br = false;
            }
        }
    }
    cout << "Jones Polynomial: " << polynomial;
}

void KauffmanBracket(int** a, int* sgn, int n)
{
    string bracket;

    for (int i = 0; i < pow(2, n); i++)
    {
        int alpha, beta, cor;
        Byte b(i, n);
        alpha = Alpha(sgn, n, b);
        beta = Beta(n, alpha);
        cor = Corank(a, n, b);
        int al = alpha - beta;


        switch (cor)
        {
        case 0:
            if (i == 0)
                bracket += "a(" + to_string(al) + ")";
            else
                bracket += "+a(" + to_string(al) + ")";
            break;
        case 1:
            bracket += "-a(" + to_string(2 + al) + ")-a(" + to_string(-2 + al) + ")";
            break;
        default:
            Sum(&bracket, cor, al);
            break;
        }
    }

    String(&bracket);

    cout << endl << "Kauffman bracket: " << bracket << endl;
    JonesPolynomial(bracket, TwistNumber(a, sgn, n));

}

int main()
{
    int n = 3;
    cout << "Enter the number of crossing: ";
    cin >> n;
    cout << "Enter the matrix:" << endl;
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    }
    cout << "Enter signs: ";
    int* sgn = new int[n];
    for (int i = 0; i < n; i++)
        cin >> sgn[i];

    KauffmanBracket(a, sgn, n);
}
