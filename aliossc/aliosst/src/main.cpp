#include <fstream>
#include <alibabacloud/oss/OssClient.h>

using namespace AlibabaCloud::OSS;

// 引入阿里的这个库后 Debug 模式下直接就没了。 Release 下运行正常。
int main(int argc, char* argv[])
{
    /* 初始化OSS账号信息。*/

    /* yourEndpoint填写Bucket所在地域对应的Endpoint。以华东1（杭州）为例，Endpoint填写为https://oss-cn-hangzhou.aliyuncs.com。*/
    std::string Endpoint = "oss-cn-shanghai.aliyuncs.com";

    //std::cout << "start" << std::endl;

    /* 初始化网络等资源。*/
    InitializeSdk();

    ClientConfiguration conf;
    /* 从环境变量中获取访问凭证。运行本代码示例之前，请确保已设置环境变量OSS_ACCESS_KEY_ID和OSS_ACCESS_KEY_SECRET。*/
    
    auto keyId = argv[1];
    auto keySecret = argv[2];
    auto bucket = argv[3];
    auto target = argv[4];
    auto source = argv[5];

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

    //std::cin.get();

    /* 释放网络等资源。*/
    ShutdownSdk();
    return 0;
}