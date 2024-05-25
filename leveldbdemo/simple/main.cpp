#include <iostream>
#include <filesystem>
#include <format>
#include <memory>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

std::unique_ptr<leveldb::DB> open_db() {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    auto dir = std::filesystem::current_path();
    std::cout << "cur dir: " << dir << std::endl;
    auto db_dir = dir.concat("demo.ldb");

    leveldb::Status status = leveldb::DB::Open(options, db_dir.string(), &db);
    std::cout << "status:" << status.ok() << " -> " << status.ToString() << std::endl;
    return std::unique_ptr<leveldb::DB>(db);
}

int main() {
    auto udb = open_db();

    auto s = udb->Put(leveldb::WriteOptions(), "aaa", "234");
    std::string value;
    s = udb->Get(leveldb::ReadOptions(), "aaa", &value);

    std::cout << "get(" << s.ToString() << "):" << value << std::endl;

    s = udb->Delete(leveldb::WriteOptions(), "aaa");

    leveldb::WriteBatch batch;
    for (int i = 0; i < 1000; ++i) {
        batch.Put(std::format("key{0}", i), std::format("value{0}", i));
    }
    leveldb::WriteOptions wo;
    wo.sync = true; // 同步写入。
    s = udb->Write(wo, &batch);

    std::cout << "batch write(" << s.ToString() << ")" << std::endl;
    
    std::cin.get();
}
