#include "printer.h"

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>

#include <QPdfWriter>

#include <QDir>
#include <QTemporaryDir>


Printer::Printer(const QString passData)
{
}

void Printer::print()
{
  const QString tmpFileName = "tmp_pass_data.pdf";

  QTemporaryDir tmp;
  QDir separator;

  QDir tmpFilePath = tmp.path() + separator.separator() + tmpFileName;
  //QDir path; path.separator();

  //QString fileName{QTemporaryDir::path() + QDir::separator() + "tmp_pass_data.pdf"};

  QPdfWriter pdfwriter("");
  pdfwriter.setPageSize(QPageSize(QPageSize::A4));
  QPainter painter(&pdfwriter);


  QPrinter printer;

  QPrintDialog dialog(&printer);
  dialog.setWindowTitle(QDialog::tr("Print Document"));
  dialog.setModal(true);
  dialog.exec();
}
