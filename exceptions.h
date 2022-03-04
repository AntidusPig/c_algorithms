#ifndef _CUSTOM_EXCEPTIONS_H_
#define _CUSTOM_EXCEPTIONS_H_

class OutOfRange {
    public:
        OutOfRange() : m_flag(1) { };
        OutOfRange(int len, int index) : m_len(len), m_index(index), m_flag(2) { }
    public:
        void what() const;  //��ȡ����Ĵ�����Ϣ
    private:
        int m_flag;  //��ͬ��flag��ʾ��ͬ�Ĵ���
        int m_len;  //��ǰ����ĳ���
        int m_index;  //��ǰʹ�õ������±�
};

#endif