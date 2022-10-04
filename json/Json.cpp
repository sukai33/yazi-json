#include <sstream>
using std::stringstream;

#include <stdexcept>

#include "Json.h"
#include "Parser.h"
using namespace yazi::json;

Json::Json() : m_type(json_null)
{
}

Json::Json(Type type) : m_type(type)
{
    switch (m_type)
    {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            m_value.m_string = new string("");
            break;
        case json_array:
            m_value.m_array = new std::list<Json>();
            break;
        case json_object:
            m_value.m_object = new std::map<string, Json>();
        default:
            break;
    }
}

Json::Json(bool value) : m_type(json_bool)
{
    m_value.m_bool = value;
}

Json::Json(int value) : m_type(json_int)
{
    m_value.m_int = value;
}

Json::Json(double value) : m_type(json_double)
{
    m_value.m_double = value;
}

Json::Json(const char * value) : m_type(json_string)
{
    m_value.m_string = new string(value);
}

Json::Json(const string & value) : m_type(json_string)
{
    m_value.m_string = new string(value);
}

Json::Json(const Json & other) : m_type(json_null)
{
    copy(other);
}

Json::~Json()
{
}

Json::Type Json::type() const
{
    return m_type;
}

bool Json::isNull() const
{
    return m_type == json_null;
}

bool Json::isBool() const
{
    return m_type == json_bool;
}

bool Json::isInt() const
{
    return m_type == json_int;
}

bool Json::isDouble() const
{
    return m_type == json_double;
}

bool Json::isString() const
{
    return m_type == json_string;
}

bool Json::isArray() const
{
    return m_type == json_array;
}

bool Json::isObject() const
{
    return m_type == json_object;
}

bool Json::asBool() const
{
    if (m_type == json_bool)
    {
        return m_value.m_bool;
    }
    throw std::logic_error("function Json::asBool value type error");
}

int Json::asInt() const
{
    if (m_type == json_int)
    {
        return m_value.m_int;
    }
    throw std::logic_error("function Json::asInt value type error");
}

double Json::asDouble() const
{
    if (m_type == json_double)
    {
        return m_value.m_double;
    }
    throw std::logic_error("function Json::asDouble value type error");
}

string Json::asString() const
{
    if (m_type == json_string)
    {
        return *(m_value.m_string);
    }
    throw std::logic_error("function Json::asString value type error");
}

void Json::copy(const Json & other)
{
    m_type = other.m_type;
    m_value = other.m_value;
}

int Json::size() const
{
    switch (m_type)
    {
        case json_array:
            return (m_value.m_array)->size();
        case json_object:
            return (m_value.m_object)->size();
        default:
            break;
    }
    throw std::logic_error("function Json::size value type error");
}

bool Json::empty() const
{
    switch (m_type)
    {
        case json_null:
            return true;
        case json_array:
            return (m_value.m_array)->empty();
        case json_object:
            return (m_value.m_object)->empty();
        default:
            break;
    }
    return false;
}

void Json::clear()
{
    switch (m_type)
    {
        case json_null:
        case json_bool:
        case json_int:
        case json_double:
            break;
        case json_string:
            {
                delete m_value.m_string;
            }
            break;
        case json_array:
            {
                for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
                {
                    it->clear();
                }
                delete m_value.m_array;
            }
            break;
        case json_object:
            {
                for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
                {
                    it->second.clear();
                }
                delete m_value.m_object;
            }
            break;
        default:
            break;
    }
    m_type = json_null;
}

bool Json::has(int index)
{
    if (m_type != json_array)
    {
        return false;
    }
    int size = (m_value.m_array)->size();
    return (index >= 0) && (index < size);
}

bool Json::has(const char * key)
{
    string name(key);
    return has(name);
}

bool Json::has(const string & key)
{
    if (m_type != json_object)
    {
        return false;
    }
    return (m_value.m_object)->find(key) != (m_value.m_object)->end();
}

void Json::remove(int index)
{
    if (m_type != json_array)
    {
        return;
    }
    int size = (m_value.m_array)->size();
    if (index < 0 || index >= size)
    {
        return;
    }
    auto it = (m_value.m_array)->begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    it->clear();
    (m_value.m_array)->erase(it);
}

void Json::remove(const char * key)
{
    string name = key;
    remove(name);
}

void Json::remove(const string & key)
{
    if (m_type != json_object)
    {
        return;
    }
    auto it = (m_value.m_object)->find(key);
    if (it != (m_value.m_object)->end())
    {
        it->second.clear();
        (m_value.m_object)->erase(key);
    }
}

void Json::append(const Json & value)
{
    if (m_type != json_array)
    {
        clear();
        m_type = json_array;
        m_value.m_array = new std::list<Json>();
    }
    (m_value.m_array)->push_back(value);
}

Json & Json::operator = (const Json & other)
{
    clear();
    copy(other);
    return *this;
}

bool Json::operator == (const Json & other)
{
    if (m_type != other.type())
    {
        return false;
    }
    switch (m_type)
    {
        case json_null:
            return true;
        case json_bool:
            return (m_value.m_bool == other.m_value.m_bool);
        case json_int:
            return (m_value.m_int == other.m_value.m_int);
        case json_double:
            return (m_value.m_double == other.m_value.m_double);
        case json_string:
            return *(m_value.m_string) == *(other.m_value.m_string);
        case json_array:
            return m_value.m_array == other.m_value.m_array;
        case json_object:
            return m_value.m_object == other.m_value.m_object;
        default:
            break;
    }
    return false;
}

bool Json::operator != (const Json & other)
{
    return !(*this == other);
}

Json & Json::operator [] (int index)
{
    if (index < 0)
    {
        throw std::logic_error("function Json::operator [int] index less than 0");
    }
    if (m_type != json_array)
    {
        clear();
        m_type = json_array;
        m_value.m_array = new std::list<Json>();
    }
    int size = (m_value.m_array)->size();
    if (index >= 0 && index < size)
    {
        auto it = (m_value.m_array)->begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        return *it;
    }
    if (index >= size)
    {
        for (int i = size; i <= index; i++)
        {
            (m_value.m_array)->push_back(Json());
        }
    }
    return (m_value.m_array)->back();
}

Json & Json::operator [] (const char * key)
{
    string name = key;
    return (*this)[name];
}

Json & Json::operator [] (const string & key)
{
    if (m_type != json_object)
    {
        clear();
        m_type = json_object;
        m_value.m_object = new std::map<string, Json>();
    }
    return (*(m_value.m_object))[key];
}

Json::operator bool()
{
    if (m_type != json_bool)
    {
        throw std::logic_error("function Json::operator (bool) requires bool value");
    }
    return m_value.m_bool;
}

Json::operator int()
{
    if (m_type != json_int)
    {
        throw std::logic_error("function Json::operator (int) requires int value");
    }
    return m_value.m_int;
}

Json::operator double()
{
    if (m_type != json_double)
    {
        throw std::logic_error("function Json::operator (double) requires double value");
    }
    return m_value.m_double;
}

Json::operator string()
{
    if (m_type != json_string)
    {
        throw std::logic_error("function Json::operator (string) requires string value");
    }
    return *(m_value.m_string);
}

void Json::parse(const string & str)
{
    Parser parser;
    parser.load(str);
    *this = parser.parse();
}

string Json::str() const
{
    stringstream ss;
    switch (m_type)
    {
        case json_null:
            ss << "null";
            break;
        case json_bool:
            if (m_value.m_bool)
            {
                ss << "true";
            }
            else
            {
                ss << "false";
            }
            break;
        case json_int:
            ss << m_value.m_int;
            break;
        case json_double:
            ss << m_value.m_double;
            break;
        case json_string:
            ss << "\"" << *(m_value.m_string) << "\"";
            break;
        case json_array:
            {
                ss << "[";
                for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
                {
                    if (it != (m_value.m_array)->begin())
                    {
                        ss << ",";
                    }
                    ss << (*it).str();
                }
                ss << "]";
            }
            break;
        case json_object:
            {
                ss << "{";
                for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
                {
                    if (it != (m_value.m_object)->begin())
                    {
                        ss << ",";
                    }
                    ss << "\"" << it->first << "\":" << it->second.str();
                }
                ss << "}";
            }
            break;
        default:
            break;
    }
    return ss.str();
}