/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -p ktorrenttorrentinterface -c KTorrentTorrentInterface org.ktorrent.torrent.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef KTORRENTTORRENTINTERFACE_H_1292410024
#define KTORRENTTORRENTINTERFACE_H_1292410024

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.ktorrent.torrent
 */
class KTorrentTorrentInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.ktorrent.torrent"; }

public:
    KTorrentTorrentInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~KTorrentTorrentInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<bool> addTracker(const QString &tracker_url)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(tracker_url);
        return asyncCallWithArgumentList(QLatin1String("addTracker"), argumentList);
    }

    inline QDBusPendingReply<bool> addWebSeed(const QString &webseed_url)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(webseed_url);
        return asyncCallWithArgumentList(QLatin1String("addWebSeed"), argumentList);
    }

    inline QDBusPendingReply<> announce()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("announce"), argumentList);
    }

    inline QDBusPendingReply<qulonglong> bytesDownloaded()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("bytesDownloaded"), argumentList);
    }

    inline QDBusPendingReply<qulonglong> bytesLeft()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("bytesLeft"), argumentList);
    }

    inline QDBusPendingReply<qulonglong> bytesLeftToDownload()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("bytesLeftToDownload"), argumentList);
    }

    inline QDBusPendingReply<qulonglong> bytesToDownload()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("bytesToDownload"), argumentList);
    }

    inline QDBusPendingReply<qulonglong> bytesUploaded()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("bytesUploaded"), argumentList);
    }

    inline QDBusPendingReply<> changeTracker(const QString &tracker_url)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(tracker_url);
        return asyncCallWithArgumentList(QLatin1String("changeTracker"), argumentList);
    }

    inline QDBusPendingReply<bool> chunkDownloaded(uint idx)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(idx);
        return asyncCallWithArgumentList(QLatin1String("chunkDownloaded"), argumentList);
    }

    inline QDBusPendingReply<uint> chunkSize()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("chunkSize"), argumentList);
    }

    inline QDBusPendingReply<uint> chunks()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("chunks"), argumentList);
    }

    inline QDBusPendingReply<bool> createStream(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("createStream"), argumentList);
    }

    inline QDBusPendingReply<QString> currentTracker()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("currentTracker"), argumentList);
    }

    inline QDBusPendingReply<QString> dataDir()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("dataDir"), argumentList);
    }

    inline QDBusPendingReply<uint> downloadSpeed()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("downloadSpeed"), argumentList);
    }

    inline QDBusPendingReply<QString> filePath(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("filePath"), argumentList);
    }

    inline QDBusPendingReply<QString> filePathOnDisk(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("filePathOnDisk"), argumentList);
    }

    inline QDBusPendingReply<double> filePercentage(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("filePercentage"), argumentList);
    }

    inline QDBusPendingReply<int> filePriority(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("filePriority"), argumentList);
    }

    inline QDBusPendingReply<qulonglong> fileSize(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("fileSize"), argumentList);
    }

    inline QDBusPendingReply<int> firstChunkOfFile(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("firstChunkOfFile"), argumentList);
    }

    inline QDBusPendingReply<QString> infoHash()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("infoHash"), argumentList);
    }

    inline QDBusPendingReply<bool> isAllowedToStart()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("isAllowedToStart"), argumentList);
    }

    inline QDBusPendingReply<bool> isMultiMediaFile(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("isMultiMediaFile"), argumentList);
    }

    inline QDBusPendingReply<bool> isPrivate()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("isPrivate"), argumentList);
    }

    inline QDBusPendingReply<int> lastChunkOfFile(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("lastChunkOfFile"), argumentList);
    }

    inline QDBusPendingReply<uint> leechersConnected()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("leechersConnected"), argumentList);
    }

    inline QDBusPendingReply<uint> leechersTotal()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("leechersTotal"), argumentList);
    }

    inline QDBusPendingReply<double> maxSeedTime()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("maxSeedTime"), argumentList);
    }

    inline QDBusPendingReply<double> maxShareRatio()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("maxShareRatio"), argumentList);
    }

    inline QDBusPendingReply<QString> name()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("name"), argumentList);
    }

    inline QDBusPendingReply<uint> numFiles()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("numFiles"), argumentList);
    }

    inline QDBusPendingReply<QString> pathOnDisk()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("pathOnDisk"), argumentList);
    }

    inline QDBusPendingReply<int> priority()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("priority"), argumentList);
    }

    inline QDBusPendingReply<bool> removeStream(uint file_index)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index);
        return asyncCallWithArgumentList(QLatin1String("removeStream"), argumentList);
    }

    inline QDBusPendingReply<bool> removeTracker(const QString &tracker_url)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(tracker_url);
        return asyncCallWithArgumentList(QLatin1String("removeTracker"), argumentList);
    }

    inline QDBusPendingReply<bool> removeWebSeed(const QString &webseed_url)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(webseed_url);
        return asyncCallWithArgumentList(QLatin1String("removeWebSeed"), argumentList);
    }

    inline QDBusPendingReply<> restoreDefaultTrackers()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("restoreDefaultTrackers"), argumentList);
    }

    inline QDBusPendingReply<> scrape()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("scrape"), argumentList);
    }

    inline QDBusPendingReply<double> seedTime()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("seedTime"), argumentList);
    }

    inline QDBusPendingReply<uint> seedersConnected()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("seedersConnected"), argumentList);
    }

    inline QDBusPendingReply<uint> seedersTotal()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("seedersTotal"), argumentList);
    }

    inline QDBusPendingReply<> setAllowedToStart(bool on)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(on);
        return asyncCallWithArgumentList(QLatin1String("setAllowedToStart"), argumentList);
    }

    inline QDBusPendingReply<> setDoNotDownload(uint file_index, bool dnd)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index) << qVariantFromValue(dnd);
        return asyncCallWithArgumentList(QLatin1String("setDoNotDownload"), argumentList);
    }

    inline QDBusPendingReply<> setFilePriority(uint file_index, int prio)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(file_index) << qVariantFromValue(prio);
        return asyncCallWithArgumentList(QLatin1String("setFilePriority"), argumentList);
    }

    inline QDBusPendingReply<> setMaxSeedTime(double hours)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(hours);
        return asyncCallWithArgumentList(QLatin1String("setMaxSeedTime"), argumentList);
    }

    inline QDBusPendingReply<> setMaxShareRatio(double ratio)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(ratio);
        return asyncCallWithArgumentList(QLatin1String("setMaxShareRatio"), argumentList);
    }

    inline QDBusPendingReply<> setPriority(int p)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(p);
        return asyncCallWithArgumentList(QLatin1String("setPriority"), argumentList);
    }

    inline QDBusPendingReply<> setTrackerEnabled(const QString &tracker_url, bool enabled)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(tracker_url) << qVariantFromValue(enabled);
        return asyncCallWithArgumentList(QLatin1String("setTrackerEnabled"), argumentList);
    }

    inline QDBusPendingReply<double> shareRatio()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("shareRatio"), argumentList);
    }

    inline QDBusPendingReply<QByteArray> stats()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("stats"), argumentList);
    }

    inline QDBusPendingReply<QString> torDir()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("torDir"), argumentList);
    }

    inline QDBusPendingReply<qulonglong> totalSize()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("totalSize"), argumentList);
    }

    inline QDBusPendingReply<QStringList> trackers()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("trackers"), argumentList);
    }

    inline QDBusPendingReply<uint> uploadSpeed()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("uploadSpeed"), argumentList);
    }

    inline QDBusPendingReply<QStringList> webSeeds()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("webSeeds"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace org {
  namespace ktorrent {
    typedef ::KTorrentTorrentInterface torrent;
  }
}
#endif
