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

#ifndef DSPAUDIODEVICE_H
#define DSPAUDIODEVICE_H

#include <DSPatch.h>

struct RtAudioMembers;

//-------------------------------------------------------------------------------------------------

class DspAudioDevice : public DspComponent
{
public:
    unsigned short pDeviceList;   // List
    unsigned short pIsStreaming;  // Bool
    unsigned short pBufferSize;   // Int
    unsigned short pSampleRate;   // Int

    DspAudioDevice();
    ~DspAudioDevice();

    bool SetDevice(short deviceIndex);

    std::string GetDeviceName(short deviceIndex) const;
    unsigned short GetDeviceInputCount(short deviceIndex) const;
    unsigned short GetDeviceOutputCount(short deviceIndex) const;
    unsigned short GetCurrentDevice() const;
    unsigned short GetDeviceCount() const;

    void SetBufferSize(int bufferSize);
    void SetSampleRate(int sampleRate);

    bool IsStreaming() const;
    int GetBufferSize() const;
    int GetSampleRate() const;

protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    virtual bool ParameterUpdating_(unsigned short index, DspParameter const& param);

private:
    std::vector<std::vector<float>> _outputChannels;
    std::vector<std::vector<float>> _inputChannels;

    RtAudioMembers* _rtAudio;

    DspMutex _buffersMutex;
    DspMutex _syncMutex;
    DspWaitCondition _waitCondt;
    DspWaitCondition _syncCondt;
    bool _gotWaitReady;
    bool _gotSyncReady;

    void _SetIsStreaming(bool isStreaming);

    void _WaitForBuffer();
    void _SyncBuffer();

    void _StopStream();
    void _StartStream();

    static int _StaticCallback(void* outputBuffer,
                               void* inputBuffer,
                               unsigned int nBufferFrames,
                               double streamTime,
                               unsigned int status,
                               void* userData);

    int _DynamicCallback(void* inputBuffer, void* outputBuffer);
};

//-------------------------------------------------------------------------------------------------

#endif  // DSPAUDIODEVICE_H
