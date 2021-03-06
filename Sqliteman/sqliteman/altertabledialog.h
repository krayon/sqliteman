/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef ALTERTABLEDIALOG_H
#define ALTERTABLEDIALOG_H

#include "database.h"
#include "tableeditordialog.h"

class QTreeWidgetItem;
class QPushButton;

/*! \brief Handle alter table features.
Sqlite3 has very limited ALTER TABLE feature set, so
there is only support for "table rename" and "add column".
Table Renaming is handled directly in the LiteManWindow
method renameTable().
Adding columns - see addColumns(). It's a wrapper around
plain ALTER TABLE ADD COLUMN statement.
Drop Column is using a workaround with tmp table, insert-select
statement and renaming. See createButton_clicked()
\author Petr Vanek <petr@scribus.info>
*/

class AlterTableDialog : public TableEditorDialog
{
	Q_OBJECT

	private:
		void addField(QString oldName, QString oldType,
					  int x, QString oldDefault);

	private slots:
		void addField();

		//! \brief Fill the GUI with table structure.
		void resetClicked();

	public:
		AlterTableDialog(LiteManWindow * parent = 0,
						 QTreeWidgetItem * item = 0,
						 const bool isActive = false
						);
		~AlterTableDialog(){};

	private:
		QTreeWidgetItem * m_item;
		QPushButton * m_alterButton;
		QList<FieldInfo> m_fields;
		QVector<bool> m_isIndexed;
		QVector<int> m_oldColumn; // -1 if no old column
		bool m_hadRowid;
		bool m_alteringActive; // true if altering currently active table
		bool m_altered; // something changed other than the name
		bool m_dropped; // a column has been dropped

		/*! \brief Execute statement, handle errors,
		and output message to the GUI.
		\param statement a SQL statement as QString
		\param message a text message to display in the log widget
		\retval bool true on SQL succes
		*/
		bool execSql(const QString & statement, const QString & message);

		//! \brief Roll back whole transaction after failure
		bool doRollback(QString message);

		//! \brief Returns a list of SQL statements to recreate triggers
		QStringList originalSource(QString tableName);

		//! \brief Returns a list of parsed create index statments
		QList<SqlParser *> originalIndexes(QString tableName);

		/*! \brief Perform a rename table action if it's required.
		\retval true on success.
		*/
		bool renameTable(QString oldTableName, QString newTableName);

		bool checkColumn(int i, QString cname,
						 QString ctype, QString cextra);
		void resizeTable();
		void swap(int i, int j);
		void drop (int i);

	private slots:
		void cellClicked(int, int);
		void alterButton_clicked();;

		//! \brief Setup the Alter button if there is something changed
		void checkChanges();
};

#endif
