#include <assert.h>
#include <qbdemo.h>

void TestBasic()
{
    Table t;
    for (int i = 0; i < 100; i++)
        t.addRecord(i, "rec" + std::to_string(i), i + 100, "rec2" + std::to_string(i));
    Table::RecordCollection rec;

    rec= t.FindMatchingRecords("id", "70");
    assert(rec.size() == 1);
    rec.clear();

    rec =  t.FindMatchingRecords("column1", "rec0");
    assert(rec.size() == 1);
    rec.clear();

    t.deleteRecordByID(0);
    rec = t.FindMatchingRecords("column1", "rec0");
    assert(rec.size() == 0);

    rec = t.FindMatchingRecords("column2", "104");
    assert(rec.size() == 1);
    rec.clear();

    rec = t.FindMatchingRecords("column3", "rec23");
    assert(rec.size() == 1);
    rec.clear();
}

void TestMultipleMatching()
{
    Table t;
    for (int i = 0; i < 100; i++)
        t.addRecord(i, "rec", 100, "rec2" + std::to_string(i));
    Table::RecordCollection rec;

    rec = t.FindMatchingRecords("column1", "rec0");
    assert(rec.size() == 0);

    rec = t.FindMatchingRecords("column1", "rec");
    assert(rec.size() == 100);
    rec.clear();

    rec = t.FindMatchingRecords("column2", "100");
    assert(rec.size() == 100);
    rec.clear();

    rec = t.FindMatchingRecords("column3", "rec21");
    assert(rec.size() == 1);
    rec.clear();

    t.deleteRecordByID(2);
    rec = t.FindMatchingRecords("column1", "rec");
    assert(rec.size() == 99);
}


int main()
{
    TestBasic();
    TestMultipleMatching();
    return 0;
}
