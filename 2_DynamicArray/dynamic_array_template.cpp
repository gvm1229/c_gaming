#include <iostream>

// ======================
// 일반 템플릿 DynamicArray<T>
// ======================
template <typename T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;

public:
    DynamicArray() {
        arr = nullptr;
        size = 0;
        capacity = 0;
    }

    ~DynamicArray() {
        delete[] arr;
    }

    // 맨 뒤에 데이터 추가
    // capacity 가 부족하면 2배로 늘리는 기능 포함
    void Add(T value) {
        if (size == capacity) {
            // 최초 실행 시 capacity 가 0이므로 1로 설정, 그 이후로는 2배씩 증가
            int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            // 새로운 배열
            T* new_arr = new T[new_capacity];
            // 기존 데이터 복사 (size 가 0일 때는 아무것도 들어있지 않은 것, 고로 복사할 필요 없음)
            for (int i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            // 기존 배열 메모리 해제 및 포인터 갱신
            delete[] arr;
            arr = new_arr;
            // capacity 갱신
            capacity = new_capacity;
        }
        // 새로운 데이터 추가 후 size 증가
        arr[size] = value;
        size++;
    }

    // 배열에서 1이라는 데이터를 찾고 삭제, 1이 없으면 아무일도 일어나지 않음
    void Remove(T value) {
        // Find 함수를 이용해 value 의 index 를 찾음
        int index = Find(value);
        if (index == -1) {
            return; // value가 배열에 없기 때문에 아무일도 하지 않음
        }
        // value 가 배열에 있으면 해당 index 부터 뒤의 모든 데이터를 왼쪽으로 시프트
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        // 삭제가 이루어졌으므로 size 감소
        size--;
    }

    // 2라는 데이터를 찾고, 2 오른쪽에 5를 삽입, 2가 없으면 아무일도 일어나지 않음
    void Insert(T target, T value) {
        // Find 함수를 이용해 target 의 index 를 찾음
        int index = Find(target);
        if (index == -1) {
            return; // target 값이 배열에 없음, 그럼 아무일도 하지 않음
        }
        // 만약 size 가 capacity 와 같다면, Add 함수를 이용해 capacity 를 늘림
        if (size == capacity) {
            // 임의의 값을 추가하여 capacity 를 늘림
            // 어떤 타입으로 사용되고 있을지 모르므로
            // 임의값은 초기화된 T 객체인 T{} 로 설정
            Add(T{});

            // Add 함수로 인해 size 가 +1 됨
            // 이대로면 새로운 값이 0 이후에 들어가게 됨
            // 그러므로 size 를 -1 하여 원래대로 복구 (다음에 Add 가 호출될 때 0 의 위치에 추가되도록)
            size--;
        }
        // index 부터 뒤의 모든 데이터를 오른쪽으로 시프트
        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        // target 오른쪽에 임의의 값 0이 들어간 자리가 생긴 상태.
        // 그곳에 value 삽입
        arr[index + 1] = value;
        size++; // 데이터가 추가되었으므로 size 증가
    }

    // 2라는 데이터를 찾고 있다면 해당 데이터의 인덱스를 리턴, 없으면 -1
    int Find(T value) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                return i;
            }
        }
        return -1;
    }

    // [추가] array 에 존재할만한 함수를 자율적으로 추가해봄
    // index 위치의 데이터를 리턴, index가 범위를 벗어나면 -1 리턴
    T Get(int index) const {
        if (index < 0 || index >= size) {
            std::cout << "유효한 index 범위가 아님" << std::endl;
            // 어떤 타입이든 리턴해야 하므로 초기화된 T 객체인 T{} 로 기본값 리턴
            return T{};
        }
        return arr[index];
    }

    int Size() const { return size; }
    int Capacity() const { return capacity; }
};

// bool 특수화
template <>
class DynamicArray<bool> {
private:
    bool* arr;
    int size;
    int capacity;

public:
    DynamicArray() {
        arr = nullptr;
        size = 0;
        capacity = 0;
    }
    
    ~DynamicArray() {
        delete[] arr;
    }
};

// 테스트
int main() {
    // 템플릿 int 테스트
    DynamicArray<int> arr;

    // Add 테스트
    arr.Add(10);
    arr.Add(20);
    arr.Add(30);

    std::cout << "=== After Add ===" << std::endl;
    for (int i = 0; i < arr.Size(); i++) {
        std::cout << "arr[" << i << "] = " << arr.Get(i) << std::endl;
    }
    std::cout << "Size: " << arr.Size() << ", Capacity: " << arr.Capacity() << std::endl;

    // Find 테스트
    int index = arr.Find(20);
    std::cout << "Find 20: " << index << std::endl;
    std::cout << "Find 99 (없는 값): " << arr.Find(99) << std::endl;

    // Insert 테스트 (20 뒤에 25 삽입)
    arr.Insert(20, 25);
    std::cout << "=== After Insert 25 after 20 ===" << std::endl;
    for (int i = 0; i < arr.Size(); i++) {
        std::cout << "arr[" << i << "] = " << arr.Get(i) << std::endl;
    }

    // Remove 테스트 (값 10 삭제)
    arr.Remove(10);
    std::cout << "=== After Remove 10 ===" << std::endl;
    for (int i = 0; i < arr.Size(); i++) {
        std::cout << "arr[" << i << "] = " << arr.Get(i) << std::endl;
    }

    // Get 테스트 (범위 벗어난 값)
    std::cout << "Get(100): " << arr.Get(100) << std::endl;

    // 템플릿 bool 테스트

    return 0;
}
