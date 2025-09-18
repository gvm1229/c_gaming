#include "MyString.h"
#include <cassert>
#include <iostream>
using namespace assignment1;

int main()
{
    // 1. GetLength
    {
        MyString s("Hello");
        assert(s.GetLength() == 5);
    }

    // 2. GetCString
    {
        MyString s("Hello");
        assert(s.GetCString()[0] == 'H');
        assert(s.GetCString()[4] == 'o');
    }

    // 3. Append
    {
        MyString s("Hello");
        s.Append(" World");
        assert(s == MyString("Hello World"));
    }

    // 4. operator+
    {
        MyString s1("Hello");
        MyString s2(" World");
        MyString s3 = s1 + s2;
        assert(s1 == MyString("Hello"));
        assert(s2 == MyString(" World"));
        assert(s3 == MyString("Hello World"));
    }

    // 5. IndexOf
    {
        MyString s("Hello");
        assert(s.IndexOf("ell") == 1);
        assert(s.IndexOf("l") == 2);
        assert(s.IndexOf("This") == -1);
    }

    // 6. LastIndexOf
    {
        MyString s("Hello");
        assert(s.LastIndexOf("ell") == 1);
        assert(s.LastIndexOf("l") == 3);
        assert(s.LastIndexOf("This") == -1);
    }

    // 7. Interleave
    {
        MyString s("Hello");
        s.Interleave(" World");
        assert(s == MyString("H eWlolrold"));
    }

    // 8. RemoveAt
    {
        MyString s("Hello");
        bool b1 = s.RemoveAt(0);
        assert(b1 == true && s == MyString("ello"));

        bool b2 = s.RemoveAt(2);
        assert(b2 == true && s == MyString("elo"));

        bool b3 = s.RemoveAt(4);
        assert(b3 == false && s == MyString("elo"));
    }

    // 9. PadLeft
    {
        MyString s1("Hello");
        s1.PadLeft(2);
        assert(s1 == MyString("Hello")); // length 보다 짧을 때

        s1.PadLeft(8);
        assert(s1 == MyString("   Hello"));

        MyString s2("World");
        s2.PadLeft(3, '-');
        assert(s2 == MyString("World"));

        s2.PadLeft(7, '-');
        assert(s2 == MyString("--World"));
    }

    // 10. PadRight
    {
        MyString s1("Hello");
        s1.PadRight(2);
        assert(s1 == MyString("Hello"));

        s1.PadRight(8);
        assert(s1 == MyString("Hello   "));

        MyString s2("World");
        s2.PadRight(3, '-');
        assert(s2 == MyString("World"));

        s2.PadRight(7, '-');
        assert(s2 == MyString("World--"));
    }

    // 11. Reverse
    {
        MyString s("Hello");
        s.Reverse();
        assert(s == MyString("olleH"));
    }

    // 12. operator==
    {
        MyString s1("Hello");
        MyString s2("Hello");
        MyString s3("World");

        assert(s1 == s2);
        assert(!(s2 == s3));
    }

    // 13. ToLower
    {
        MyString s("HEllo 123K");
        s.ToLower();
        assert(s == MyString("hello 123k"));
    }

    // 14. ToUpper
    {
        MyString s("HEllo 123K");
        s.ToUpper();
        assert(s == MyString("HELLO 123K"));
    }

    std::cout << "모든 테스트 통과" << std::endl;
    return 0;
}
