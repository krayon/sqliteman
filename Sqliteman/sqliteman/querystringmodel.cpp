/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#include "querystringmodel.h"

QueryStringModel::QueryStringModel(QObject * parent)
	: QStringListModel(parent)
{
}

Qt::ItemFlags QueryStringModel::flags (const QModelIndex & index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void QueryStringModel::clear()
{
	setStringList(QStringList());
}

void QueryStringModel::append(const QString & value)
{
	QStringList l(stringList());
	l.append(value);
	setStringList(l);
}
