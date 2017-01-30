#ifndef INSTRUCTIONMODEL_H
#define INSTRUCTIONMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>

typedef struct
{
	QString decoded;
	QString hex;
	int size;
	uint16_t address;
} InstructionData;

typedef QList<InstructionData> InstructionList;

class InstructionModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(int current READ current() CONSTANT)
private:
	InstructionList instructions;
	int mCurrent;

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
	int current();

public slots:
	void clear();
	void setInstructions(InstructionList list, int current);
};


#endif // INSTRUCTIONMODEL_H
