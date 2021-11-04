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
    /*!
     * \param fileName - имя файла для записи
     */
    GetIpInfo(QObject *parent, QString fileName);

    /*!
     * \brief checkIp - Метод проверки IP
     * \param ip_addr - IP-адрес
     */
    void checkIp(QString ip_addr);

private:
    /*!
     * \brief WhoIsQuery - метод запроса
     * \param serv - к кому запрос
     * \param ip_addr - тело запроса
     * \return - результат запроса
     */
    bool WhoIsQuery(QString serv, QString ip_addr);

    /*!
     * \brief HostToAddress - конвертирование Hostname в IP-адрес
     */
    void HostToAddress(QString hostname , QHostAddress &ip);

private slots:
    /*!
     * \brief readData - обработка данных ответа
     */
    void readData();

public:
signals:
    /*!
     * \brief getInfoIp - получена информация
     */
    void getInfoIp();

private:
    QTcpSocket mm_socket;           //!< сокет
    QString mm_ip_addr;             //!< запрашиваемый IP-адрес
    QString mm_provider;            //!< провайдер
    QString mm_data;                //!< данные ответа
    QString mm_fileName;            //!< имя файла для записи
};

#endif // GETIPINFO_H
