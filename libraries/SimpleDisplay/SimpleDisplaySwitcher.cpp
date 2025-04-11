#include <SimpleDisplaySwitcher.h>

void SimpleDisplaySwitcher::writeFirstRow(String firstString, String secondString)
{
    if (this->displayCase)
    {
        this->display->writeFirstRow(secondString);
    }
    else
    {
        this->display->writeFirstRow(firstString);
    }
}

void SimpleDisplaySwitcher::writeSecondRow(String firstString, String secondString)
{
    if (this->displayCase)
    {
        this->display->writeSecondRow(secondString);
    }
    else
    {
        this->display->writeSecondRow(firstString);
    }
}
void SimpleDisplaySwitcher::writeThirdRow(String firstString, String secondString)
{
    if (this->displayCase)
    {
        this->display->writeThirdRow(secondString);
    }
    else
    {
        this->display->writeThirdRow(firstString);
    }
}

void SimpleDisplaySwitcher::switchDisplay()
{
    if (this->displayCase)
    {
        this->displayCase = 0;
    }
    else
    {
        this->displayCase = 1;
    }
}