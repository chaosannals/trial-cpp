#include <iostream>
#include <filesystem>
#include <format>
#include <memory>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
//#include <faker-cxx/Date.h>
#include <faker-cxx/Internet.h>
//#include <faker-cxx/Location.h>
#include <faker-cxx/String.h>
#include <faker-cxx/Person.h>

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

    leveldb::WriteOptions wo;
    wo.sync = true; // 同步写入。

    leveldb::WriteBatch batch;
    for (int i = 0; i < 1000; ++i) {
        const auto id = faker::String::uuid();
        const auto username = faker::Internet::username();
        std::cout << "put:" << id << ":" << username << std::endl;
        batch.Put(id, username);
    }
    s = udb->Write(wo, &batch);

    leveldb::WriteBatch batch2;
    for (int i = 0; i < 1000; ++i) {
        const auto id = faker::String::uuid();
        const auto fullName = faker::Person::fullName(faker::Country::China);
        std::cout << "put:" << id << ":" << fullName << std::endl;
        batch.Put(id, fullName);
    }
    s = udb->Write(wo, &batch2);

    std::cout << "batch write(" << s.ToString() << ")" << std::endl;
    
    std::cin.get();
}
