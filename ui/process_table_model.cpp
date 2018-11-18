#include "process_table_model.h"

ProcessTableModel::ProcessTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    sortColumn = -1;
    sortOrder = Qt::AscendingOrder;

    // Установка максимального значения
    maxProperty << 0 << 0 << 100 << 1024 * 128 << 50 << 1;
}


void ProcessTableModel::refresh() {
    emit layoutAboutToBeChanged();

    // Получаем список процессов
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
    EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);

    // Сколько процессов возвращено.
    cProcesses = cbNeeded / sizeof(DWORD);
    for (i = 0; i < cProcesses; i++) {
        if (aProcesses[i] == 0 ) continue;
        // Если этого процесса еще нет в списке
        if(!pidSet.contains(aProcesses[i])) {
            processList.append(new Process(aProcesses[i]));
            pidSet.insert(aProcesses[i]);
        }
    }

    // Список процессов, которые нужно удалить
    QList<Process*> toDelete;
    // iterate through current process list to refresh info
    // and remove those have already been killed
    for(Process* process : processList) {
        if(!process->refresh())
            toDelete.append(process);
    }

    // Удаляем процессы
    /*for(Process * process : toDelete) {
        pidSet.remove(process->getId());
        processList.removeOne(process);
        delete process;
    }*/

    // Сортируем
    sortByColumn(sortColumn, sortOrder);
    emit layoutChanged();
}

int ProcessTableModel::rowCount(const QModelIndex& parent) const {
    return processList.size();
}

int ProcessTableModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

ProcessTableModel::~ProcessTableModel() {
    for (Process* process: processList) {
        delete process;
    }
}

QVariant ProcessTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            switch(section) {
            case 0:
                return QString("Process Name");
            case 1:
                return QString("PID");
            case 2:
                return QString("%1 %\n\nCPU").arg(cpuUtilization);
            case 3:
                return QString("%1 %\n\nMemory").arg(memoryUtilization);
            default:
                return QString("wtf");
            }
        }else if (role == Qt::TextAlignmentRole) {
            if (section == 0)     return (int)Qt::AlignBottom | (int)Qt::AlignLeft;
            else if(section == 1) return (int)Qt::AlignBottom | (int)Qt::AlignHCenter;
            else return (int)Qt::AlignBottom | (int)Qt::AlignRight;
        }
    }
    return QVariant();
}

QVariant ProcessTableModel::data(const QModelIndex& index, int role) const {
    if(!index.isValid()) return QVariant();

    Process* process = processList[index.row()];
    if(role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return process->getName();
        case 1:
            return process->getId();
        /*case Process::CPUUsage:
        {
            float cpuUsage = process->property(Process::CPUUsage).toFloat();
            if(cpuUsage < 0.1)
                return "0 %";
            else
                return QString::number(cpuUsage, 'f', 1) + " %";
        }
        case Process::MemoryUsage:
        {
            unsigned int memory = process->property(Process::MemoryUsage).toUInt();
            if(memory < 1024)
                return QString::number(memory) + " KB";
            else if(memory < 1024 * 1024)
                return QString::number(memory / 1024, 'f', 1) + " MB";
            else
                return QString::number(memory / (1024 * 1024), 'f', 1) + " GB";
        }*/
        default:
            return QString("None");
        }
    }else if (role == Qt::BackgroundRole) {
        if(index.column() > 1) {
           //int level =  process->property(index.column()).toFloat() / (maxProperty.at(index.column()) / 5);
           //level = level > 4 ? 4 : level;
            int level = 4;
            return QBrush(QColor(255, 198, 61, 80 + 100 * ((float)level / 4)));
        }else {
            return QVariant();
        }
    }else if (role == Qt::TextAlignmentRole) {
        switch(index.column()) {
        case 0:
            return (int)Qt::AlignLeft | (int)Qt::AlignVCenter;
        case 1:
            return (int)Qt::AlignHCenter | (int)Qt::AlignVCenter;
        default:
            return (int)Qt::AlignRight | (int)Qt::AlignVCenter;
        }
    }
    return QVariant();
}

void ProcessTableModel::sortByColumn(int column, Qt::SortOrder order) {
    if(column < 0)
        return;

    sortColumn = column;
    sortOrder = order;
    sort(column, order);
}

void ProcessTableModel::sort(int column, Qt::SortOrder order) {
    emit layoutAboutToBeChanged();

    if(order == Qt::AscendingOrder)
        std::sort(processList.begin(),processList.end(),
              [=](Process * left, Process * right)
        {
            // If sorted by process name
            if(column == 0)
                return left->getName().compare(right->getName(), Qt::CaseInsensitive) < 0;
            /*else
                return left->property(column).toFloat() < right->property(column).toFloat();*/
        });
    else
        std::sort(processList.begin(),processList.end(),
              [=](Process * left, Process * right)
        {
            // If sorted by process name
            if(column == 0)
                return left->getName().compare(right->getName(), Qt::CaseInsensitive) > 0;
            /* else
                return left->property(column).toFloat() > right->property(column).toFloat();*/
        });

    emit layoutChanged();
}
