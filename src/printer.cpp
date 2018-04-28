#include "printer.h"

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QTextDocument>

Printer::Printer(const PassData& _passData) :
  passData(_passData)
{
}

void Printer::print() const
{
  QPrinter printer;
  QTextDocument textDocument;

  textDocument.setHtml(passData.getPdfHtml());

  QPrintDialog printDialog(&printer);
  printDialog.setWindowTitle(QDialog::tr("Print Passphrases"));
  printDialog.setModal(true);
  printDialog.exec();

  textDocument.setPageSize(printer.pageRect().size());
  textDocument.print(&printer);
}

Printer::~Printer()
{
}
