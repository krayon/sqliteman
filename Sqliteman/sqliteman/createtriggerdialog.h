/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef CREATETRIGGERDIALOG_H
#define CREATETRIGGERDIALOG_H

#include <qwidget.h>

#include "ui_createtriggerdialog.h"

class QTreeWidgetItem;

/*! \brief GUI for trigger creation
\author Petr Vanek <petr@scribus.info>
*/
class CreateTriggerDialog : public QDialog
{
	Q_OBJECT

	public:
		CreateTriggerDialog(QTreeWidgetItem * item, QWidget * parent = 0);
		~CreateTriggerDialog();

		bool update;

	private:
		Ui::CreateTriggerDialog ui;
		void resultAppend(QString text);

	private slots:
		void createButton_clicked();
};

#endif
