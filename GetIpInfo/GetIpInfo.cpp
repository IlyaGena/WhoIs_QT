#include "GetIpInfo.h"

GetIpInfo::GetIpInfo(QObject *parent, QString fileName) : QObject(parent)
{
    mm_fileName = fileName;
    QObject::connect(&mm_socket, &QIODevice::readyRead, this, &GetIpInfo::readData);
}

void GetIpInfo::checkIp(QString ip_addr)
{
    mm_ip_addr = ip_addr;

    if(WhoIsQuery("whois.iana.org", mm_ip_addr))
        qDebug() << "Whois query failed";
}

bool GetIpInfo::WhoIsQuery(QString serv, QString ip_addr)
{
    QHostAddress ip_tmp;
    QString message;

    qDebug() << QString("Resolving %1 ...").arg(serv);
    HostToAddress(serv , ip_tmp);

    if(ip_tmp == QHostAddress())
    {
        qDebug() << "Failed";
        return false;
    }
    else
        qDebug() << "Resolved!";

    qDebug() << "Connect to address on port 43: " << ip_tmp;

    //Now connect to remote server
    mm_socket.connectToHost(serv, 43);
    mm_socket.waitForConnected();

    //if network error
    if(mm_socket.state() == QAbstractSocket::UnconnectedState)
    {
        qDebug("Connection error!");
        return false;
    }
    if(mm_socket.state() == QAbstractSocket::ConnectedState)
        qDebug() << "Connect!";

    //Now send some data or message
    qDebug() << QString("Querying for %1 ...").arg(ip_addr);

    message = QString("%1\r\n").arg(ip_addr);

    mm_socket.write(message.toUtf8());
    mm_socket.flush();

    return 0;
}

void GetIpInfo::HostToAddress(QString hostname, QHostAddress &ip)
{
    QHostInfo info = QHostInfo::fromName(hostname);

    if (!info.addresses().isEmpty())
        ip = info.addresses().first();

    return ;
}

void GetIpInfo::readData()
{
    QString data = QString(mm_socket.readAll());
    if (mm_provider.isEmpty())
    {
        QRegExp regularEx("whois.\\S+");

        regularEx.indexIn(data);

        mm_provider = regularEx.cap();

        if(mm_provider == "")
        {
            qDebug() << " Provider got found!";
            return;
        }
        qDebug() << QString("Whois server is: %1").arg(mm_provider);
        mm_socket.close();
        WhoIsQuery(mm_provider, mm_ip_addr);
        return;
    }
    else {
        QFile file(mm_fileName);

        if(!file.open(QIODevice::Append))
            return;

        QTextStream stream(&file);
        stream << data;

        file.close();

        emit getInfoIp();
    }
}
