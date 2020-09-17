//
// Created by stryku on 17.09.20.
//

#ifndef KEEPASSXC_OKONPREPARER_H
#define KEEPASSXC_OKONPREPARER_H

#include <QRunnable>
#include <QObject>

#include <okon/okon.h>

class OkonPreparer : public QObject, public QRunnable {
    Q_OBJECT

private:
    struct DataForCallback {
        OkonPreparer* preparerPtr;
        int lastPercentageReported;
    };

public:
    OkonPreparer(const QString& fileToPrepare, QObject* parent);
    ~OkonPreparer();

    void run() override ;

    static void progressCallback(void* userData, int percentage) ;

signals:
    void progressChanged(int percentage);

private:
    void reportProgress(int percentage);

private:
    const std::string m_fileToPrepare;
};

#endif //KEEPASSXC_OKONPREPARER_H
