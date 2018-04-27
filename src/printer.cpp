#include "printer.h"

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>

#include <QPdfWriter>

#include <QDir>
#include <QTemporaryDir>


///
#include <QFileDialog>
#include <QTextDocument>
///

Printer::Printer(const PassData& passData) :
  passData(passData)
{
}

void Printer::print()
{
  /// generate pdf
  QString fileName = QFileDialog::getSaveFileName(nullptr, "Export PDF", QString(), "*.pdf");
  if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

  QPrinter printer(QPrinter::PrinterResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPaperSize(QPrinter::A4);
  printer.setOutputFileName(fileName);

  QTextDocument doc;

  doc.setHtml(passData.getPdfHtml());
  doc.setPageSize(printer.pageRect().size());
  doc.print(&printer);

  /// create pdf
//  const QString tmpFileName = "tmp_pass_data.pdf";

//  QTemporaryDir tmp;
//  QDir separator;

//  QDir tmpFilePath = tmp.path() + separator.separator() + tmpFileName;
//  //QDir path; path.separator();

//  //QString fileName{QTemporaryDir::path() + QDir::separator() + "tmp_pass_data.pdf"};

//  QPdfWriter pdfwriter("");
//  pdfwriter.setPageSize(QPageSize(QPageSize::A4));
//  QPainter painter(&pdfwriter);


//  QPrinter printer;

//  QPrintDialog dialog(&printer);
//  dialog.setWindowTitle(QDialog::tr("Print Document"));
//  dialog.setModal(true);
//  dialog.exec();
}
