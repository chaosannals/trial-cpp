#include <fstream>
#include <alibabacloud/oss/OssClient.h>
#include <json/json.h>

using namespace AlibabaCloud::OSS;

// 引入阿里的这个库后 Debug 模式下直接就没了。 Release 下运行正常。
int main(int argc, char* argv[])
{
    Json::Value root;

    std::fstream confJson("Config.json");
    if (!confJson.good()) {
        confJson.swap(std::fstream("Config.example.json"));
    }

    confJson >> root;


    /* 初始化OSS账号信息。*/

    /* yourEndpoint填写Bucket所在地域对应的Endpoint。以华东1（杭州）为例，Endpoint填写为https://oss-cn-hangzhou.aliyuncs.com。*/
    std::string Endpoint = root.get("endPoint", "aaa").asString();
    

    std::cout << "endPoint:" << Endpoint << std::endl;

    std::string keyId;
    std::string keySecret;
    std::string bucket;
    std::string target;
    std::string source;

    if (argc < 6) {
        keyId = root.get("keyId", "keyId").asString();
        keySecret = root.get("keySecret", "keySecret").asString();
        bucket = root.get("bucket", "bucket").asString();
        target = root.get("target", "target").asString();
        source = root.get("source", "source").asString();
    }
    else {
        keyId = argv[1];
        keySecret = argv[2];
        bucket = argv[3];
        target = argv[4];
        source = argv[5];
    }
    std::cout << "keyId:" << keyId << std::endl;
    std::cout << "keySecret:" << keySecret << std::endl;
    std::cout << "bucket:" << bucket << std::endl;
    std::cout << "target:" << target << std::endl;
    std::cout << "source:" << source << std::endl;

    /* 初始化网络等资源。*/
    InitializeSdk();

    ClientConfiguration conf;
    auto credentialsProvider = std::make_shared<SimpleCredentialsProvider>(
        keyId,
        keySecret
    );
    OssClient client(Endpoint, credentialsProvider, conf);

    //auto content = std::shared_ptr<std::iostream>(new std::fstream(source));

    auto result = client.PutObject(bucket, target, source);

    auto code = result.error().Code();
    auto message = result.error().Message();

    if (!code.empty()) {
        std::cout << code << std::endl;
    }
    if (!message.empty()) {
        std::cout << message << std::endl;
    }

    std::cin.get();

    /* 释放网络等资源。*/
    ShutdownSdk();
    return 0;
}