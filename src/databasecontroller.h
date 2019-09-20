#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>

#include <tyristmanual.h>
#include <services/stream/pipestream.h>
#include <config/server_command.h>

class DataBaseController : public QObject
{
        Q_OBJECT
    private:
        class ServerSignalChecker;
        mutable PipeStream commandOutputStream, dataInputStream, dataOutputStream, signalInputStream;
        QThread* checkerThread;
        ServerSignalChecker* checker;
    public:
        DataBaseController();
        ~DataBaseController();
        int count() const;
        void append(TyristManual record);
        void remove(id_type id);
        void update(id_type record_id, TyristManual record);
        int compareRecordsByID(id_type, id_type);
        TyristManual record(id_type id) const;
        QVector<TyristManual> records();
        bool save(QString filename);
        bool load(QString filename);
        void clear();
        bool isModidfied() const;
    signals:
        void update_signal(id_type);
        void append_signal(id_type);
        void remove_signal(id_type);
        void clear_signal();
        void server_stop_signal();

        // этот сигнал требуется для чекера чтобы мы могли требовать считывать тогда когда как бы этого захотим
        void checking_next_signal();
    private slots:
        void serverSignaled(ClientCommand);
};

class DataBaseController::ServerSignalChecker : public QObject
{
        Q_OBJECT
    private:
        PipeStream& signalInputStream;
    public:
        explicit ServerSignalChecker(PipeStream& input);
    public slots:
        void start();
    signals:
        void check_command(ClientCommand);
};


#endif // DATABASECONTROLLER_H
