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

#include <cppjieba/Jieba.hpp>

const char* const DICT_PATH = "jieba.dict.utf8";
const char* const HMM_PATH = "hmm_model.utf8";
const char* const USER_DICT_PATH = "user.dict.utf8";
const char* const IDF_PATH = "idf.utf8";
const char* const STOP_WORD_PATH = "stop_words.utf8";

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

    cppjieba::Jieba jieba(DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH);
    std::vector<std::string> words;
    std::vector<cppjieba::Word> jiebawords;
    std::string jbs;
    std::string result;

    jbs = "他来到了网易杭研大厦";
    std::cout << jbs << std::endl;
    std::cout << "[demo] Cut With HMM" << std::endl;
    jieba.Cut(jbs, words, true);
    std::cout << limonp::Join(words.begin(), words.end(), "/") << std::endl;
    
    std::cin.get();
}
