# yazi-json

a tiny c++ json parser

## example

main.json
```json
{
    "name": "jack",
    "age": 30,
    "area": ["c++", "php", "python", "go"]
}
```

main.cpp
```c++
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Json.h"
using namespace yazi::json;

int main()
{
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
```