#include "process.h"
#include "process_table_model.h"

Process::Process(unsigned int id, QObject * parent)
    :QObject(parent)
{
    // Добавляем информацию о данных процесса
    propertyList << QString() << id << 0.0f << 0.0f << 0.0f << 0.0f;

    // TODO: Получить информцию о процессе
}

const QVariant & Process::property(int propertyName) {
    return propertyList.at(propertyName);
}

bool Process::refresh() {
    // TODO: Получить информацию о процессе
    return true;
}
