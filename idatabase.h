#ifndef IDATABASE_H
#define IDATABASE_H

/**
 Interface fo the Database
 In the future, it would be easier to migrate to new database,
 By just creating a new derived class based on IDatabase
 **/

#include <string>
#include <vector>
#include <memory>

enum MaterialType
{
    mtWood,
    mtMetal
};

enum MaterialSize
{
    msS,
    msM,
    msL
};

class Quote
{
public:
    Quote(int in_id, const std::string& in_name, const std::string& in_customer_name, MaterialType in_m_type, MaterialSize in_m_size)
    {
        _id = in_id;
        update_infos(in_name, in_customer_name, in_m_type, in_m_size);
    }
    void update_infos(const std::string& in_name, const std::string& in_customer_name, MaterialType in_m_type, MaterialSize in_m_size)
    {
        _name = in_name;
        _customer_name = in_customer_name;
        _m_type = in_m_type;
        _m_size = in_m_size;
    }
    std::string name() const { return _name; }
    std::string customer_name() const { return _customer_name; }
    MaterialType m_type() const { return _m_type; }
    MaterialSize m_size() const { return _m_size; }
    int id() const { return _id; }
private:
    std::string _name;
    std::string _customer_name;
    MaterialType _m_type;
    MaterialSize _m_size;
    int _id;
};


class IDatabase
{
public:
    virtual int addquote(const std::string& name, const std::string& customer_name, MaterialType m_type, MaterialSize m_size) = 0;
    virtual bool editquote(int id, const std::string& new_name, const std::string& new_customer_name, MaterialType new_m_type, MaterialSize new_m_size) = 0;
    virtual bool deletequote(int id) = 0;
    virtual std::shared_ptr<Quote> getquote(int id) const = 0;
    virtual std::vector< std::shared_ptr<Quote> > getallquotes() const = 0;
};


#endif // IDATABASE_H
