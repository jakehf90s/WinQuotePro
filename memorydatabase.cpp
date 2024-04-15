#include "memorydatabase.h"
#include <QDebug>

MemoryDatabase::MemoryDatabase()
    :_curId(-1)
{

}

int MemoryDatabase::addquote(const std::string &name, const std::string &customer_name, MaterialType m_type, MaterialSize m_size)
{
    _curId += 1;
    auto quote = std::make_shared<Quote>(_curId, name, customer_name, m_type, m_size);
    _quotes.push_back(quote);
    qDebug() << "Added " << _curId << " to " << name << "  " << customer_name << "  " << m_type << "  " << m_size;
    return _curId;
}

bool MemoryDatabase::editquote(int id, const std::string &new_name, const std::string &new_customer_name, MaterialType new_m_type, MaterialSize new_m_size)
{
    qDebug() << "Editing " << id << " to " << new_name << "  " << new_customer_name << "  " << new_m_type << "  " << new_m_size;
    for (const auto& quote: _quotes) {
        if (quote->id() == id) {
            quote->update_infos(new_name, new_customer_name, new_m_type, new_m_size);
            return true;
        }
    }
    return false;
}

bool MemoryDatabase::deletequote(int id)
{
    qDebug() << "Deleting " << id;
    for(size_t i = 0; i < _quotes.size(); ++i) {
        if (_quotes.at(i)->id() == id) {
            _quotes.erase(_quotes.begin() + i);
            return true;
        }
    }
    return false;
}

std::shared_ptr<Quote> MemoryDatabase::getquote(int id) const
{
    for (const auto& quote: _quotes) {
        if (quote->id() == id) {
            return quote;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Quote> > MemoryDatabase::getallquotes() const
{
    return _quotes;
}
