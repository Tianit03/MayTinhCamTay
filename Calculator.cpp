#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

int layThuTuUuTien(char o)
{
    if (o == '+' || o == '-')
        return 1;
    else if (o == '*' || o == '/')
        return 2;
    else if (o == '^')
        return 3;
    else
        return 0;
}

double tinhToan(double a, double b, char operation)
{
    switch (operation)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
                throw runtime_error("Divide by zero");
            return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

void thucHienPhepTinh(stack<double>& sos, stack<char>& toanTu)
{
    double n2 = sos.top();
    sos.pop();
    double n1 = sos.top();
    sos.pop();
    char op = toanTu.top();
    toanTu.pop();

    sos.push(tinhToan(n1, n2, op));
}

double tinhGiaTriBieuThuc(const string& bieu_thuc)
{
    stack<double> sos;
    stack<char> toanTu;

    for (int i = 0; i < bieu_thuc.size(); i++)
    {
        char c = bieu_thuc[i];

        if (c == ' ')
            continue;
        else if (isdigit(c) || c == '.')
        {
            string chuoi_sos;
            while (i < bieu_thuc.size() && (isdigit(bieu_thuc[i]) || bieu_thuc[i] == '.'))
            {
                chuoi_sos += bieu_thuc[i];
                i++;
            }
            i--;

            double so = stod(chuoi_sos);
            sos.push(so);
        }
        else if (c == '(')
        {
            toanTu.push(c);
        }
        else if (c == ')')
        {
            while (!toanTu.empty() && toanTu.top() != '(')
            {
                thucHienPhepTinh(sos, toanTu);
            }
            if (!toanTu.empty() && toanTu.top() == '(')
            {
                toanTu.pop();
            }
        }
        else
        {
            while (!toanTu.empty() && layThuTuUuTien(toanTu.top()) >= layThuTuUuTien(c))
            {
                thucHienPhepTinh(sos, toanTu);
            }
            toanTu.push(c);
        }
    }

    while (!toanTu.empty())
    {
        thucHienPhepTinh(sos, toanTu);
    }

    return sos.top();
}

int main()
{
    string bieu_thuc;
    getline(cin, bieu_thuc);

    try
    {
        double ketQua = tinhGiaTriBieuThuc(bieu_thuc);
        cout << ketQua << endl;
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
