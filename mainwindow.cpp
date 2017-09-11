#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QTableWidgetItem>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 3, this);
    ui->tableView->setModel(model);

    QStringList images = QStringList() << "://img/meat.png"
                                       << "://img/bread.png"
                                       << "://img/milk.png";

    QStringList products = QStringList() << "meat" << "bread" << "milk";
    for (int i = 0; i < products.count(); ++i) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(products[i]));
        model->appendRow(items);
        QModelIndex indx = model->index(i, 1);
        ui->tableView->setIndexWidget(indx, createBtn());
        indx = model->index(i, 2);
        QLabel *lb = new QLabel(this);
        lb->setPixmap(QPixmap(images.at(i)).scaled(30, 30));
        ui->tableView->setIndexWidget(indx, lb);
    }
    ui->tableView->resizeColumnsToContents();

    QHeaderView *verticalHeader = ui->tableView->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(37);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget *MainWindow::createBtn()
{
    QWidget* wgt = new QWidget;
    QBoxLayout* layout = new QHBoxLayout;
    QIcon icon = style()->standardIcon(QStyle::SP_DialogOkButton);
    QPushButton *btn = new QPushButton(icon, "Change color", this);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(on_btnClicked()));
    layout->setMargin(5);
    layout->addStretch();
    layout->addWidget(btn);
    wgt->setLayout(layout);
    return wgt;
}

void MainWindow::on_btnClicked()
{
    if (QPushButton *btn = qobject_cast<QPushButton*> (sender())) {
        QModelIndex indx = ui->tableView->indexAt(btn->parentWidget()->pos());
        QStandardItem *item = model->item(indx.row(), 0);
        QColor color;
        if (item->data(Qt::TextColorRole) != QColor(Qt::red)) {
            color = Qt::red;
        } else {
            color = Qt::black;
        }
        item->setData(color, Qt::TextColorRole);
        item->setData("QColor(Qt::red)", Qt::ToolTipRole);
    }
}
