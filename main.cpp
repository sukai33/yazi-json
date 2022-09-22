#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Json.h"
using namespace yazi::json;

#include <sys/time.h>

int main()
{
    // ifstream fin("./t.json");
    // stringstream ss;
    // ss << fin.rdbuf();
    // const string & data = ss.str();
    // Json v;
    // v.parse(data);
    // std::cout << v.str() << std::endl;
    // return 0;

    // Json v1 = true;
    // Json v2 = 123;
    // Json v3 = 1.23;
    // Json v4 = "hello world";
    // std::cout << v1.str() << std::endl;
    // std::cout << v2.str() << std::endl;
    // std::cout << v3.str() << std::endl;
    // std::cout << v4.str() << std::endl;

    // bool b = v1;
    // int i = v2;
    // double f = v3;
    // const string & s = v4;

    // Json null;
    // std::cout << null.str() << std::endl;
    // return 0;

    // Json arr;
    // arr.append(123);
    // arr.append(1.23);
    // arr.append("hello world");
    // std::cout << arr.str() << std::endl;

    // arr.remove(1);
    // std::cout << arr.str() << std::endl;

    // Json arr;
    // arr[0] = 123;
    // arr[1] = 1.23;
    // arr[2] = "hello world";
    // arr[5] = true;
    // std::cout << arr.str() << std::endl;

    // // object value
    // Json obj;
    // obj["name"] = "jun";
    // obj["age"] = 18;
    // obj["arr"] = arr;
    // std::cout << obj.str() << std::endl;
    // obj.clear();
    // return 0;

    try
    {
        ifstream fin("./test.json");
        stringstream ss;
        ss << fin.rdbuf();
        const string & data = ss.str();

        struct timeval tv;
        gettimeofday(&tv, NULL);
        int start_sec = tv.tv_sec;
        int start_usec = tv.tv_usec;
        const int max = 1;
        for (int i = 0; i < max; i++)
        {
            Json json;
            json.parse(data);
            std::cout << json.str() << std::endl;
            json.clear();
        }
        gettimeofday(&tv, NULL);
        int end_sec = tv.tv_sec;
        int end_usec = tv.tv_usec;
        double time_diff = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
        std::cout << time_diff / 1000 / max << "ms" << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "catch exception: " << e.what() << std::endl;
    }
    return 0;
}
