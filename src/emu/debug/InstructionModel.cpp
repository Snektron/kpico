#include "emu/debug/InstructionModel.h"
#include <QDebug>
#include <QThread>

int InstructionModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return disassembly.size();
}

QVariant InstructionModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() >= disassembly.size())
		return QVariant();

	const Instruction *data = disassembly.atIndex(index.row());
	switch(role)
	{
	case AddressRole:
		return data->address;
	case HexRole:
		return data->hex;
	case DecodedRole:
		return data->decoded;
	case SizeRole:
		return data->size;
	}

	return QVariant();
}

QHash<int, QByteArray> InstructionModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[AddressRole] = "address";
	roles[HexRole] = "hexdata";
	roles[DecodedRole] = "instruction";
	roles[SizeRole] = "size";
	return roles;
}

int InstructionModel::indexAtAddress(int address)
{
	return disassembly.indexAtAddress(address & 0xFFFF);
}

void InstructionModel::setInstructions(InstructionList list)
{

	if (disassembly.size() > 0)
	{
		beginRemoveRows(QModelIndex(), 0, disassembly.size() - 1);
		disassembly.instructions().clear();
		endRemoveRows();
	}

	if (list.size() > 0)
	{
		beginInsertRows(QModelIndex(), 0, list.size() - 1);
		disassembly = list;
		endInsertRows();
	}
}
