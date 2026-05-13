#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

enum class TOKEN {TAG_NAME, ATTR_NAME, ATTR_VALUE};

std::vector<std::string> ft_split(const std::string& src, const std::string & sep)
{
    std::vector<std::string> result;
    std::string current;

    current = "";
    for (std::size_t i = 0; i < src.length(); ++i)
    {
        if (sep.find(src[i]) != std::string::npos)
        {
            if (!current.empty())
                result.push_back(current);
            current.clear();
        }
        else
            current.append(1u, src[i]);
    }
    if (!current.empty())
        result.push_back(current);
    return (result);
}


std::string trimPrefix(const std::string& str, const std::string& prefix) {
    string s = str;
    if (s.compare(0, prefix.length(), prefix) == 0) {
        s.erase(0, prefix.length());
    }
    return (s);
}

string trimSuffix(const std::string& str, const std::string& suffix) {
    string  s = str;
    
    if (s.length() >= suffix.length() && 
        s.compare(s.length() - suffix.length(), suffix.length(), suffix) == 0) {
        s.erase(s.length() - suffix.length());
    }
    return (s);
}

string  trim(const string & str, const string & set)
{
    string  res;

    res = trimPrefix(str, set);
    res = trimSuffix(res, set);
    return (res);
}



class Tag
{
    private:
        std::string _original;
        std::string _type;
        std::map<string, string>    _attribute;
        bool                        _is_ending_tag;
        
        void    init_attribute(const vector<pair<TOKEN, string>> & parsed);
    
        
    public:
        Tag(void);
        Tag(const string & to_parse);
        Tag(const Tag & src);
        Tag & operator=(const Tag & rhs);
        ~Tag() {};
        
        const string & getOriginalString(void) const {
            return (this->_original);
        }
        const string & getType(void) const{
            return (this->_type);
        };
        const map<string, string>   & getAttribute(void) const{
            return (this->_attribute);
        };
        bool    getIsEndingTag(void) const{
            return (this->_is_ending_tag);
        }
        
};

bool    operator==(const Tag & tag_a, const Tag & tag_b)
{
    if (tag_a.getType() == tag_b.getType())
        return (true);
    return (false);
}

Tag::Tag() : _original(), _type(), _attribute(), _is_ending_tag(false)
{
}

std::vector<pair<TOKEN, string>>    parseString(vector<string> & strs)
{
    vector<pair<TOKEN, string>>   res;

    for (size_t i = 0; i < strs.size(); i++)
    {
        if ((strs[i] != "=" && strs[i][0] != '"') && (i + 1 == strs.size() || strs[i + 1] != "="))
        {
            res.push_back(make_pair(TOKEN::TAG_NAME, strs[i]));
        }
        else if ((strs[i] != "=" && strs[i][0] != '"') && (i + 1 != strs.size() && strs[i + 1] == "="))
        {
            res.push_back(make_pair(TOKEN::ATTR_NAME, strs[i]));
        }
        else if (strs[i] == "=")
            continue;
        else if ((i > 0 && strs[i - 1] == "=") && strs[i][0] == '"')
        {
            res.push_back(make_pair(TOKEN::ATTR_VALUE, strs[i]));
        }
    }
    return (res);
}

void    Tag::init_attribute(const vector<pair<TOKEN, string>> & parsed)
{
    for (size_t i = 1; i < parsed.size(); i += 2)
    {
        this->_attribute[parsed[i].second] = parsed[i + 1].second;
    }
}

Tag::Tag(const string & to_parse)
{
    string  str;
    vector<string> strs;
    vector<pair<TOKEN, string>> parsed;

    this->_original = to_parse;
    str = trimPrefix(to_parse, "<");
    str = trimSuffix(str, ">");
    this->_is_ending_tag = false;
    if (str[0] == '/')
    {
        this->_is_ending_tag = true;
        this->_type = str.substr(1, str.size() - 1);
        return ;
    }
    strs = ft_split(str, " ");
    parsed = parseString(strs);
    this->_type = parsed[0].second;
    init_attribute(parsed);
}

Tag::Tag(const Tag & src)
{
    *this = src;
}

Tag & Tag::operator=(const Tag & rhs)
{
    if (this != &rhs)
    {
        this->_attribute = rhs._attribute;
        this->_original = rhs._original;
        this->_type = rhs._type;
        this->_is_ending_tag = rhs._is_ending_tag;
    }
    return (*this);
}

std::ostream & operator<<(ostream & os, const map<string, string> & map)
{
    std::map<string, string>::const_iterator it;

    it = map.begin();
    for (; it != map.end(); ++it)
    {
        os << it->first << ": " << it->second << endl;
    }
    return (os);
}

std::ostream & operator<<(ostream & os, const Tag & tag)
{
    os << "Tag Name: " << tag.getType() << endl;
    os << "Is_endingTag; " << tag.getIsEndingTag() << endl;
    os << "Original Str: " << tag.getOriginalString() << endl;
    os << "Attribute: " << endl;
    os << tag.getAttribute() ;
    return (os);
}


class Node
{
    private:
        Node    *_parent;
        vector<Node *>  _son;
        Tag            *_tag;
        
    public:
        Node(Tag * tag, Node * parent);
        Node(const Node & src);
        Node &operator=(const Node & rhs);
        ~Node();
};

Node::Node(Tag * tag, Node * parent): _parent(), _tag(tag), _son()
{
}

Node &Node::operator=(const Node & rhs)
{
    if (this != &rhs)
    {
        this->_parent = rhs._parent;
        this->_son = rhs._son;
        this->_tag = rhs._tag;
    }
    return (*this);
}

class Tree
{
    private:
        Node *root;
    public:
        Tree() {};
        Tree(vector<Tag> tags);
        Tree(const )
};

void    takeQuerie(Tree & tree, int n_quieries)
{
    
}


int main() {
    int i;
    int n_tag;
    std::string buffer;
    vector<string>  strs;
    vector<Tag>     tags;
    Tree            tree;

    i = 0;
    std::getline(std::cin, buffer);
    strs = ft_split(buffer, " ");
    n_tag = atoi(strs[0].c_str());
    while (std::getline(std::cin, buffer) && i < n_tag)
    {
        if (i < n_tag)
        {
            tags.push_back(Tag(buffer));
        }
        i += 1;
    }
    tree = Tree(tags);
    return 0;
}
