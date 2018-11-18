#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "../core/process.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

class ProcessTableModel : public QAbstractTableModel {
    Q_OBJECT
private:
    // Список процессов
    QList<Process *> processList;
    QSet<unsigned int> pidSet;

    unsigned int cpuUtilization = 0; // Использование процессора в процентах
    unsigned int memoryUtilization = 0; // Использование памяти в процентах

    QList<float> maxProperty;
    int sortColumn; // По какому столбцу сотируем
    Qt::SortOrder sortOrder; // Направление сортировки

public:
    /**
     * Создаем экземпляр класса со списком процессов
     */
    explicit ProcessTableModel(QObject* parent = nullptr);
    virtual ~ProcessTableModel();
protected:
    /**
     * Возвращаем количество строк
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    /**
     * Возвращаем количество столбцов
     */
    int columnCount(const QModelIndex& parent) const;

    // Возвращает данные, хранящиеся в данной роли для элемента, указанного индексом .
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    // Возвращает данные для данной роли и раздела в заголовке с указанной ориентацией
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    /**
     * Сортировать по
     */
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
public slots:
    /**
     * Обновить данные всех процессов
     */
    void refresh();

    /**
     * Сортировка по стоблцу
     * @param column - столбец для сортировки
     * @param order - направление сортировки
     */
    void sortByColumn(int column, Qt::SortOrder order);
};
