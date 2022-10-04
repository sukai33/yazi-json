#pragma once

#include <string>
using std::string;

#include <list>
#include <map>

namespace yazi {
namespace json {

class Json
{
public:
    enum Type
    {
        json_null = 0,  // null value
        json_bool,      // bool value
        json_int,       // integer value
        json_double,    // double value
        json_string,    // string value
        json_array,     // array value
        json_object     // object value
    };

    Json();
    Json(Type type);
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char * value);
    Json(const string & value);
    Json(const Json & other);
    ~Json();

    Type type() const;

    bool isNull() const;
    bool isBool() const;
    bool isInt() const;
    bool isDouble() const;
    bool isString() const;
    bool isArray() const;
    bool isObject() const;

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    string asString() const;

    // number of values in array or object
    int size() const;

    // return true if empty array, empty object, or null, otherwise, false.
    bool empty() const;

    void clear();

    bool has(int index);
    bool has(const char * key);
    bool has(const string & key);

    void remove(int index);
    void remove(const char * key);
    void remove(const string & key);

    // append value to array at the end.
    void append(const Json & value);

    Json & operator = (const Json & other);
    bool operator == (const Json & other);
    bool operator != (const Json & other);

    Json & operator [] (int index);
    Json & operator [] (const char * key);
    Json & operator [] (const string & key);

    operator bool();
    operator int();
    operator double();
    operator string();

    void parse(const string & str);
    string str() const;

    typedef std::list<Json>::iterator iterator;
    iterator begin()
    {
        return (m_value.m_array)->begin();
    }
    iterator end()
    {
        return (m_value.m_array)->end();
    }

private:
    void copy(const Json & other);

private:
    union Value
    {
        bool m_bool;
        int m_int;
        double m_double;
        std::string * m_string;
        std::list<Json> * m_array;
        std::map<string, Json> * m_object;
    };

    Type m_type;
    Value m_value;
};

}}