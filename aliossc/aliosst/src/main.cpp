#include <fstream>
#include <alibabacloud/oss/OssClient.h>

using namespace AlibabaCloud::OSS;

// ���밢��������� Debug ģʽ��ֱ�Ӿ�û�ˡ� Release ������������
int main(int argc, char* argv[])
{
    /* ��ʼ��OSS�˺���Ϣ��*/

    /* yourEndpoint��дBucket���ڵ����Ӧ��Endpoint���Ի���1�����ݣ�Ϊ����Endpoint��дΪhttps://oss-cn-hangzhou.aliyuncs.com��*/
    std::string Endpoint = "oss-cn-shanghai.aliyuncs.com";

    //std::cout << "start" << std::endl;

    /* ��ʼ���������Դ��*/
    InitializeSdk();

    ClientConfiguration conf;
    /* �ӻ��������л�ȡ����ƾ֤�����б�����ʾ��֮ǰ����ȷ�������û�������OSS_ACCESS_KEY_ID��OSS_ACCESS_KEY_SECRET��*/
    
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

    /* �ͷ��������Դ��*/
    ShutdownSdk();
    return 0;
}