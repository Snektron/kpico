#include "emu/debug/InstructionModel.h"
#include <QDebug>
#include <QThread>

int InstructionModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return instructions.length();
}

QVariant InstructionModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() >= instructions.length())
		return QVariant();

	InstructionData data = instructions[index.row()];
	switch(role)
	{
	case AddressRole:
		return data.address;
	case HexRole:
		return data.hex;
	case DecodedRole:
		return data.decoded;
	case SizeRole:
		return data.size;
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

int InstructionModel::current()
{
	return mCurrent;
}

void InstructionModel::clear()
{
	beginRemoveRows(QModelIndex(), 0, instructions.size());
	instructions.clear();
	endRemoveRows();
}

void InstructionModel::setInstructions(InstructionList list, int current)
{
	mCurrent = current;

	if (instructions.size() > 0)
	{
		beginRemoveRows(QModelIndex(), 0, instructions.size() - 1);
		instructions.clear();
		endRemoveRows();
	}

	if (list.size() > 0)
	{
		beginInsertRows(QModelIndex(), 0, list.size() - 1);
		instructions = list;
		endInsertRows();
	}
}
