
#include "OkonPreparer.h"


OkonPreparer::OkonPreparer(const QString& fileToPrepare, QObject* parent)
        : QObject{parent}
        , m_fileToPrepare{fileToPrepare.toStdString()}
{}

OkonPreparer::~OkonPreparer()
{
    int a = 2;
    a  = 4;
    (void)a;
}

void OkonPreparer::run() {
    auto dataForCallback = new DataForCallback;
    dataForCallback->preparerPtr = this;
    dataForCallback->lastPercentageReported = -111;

    okon_prepare(m_fileToPrepare.c_str(),
                 "okon_wd/",
                 "passwords.okon",
                 static_cast<okon_prepare_progress_callback_t>(&OkonPreparer::progressCallback),
                 dataForCallback);
}

void OkonPreparer::progressCallback(void* userData, int percentage) {
    auto& data = *reinterpret_cast<DataForCallback*>(userData);

    int toReport{};

    if(percentage == okon_prepare_progress_special_value_unknown) {
        toReport = 0;
    } else if(percentage <= data.lastPercentageReported) {
        return;
    } else {
        toReport = percentage;
    }

    data.preparerPtr->reportProgress(toReport);
    data.lastPercentageReported = toReport;
}

void OkonPreparer::reportProgress(int percentage) {
    emit progressChanged(percentage);
}
