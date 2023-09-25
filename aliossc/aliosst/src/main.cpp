#include <fstream>
#include <alibabacloud/oss/OssClient.h>
#include <json/json.h>

// 引入阿里的这个库后 Debug 模式下直接就没了。 Release 下运行正常。
using namespace AlibabaCloud::OSS;

bool endsWith(std::string& s, std::string sub) {
    return s.rfind(sub) == (s.length() - sub.length());
}

int64_t getFileSize(const std::string& file)
{
    std::fstream f(file, std::ios::in | std::ios::binary);
    f.seekg(0, f.end);
    int64_t size = f.tellg();
    f.close();
    return size;
}

// 引入阿里的这个库后 Debug 模式下直接就没了。 Release 下运行正常。
int main(int argc, char* argv[])
{
    Json::Value root;

    std::fstream confJson("Config.json");
    if (!confJson.good()) {
        confJson.swap(std::fstream("Config.example.json"));
    }

    if (confJson.good()) {
        confJson >> root;
    }


    /* 初始化OSS账号信息。*/

    /* yourEndpoint填写Bucket所在地域对应的Endpoint。以华东1（杭州）为例，Endpoint填写为https://oss-cn-hangzhou.aliyuncs.com。*/
    std::string Endpoint = root.get("endPoint", "oss-cn-shanghai.aliyuncs.com").asString();
    

    // std::cout << "endPoint:" << Endpoint << std::endl;

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
    //std::cout << "keyId:" << keyId << std::endl;
    //std::cout << "keySecret:" << keySecret << std::endl;
    //std::cout << "bucket:" << bucket << std::endl;
    //std::cout << "target:" << target << std::endl;
    //std::cout << "source:" << source << std::endl;

    /* 初始化网络等资源。*/
    InitializeSdk();

    ClientConfiguration conf;
    auto credentialsProvider = std::make_shared<SimpleCredentialsProvider>(
        keyId,
        keySecret
    );
    OssClient client(Endpoint, credentialsProvider, conf);

    //auto content = std::shared_ptr<std::iostream>(new std::fstream(source));
    //PutObjectRequest request(bucket, target, content); // 简单上传请求

    InitiateMultipartUploadRequest initUploadRequest(bucket, target); // 分片上传请求
    if (endsWith(target, ".json")) {
        initUploadRequest.MetaData().addHeader("Content-Type", "application/json");
    }
    if (endsWith(target, ".apk")) {
        initUploadRequest.MetaData().addHeader("Content-Type", "application/vnd.android.package-archive");
    }

    auto uploadIdResult = client.InitiateMultipartUpload(initUploadRequest);
    auto uploadId = uploadIdResult.result().UploadId();
    int64_t partSize = 100 * 1024;
    PartList partETagList;
    auto fileSize = getFileSize(source);
    int partCount = static_cast<int>(fileSize / partSize);
    /* 计算分片个数 */
    if (fileSize % partSize != 0) {
        partCount++;
    }

    /* 对每一个分片进行上传 */
    for (int i = 1; i <= partCount; i++) {
        auto skipBytes = partSize * (i - 1);
        auto size = (partSize < fileSize - skipBytes) ? partSize : (fileSize - skipBytes);
        std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>(source, std::ios::in | std::ios::binary);
        content->seekg(skipBytes, std::ios::beg);

        UploadPartRequest uploadPartRequest(bucket, target, content);
        uploadPartRequest.setContentLength(size);
        uploadPartRequest.setUploadId(uploadId);
        uploadPartRequest.setPartNumber(i);
        auto uploadPartOutcome = client.UploadPart(uploadPartRequest);
        if (uploadPartOutcome.isSuccess()) {
            Part part(i, uploadPartOutcome.result().ETag());
            partETagList.push_back(part);
        }
        else {
            std::cout << "uploadPart fail" <<
                ",code:" << uploadPartOutcome.error().Code() <<
                ",message:" << uploadPartOutcome.error().Message() <<
                ",requestId:" << uploadPartOutcome.error().RequestId() << std::endl;
        }

    }

    /* 完成分片上传 */
    /* 
       在执行完成分片上传操作时，需要提供所有有效的partETags。
       OSS收到提交的partETags后，会逐一验证每个分片的有效性。
       当所有的数据分片验证通过后，OSS将把这些分片组合成一个完整的文件。
    */
    CompleteMultipartUploadRequest request(bucket, target);
    request.setUploadId(uploadId);
    request.setPartList(partETagList);
    /*（可选）请参见如下示例设置读写权限ACL */
    //request.setAcl(CannedAccessControlList::Private);
    auto result = client.CompleteMultipartUpload(request);

    //auto result = client.PutObject(request); // 简单上传

    if (!result.isSuccess()) {

        auto code = result.error().Code();
        auto message = result.error().Message();

        if (!code.empty()) {
            std::cout << code << std::endl;
        }
        if (!message.empty()) {
            std::cout << message << std::endl;
        }
    }

    // std::cin.get();

    /* 释放网络等资源。*/
    ShutdownSdk();
    return 0;
}