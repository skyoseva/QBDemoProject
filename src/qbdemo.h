#ifndef QBDEMO_H
#define QBDEMO_H

#include <string>
#include <vector>
#include <map>
#include <set>

/**
 * @brief The RecordException class
 */

class RecordException: public std::exception
{
    std::string m_sWaht;
public:
    RecordException() noexcept;
    RecordException(const char* error) noexcept;
    virtual const char * what() const noexcept;
    void setError(const char* error);
    virtual ~RecordException() noexcept;
};

/**
 * @brief The Record class
 * Represents a table row
 */

class Record
{
public:
    unsigned getID() const;
    const std::string& getColumn1() const;
    long getColumn2() const;
    const std::string& getColumn3() const;

    Record(unsigned _id, const std::string& _column1, long _column2, const std::string& _column3);
    Record();

private:
    unsigned m_id; //unique record id
    std::string m_column1;
    long m_column2;
    std::string m_column3;
};

/**
 * @brief The Table class
 * Represents collection of rows
 */
class Table
{
public:
    typedef std::vector<Record> RecordCollection; // represents a record collection to be returned by FindMatchingRecords

    /**
     * @brief addRecord
     * @param _id       - record id
     * @param _column1  - record _column1 value
     * @param _column2  - record _column2 value
     * @param _column3  - record _column3 value
     */
    void addRecord(unsigned _id, const std::string& _column1, long _column2, const std::string& _column3);

    /**
     * @brief FindMatchingRecords
     * @param columnName   - column to be searched
     * @param matchString  - value to be searched for
     * @return vector of Records if matchString is found, empty vector otherwise
     */
    RecordCollection FindMatchingRecords(const std::string& columnName, const std::string& matchString);

    /**
     * @brief deleteRecordByID
     * @param id - id of record to be deleted
     */
    void deleteRecordByID(unsigned id);

private:
    std::map<unsigned, Record> m_records;                   // id to Record map
    std::map<std::string, std::set<unsigned>> m_colunm1IDs; // column1 values to ids, which cotain this value
    std::map<long, std::set<unsigned>> m_colunm2IDs;        // column2 values to ids, which cotain this value
    std::map<std::string, std::set<unsigned>> m_colunm3IDs; // column3 values to ids, which cotain this value

    //helper functions

    template <typename T>
    void addColumnIdMap(std::map<T, std::set<unsigned>>& _map, const T& _columnValue, unsigned _id);

    template <typename T>
    void deleteColumnIdMap(std::map<T, std::set<unsigned>>& _map, const T& _columnValue, unsigned _id);

    template<typename T>
    void addToCollection(RecordCollection& collection, const T& columnValue, const std::map<T, std::set<unsigned>>& _map);
};

template <typename T>
void Table::addColumnIdMap(std::map<T, std::set<unsigned>>& _map, const T& _columnValue, unsigned _id)
{
    auto it = _map.find(_columnValue);
    if (it != _map.end())
    {
        it->second.insert(_id);
    }
    else
        _map.insert({_columnValue, {_id}});
}

template<typename T>
void Table::addToCollection(RecordCollection& collection, const T& value, const std::map<T, std::set<unsigned>>& _map)
{
    auto it = _map.find(value);
    if (it != _map.end())
    {
        for (auto elem : it->second)
            collection.emplace_back(m_records[elem]);
    }
}

template <typename T>
void Table::deleteColumnIdMap(std::map<T, std::set<unsigned>>& _map, const T& _columnValue, unsigned _id)
{
    _map[_columnValue].erase(_id);
    if (_map[_columnValue].empty())
        _map.erase(_columnValue);
}


#endif // QBDEMO_H
