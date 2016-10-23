//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Surigoma                                               //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <sstream>

namespace arch
{
namespace html
{
class element
{
private:
    std::string tag;
    std::vector<element> children;
    std::map<std::string, std::string> attribute;
    std::string value;
    element *parent, *owner;

    bool is_children(std::string tag)
    {
        for(element &item : children)
        {
            if(item.get_tag() == tag){return true;}
        }
        return false;
    }
    std::vector<std::vector<element>::iterator> find_children_all(std::string tag)
    {
        std::vector<std::vector<element>::iterator> result;
        auto itr = children.begin();
        while(itr != children.end())
        {
            if(itr->get_tag() == tag)
            {
                result.push_back(itr);
            }
            itr++;
        }
        return result;
    }
    element& find_children(std::string tag, unsigned int index = 0)
    {
        auto result = find_children_all(tag);
        if(result.size() > 0)
        {
            return *result[index];
        }
        else
        {
            return *children.end();
        }
    }

    // INFO: これいる?
    element& find_children_first(std::string tag)
    {
        return find_children(tag);
    }
    static std::string indent(std::string source, unsigned int i = 1)
    {
        std::stringstream ss(source);
        std::string result = "", ind = "";
        for(unsigned int count = 0; count < i; count++)
        {
            ind += "\t";
        }
        for(std::string line; std::getline(ss, line);)
        {
            result += ind + line + "\n";
        }
        return result.substr(0, result.size() - 1);
    }
public:
	static element null() { return element(""); };
    element(){}
    element(std::string tag)
    {
        this->tag = tag;
    }
    element(std::string tag, element *parent, element *owner)
    {
        this->tag = tag;
        this->parent = parent;
        if(this->parent == nullptr)
        {
            this->owner = this;
        }
        else
        {
            this->owner = owner;
        }
    }
    ~element()
    {
        children.clear();
        attribute.clear();
    }
    element operator[](std::string tag)
    {
        return *this << tag;
    }
    element operator[](unsigned int index)
    {
        if(children.size() > index)
        {
            return children[index];
        }
        return null();
    }
    element& operator<<(std::string tag)
    {
        if(is_children(tag))
        {
            return find_children_first(tag);
        }
        element result(tag, this, owner);
        children.push_back(result);
        return children.back();
    }
    element& operator<<(element &item)
    {
        if(item.get_owner() == owner && item.get_parent() != parent)
        {
            children.push_back(element(item));
        }
        else
        {
            children.push_back(item);
        }
        children.back().set_owner(owner);
        children.back().set_parent(this);
        return children.back();
    }
    element& operator=(std::string value)
    {
        this->value = value;
        return *this;
    }
    std::string get_tag(){return tag;}
    element* get_owner(){return owner;}
    void set_owner(element *owner){ this->owner = owner; }
    element* get_parent(){return parent;}
    void set_parent(element *parent){ this->parent = parent; }
    std::vector<element> childrens()
    {
        return children;
    }
    void set_attribute(std::string key, std::string value)
    {
        attribute[key] = value;
    }
    std::string get_attribute(std::string key)
    {
        return attribute[key];
    }
    std::map<std::string,std::string> attributes()
    {
        return attribute;
    }
    bool delete_attribute(std::string key)
    {
        if(attribute.end() == attribute.find(key))
        {
            return false;
        }
        attribute.erase(key);
        return true;
    }
    std::string get_text()
    {
        return value;
    }
    std::string to_string()
    {
        std::string result = "<" + tag;
        for(auto pair : attribute)
        {
            result += " " + pair.first + "=" + pair.second;
        }
        result += ">\r\n";
        for(element &item : children)
        {
            result += indent(item.to_string()) + "\r\n";
        }
        if(value != "")
        {
            result += indent(value) + "\r\n";
        }
        result += "</" + tag + ">";
        return result;
    }
};
    //constexpr element html(){ return "html"; }
}
}
