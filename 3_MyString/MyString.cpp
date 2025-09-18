#include "MyString.h"

namespace assignment1
{
    // 과제에서 제공한 메소드

    // 기본 생성자 & 인자 생성자
    MyString::MyString(const char* s)
    {
        // s 가 비었을 때
        // nullptr 인 경우도 이쪽으로 처리
        if (!s) {
            // 길이 0 설정
            length = 0;
            // 빈 문자열 할당
            data = new char[1];
            data[0] = '\0';
        }
        // s 가 비어있지 않을 때
        else {
            // 길이 계산
            // 객체 생성 중이기 때문에 length 는 아직 미정, 그러므로 s.GetLength() 는 사용 불가
            // strlen 의 대체 메소드를 구현하여 사용
            length = StrLength(s);
            // 메모리 할당
            data = new char[length + 1];
            // 문자열 복사 (새로운 객체를 생성하는 거니까 깊은 복사)
            // strcopy 의 대체 메소드를 구현하여 사용
            StrCopy(data, s);
        }
    }

    // 복사 생성자
    MyString::MyString(const MyString& other)
    {
        // other 는 char 타입이 아닌, MyString 타입이므로
        // MyString 클래스 안인 이곳에선 other.length 를 바로 사용 가능
        length = other.length;
        // 메모리 할당
        data = new char[length + 1];
        // 문자열 복사 (새로운 객체를 생성하는 거니까 깊은 복사)
        StrCopy(data, other.data);
    }

    // 소멸자
    MyString::~MyString()
    {
        // 동적 할당 해제
        delete[] data;
    }

    // 문자열 길이 반환
    unsigned int MyString::GetLength() const
    {
        return length;
    }
    
    // C 스타일 문자열 반환
    const char* MyString::GetCString() const
    {
        return data;
    }

    // 현재 문자열 뒤에 s 를 덧붙임
    void MyString::Append(const char* s)
    {
        // s 가 비었을 때
        if (!s) return;

        // s 가 비어있지 않을 때
        // s 의 길이를 "추가해야 할 길이", 즉 addLength 로 계산
        unsigned int addLength = StrLength(s);
        // 현재 길이 + 추가해야 할 길이로 새로운 메모리 할당
        char *newData = new char[length + addLength + 1];

        // 기존 문자열 복사
        for (unsigned int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        // 기존 문자열 뒤 (length + i) 에 s 복사
        for (unsigned int i = 0; i < addLength; i++) {
            newData[length + i] = s[i];
        }

        // 문자열 맨 뒤에 null 문자 추가
        newData[length + addLength] = '\0';

        // 기존 메모리 해제
        delete[] data;
        // data 가 새 메모리를 가리키도록 변경
        data = newData;
        // 길이 갱신
        length += addLength;
    }

    // + 연산자 오버로딩
    MyString MyString::operator+(const MyString& other) const
    {
        // 기존 문자열과 other 문자열의 길이를 더한 길이로 새로운 MyString 객체 생성
        unsigned int newLength = length + other.length;
        // 기존 문자열과 other 문자열의 길이로 새로운 메모리 할당
        char* newData = new char[newLength + 1];

        // 기존 문자열 복사
        for (unsigned int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        // 기존 문자열 뒤 (length + i) 에 other 문자열 복사
        for (unsigned int i = 0; i < other.length; i++) {
            newData[length + i] = other.data[i];
        }

        // 문자열 맨 뒤에 null 문자 추가
        newData[newLength] = '\0';

        // result 라는 이름의 새로운 MyString 객체 생성
        MyString result(newData);
        // 중간자로 사용한 newData 동적 할당 해제
        delete[] newData;
        // 객체 반환
        return result;
    }

    // 찾고자 하는 문자열이 처음으로 나타나는 위치 반환
    // 못 찾으면 -1 반환
    int MyString::IndexOf(const char* s)
    {
        // 찾고자 하는 문자열의 길이
        unsigned int targetLength = StrLength(s);
        // 찾고자 하는 문자열이 비어있을 때
        if (targetLength == 0) return -1;

        // 찾고자 하는 문자열이 비어있지 않을 때
        for (unsigned int i = 0; i + targetLength <= length; i++) {
            // data[i] 부터 targetLength 만큼 비교
            // 찾고자 하는 문자열 s 는 i 에서 우측으로 진행하며 비교
            unsigned int j = 0;
            while (j < targetLength && data[i + j] == s[j]) j++;
            // 특정 i 에서 j 가 targetLength 까지 도달했다면, 즉 다 일치했다면
            // 찾고자 하는 문자열이 처음으로 나타나는 위치, 즉 i 반환
            if (j == targetLength) return i;
        }

        // 찾고자 하는 문자열이 미발견이라면 -1 반환
        return -1;
    }

    // 찾고자 하는 문자열이 마지막으로 나타나는 위치 반환
    // 못 찾으면 -1 반환
    int MyString::LastIndexOf(const char* s)
    {
        // 찾고자 하는 문자열의 길이
        unsigned int targetLength = StrLength(s);
        // 찾고자 하는 문자열이 비어있을 때
        if (targetLength == 0) return -1;

        // 찾고자 하는 문자열이 비어있지 않을 때
        // 마지막 위치부터 역순으로 탐색
        for (int i = length - targetLength; i >= 0; i--) {
            // data[i] 부터 targetLength 만큼 비교
            // 찾고자 하는 문자열 s 는 i 에서 우측으로 진행하며 비교
            unsigned int j = 0;
            while (j < targetLength && data[i + j] == s[j]) j++;
            // 특정 i 에서 j 가 targetLength 까지 도달했다면, 즉 다 일치했다면
            // 찾고자 하는 문자열이 처음으로 나타나는 위치, 즉 i 반환
            if (j == targetLength) return i;
        }

        // 찾고자 하는 문자열이 미발견이라면 -1 반환
        return -1;
    }

    // 두 문자열을 한 글자씩 번갈아가며 결합
    // 현 객체의 문자열부터 시작
    // 길이가 더 긴 쪽이 남으면 그쪽 문자열을 그대로 덧붙임
    void MyString::Interleave(const char* s)
    {
        // 추가하고자 하는 문자열의 길이
        unsigned int addLength = StrLength(s);
        // 추가하고자 하는 문자열이 비어있을 때는 아무 작업도 하지 않음
        if (addLength == 0) return;

        // 추가하고자 하는 문자열이 비어있지 않을 때
        unsigned int newLength = length + addLength;
        // 현재 길이 + 추가해야 할 길이로 새로운 메모리 할당
        char* newData = new char[newLength + 1];
        
        // 두 문자열을 한 글자씩 번갈아가며 결합
        unsigned int i = 0; // data 인덱스
        unsigned int j = 0; // s 인덱스
        unsigned int k = 0; // newData 인덱스

        // 본 문자열과 추가 문자열 중 더 긴 쪽이 끝날 때까지 반복
        while (i < length || j < addLength) {
            if (i < length) newData[k++] = data[i++];
            if (j < addLength) newData[k++] = s[j++];
        }

        // 문자열 맨 뒤에 null 문자 추가
        newData[newLength] = '\0';

        // 기존 메모리 해제
        delete[] data;
        // data 가 새 메모리를 가리키도록 변경
        data = newData;
        // 길이 갱신
        length = newLength;
    }
    
    // 입력받은 index 위치의 문자를 제거
    // index 가 유효하지 않을 때는 false 반환
    // 성공적으로 제거했을 때는 true 반환
    bool MyString::RemoveAt(unsigned int index)
    {
        // index 가 유효하지 않을 때는 실패의 의미로 false 반환
        if (index >= length) return false;

        // index 가 유효할 때
        for (unsigned int i = index; i < length - 1; i++) {
            data[i] = data[i + 1];
        }
        // 문자열 길이 1 감소
        length--;
        // 줄어든 문자열 맨 뒤에 null 문자 추가
        data[length] = '\0';
        // 성공의 의미로 true 반환
        return true;
    }
    
    // totalLength 를 맞추기 위해 왼쪽에 공백 문자로 채움
    // totalLength 가 현재 문자열 길이보다 작거나 같을 때는 아무 작업도 하지 않음
    void MyString::PadLeft(unsigned int totalLength)
    {
        // 코드 중복을 피하기 위해 공백 문자를 가지고 PadLeft 호출
        PadLeft(totalLength, ' ');
    }
    
    // totalLength 를 맞추기 위해 왼쪽에 c 문자로 채움
    // totalLength 가 현재 문자열 길이보다 작거나 같을 때는 아무 작업도 하지 않음
    void MyString::PadLeft(unsigned int totalLength, const char c)
    {
        // totalLength 가 현재 문자열 길이보다 작거나 같을 때
        if (totalLength <= length) return;

        // totalLength 가 현재 문자열 길이보다 클 때
        // 새로 채워야 할 길이
        unsigned int padLength = totalLength - length;
        // 최종적으로 맞춰야 할 문자열 길이로 새로운 메모리 할당
        char* newData = new char[totalLength + 1];

        // 왼쪽에 padLength 만큼 c 문자로 채움
        for (unsigned int i = 0; i < padLength; i++) {
            newData[i] = c;
        }
        // 그 뒤에 기존 문자열 복사
        for (unsigned int i = 0; i < length; i++) {
            newData[padLength + i] = data[i];
        }

        // 문자열 맨 뒤에 null 문자 추가
        newData[totalLength] = '\0';

        // 기존 메모리 해제
        delete[] data;
        // data 가 새 메모리를 가리키도록 변경
        data = newData;
        // 길이 갱신
        length = totalLength;
    }
    
    // totalLength 를 맞추기 위해 오른쪽에 공백 문자로 채움
    // totalLength 가 현재 문자열 길이보다 작거나 같을 때는 아무 작업도 하지 않음
    void MyString::PadRight(unsigned int totalLength)
    {
        // 코드 중복을 피하기 위해 공백 문자를 가지고 PadRight 호출
        PadRight(totalLength, ' ');
    }
    
    // totalLength 를 맞추기 위해 오른쪽에 c 문자로 채움
    // totalLength 가 현재 문자열 길이보다 작거나 같을 때는 아무 작업도 하지 않음
    void MyString::PadRight(unsigned int totalLength, const char c)
    {
        // totalLength 가 현재 문자열 길이보다 작거나 같을 때
        if (totalLength <= length) return;

        // totalLength 가 현재 문자열 길이보다 클 때
        // 새로 채워야 할 길이
        unsigned int padLength = totalLength - length;
        // 최종적으로 맞춰야 할 문자열 길이로 새로운 메모리 할당
        char* newData = new char[totalLength + 1];

        // 기존 문자열 복사
        for (unsigned int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        // 그 뒤에 padLength 만큼 c 문자로 채움
        for (unsigned int i = 0; i < padLength; i++) {
            newData[length + i] = c;
        }

        // 문자열 맨 뒤에 null 문자 추가
        newData[totalLength] = '\0';

        // 기존 메모리 해제
        delete[] data;
        // data 가 새 메모리를 가리키도록 변경
        data = newData;
        // 길이 갱신
        length = totalLength;
    }
    
    // 문자열을 뒤집음
    // 메모리 재할당 없이 제자리에서 뒤집기
    void MyString::Reverse()
    {
        // 길이가 0 이거나 1 일 때는 뒤집어도 동일한 문자열이므로 아무 작업도 하지 않음
        if (length <= 1) return;

        // 길이가 2 이상일 때
        // 절반만 순회하며 앞뒤 문자 교환
        for (unsigned int i = 0; i < length / 2; i++) {
            char temp = data[i];
            data[i] = data[length - 1 - i];
            data[length - 1 - i] = temp;
        }
    }
    
    // == 연산자 오버로딩
    bool MyString::operator==(const MyString& rhs) const
    {
        // 길이가 다르면 false 반환
        if (length != rhs.length) return false;

        // 길이가 같을 때
        // 각 문자 비교
        // 하나라도 다르면 false 반환
        for (unsigned int i = 0; i < length; i++) {
            if (data[i] != rhs.data[i]) return false;
        }

        // 모든 문자가 동일할 때 true 반환
        return true;
    }
    
    // 소문자로 변환
    void MyString::ToLower()
    {
        for (unsigned int i = 0; i < length; i++) {
            // 대문자 범위에 있을 때만 변환
            if (data[i] >= 'A' && data[i] <= 'Z') {
                // 아스키 코드 표를 이용한 대문자 -> 소문자 변환
                data[i] = data[i] - 'A' + 'a';
            }
        }
    }
    
    // 대문자로 변환
    void MyString::ToUpper()
    {
        for (unsigned int i = 0; i < length; i++) {
            // 소문자 범위에 있을 때만 변환
            if (data[i] >= 'a' && data[i] <= 'z') {
                // 아스키 코드 표를 이용한 소문자 -> 대문자 변환
                data[i] = data[i] - 'a' + 'A';
            }
        }
    }

    // 별도로 추가한 유틸리티 메소드
    
    // 문자열 길이 계산 (length 미사용, 인자 s 의 길이 측정용)
    // strlen 의 대체
    unsigned int MyString::StrLength(const char* s) const
    {
        // s 가 비었을 때는 이 기본값이 변화 없이 0 그대로 반환
        unsigned int len = 0;

        // s 가 비어있지 않을 때,
        // 그리고 첫 문자가 null 이 아닐 때만 while 문 실행
        // s 가 nullptr 인 경우도 이쪽으로 처리
        while (s && s[len] != '\0') len++;

        // 계산된 길이 반환
        return len;
    }

    // 깊은 문자열 복사
    // strcopy 의 대체
    void MyString::StrCopy(char* result, const char* src) const
    {
        // src 가 비었을 때는 아무 작업도 하지 않음
        if (!src) return;

        // src 가 비어있지 않을 때
        unsigned int i = 0;
        
        // src 의 각 문자를 result 에 복사
        // 첫 문자가 null 이 아닐 때만 while 문 실행
        while (src[i] != '\0') {
            result[i] = src[i];
            i++;
        }

        // 문자열 맨 뒤에 null 문자 추가
        result[i] = '\0';
    }
}
