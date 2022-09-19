#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Json.h"
using namespace yazi::json;

int main()
{
    // Json v1;
    // v1["name"] = "jack";
    // Json v2 = v1;

    // if (v1 == v2)
    // {
    //     std::cout << "yes" << std::endl;
    // }

    // v2.clear();
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
        ifstream fin("./main.json");
        stringstream ss;
        ss << fin.rdbuf();
        const string & data = ss.str();

        Json json;
        json.parse(data);
        std::cout << json.str() << std::endl;

        const string & name = json["name"];
        int type = json["age"];
        const string & area = json["area"][0];
        json.clear();
    }
    catch (std::exception & e)
    {
        std::cout << "catch exception: " << e.what() << std::endl;
    }
    return 0;
}
