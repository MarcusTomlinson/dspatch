/************************************************************************
DSPatch - Cross-Platform, Object-Oriented, Flow-Based Programming Library
Copyright (c) 2012-2014 Marcus Tomlinson

This file is part of DSPatch.

GNU Lesser General Public License Usage
This file may be used under the terms of the GNU Lesser General Public
License version 3.0 as published by the Free Software Foundation and
appearing in the file LGPLv3.txt included in the packaging of this
file. Please review the following information to ensure the GNU Lesser
General Public License version 3.0 requirements will be met:
http://www.gnu.org/copyleft/lgpl.html.

Other Usage
Alternatively, this file may be used in accordance with the terms and
conditions contained in a signed written agreement between you and
Marcus Tomlinson.

DSPatch is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
************************************************************************/

#include <dspatch/DspSignalBus.h>

//=================================================================================================

DspSignalBus::~DspSignalBus()
{
}

//=================================================================================================

bool DspSignalBus::SetSignal(unsigned short signalIndex, DspSignal const* newSignal)
{
    if (signalIndex < _signals.size() && newSignal != NULL)
    {
        return _signals[signalIndex].SetSignal(newSignal);
    }
    else
    {
        return false;
    }
}

//-------------------------------------------------------------------------------------------------

bool DspSignalBus::SetSignal(std::string const& signalName, DspSignal const* newSignal)
{
    unsigned short signalIndex;

    if (FindSignal(signalName, signalIndex) && newSignal != NULL)
    {
        return _signals[signalIndex].SetSignal(newSignal);
    }
    else
    {
        return false;
    }
}

//-------------------------------------------------------------------------------------------------

DspSignal* DspSignalBus::GetSignal(unsigned short signalIndex)
{
    if (signalIndex < _signals.size())
    {
        return &_signals[signalIndex];
    }
    else
    {
        return NULL;
    }
}

//-------------------------------------------------------------------------------------------------

DspSignal* DspSignalBus::GetSignal(std::string const& signalName)
{
    unsigned short signalIndex;

    if (FindSignal(signalName, signalIndex))
    {
        return &_signals[signalIndex];
    }
    else
    {
        return NULL;
    }
}

//-------------------------------------------------------------------------------------------------

bool DspSignalBus::FindSignal(std::string const& signalName, unsigned short& returnIndex) const
{
    if (signalName == "")
    {
        return false;
    }

    for (unsigned short i = 0; i < _signals.size(); i++)
    {
        if (_signals[i].GetSignalName() == signalName)
        {
            returnIndex = i;
            return true;
        }
    }
    // if you get here the variable was not found.
    return false;
}

//-------------------------------------------------------------------------------------------------

bool DspSignalBus::FindSignal(unsigned short signalIndex, unsigned short& returnIndex) const
{
    if (signalIndex < _signals.size())
    {
        returnIndex = signalIndex;
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------

unsigned short DspSignalBus::GetSignalCount() const
{
    return _signals.size();
}

//-------------------------------------------------------------------------------------------------

void DspSignalBus::ClearValue(unsigned short signalIndex)
{
    if (signalIndex < _signals.size())
    {
        return _signals[signalIndex].ClearValue();
    }
}

//-------------------------------------------------------------------------------------------------

void DspSignalBus::ClearValue(std::string const& signalName)
{
    unsigned short signalIndex;

    if (FindSignal(signalName, signalIndex))
    {
        return _signals[signalIndex].ClearValue();
    }
}

//-------------------------------------------------------------------------------------------------

void DspSignalBus::ClearAllValues()
{
    for (unsigned short i = 0; i < _signals.size(); i++)
    {
        _signals[i].ClearValue();
    }
}

//=================================================================================================

bool DspSignalBus::_AddSignal(std::string const& signalName)
{
    if (signalName != "")
    {
        unsigned short signalIndex;
        if (FindSignal(signalName, signalIndex))  // if the name already exists
        {
            return false;
        }
    }

    _signals.push_back(DspSignal(signalName));

    return true;
}

//-------------------------------------------------------------------------------------------------

bool DspSignalBus::_RemoveSignal()
{
    if (_signals.size() > 0)
    {
        _signals.pop_back();
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

void DspSignalBus::_RemoveAllSignals()
{
    _signals.clear();
}

//=================================================================================================
