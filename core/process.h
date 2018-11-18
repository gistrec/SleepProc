#pragma once

class Process : public QObject {
public:
    // Данные о процессе
    enum Property {
        ProcessName = 0,
        ID,
        CPUUsage,
        MemoryUsage,
        PropertyCount
    };


    /**
     * Создаем объект процесса
     * @param id - идентификатор процесса
     * @param parent
     */
    explicit Process(unsigned int id, QObject* parent = nullptr);

    /**
     * Обновляем данные о процессе
     * @return bool - существует ли еще процесс
     */
    bool refresh();

    /**
     * Получить свойство
     * @param propertyName - название свойства
     * @return значение свойства
     */
    const QVariant & property(int propertyName);

private:
    // Список данных о процессе в порядке, как в enum Property:
    QVariantList propertyList;
};
