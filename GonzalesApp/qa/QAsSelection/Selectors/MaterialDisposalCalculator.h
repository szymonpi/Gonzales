#pragma once

class MaterialDisposalCalculator
{
public:
    MaterialDisposalCalculator(const int& qaCount,
                               const int& newPercent)
    {
        newQa = qaCount*(double)newPercent/100;
        unsigned oldMaterial = 1 - newQa;
        forRepetitionsQa = oldMaterial / 2;
        notLearnedQa = oldMaterial/2;
    }

    unsigned maxNew()
    {
        return newQa;
    }

    unsigned maxNotLearned()
    {
        return notLearnedQa;
    }

    unsigned maxForRepetition()
    {
        return forRepetitionsQa;
    }

private:
    unsigned notLearnedQa;
    unsigned newQa;
    unsigned forRepetitionsQa;

};
