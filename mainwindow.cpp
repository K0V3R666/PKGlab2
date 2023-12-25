#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QImageWriter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->DefoltPath = "C:/Users/acer/Desktop/ПКГ/2lab";
    this->setFixedSize(920,600);
    ui->mainTable->setFixedSize(900,500);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chooseFileBut_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(nullptr, "Выберите папку", DefoltPath);
    if (!folderPath.isEmpty())
    {
        QDir selectedFolder(folderPath);
        ui->mainTable->setRowCount(0);
        ui->InfLabel->setText("");
        if (selectedFolder.exists())
        {
            QStringList nameFilters;
            nameFilters << "*.jpg" << "*.gif" << "*.tif" << "*.bmp" << "*.png" << "*.pcx";
            QFileInfoList allFiles = selectedFolder.entryInfoList(QDir::Files);
            QFileInfoList files = selectedFolder.entryInfoList(nameFilters, QDir::Files);
            int ignored = allFiles.count() - files.count();

            int CountElements = files.count();
            if (!files.isEmpty())
            {
                //ui->mainTable->setRowCount(CountElements);
                ui->mainTable->setColumnCount(6);
                ui->mainTable->setColumnWidth(0,150);
                ui->mainTable->setColumnWidth(1,140);
                ui->mainTable->setColumnWidth(2,140);
                ui->mainTable->setColumnWidth(3,140);
                ui->mainTable->setColumnWidth(4,140);
                ui->mainTable->setColumnWidth(5,140);
                QStringList horizontalHeaders;
                horizontalHeaders << "Название" << "Размер(px)" << "Горизонт. разрешение"<<"Верт. разрешение"<<"Глубина цвета"<<"Степень сжатия";
                ui->mainTable->setHorizontalHeaderLabels(horizontalHeaders);
                foreach (const QFileInfo &fileInfo, files) {
                    QString name = fileInfo.fileName();
                    QImage image(fileInfo.filePath());
                    QImageWriter forCompression(fileInfo.filePath());

                    if (!image.isNull()) {
                        QStringList columnData;
                        columnData << name;
                        columnData << QString("%1x%2px").arg(image.width()).arg(image.height());
                        columnData << QString("%1 horiz").arg(image.dotsPerMeterX() / 0.0254);
                        columnData << QString("%1 vert").arg(image.dotsPerMeterY() / 0.0254);
                        columnData << QString::number(image.bitPlaneCount());
                        columnData << QString::number(forCompression.compression());

                        int row = ui->mainTable->rowCount();
                        ui->mainTable->insertRow(row);
                        for (int i = 0; i < columnData.size(); i++)
                        {
                            QTableWidgetItem *item = new QTableWidgetItem(columnData[i]);
                            ui->mainTable->setItem(row, i, item);
                        }
                    }
                }
                QString str = "Количество проигнорированных элементов: "+ QString::number(ignored) +
                        "\nКоличество элементов в списке: "+QString::number(CountElements);
                ui->InfLabel->setText(str);
            } else
            {
                ui->InfLabel->setText("Нет Изображений с указанными типами");
            }
        }
        else
        {
            ui->InfLabel->setText("Что-то не так с выбранной директорией");
        }

    }
}


void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Изображения (*.jpg *.jpeg *.png *.gif *.bmp *.pcx *.tif);;Текстовые файлы (*.txt)");
    dialog.setDirectory(this->DefoltPath);
    QString filepath = dialog.getOpenFileName();
    if (!filepath.isEmpty())
    {
        ui->InfLabel->setText("");
        ui->mainTable->setRowCount(0);
        ui->mainTable->setColumnCount(6);
        ui->mainTable->setColumnWidth(0,150);
        ui->mainTable->setColumnWidth(1,140);
        ui->mainTable->setColumnWidth(2,140);
        ui->mainTable->setColumnWidth(3,140);
        ui->mainTable->setColumnWidth(4,140);
        ui->mainTable->setColumnWidth(5,140);
        QStringList horizontalHeaders;
        horizontalHeaders << "Название" << "Размер(px)" << "Горизонт. разрешение"<<"Верт. разрешение"<<"Глубина цвета"<<"Степень сжатия";
        ui->mainTable->setHorizontalHeaderLabels(horizontalHeaders);

        QFileInfo fileInfo(filepath);
        QString name = fileInfo.fileName();
        QImage image(fileInfo.filePath());
        QImageWriter forCompression(fileInfo.filePath());


        if (!image.isNull()) {
            QStringList columnData;
            columnData << name;
            columnData << QString("%1x%2px").arg(image.width()).arg(image.height());
            columnData << QString("%1 horiz").arg(image.dotsPerMeterX() / 0.0254);
            columnData << QString("%1 vert").arg(image.dotsPerMeterY() / 0.0254);
            columnData << QString::number(image.bitPlaneCount());
            columnData << QString::number(forCompression.compression());

            int row = ui->mainTable->rowCount();
            ui->mainTable->insertRow(row);
            for (int i = 0; i < columnData.size(); i++)
            {
                QTableWidgetItem *item = new QTableWidgetItem(columnData[i]);
                ui->mainTable->setItem(row, i, item);
            }
            QString str = "Количество проигнорированных элементов: 0\nКоличество элементов в списке: 1";

            ui->InfLabel->setText(str);
        }
    }
}

