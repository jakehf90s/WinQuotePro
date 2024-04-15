#ifndef MEMORYDATABASE_H
#define MEMORYDATABASE_H

/**
 This will serve as the database for the app
 It is more straight-forward to show how to override the base class IDatabase
 If needed, a new Database support can be created easily
 * */


#include "idatabase.h"

class MemoryDatabase : public IDatabase
{
public:
    MemoryDatabase();
    virtual int addquote(const std::string& name, const std::string& customer_name, MaterialType m_type, MaterialSize m_size) override;
    virtual bool editquote(int id, const std::string& new_name, const std::string& new_customer_name,
                           MaterialType new_m_type, MaterialSize new_m_size) override;
    virtual bool deletequote(int id) override;
    virtual std::shared_ptr<Quote> getquote(int id) const override;
    virtual std::vector< std::shared_ptr<Quote> > getallquotes() const override;
private:
    std::vector< std::shared_ptr< Quote > > _quotes;
    int _curId;
};

#endif // MEMORYDATABASE_H
