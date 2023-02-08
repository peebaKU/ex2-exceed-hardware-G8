#include <bits/stdc++.h>
using namespace std;
 
int main(int argc, char *argv[]) {
 
 char a_XmlData[]="<body><name>amss</name><age>19</age></body>";
 char a_XmlRequest[251]={0};
 char a_ServiceMethod[]="applicationformat.svc/getdetail";
 char a_Request[151]={0};
 char a_HostIp[31]="76.127.24.111";
 char a_Port[]="81";
 
 
 
 sprintf(a_Request,"http://%s:%s/%s/%s HTTP/1.1",a_HostIp,a_Port,a_ServiceMethod);
 
 cout<<"Method and Resource path is below:";
 
 cout<<a_Request;
 
 strcat(a_HostIp,":");
    strcat(a_HostIp,a_Port);
 
 cout<<"HOST header is below:"<<endl;;
 cout<<a_HostIp;
 
 sprintf(a_XmlRequest,"POST %s\r\nHost: %s\r\nContent-Type: application/xml\r\nContent-Length: %d\r\n\r\n%s\r\n",aszRequest,aszHostIp,strlen(aszXmlData),aszXmlData);
 
 cout<<"POST Request which send to the server:"<<endl;
 cout<<a_XmlRequest;
 
 
 return 0;
}