#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableView>

// git测试
#include "QJsonTableModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

   void init();
   QString readJson(QString sPath);
private:
    Ui::MainWindow *ui;
    QTableView *m_pEpisodeTableView;
    QJsonTableModel *m_pEpisodes;
};

#endif // MAINWINDOW_H
