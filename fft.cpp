#include "fft.h"
#include "BigInt.h"

vcd fft(const vcd &as) {
    int n = as.size();
    int k = 0; // Длина n в битах
    while ((1 << k) < n) k++;
    std::vector<int> rev(n);
    rev[0] = 0;
    int high1 = -1;
    for (int i = 1; i < n; i++) {
        if ((i & (i - 1)) == 0) // Проверка на степень двойки. Если i ей является, то i-1 будет состоять из кучи единиц.
            high1++;
        rev[i] = rev[i ^ (1 << high1)]; // Переворачиваем остаток
        rev[i] |= (1 << (k - high1 - 1)); // Добавляем старший бит
    }

    vcd roots(n);
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        roots[i] = cd(cos(alpha), sin(alpha));
    }

    vcd cur(n);
    for (int i = 0; i < n; i++)
        cur[i] = as[rev[i]];

    for (int len = 1; len < n; len <<= 1) {
        vcd ncur(n);
        int rstep = roots.size() / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            for (int i = 0; i < len; i++) {
                cd val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++, p1++;
            }
            pdest += len;
        }
        cur.swap(ncur);
    }
    return cur;
}

vcd fft_rev(const vcd &as) {
    vcd res = fft(as);
    for (int i = 0; i < (int) res.size(); i++) res[i] /= as.size();
    reverse(res.begin() + 1, res.end());
    return res;
}

void multiply(const BigInt &A, const BigInt &B, BigInt &Res) {
    std::vector<int> a = A.GetData();
    std::vector<int> b = B.GetData();
    vcd aa(a.begin(), a.end()), bb(b.begin(), b.end());
    size_t n = 1;
    while (n < std::max(a.size(), b.size())) n <<= 1;
    n <<= 1;

    aa.resize(n), bb.resize(n);

    vcd a_vals = fft(aa);
    vcd b_vals = fft(bb);

    vcd c_vals(a_vals.size());

    for (int i = 0; i < n; i++)
        c_vals[i] = a_vals[i] * b_vals[i];

    vcd c = fft_rev(c_vals);

    std::vector<int> res(a.size() + b.size() - 1);

    for (int i = 0; i < res.size(); ++i)
        res[i] = (int) lround(c[i].real());

    int carry = 0;
    for (size_t i = res.size() - 1; i > 0; --i) {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }
    res[0] += carry;
    const int tmp = res[0] % 10;
    res[0] /= 10;
    res.emplace(res.begin() + 1, tmp);

    Res.SetData(res);
    Res.SetSign(A.GetSign() && B.GetSign() || !A.GetSign() && !B.GetSign());
}