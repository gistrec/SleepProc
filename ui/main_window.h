#pragma once
#include "process_table_model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QPoint origin;
    bool isDragging;

    QTimer refreshTimer;
    ProcessTableModel processModel;
private slots:
    void refresh();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static const int REFRESH_RATE;
    void updateWidget(const QVariantList & property);
protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
private:
    Ui::MainWindow *ui;
};
