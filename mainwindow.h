#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>


//Forward declarations
class QComboBox;
class QLineEdit;
class QTableWidget;
class QPushButton;
class IDatabase;
class QTableWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleAdd();
    void handleUpdate();
    void handleDelete();
    void handleTableSelectionChanged(const QModelIndex &index);
    void handleTableSelectionChanged2(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    std::shared_ptr<IDatabase> _database;
    QComboBox* _comboMatType;
    QComboBox* _comboMatSize;
    QLineEdit* _editCustName;
    QLineEdit* _editQuoteName;
    QTableWidget* _mainTable;
    QPushButton* _btnAdd;
    QPushButton* _btnUpdate;
    QPushButton* _btnDelete;

    int getSelectedId();

    void refreshTable();
};
#endif // MAINWINDOW_H
