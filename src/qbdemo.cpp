#include <qbdemo.h>
#include <algorithm>

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

RecordException::RecordException() noexcept {}

RecordException::RecordException(const char* error) noexcept
{
    setError(error);
}

const char * RecordException::what() const noexcept
{
    return m_sWaht.c_str();
}

void RecordException::setError(const char* error)
{
    if (error)
        m_sWaht = error;
}

RecordException::~RecordException() noexcept {}

Record::Record(){}

Record::Record(unsigned _id, const std::string& _column1, long _column2, const std::string& _column3)
{
    if (_column1.empty() || _column3.empty())
        throw RecordException("Invalid attribute");
    m_id = _id;
    m_column1 = _column1;
    m_column2 = _column2;
    m_column3 = _column3;
}

unsigned Record::getID() const { return m_id; }

const std::string& Record::getColumn1() const { return m_column1; }

long Record::getColumn2() const { return m_column2; }

const std::string& Record::getColumn3() const { return m_column3; }

void Table::addRecord(unsigned _id, const std::string& _column1, long _column2, const std::string& _column3)
{
    auto it = m_records.find(_id);
    if (it != m_records.end())
        throw RecordException("Duplicate record id");
    m_records.insert({_id, {_id, _column1, _column2, _column3}});
    addColumnIdMap(m_colunm1IDs, _column1, _id);
    addColumnIdMap(m_colunm2IDs, _column2, _id);
    addColumnIdMap(m_colunm3IDs, _column3, _id);
}

Table::RecordCollection Table::FindMatchingRecords(const std::string& columnName, const std::string& matchString)
{
    Table::RecordCollection result;

    if (columnName == "id" && is_number(matchString))
    {
        auto it = m_records.find(std::stoul(matchString));
        if (it != m_records.end())
            result.push_back(it->second);
    }
    else if (columnName == "column1")
       addToCollection(result, matchString, m_colunm1IDs);
    else if (columnName == "column2"  && is_number(matchString))
       addToCollection(result, std::stol(matchString), m_colunm2IDs);
    else if (columnName == "column3")
       addToCollection(result, matchString, m_colunm3IDs);

    return result;
}

void Table::deleteRecordByID(unsigned id)
{
    deleteColumnIdMap(m_colunm1IDs, m_records[id].getColumn1(), id);
    deleteColumnIdMap(m_colunm2IDs, m_records[id].getColumn2(), id);
    deleteColumnIdMap(m_colunm3IDs, m_records[id].getColumn3(), id);
    m_records.erase(id);
}
