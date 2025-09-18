#pragma once

namespace assignment1
{
    class MyString
    {
    private:
        // 멤버 변수
        // 문자열 데이터를 저장할 포인터
        char* data;
        // 문자열의 길이를 저장할 변수
        unsigned int length;
    
        // 유틸리티 메소드
        // 문자열 길이 계산 (length 미사용, 인자 s 의 길이 측정용)
        // strlen 의 대체
        unsigned int StrLength(const char* s) const;
        // 깊은 문자열 복사
        // strcopy 의 대체
        void StrCopy(char* result, const char* src) const;
    
    // 기본 제공 시그니처 변경 없음
    public:
        MyString(const char* s);
        MyString(const MyString& other);
        ~MyString();
        unsigned int GetLength() const;
        const char* GetCString() const;
        void Append(const char* s);
        MyString operator+(const MyString& other) const;
        int IndexOf(const char* s);
        int LastIndexOf(const char* s);
        void Interleave(const char* s);
        bool RemoveAt(unsigned int i);
        void PadLeft(unsigned int totalLength);
        void PadLeft(unsigned int totalLength, const char c);
        void PadRight(unsigned int totalLength);
        void PadRight(unsigned int totalLength, const char c);
        void Reverse();
        bool operator==(const MyString& rhs) const;
        void ToLower();
        void ToUpper();
    };
}
