#include "BigInt.h"

std::vector<int> BigInt::GetData() const {
    return Data;
}

void BigInt::SetSign(const bool i) {
    PosSign = i;
}

std::ostream &operator<<(std::ostream &os, const BigInt &B) {
    if (!B.PosSign) os << '-';
    for (int i: B.Data) os << i;
    return os;
}

BigInt::BigInt(std::fstream &file) {
    char ch = 0;
    while (file.get(ch) && ch != '\n' && ch != '\t' && ch != ' ') {
        if (ch == '-') {
            PosSign ? PosSign = false : PosSign = true;
            continue;
        } else if (std::isalpha(ch)) continue;
        Data.push_back((int) ch - '0');
    }
}

void BigInt::SetData(const std::vector<int> &i) {
    Data = i;
}

bool BigInt::GetSign() const {
    return PosSign;
}



