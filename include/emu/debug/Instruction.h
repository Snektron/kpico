#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>
#include <QList>
#include <stdint.h>

typedef struct
{
	QString decoded;
	QString hex;
	int size;
	int index;
	uint16_t address;
} Instruction;

class InstructionList
{
private:
	int mIndices[65536];
	QList<Instruction> mInstructions;

public:
	inline int size() const { return mInstructions.size(); }
	inline int indexAtAddress(uint16_t address) const { return mIndices[address]; }
	inline const Instruction* atAddress(uint16_t address) const { return atIndex(mIndices[address]); }
	inline const Instruction* atIndex(int index) const { return &mInstructions[index]; }
	inline QList<Instruction> instructions() { return mInstructions; }
	inline void setIndex (uint16_t address, int index) { mIndices[address] = index; }
	inline void addInstruction(Instruction &i)
	{
		i.index = mInstructions.size();
		setIndex(i.address, i.index);
		mInstructions << i;
	}
};

#endif // INSTRUCTION_H
