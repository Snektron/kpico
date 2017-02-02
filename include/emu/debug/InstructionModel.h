#ifndef INSTRUCTIONMODEL_H
#define INSTRUCTIONMODEL_H

#include <QAbstractListModel>
#include <QString>
#include "emu/debug/Instruction.h"

class InstructionModel : public QAbstractListModel
{
	Q_OBJECT
private:
	InstructionList disassembly;

public:
	enum InstructionModelRoles
	{
		AddressRole = Qt::UserRole + 1,
		HexRole,
		DecodedRole,
		SizeRole
	};

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QHash<int, QByteArray> roleNames() const;

	Q_INVOKABLE int indexAtAddress(int address);
public slots:
	void setInstructions(InstructionList list);
};


#endif // INSTRUCTIONMODEL_H
