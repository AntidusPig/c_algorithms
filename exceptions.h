#ifndef _CUSTOM_EXCEPTIONS_H_
#define _CUSTOM_EXCEPTIONS_H_

class OutOfRange {
    public:
        OutOfRange() : m_flag(1) { };
        OutOfRange(int len, int index) : m_len(len), m_index(index), m_flag(2) { }
    public:
        void what() const;  //获取具体的错误信息
    private:
        int m_flag;  //不同的flag表示不同的错误
        int m_len;  //当前数组的长度
        int m_index;  //当前使用的数组下标
};

#endif