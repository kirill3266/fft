#ifndef ANN_BIGINT_H
#define ANN_BIGINT_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>

class BigInt {
    std::vector<int> Data;
    bool PosSign = true;
public:
    BigInt() = default;

    explicit BigInt(std::fstream &file);

    void SetData(const std::vector<int> &i);

    std::vector<int> GetData() const;

    void SetSign(const bool i);

    bool GetSign() const;

    friend std::ostream &operator<<(std::ostream &os, const BigInt &B);

};

#endif //ANN_BIGINT_H
