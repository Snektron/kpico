#include "emu/debug/InstructionModel.h"
#include <QDebug>
#include <QThread>

int InstructionModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return instructions.size();
}

QVariant InstructionModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() >= instructions.size())
		return QVariant();

	const Instruction *data = instructions.atIndex(index.row());
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
	return instructions.indexAtAddress(address & 0xFFFF);
}

void InstructionModel::setInstructions(InstructionList list)
{

	if (instructions.size() > 0)
	{
		beginRemoveRows(QModelIndex(), 0, instructions.size() - 1);
		instructions.instructions().clear();
		endRemoveRows();
	}

	if (list.size() > 0)
	{
		beginInsertRows(QModelIndex(), 0, list.size() - 1);
		instructions = list;
		endInsertRows();
	}
}
