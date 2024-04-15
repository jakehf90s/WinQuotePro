#include "mainwindow.h"
#include "memorydatabase.h"
#include "pricer.h"

#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTableWidgetItem>

const QStringList headers = {"ID", "Name", "Customer Name", "Material Type", "Material Size", "Price"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();

    _editQuoteName = new QLineEdit();
    _editCustName = new QLineEdit();
    _comboMatType = new QComboBox();
    _comboMatType->addItems({"Wood", "Metal"});
    _comboMatSize = new QComboBox();
    _comboMatSize->addItems({"S", "M", "L"});
    _mainTable = new QTableWidget();
    _mainTable->setSelectionMode(QAbstractItemView::SingleSelection);
    _mainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _mainTable->setColumnCount(headers.size());
    _mainTable->setHorizontalHeaderLabels(headers);

    _btnAdd = new QPushButton("Add");
    _btnUpdate = new QPushButton("Update");
    _btnDelete = new QPushButton("Delete");

    QFormLayout* conLayout = new QFormLayout();
    conLayout->addRow("Name", _editQuoteName);
    conLayout->addRow("Customer Name", _editCustName);
    conLayout->addRow("Material Type", _comboMatType);
    conLayout->addRow("Material Size", _comboMatSize);

    QHBoxLayout* btnsLayout = new QHBoxLayout();
    btnsLayout->addWidget(_btnAdd);
    btnsLayout->addWidget(_btnUpdate);
    btnsLayout->addWidget(_btnDelete);

    QVBoxLayout* lLayout = new QVBoxLayout();
    lLayout->addLayout(conLayout);
    lLayout->addLayout(btnsLayout);
    lLayout->setSpacing(20);
    lLayout->addStretch();

    mLayout->addLayout(lLayout);
    mLayout->addWidget(_mainTable, 1);
    mLayout->addStretch();
    mWidget->setLayout(mLayout);
    this->setCentralWidget(mWidget);

    connect(_btnAdd, &QPushButton::clicked, this, &MainWindow::handleAdd);
    connect(_btnUpdate, &QPushButton::clicked, this, &MainWindow::handleUpdate);
    connect(_btnDelete, &QPushButton::clicked, this, &MainWindow::handleDelete);
    connect(_mainTable, &QTableWidget::activated, this, &MainWindow::handleTableSelectionChanged);
    connect(_mainTable, &QTableWidget::currentItemChanged, this, &MainWindow::handleTableSelectionChanged2);

    _database = std::make_shared<MemoryDatabase>();
}

MainWindow::~MainWindow() {}

void MainWindow::handleAdd()
{
    std::string name = _editQuoteName->text().toStdString();
    std::string cust_name = _editCustName->text().toStdString();
    MaterialType mt = (MaterialType)_comboMatType->currentIndex();
    MaterialSize ms = (MaterialSize)_comboMatSize->currentIndex();
    _database->addquote(name, cust_name, mt, ms);
    this->refreshTable();
}

void MainWindow::handleUpdate()
{
    int id = getSelectedId();
    if (id < 0) return;
    std::string name = _editQuoteName->text().toStdString();
    std::string cust_name = _editCustName->text().toStdString();
    MaterialType mt = (MaterialType)_comboMatType->currentIndex();
    MaterialSize ms = (MaterialSize)_comboMatSize->currentIndex();
    _database->editquote(id, name, cust_name, mt, ms);
    this->refreshTable();
}

void MainWindow::handleDelete()
{
    int id = getSelectedId();
    if (id < 0) return;
    _database->deletequote(id);
    this->refreshTable();
}

void MainWindow::handleTableSelectionChanged(const QModelIndex &index)
{
    int id = getSelectedId();
    if (id < 0) return;
    std::shared_ptr<Quote> quote = _database->getquote(id);
    _editQuoteName->setText(quote->name().c_str());
    _editCustName->setText(quote->customer_name().c_str());
    _comboMatType->setCurrentIndex((int)quote->m_type());
    _comboMatSize->setCurrentIndex((int)quote->m_size());
}

void MainWindow::handleTableSelectionChanged2(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    handleTableSelectionChanged(QModelIndex());
}

int MainWindow::getSelectedId()
{
    QList<QTableWidgetItem*> selectedItems = _mainTable->selectedItems();
    if (selectedItems.isEmpty()) {
        return - 1;
    }
    int firstSelectedRow = _mainTable->currentRow();
    QTableWidgetItem* idItem = _mainTable->item(firstSelectedRow, 0);
    int ret = idItem->text().toInt();
    return ret;
}

void MainWindow::refreshTable()
{
    std::vector< std::shared_ptr<Quote> > quotes = _database->getallquotes();
    _mainTable->clearContents();
    _mainTable->setRowCount(quotes.size());

    int row = 0;
    for (const auto& quote : quotes) {
        // Ensure the quote is valid
        if (!quote) continue;

        double price = Pricer::getPriceAPI(quote->m_type(), quote->m_size());

        QString matStr = "Wood";
        QString matSStr = "S";
        if (quote->m_type() == MaterialType::mtMetal) {
            matStr = "Metal";
        }
        if (quote->m_size() == MaterialSize::msM) {
            matSStr = "L";
        } else if (quote->m_size() == MaterialSize::msL) {
            matSStr = "L";
        }


        _mainTable->setItem(row, 0, new QTableWidgetItem( QString::number(quote->id())) );
        _mainTable->setItem(row, 1, new QTableWidgetItem( QString::fromStdString(quote->name())) );
        _mainTable->setItem(row, 2, new QTableWidgetItem( QString::fromStdString(quote->customer_name())) );
        _mainTable->setItem(row, 3, new QTableWidgetItem(matStr) );
        _mainTable->setItem(row, 4, new QTableWidgetItem(matSStr) );
        _mainTable->setItem(row, 5, new QTableWidgetItem(QString::number(price)));

        row++;
    }
}
