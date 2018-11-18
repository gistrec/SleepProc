#pragma once
#include <Qobject>
#include <QVariant>
#include <QVariantList>

class Process {
private:
    // Данные о процессе
    QString name; // Название процесса
    uint id;      // Идентефикатор
    uint CPUUsage    = 0.f;  // Использование CPU
    uint MemoryUsage = 0.f;  // Использование RAM

public:
    /**
     * Создаем объект процесса
     * @param id - идентификатор процесса
     * @param parent
     */
    explicit Process(uint id);

    /**
     * Обновляем данные о процессе
     * @return bool - существует ли еще процесс
     */
    bool refresh();

    /**
     * Функции для получения данных о процессе
     */
    const QString& getName() const;
    uint getId() const;
    uint getCPUUsage() const;
    uint getMemoryUsage() const;
};
