#ifndef GETIPINFO_H
#define GETIPINFO_H

#include <QObject>
#include <QHostAddress>
#include <QHostInfo>
#include <QUrl>
#include <QWebSocket>
#include <QRegExp>
#include <QFile>

class GetIpInfo : public QObject
{
    Q_OBJECT

public:
    GetIpInfo(QObject *parent, QString fileName);

    void checkIp(QString ip_addr);

private:
    /*!
     * \brief WhoIsQuery
     * \param server
     * \param query
     * \param response
     * \return
     */
    bool WhoIsQuery(QString serv, QString ip_addr);

    void HostToAddress(QString hostname , QHostAddress &ip);

private slots:
    void readData();

public:
signals:
    /*!
     * \brief getInfoIp - получена информация
     */
    void getInfoIp();

private:
    QTcpSocket mm_socket;
    QString mm_ip_addr;
    QString mm_provider;
    QString mm_data;
    QString mm_fileName;
};

#endif // GETIPINFO_H
